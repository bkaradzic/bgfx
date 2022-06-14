/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_OSX

#import <Cocoa/Cocoa.h>

#include <bgfx/platform.h>

#include <bx/uint32_t.h>
#include <bx/thread.h>
#include <bx/os.h>
#include <bx/handlealloc.h>

@interface AppDelegate : NSObject<NSApplicationDelegate>
{
	bool terminated;
}

+ (AppDelegate *)sharedDelegate;
- (id)init;
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;
- (bool)applicationHasTerminated;

@end

@interface Window : NSObject<NSWindowDelegate>
{
}

+ (Window*)sharedDelegate;
- (id)init;
- (void)windowCreated:(NSWindow*)window;
- (void)windowWillClose:(NSNotification*)notification;
- (BOOL)windowShouldClose:(NSWindow*)window;
- (void)windowDidResize:(NSNotification*)notification;
- (void)windowDidBecomeKey:(NSNotification *)notification;
- (void)windowDidResignKey:(NSNotification *)notification;

@end

namespace entry
{
	///
	inline void osxSetNSWindow(void* _window, void* _nsgl = NULL)
	{
		bgfx::PlatformData pd;
		pd.ndt          = NULL;
		pd.nwh          = _window;
		pd.context      = _nsgl;
		pd.backBuffer   = NULL;
		pd.backBufferDS = NULL;
		bgfx::setPlatformData(pd);
	}

	static uint8_t s_translateKey[256];

	struct MainThreadEntry
	{
		int m_argc;
		const char* const* m_argv;

		static int32_t threadFunc(bx::Thread* _thread, void* _userData)
		{
			BX_UNUSED(_thread);

			CFBundleRef mainBundle = CFBundleGetMainBundle();
			if (mainBundle != nil)
			{
				CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
				if (resourcesURL != nil)
				{
					char path[PATH_MAX];
					if (CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8*)path, PATH_MAX) )
					{
						chdir(path);
					}

					CFRelease(resourcesURL);
				}
			}

			MainThreadEntry* self = (MainThreadEntry*)_userData;
			uint32_t result = main(self->m_argc, self->m_argv);
			[NSApp terminate:nil];
			return result;
		}
	};

	struct Context
	{
		Context()
			: m_scrollf(0.0f)
			, m_mx(0)
			, m_my(0)
			, m_scroll(0)
			, m_style(0)
			, m_exit(false)
			, m_mouseLock(NULL)
		{
			s_translateKey[27]             = Key::Esc;
			s_translateKey[uint8_t('\r')]  = Key::Return;
			s_translateKey[uint8_t('\t')]  = Key::Tab;
			s_translateKey[127]            = Key::Backspace;
			s_translateKey[uint8_t(' ')]   = Key::Space;

			s_translateKey[uint8_t('+')]   =
			s_translateKey[uint8_t('=')]   = Key::Plus;
			s_translateKey[uint8_t('_')]   =
			s_translateKey[uint8_t('-')]   = Key::Minus;

			s_translateKey[uint8_t('~')]   =
			s_translateKey[uint8_t('`')]   = Key::Tilde;

			s_translateKey[uint8_t(':')]   =
			s_translateKey[uint8_t(';')]   = Key::Semicolon;
			s_translateKey[uint8_t('"')]   =
			s_translateKey[uint8_t('\'')]  = Key::Quote;

			s_translateKey[uint8_t('{')]   =
			s_translateKey[uint8_t('[')]   = Key::LeftBracket;
			s_translateKey[uint8_t('}')]   =
			s_translateKey[uint8_t(']')]   = Key::RightBracket;

			s_translateKey[uint8_t('<')]   =
			s_translateKey[uint8_t(',')]   = Key::Comma;
			s_translateKey[uint8_t('>')]   =
			s_translateKey[uint8_t('.')]   = Key::Period;
			s_translateKey[uint8_t('?')]   =
			s_translateKey[uint8_t('/')]   = Key::Slash;
			s_translateKey[uint8_t('|')]   =
			s_translateKey[uint8_t('\\')]  = Key::Backslash;

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
				s_translateKey[uint8_t(ch)]       =
				s_translateKey[uint8_t(ch - ' ')] = Key::KeyA + (ch - 'a');
			}

			for(int ii=0; ii<ENTRY_CONFIG_MAX_WINDOWS; ++ii)
			{
				m_window[ii] = NULL;
			}
		}

		NSEvent* waitEvent()
		{
			return [NSApp
				nextEventMatchingMask:NSEventMaskAny
				untilDate:[NSDate distantFuture] // wait for event
				inMode:NSDefaultRunLoopMode
				dequeue:YES
				];
		}

		NSEvent* peekEvent()
		{
			return [NSApp
				nextEventMatchingMask:NSEventMaskAny
				untilDate:[NSDate distantPast] // do not wait for event
				inMode:NSDefaultRunLoopMode
				dequeue:YES
				];
		}

		void getMousePos(NSWindow *window, int* outX, int* outY)
		{
			//WindowHandle handle = { 0 };
			//NSWindow* window = m_window[handle.idx];

			NSRect  originalFrame = [window frame];
			NSPoint location      = [window mouseLocationOutsideOfEventStream];
			NSRect  adjustFrame   = [window contentRectForFrameRect: originalFrame];

			int32_t x = location.x;
			int32_t y = int32_t(adjustFrame.size.height) - int32_t(location.y);

			// clamp within the range of the window
			*outX = bx::clamp(x, 0, int32_t(adjustFrame.size.width) );
			*outY = bx::clamp(y, 0, int32_t(adjustFrame.size.height) );
		}

		void setMousePos(NSWindow* _window, int _x, int _y)
		{
			NSRect  originalFrame = [_window frame];
			NSRect  adjustFrame   = [_window contentRectForFrameRect: originalFrame];

			adjustFrame.origin.y = NSMaxY(NSScreen.screens[0].frame) - NSMaxY(adjustFrame);

			CGWarpMouseCursorPosition(CGPointMake(_x + adjustFrame.origin.x, _y + adjustFrame.origin.y));
			CGAssociateMouseAndMouseCursorPosition(YES);
		}

		void setMouseLock(NSWindow* _window, bool _lock)
		{
			NSWindow* newMouseLock = _lock ? _window : NULL;

			if ( m_mouseLock != newMouseLock )
			{
				if ( _lock )
				{
					NSRect  originalFrame = [_window frame];
					NSRect  adjustFrame   = [_window contentRectForFrameRect: originalFrame];

					m_cmx = (int)adjustFrame.size.width / 2;
					m_cmy = (int)adjustFrame.size.height / 2;

					setMousePos(_window, m_cmx, m_cmy);
					[NSCursor hide];
				}
				else
				{
					[NSCursor unhide];
				}
				m_mouseLock = newMouseLock;
			}
		}


		uint8_t translateModifiers(int flags)
		{
			return 0
				| ( (0 != (flags & NX_DEVICELSHIFTKEYMASK) ) ? Modifier::LeftShift  : 0)
				| ( (0 != (flags & NX_DEVICERSHIFTKEYMASK) ) ? Modifier::RightShift : 0)
				| ( (0 != (flags & NX_DEVICELALTKEYMASK) )   ? Modifier::LeftAlt    : 0)
				| ( (0 != (flags & NX_DEVICERALTKEYMASK) )   ? Modifier::RightAlt   : 0)
				| ( (0 != (flags & NX_DEVICELCTLKEYMASK) )   ? Modifier::LeftCtrl   : 0)
				| ( (0 != (flags & NX_DEVICERCTLKEYMASK) )   ? Modifier::RightCtrl  : 0)
				| ( (0 != (flags & NX_DEVICELCMDKEYMASK) )   ? Modifier::LeftMeta   : 0)
				| ( (0 != (flags & NX_DEVICERCMDKEYMASK) )   ? Modifier::RightMeta  : 0)
				;
		}

		Key::Enum handleKeyEvent(NSEvent* event, uint8_t* specialKeys, uint8_t* _pressedChar)
		{
			NSString* key = [event charactersIgnoringModifiers];
			unichar keyChar = 0;
			if ([key length] == 0)
			{
				return Key::None;
			}

			keyChar = [key characterAtIndex:0];
			*_pressedChar = (uint8_t)keyChar;

			int keyCode = keyChar;
			*specialKeys = translateModifiers(int([event modifierFlags]));

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

				NSWindow *window = [event window];
				WindowHandle handle = {UINT16_MAX};
				if (nil != window)
				{
					handle = findHandle(window);
				}
				if (!isValid(handle))
				{
					[NSApp sendEvent:event];
					[NSApp updateWindows];
					return true;
				}

				switch (eventType)
				{
				case NSEventTypeMouseMoved:
				case NSEventTypeLeftMouseDragged:
				case NSEventTypeRightMouseDragged:
				case NSEventTypeOtherMouseDragged:
					getMousePos(window, &m_mx, &m_my);

					if (window == m_mouseLock)
					{
						m_mx -= m_cmx;
						m_my -= m_cmy;

						setMousePos(window, m_cmx, m_cmy);
					}

					m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_scroll);
					break;

				case NSEventTypeLeftMouseDown:
					{
						// Command + Left Mouse Button acts as middle! This just a temporary solution!
						// This is because the average OSX user doesn't have middle mouse click.
						MouseButton::Enum mb = ([event modifierFlags] & NSEventModifierFlagCommand)
							? MouseButton::Middle
							: MouseButton::Left
							;
						m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_scroll, mb, true);
					}
					break;

				case NSEventTypeLeftMouseUp:
					m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_scroll, MouseButton::Left, false);
					m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_scroll, MouseButton::Middle, false);
					break;

				case NSEventTypeRightMouseDown:
					m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_scroll, MouseButton::Right, true);
					break;

				case NSEventTypeRightMouseUp:
					m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_scroll, MouseButton::Right, false);
					break;

				case NSEventTypeOtherMouseDown:
					m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_scroll, MouseButton::Middle, true);
					break;

				case NSEventTypeOtherMouseUp:
					m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_scroll, MouseButton::Middle, false);
					break;

				case NSEventTypeScrollWheel:
					m_scrollf += [event deltaY];

					m_scroll = (int32_t)m_scrollf;
					m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_scroll);
					break;

				case NSEventTypeKeyDown:
					{
						uint8_t modifiers = 0;
						uint8_t pressedChar[4];
						Key::Enum key = handleKeyEvent(event, &modifiers, &pressedChar[0]);

						// Returning false means that we take care of the key (instead of the default behavior)
						if (key != Key::None)
						{
							if (key == Key::KeyQ && (modifiers & Modifier::RightMeta) )
							{
								m_eventQueue.postExitEvent();
							}
							else
							{
								enum { ShiftMask = Modifier::LeftShift|Modifier::RightShift };
								m_eventQueue.postCharEvent(handle, 1, pressedChar);
								m_eventQueue.postKeyEvent(handle, key, modifiers, true);
								return false;
							}
						}
					}
					break;

				case NSEventTypeKeyUp:
					{
						uint8_t modifiers  = 0;
						uint8_t pressedChar[4];
						Key::Enum key = handleKeyEvent(event, &modifiers, &pressedChar[0]);

						BX_UNUSED(pressedChar);

						if (key != Key::None)
						{
							m_eventQueue.postKeyEvent(handle, key, modifiers, false);
							return false;
						}

					}
					break;

				default:
					break;
				}

				[NSApp sendEvent:event];
				[NSApp updateWindows];

				return true;
			}

			return false;
		}

		void windowDidResize(NSWindow *window)
		{
			WindowHandle handle = findHandle(window);
			NSRect originalFrame = [window frame];
			NSRect rect = [window contentRectForFrameRect: originalFrame];
			uint32_t width  = uint32_t(rect.size.width);
			uint32_t height = uint32_t(rect.size.height);
			m_eventQueue.postSizeEvent(handle, width, height);

			// Make sure mouse button state is 'up' after resize.
			m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_scroll, MouseButton::Left,  false);
			m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_scroll, MouseButton::Right, false);
		}

		void windowDidBecomeKey(NSWindow *window)
		{
			WindowHandle handle = findHandle(window);
			m_eventQueue.postSuspendEvent(handle, Suspend::WillResume);
			m_eventQueue.postSuspendEvent(handle, Suspend::DidResume);
		}

		void windowDidResignKey(NSWindow *window)
		{
			WindowHandle handle = findHandle(window);
			m_eventQueue.postSuspendEvent(handle, Suspend::WillSuspend);
			m_eventQueue.postSuspendEvent(handle, Suspend::DidSuspend);
		}

		int32_t run(int _argc, const char* const* _argv)
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

			m_style = 0
				| NSWindowStyleMaskTitled
				| NSWindowStyleMaskResizable
				| NSWindowStyleMaskClosable
				| NSWindowStyleMaskMiniaturizable
				;

			NSRect screenRect = [[NSScreen mainScreen] frame];
			const float centerX = (screenRect.size.width  - (float)ENTRY_DEFAULT_WIDTH )*0.5f;
			const float centerY = (screenRect.size.height - (float)ENTRY_DEFAULT_HEIGHT)*0.5f;
			NSString* appName = [[NSProcessInfo processInfo] processName];
			createWindow(centerX, centerY, ENTRY_DEFAULT_WIDTH, ENTRY_DEFAULT_HEIGHT, ENTRY_WINDOW_FLAG_NONE, [appName UTF8String]);

			m_windowFrame = [m_window[0] frame];

			osxSetNSWindow(m_window[0]);

			MainThreadEntry mte;
			mte.m_argc = _argc;
			mte.m_argv = _argv;

			bx::Thread thread;
			thread.init(mte.threadFunc, &mte);

			WindowHandle handle = { 0 };
			NSRect contentRect = [m_window[0] contentRectForFrameRect: m_windowFrame];
			uint32_t width = uint32_t(contentRect.size.width);
			uint32_t height = uint32_t(contentRect.size.height);
			m_eventQueue.postSizeEvent(handle, width, height);

			while (!(m_exit = [dg applicationHasTerminated]) )
			{
				bgfx::renderFrame();

				@autoreleasepool
				{
					while (dispatchEvent(peekEvent() ) )
					{
					}
				}
			}

			m_eventQueue.postExitEvent();

			while (bgfx::RenderFrame::NoContext != bgfx::renderFrame() ) {};
			thread.shutdown();

			return 0;
		}

		WindowHandle findHandle(NSWindow *_window)
		{
			bx::MutexScope scope(m_lock);
			for (uint16_t ii = 0, num = m_windowAlloc.getNumHandles(); ii < num; ++ii)
			{
				uint16_t idx = m_windowAlloc.getHandleAt(ii);
				if (_window == m_window[idx])
				{
					WindowHandle handle = { idx };
					return handle;
				}
			}

			WindowHandle invalid = { UINT16_MAX };
			return invalid;
		}

		EventQueue m_eventQueue;
		bx::Mutex m_lock;

		bx::HandleAllocT<ENTRY_CONFIG_MAX_WINDOWS> m_windowAlloc;
		NSWindow* m_window[ENTRY_CONFIG_MAX_WINDOWS];
		NSRect m_windowFrame;

		float   m_scrollf;
		int32_t m_mx;
		int32_t m_my;
		int32_t m_scroll;
		int32_t m_style;
		bool    m_exit;

		NSWindow* m_mouseLock;
		int32_t m_cmx;
		int32_t m_cmy;
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
		BX_UNUSED(_flags);

		bx::MutexScope scope(s_ctx.m_lock);
		WindowHandle handle = { s_ctx.m_windowAlloc.alloc() };

		if (UINT16_MAX != handle.idx)
		{
			void (^createWindowBlock)(void) = ^(void) {
				NSRect rect = NSMakeRect(_x, _y, _width, _height);
				NSWindow* window = [
					[NSWindow alloc]
					initWithContentRect:rect
					styleMask:s_ctx.m_style
					backing:NSBackingStoreBuffered defer:NO
					];
				NSString* appName = [NSString stringWithUTF8String:_title];
				[window setTitle:appName];
				[window makeKeyAndOrderFront:window];
				[window setAcceptsMouseMovedEvents:YES];
				[window setBackgroundColor:[NSColor blackColor]];
				[[Window sharedDelegate] windowCreated:window];

				s_ctx.m_window[handle.idx] = window;

				s_ctx.m_eventQueue.postSizeEvent(handle, _width, _height);
				s_ctx.m_eventQueue.postWindowEvent(handle, window);
			};

			if ([NSThread isMainThread])
			{
				createWindowBlock();
			}
			else
			{
				dispatch_async(dispatch_get_main_queue(), createWindowBlock);
			}
		}

		return handle;
	}

	void destroyWindow(WindowHandle _handle, bool _closeWindow)
	{
		if (isValid(_handle))
		{
			dispatch_async(dispatch_get_main_queue()
				, ^(void){
					NSWindow *window = s_ctx.m_window[_handle.idx];
					if ( NULL != window)
					{
						s_ctx.m_eventQueue.postWindowEvent(_handle);
						s_ctx.m_window[_handle.idx] = NULL;
						if ( _closeWindow )
						{
							[window close];
						}

						if (0 == _handle.idx)
						{
							[NSApp terminate:nil];
						}
					}
				});

			bx::MutexScope scope(s_ctx.m_lock);
			s_ctx.m_windowAlloc.free(_handle.idx);
		}
	}

	void destroyWindow(WindowHandle _handle)
	{
		destroyWindow(_handle, true);
	}

	void setWindowPos(WindowHandle _handle, int32_t _x, int32_t _y)
	{
		dispatch_async(dispatch_get_main_queue()
			, ^{
				NSWindow* window = s_ctx.m_window[_handle.idx];
				NSScreen* screen = [window screen];

				NSRect screenRect = [screen frame];
				CGFloat menuBarHeight = [[[NSApplication sharedApplication] mainMenu] menuBarHeight];

				NSPoint position = { float(_x), screenRect.size.height - menuBarHeight - float(_y) };

				[window setFrameTopLeftPoint: position];
			});
	}

	void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height)
	{
		NSSize size = { float(_width), float(_height) };
		dispatch_async(dispatch_get_main_queue()
			, ^{
				[s_ctx.m_window[_handle.idx] setContentSize: size];
			});
	}

	void setWindowTitle(WindowHandle _handle, const char* _title)
	{
		NSString* title = [[NSString alloc] initWithCString:_title encoding:1];
		dispatch_async(dispatch_get_main_queue()
			, ^{
				[s_ctx.m_window[_handle.idx] setTitle: title];
				[title release];
			});
	}

	void setWindowFlags(WindowHandle _handle, uint32_t _flags, bool _enabled)
	{
		BX_UNUSED(_handle, _flags, _enabled);
	}

	void toggleFullscreen(WindowHandle _handle)
	{
		dispatch_async(dispatch_get_main_queue()
			, ^{
				NSWindow* window = s_ctx.m_window[_handle.idx];
				[window toggleFullScreen:nil];
			});
	}

	void setMouseLock(WindowHandle _handle, bool _lock)
	{
		dispatch_async(dispatch_get_main_queue()
			, ^{
				NSWindow* window = s_ctx.m_window[_handle.idx];
				s_ctx.setMouseLock(window, _lock);
			});
	}

} // namespace entry

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

@implementation Window

+ (Window*)sharedDelegate
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

	return self;
}

- (void)windowCreated:(NSWindow*)window
{
	assert(window);

	[window setDelegate:self];
}

- (void)windowWillClose:(NSNotification*)notification
{
	BX_UNUSED(notification);
	NSWindow *window = [notification object];

	[window setDelegate:nil];

	destroyWindow(entry::s_ctx.findHandle(window), false);
}

- (BOOL)windowShouldClose:(NSWindow*)window
{
	assert(window);
	BX_UNUSED(window);
	return true;
}

- (void)windowDidResize:(NSNotification*)notification
{
	NSWindow *window = [notification object];
	using namespace entry;
	s_ctx.windowDidResize(window);
}

- (void)windowDidBecomeKey:(NSNotification*)notification
{
	NSWindow *window = [notification object];
	using namespace entry;
	s_ctx.windowDidBecomeKey(window);
}

- (void)windowDidResignKey:(NSNotification*)notification
{
	NSWindow *window = [notification object];
	using namespace entry;
	s_ctx.windowDidResignKey(window);
}

@end

int main(int _argc, const char* const* _argv)
{
	using namespace entry;
	return s_ctx.run(_argc, _argv);
}

#endif // BX_PLATFORM_OSX
