/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_OSX

#import <Cocoa/Cocoa.h>

#include <bgfxplatform.h>

#include <bx/uint32_t.h>
#include <bx/thread.h>
#include <bx/os.h>

#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720

@interface AppDelegate : NSObject<NSApplicationDelegate>
{
	bool terminated;
}

+ (AppDelegate *)sharedDelegate;
- (id)init;
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;
- (bool)applicationHasTerminated;

@end

@implementation AppDelegate

+ (AppDelegate *)sharedDelegate
{
	static id delegate = [AppDelegate new];
	return delegate;
}

- (id)init
{
	self = [super init];

	if (nil == self)
	{
		return nil;
	}

	self->terminated = false;
	return self;
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
	BX_UNUSED(sender);
	self->terminated = true;
	return NSTerminateCancel;
}

- (bool)applicationHasTerminated
{
	return self->terminated;
}

@end

@interface Window : NSObject<NSWindowDelegate>
{
	unsigned int windowCount;
}

+ (Window *)sharedDelegate;
- (id)init;
- (void)windowCreated:(NSWindow *)window;
- (void)windowWillClose:(NSNotification *)notification;
- (BOOL)windowShouldClose:(NSWindow *)window;

@end

@implementation Window

+ (Window *)sharedDelegate
{
	static id windowDelegate = [Window new];
	return windowDelegate;
}

- (id)init
{
	self = [super init];
	if (nil == self)
	{
		return nil;
	}

	self->windowCount = 0;
	return self;
}

- (void)windowCreated:(NSWindow *)window
{
	assert(window);

	[window setDelegate:self];

	assert(self->windowCount < ~0u);
	self->windowCount += 1;
}

- (void)windowWillClose:(NSNotification *)notification
{
	BX_UNUSED(notification);
}

- (BOOL)windowShouldClose:(NSWindow *)window
{
	assert(window);

	[window setDelegate:nil];

	assert(self->windowCount);
	self->windowCount -= 1;

	if (self->windowCount == 0)
	{
		[NSApp terminate:self];
		return false;
	}

	return true;
}
@end

namespace entry
{
	static WindowHandle s_defaultWindow = { 0 };	// TODO: Add support for more windows
	static uint8_t s_translateKey[256];

	struct MainThreadEntry
	{
		int m_argc;
		char** m_argv;

		static int32_t threadFunc(void* _userData)
		{
			MainThreadEntry* self = (MainThreadEntry*)_userData;
			return main(self->m_argc, self->m_argv);
		}
	};

	struct Context
	{
		Context()
			: m_exit(false)
		{
			s_translateKey[27]             = Key::Esc;
			s_translateKey[13]             = Key::Return;
			s_translateKey[9]              = Key::Tab;
			s_translateKey[127]            = Key::Backspace;
			s_translateKey[uint8_t(' ')]   = Key::Space;

			s_translateKey[uint8_t('+')]   =
			s_translateKey[uint8_t('=')]   = Key::Plus;
			s_translateKey[uint8_t('_')]   =
			s_translateKey[uint8_t('-')]   = Key::Minus;

			s_translateKey[uint8_t('0')]   = Key::Key0;
			s_translateKey[uint8_t('1')]   = Key::Key1;
			s_translateKey[uint8_t('2')]   = Key::Key2;
			s_translateKey[uint8_t('3')]   = Key::Key3;
			s_translateKey[uint8_t('4')]   = Key::Key4;
			s_translateKey[uint8_t('5')]   = Key::Key5;
			s_translateKey[uint8_t('6')]   = Key::Key6;
			s_translateKey[uint8_t('7')]   = Key::Key7;
			s_translateKey[uint8_t('8')]   = Key::Key8;
			s_translateKey[uint8_t('9')]   = Key::Key9;

			for (char ch = 'a'; ch <= 'z'; ++ch)
			{
				s_translateKey[uint8_t(ch)]             =
				s_translateKey[uint8_t(ch - ' ')] = Key::KeyA + (ch - 'a');
			}
		}

		NSEvent* waitEvent()
		{
			return [NSApp
				nextEventMatchingMask:NSAnyEventMask
				untilDate:[NSDate distantFuture] // wait for event
				inMode:NSDefaultRunLoopMode
				dequeue:YES
				];
		}

		NSEvent* peekEvent()
		{
			return [NSApp
				nextEventMatchingMask:NSAnyEventMask
				untilDate:[NSDate distantPast] // do not wait for event
				inMode:NSDefaultRunLoopMode
				dequeue:YES
				];
		}

		void getMousePos(int* outX, int* outY)
		{
			NSRect originalFrame = [m_window frame];
			NSPoint location = [m_window mouseLocationOutsideOfEventStream];
			NSRect adjustFrame = [NSWindow contentRectForFrameRect: originalFrame styleMask: NSTitledWindowMask];

			int x = location.x;
			int y = (int)adjustFrame.size.height - (int)location.y;

			// clamp within the range of the window

			if (x < 0) x = 0;
			if (y < 0) y = 0;
			if (x > (int)adjustFrame.size.width) x = (int)adjustFrame.size.width;
			if (y > (int)adjustFrame.size.height) y = (int)adjustFrame.size.height;

			*outX = x;
			*outY = y;
		}

		uint8_t translateModifiers(int flags)
		{
			uint8_t mask = 0;

			if (flags & NSShiftKeyMask)
				mask |= Modifier::LeftShift | Modifier::RightShift;

			if (flags & NSAlternateKeyMask)
				mask |= Modifier::LeftAlt | Modifier::RightAlt;

			if (flags & NSControlKeyMask)
				mask |= Modifier::LeftCtrl | Modifier::RightCtrl;

			if (flags & NSCommandKeyMask)
				mask |= Modifier::LeftMeta | Modifier::RightMeta;

			return mask;
		}

		Key::Enum handleKeyEvent(NSEvent* event, uint8_t* specialKeys)
		{
			NSString* key = [event charactersIgnoringModifiers];
			unichar keyChar = 0;
//DBG("keyChar %d", keyChar);
			if ([key length] == 0)
			{
				return Key::None;
			}

			keyChar = [key characterAtIndex:0];

			int keyCode = keyChar;
//DBG("keyCode %d", keyCode);
			*specialKeys = translateModifiers([event modifierFlags]);

			// if this is a unhandled key just return None
			if (keyCode < 256)
			{
				return (Key::Enum)s_translateKey[keyCode];
			}

			switch (keyCode)
			{
			case NSF1FunctionKey:  return Key::F1;
			case NSF2FunctionKey:  return Key::F2;
			case NSF3FunctionKey:  return Key::F3;
			case NSF4FunctionKey:  return Key::F4;
			case NSF5FunctionKey:  return Key::F5;
			case NSF6FunctionKey:  return Key::F6;
			case NSF7FunctionKey:  return Key::F7;
			case NSF8FunctionKey:  return Key::F8;
			case NSF9FunctionKey:  return Key::F9;
			case NSF10FunctionKey: return Key::F10;
			case NSF11FunctionKey: return Key::F11;
			case NSF12FunctionKey: return Key::F12;

			case NSLeftArrowFunctionKey:   return Key::Left;
			case NSRightArrowFunctionKey:  return Key::Right;
			case NSUpArrowFunctionKey:     return Key::Up;
			case NSDownArrowFunctionKey:   return Key::Down;

			case NSPageUpFunctionKey:      return Key::PageUp;
			case NSPageDownFunctionKey:    return Key::PageDown;
			case NSHomeFunctionKey:        return Key::Home;
			case NSEndFunctionKey:         return Key::End;

			case NSPrintScreenFunctionKey: return Key::Print;
			}

			return Key::None;
		}

		bool dispatchEvent(NSEvent* event)
		{
			if (event)
			{
				NSEventType eventType = [event type];

				switch (eventType)
				{
					case NSMouseMoved:
					{
						int x, y;
						getMousePos(&x, &y);
						m_eventQueue.postMouseEvent(s_defaultWindow, x, y, 0);
						break;
					}

					case NSLeftMouseDown:
					{
						int x, y;
						getMousePos(&x, &y);
						m_eventQueue.postMouseEvent(s_defaultWindow, x, y, 0, MouseButton::Left, true);
						break;
					}

					case NSLeftMouseUp:
					{
						int x, y;
						getMousePos(&x, &y);
						m_eventQueue.postMouseEvent(s_defaultWindow, x, y, 0, MouseButton::Left, false);
						break;
					}

					case NSRightMouseDown:
					{
						int x, y;
						getMousePos(&x, &y);
						m_eventQueue.postMouseEvent(s_defaultWindow, x, y, 0, MouseButton::Right, true);
						break;
					}

					case NSRightMouseUp:
					{
						int x, y;
						getMousePos(&x, &y);
						m_eventQueue.postMouseEvent(s_defaultWindow, x, y, 0, MouseButton::Right, false);
						break;
					}

					case NSKeyDown:
					{
						uint8_t modifiers = 0;
						Key::Enum key = handleKeyEvent(event, &modifiers);

						// If KeyCode is none we don't don't handle the key and special case for cmd+q (quit)
						// Note that return false here means that we take care of the key (instead of the default behavior)
						if (key != Key::None)
						{
							if (key != Key::KeyQ
							&& !(modifiers & Modifier::RightMeta) )
							{
								m_eventQueue.postKeyEvent(s_defaultWindow, key, modifiers, true);
								return false;
							}
						}

						break;
					}

					case NSKeyUp:
					{
						uint8_t modifiers  = 0;
						Key::Enum key = handleKeyEvent(event, &modifiers);

						if (key != Key::None)
						{
							m_eventQueue.postKeyEvent(s_defaultWindow, key, modifiers, false);
							return false;
						}

						break;
					}
				}

				[NSApp sendEvent:event];
				[NSApp updateWindows];

				return true;
			}

			return false;
		}

		int32_t run(int _argc, char** _argv)
		{
			[NSApplication sharedApplication];

			id dg = [AppDelegate sharedDelegate];
			[NSApp setDelegate:dg];
			[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
			[NSApp activateIgnoringOtherApps:YES];
			[NSApp finishLaunching];

			[[NSNotificationCenter defaultCenter]
				postNotificationName:NSApplicationWillFinishLaunchingNotification
				object:NSApp];

			[[NSNotificationCenter defaultCenter]
				postNotificationName:NSApplicationDidFinishLaunchingNotification
				object:NSApp];

			id quitMenuItem = [NSMenuItem new];
			[quitMenuItem
				initWithTitle:@"Quit"
				action:@selector(terminate:)
				keyEquivalent:@"q"];

			id appMenu = [NSMenu new];
			[appMenu addItem:quitMenuItem];

			id appMenuItem = [NSMenuItem new];
			[appMenuItem setSubmenu:appMenu];

			id menubar = [[NSMenu new] autorelease];
			[menubar addItem:appMenuItem];
			[NSApp setMainMenu:menubar];

			NSRect rect = NSMakeRect(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
			NSWindow* window = [NSWindow alloc];
			[window
				initWithContentRect:rect
				styleMask:0
				|NSTitledWindowMask
				|NSClosableWindowMask
				|NSMiniaturizableWindowMask
				|NSResizableWindowMask
				backing:NSBackingStoreBuffered defer:NO
				];
			NSString* appName = [[NSProcessInfo processInfo] processName];
			[window setTitle:appName];
			[window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
			[window makeKeyAndOrderFront:window];
			[window setAcceptsMouseMovedEvents:YES];
			[window setBackgroundColor:[NSColor blackColor]];
			[[Window sharedDelegate] windowCreated:window];

			m_window = window;

			bgfx::osxSetNSWindow(window);

			MainThreadEntry mte;
			mte.m_argc = _argc;
			mte.m_argv = _argv;

			bx::Thread thread;
			thread.init(mte.threadFunc, &mte);

			while (!(m_exit = [dg applicationHasTerminated]) )
			{
				if (bgfx::RenderFrame::Exiting == bgfx::renderFrame() )
				{
					break;
				}

				while (dispatchEvent(peekEvent() ) )
				{
				}
			}


			m_eventQueue.postExitEvent();

			while (bgfx::RenderFrame::NoContext != bgfx::renderFrame() ) {};
			thread.shutdown();

			return 0;
		}

		EventQueue m_eventQueue;

		bool m_exit;
		NSWindow* m_window;
	};

	static Context s_ctx;

	const Event* poll()
	{
		return s_ctx.m_eventQueue.poll();
	}

	const Event* poll(WindowHandle _handle)
	{
		return s_ctx.m_eventQueue.poll(_handle);
	}

	void release(const Event* _event)
	{
		s_ctx.m_eventQueue.release(_event);
	}

	WindowHandle createWindow(int32_t _x, int32_t _y, uint32_t _width, uint32_t _height, uint32_t _flags, const char* _title)
	{
		BX_UNUSED(_x, _y, _width, _height, _flags, _title);
		WindowHandle handle = { UINT16_MAX };
		return handle;
	}

	void destroyWindow(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
	}

	void setWindowPos(WindowHandle _handle, int32_t _x, int32_t _y)
	{
		BX_UNUSED(_handle, _x, _y);
	}

	void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height)
	{
		BX_UNUSED(_handle, _width, _height);
	}

	void setWindowTitle(WindowHandle _handle, const char* _title)
	{
		BX_UNUSED(_handle, _title);
	}

	void toggleWindowFrame(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
	}

	void setMouseLock(WindowHandle _handle, bool _lock)
	{
		BX_UNUSED(_handle, _lock);
	}

} // namespace entry

int main(int _argc, char** _argv)
{
	using namespace entry;
	return s_ctx.run(_argc, _argv);
}

#endif // BX_PLATFORM_OSX
