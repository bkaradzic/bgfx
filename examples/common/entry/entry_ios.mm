/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_IOS

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <QuartzCore/CAEAGLLayer.h>

#include <bgfxplatform.h>

#include <bx/uint32_t.h>
#include <bx/thread.h>

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
		Context(uint32_t _width, uint32_t _height)
		{
			const char* argv[1] = { "ios" };
			m_mte.m_argc = 1;
			m_mte.m_argv = const_cast<char**>(argv);

			m_eventQueue.postSizeEvent(_width, _height);

			// Prevent render thread creation.
			bgfx::renderFrame();

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
		CFBundleRef mainBundle = CFBundleGetMainBundle();
		CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
		char path[PATH_MAX];
		if (CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX) )
		{
			chdir(path);
		}
		CFRelease(resourcesURL);

		MainThreadEntry* self = (MainThreadEntry*)_userData;
		int32_t result = main(self->m_argc, self->m_argv);
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
		BX_UNUSED(_width, _height);
	}

	void setWindowTitle(const char* _title)
	{
		BX_UNUSED(_title);
	}

	void toggleWindowFrame()
	{
	}

	void setMouseLock(bool _lock)
	{
		BX_UNUSED(_lock);
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
		//[m_displayLink setFrameInterval:1];
		//[m_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		//		[m_displayLink addToRunLoop:[NSRunLoop currentRunLoop]];
		[m_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
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

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	BX_UNUSED(touches);
	UITouch *touch = [[event allTouches] anyObject];
	CGPoint touchLocation = [touch locationInView:self];

	s_ctx->m_eventQueue.postMouseEvent(touchLocation.x, touchLocation.y, 0);
	s_ctx->m_eventQueue.postMouseEvent(touchLocation.x, touchLocation.y, 0, MouseButton::Left, true);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	BX_UNUSED(touches);
	UITouch *touch = [[event allTouches] anyObject];
	CGPoint touchLocation = [touch locationInView:self];
	s_ctx->m_eventQueue.postMouseEvent(touchLocation.x, touchLocation.y, 0, MouseButton::Left, false);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	BX_UNUSED(touches);
	UITouch *touch = [[event allTouches] anyObject];
	CGPoint touchLocation = [touch locationInView:self];
	s_ctx->m_eventQueue.postMouseEvent(touchLocation.x, touchLocation.y, 0);
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	BX_UNUSED(touches);
	UITouch *touch = [[event allTouches] anyObject];
	CGPoint touchLocation = [touch locationInView:self];
	s_ctx->m_eventQueue.postMouseEvent(touchLocation.x, touchLocation.y, 0, MouseButton::Left, false);
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
	BX_UNUSED(application, launchOptions);

	CGRect rect = [ [UIScreen mainScreen] bounds];
	m_window = [ [UIWindow alloc] initWithFrame: rect];
	m_view = [ [View alloc] initWithFrame: rect];

	[m_window addSubview: m_view];
	[m_window makeKeyAndVisible];

	//float scaleFactor = [[UIScreen mainScreen] scale]; // should use this, but ui is too small on ipad retina
	float scaleFactor = 1.0f;
	[m_view setContentScaleFactor: scaleFactor ];

	s_ctx = new Context((uint32_t)(scaleFactor*rect.size.width), (uint32_t)(scaleFactor*rect.size.height));
	return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
	BX_UNUSED(application);
	[m_view stop];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
	BX_UNUSED(application);
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
	BX_UNUSED(application);
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
	BX_UNUSED(application);
	[m_view start];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	BX_UNUSED(application);
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
