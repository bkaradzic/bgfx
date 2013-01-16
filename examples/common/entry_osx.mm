/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bx/bx.h>

#if BX_PLATFORM_OSX

#include <bgfxplatform.h>
#include <bx/uint32_t.h>
#include <bx/thread.h>

#include "entry.h"
#include "dbg.h"

#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720

extern int _main_(int _argc, char** _argv);

@interface bgfxApplicationDelegate : NSObject <NSApplicationDelegate> {
	bool terminated;
}
+ (bgfxApplicationDelegate *)sharedDelegate;
- (id)init;
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;
- (bool)applicationHasTerminated;
@end

@implementation bgfxApplicationDelegate
+ (bgfxApplicationDelegate *)sharedDelegate {
	static id delegate = [bgfxApplicationDelegate new];
	return delegate;
}

- (id)init {
	self = [super init];
	if (self) {
		self->terminated = false;        
	}
	return self;
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender {
	self->terminated = true;
	return NSTerminateCancel;
}

- (bool)applicationHasTerminated {
	return self->terminated;
}
@end

@interface bgfxWindowDelegate : NSObject <NSWindowDelegate> {
	unsigned int windowCount;
}
+ (bgfxWindowDelegate *)sharedDelegate;
- (id)init;
- (void)windowCreated:(NSWindow *)window;
- (BOOL)windowShouldClose:(NSWindow *)window;
@end

@implementation bgfxWindowDelegate
+ (bgfxWindowDelegate *)sharedDelegate {
	static id windowDelegate = [bgfxWindowDelegate new];
	return windowDelegate;
}

- (id)init {
	self = [super init];
	if (self) {
		self->windowCount = 0;
	}
	return self;
}

- (void)windowCreated:(NSWindow *)window {
	assert(window);
	
	[window setDelegate:self];

	assert(self->windowCount < ~0u);
	self->windowCount += 1;
}

- (BOOL)windowShouldClose:(NSWindow *)window {
	assert(window);
	
	[window setDelegate:nil];

	assert(self->windowCount);
	self->windowCount -= 1;
	
	if (self->windowCount == 0) {
		[NSApp terminate:self];
		return false;
	}
	return true;
}
@end

namespace entry
{
	struct MainThreadEntry
	{
		int m_argc;
		char** m_argv;
		
		static int32_t threadFunc(void* _userData)
		{
			MainThreadEntry* self = (MainThreadEntry*)_userData;
			return _main_(self->m_argc, self->m_argv);
		}
	};
	
	struct Context
	{
		Context()
			: m_exit(false)
		{
		}
		
		NSEvent* WaitEvent () {
			return
			[NSApp
			 nextEventMatchingMask:NSAnyEventMask
			 untilDate:[NSDate distantFuture] // wait for event
			 inMode:NSDefaultRunLoopMode
			 dequeue:YES];
		}
		
		NSEvent* PeekEvent () {
			return
			[NSApp
			 nextEventMatchingMask:NSAnyEventMask
			 untilDate:[NSDate distantPast] // do not wait for event
			 inMode:NSDefaultRunLoopMode
			 dequeue:YES];
		}
		
		bool DispatchEvent (NSEvent* event) {
			if (event) {
				[NSApp sendEvent:event];
				[NSApp updateWindows];
				return true;
			}
			return false;
		}
		
		int32_t main(int _argc, char** _argv)
		{
			[NSApplication sharedApplication];			
			id dg = [bgfxApplicationDelegate sharedDelegate];
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
			[window makeKeyAndOrderFront:nil];
			[[bgfxWindowDelegate sharedDelegate] windowCreated:window];
			
			bgfx::osxSetNSWindow(window);
			
			MainThreadEntry mte;
			mte.m_argc = _argc;
			mte.m_argv = _argv;
			
			bx::Thread thread;
			thread.init(mte.threadFunc, &mte);

			while (!(m_exit = [dg applicationHasTerminated]))
			{
				DispatchEvent(WaitEvent());				
				while (DispatchEvent(PeekEvent()));
			}
			
			thread.shutdown();
			
			return 0;
		}
		
		bool m_exit;
		
	};
	
	static Context s_ctx;
	
	Event::Enum poll()
	{
		return s_ctx.m_exit ? Event::Exit : Event::Nop;
	}

} // namespace entry

int main(int _argc, char** _argv)
{
	using namespace entry;
	return s_ctx.main(_argc, _argv);
}

#endif // BX_PLATFORM_OSX
