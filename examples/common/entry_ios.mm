/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bx/bx.h>

#if BX_PLATFORM_IOS

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <QuartzCore/CAEAGLLayer.h>

#include <bgfxplatform.h>
#include <bx/uint32_t.h>
#include <bx/thread.h>

#include "entry_p.h"
#include "dbg.h"

extern int _main_(int _argc, char** _argv);

namespace bgfx
{
	void renderFrame();
}

namespace entry
{
	struct MainThreadEntry
	{
		int m_argc;
		char** m_argv;

		static int32_t threadFunc(void* _userData);
	};

	struct Context
	{
		Context()
		{
			const char* argv[1] = { "ios" };
			m_mte.m_argc = 1;
			m_mte.m_argv = const_cast<char**>(argv);

			m_eventQueue.postSizeEvent(768, 1024);

			m_thread.init(MainThreadEntry::threadFunc, &m_mte);
		}

		~Context()
		{
			m_thread.shutdown();
		}

		MainThreadEntry m_mte;
		bx::Thread m_thread;

		EventQueue m_eventQueue;
	};

	static Context* s_ctx;

	int32_t MainThreadEntry::threadFunc(void* _userData)
	{
		MainThreadEntry* self = (MainThreadEntry*)_userData;
		int32_t result = _main_(self->m_argc, self->m_argv);
		return result;
	}

	const Event* poll()
	{
		return s_ctx->m_eventQueue.poll();
	}

	void release(const Event* _event)
	{
		s_ctx->m_eventQueue.release(_event);
	}

	void setWindowSize(uint32_t _width, uint32_t _height)
	{
	}

	void toggleWindowFrame()
	{
	}

	void setMouseLock(bool _lock)
	{
	}

} // namespace entry

using namespace entry;

@interface View : UIView
{
	CADisplayLink* m_displayLink;
}

@end

@implementation View

+ (Class)layerClass
{
	return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)rect
{
	self = [super initWithFrame:rect];

	if (nil == self)
	{
		return nil;
	}

	CAEAGLLayer* layer = (CAEAGLLayer*)self.layer;
	bgfx::iosSetEaglLayer(layer);

	return self;
}

- (void)start
{
	if (nil == m_displayLink)
	{
		m_displayLink = [self.window.screen displayLinkWithTarget:self selector:@selector(renderFrame)];
		[m_displayLink setFrameInterval:1];
		[m_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
	}
}

- (void)stop
{
	if (nil != m_displayLink)
	{
		[m_displayLink invalidate];
		m_displayLink = nil;
	}
}

- (void)renderFrame
{
	bgfx::renderFrame();
}

@end

@interface AppDelegate : UIResponder<UIApplicationDelegate>
{
	UIWindow* m_window;
	View* m_view;
}

@property (nonatomic, retain) UIWindow* m_window;
@property (nonatomic, retain) View* m_view;

@end

@implementation AppDelegate

@synthesize m_window;
@synthesize m_view;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	CGRect rect = [ [UIScreen mainScreen] bounds];
	m_window = [ [UIWindow alloc] initWithFrame: rect];
	m_view = [ [View alloc] initWithFrame: rect];

	[m_window addSubview: m_view];
	[m_window makeKeyAndVisible];

	s_ctx = new Context;
	return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
	[m_view stop];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
	[m_view start];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	[m_view stop];
}

- (void)dealloc
{
	[m_window release];
	[m_view release];
	[super dealloc];
}

@end

int main(int _argc, char* _argv[])
{
	NSAutoreleasePool* pool = [ [NSAutoreleasePool alloc] init];
	int exitCode = UIApplicationMain(_argc, _argv, @"UIApplication", NSStringFromClass([AppDelegate class]) );
	[pool release];
	return exitCode;
}

#endif // BX_PLATFORM_IOS
