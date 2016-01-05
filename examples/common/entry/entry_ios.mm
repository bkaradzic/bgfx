/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_IOS

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <QuartzCore/CAEAGLLayer.h>

#if __IPHONE_8_0 && !TARGET_IPHONE_SIMULATOR  // check if sdk/target supports metal
#   import <Metal/Metal.h>
#   import <QuartzCore/CAMetalLayer.h>
//#   define HAS_METAL_SDK
#endif

#include <bgfx/bgfxplatform.h>

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

	static WindowHandle s_defaultWindow = { 0 };

	struct Context
	{
		Context(uint32_t _width, uint32_t _height)
		{
			static const char* argv[1] = { "ios" };
			m_mte.m_argc = 1;
			m_mte.m_argv = const_cast<char**>(argv);

			m_eventQueue.postSizeEvent(s_defaultWindow, _width, _height);

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
		if ( mainBundle != nil )
		{
			CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
			if ( resourcesURL != nil )
			{
				char path[PATH_MAX];
				if (CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX) )
				{
					chdir(path);
				}
				CFRelease(resourcesURL);
			}
		}

		MainThreadEntry* self = (MainThreadEntry*)_userData;
		int32_t result = main(self->m_argc, self->m_argv);
		return result;
	}

	const Event* poll()
	{
		return s_ctx->m_eventQueue.poll();
	}

	const Event* poll(WindowHandle _handle)
	{
		return s_ctx->m_eventQueue.poll(_handle);
	}

	void release(const Event* _event)
	{
		s_ctx->m_eventQueue.release(_event);
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

	void toggleFullscreen(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
	}

	void setMouseLock(WindowHandle _handle, bool _lock)
	{
		BX_UNUSED(_handle, _lock);
	}

} // namespace entry

using namespace entry;

#ifdef HAS_METAL_SDK
static	id<MTLDevice>  m_device = NULL;
#else
static	void* m_device = NULL;
#endif

@interface ViewController : UIViewController
@end
@implementation ViewController
- (BOOL)prefersStatusBarHidden
{
	return YES;
}
@end


@interface View : UIView
{
	CADisplayLink* m_displayLink;
}

@end

@implementation View

+ (Class)layerClass
{
#ifdef HAS_METAL_SDK
	Class metalClass = NSClassFromString(@"CAMetalLayer");    //is metal runtime sdk available
	if ( metalClass != nil)
	{
		m_device = MTLCreateSystemDefaultDevice(); // is metal supported on this device (is there a better way to do this - without creating device ?)
		if (m_device)
		{
			[m_device retain];
			return metalClass;
		}
	}
#endif

	return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)rect
{
	self = [super initWithFrame:rect];

	if (nil == self)
	{
		return nil;
	}

	bgfx::PlatformData pd;
	pd.ndt          = NULL;
	pd.nwh          = self.layer;
	pd.context      = m_device;
	pd.backBuffer   = NULL;
	pd.backBufferDS = NULL;
	bgfx::setPlatformData(pd);

	return self;
}

- (void)layoutSubviews
{
	uint32_t frameW = (uint32_t)(self.contentScaleFactor * self.frame.size.width);
	uint32_t frameH = (uint32_t)(self.contentScaleFactor * self.frame.size.height);
	s_ctx->m_eventQueue.postSizeEvent(s_defaultWindow, frameW, frameH);
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

	s_ctx->m_eventQueue.postMouseEvent(s_defaultWindow, touchLocation.x, touchLocation.y, 0);
	s_ctx->m_eventQueue.postMouseEvent(s_defaultWindow, touchLocation.x, touchLocation.y, 0, MouseButton::Left, true);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	BX_UNUSED(touches);
	UITouch *touch = [[event allTouches] anyObject];
	CGPoint touchLocation = [touch locationInView:self];
	s_ctx->m_eventQueue.postMouseEvent(s_defaultWindow, touchLocation.x, touchLocation.y, 0, MouseButton::Left, false);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	BX_UNUSED(touches);
	UITouch *touch = [[event allTouches] anyObject];
	CGPoint touchLocation = [touch locationInView:self];
	s_ctx->m_eventQueue.postMouseEvent(s_defaultWindow, touchLocation.x, touchLocation.y, 0);
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	BX_UNUSED(touches);
	UITouch *touch = [[event allTouches] anyObject];
	CGPoint touchLocation = [touch locationInView:self];
	s_ctx->m_eventQueue.postMouseEvent(s_defaultWindow, touchLocation.x, touchLocation.y, 0, MouseButton::Left, false);
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

	UIViewController *viewController = [[ViewController alloc] init];
	viewController.view = m_view;

	[m_window setRootViewController:viewController];
	[m_window makeKeyAndVisible];

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
	s_ctx->m_eventQueue.postSuspendEvent(s_defaultWindow, Suspend::WillSuspend);
	[m_view stop];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
	BX_UNUSED(application);
	s_ctx->m_eventQueue.postSuspendEvent(s_defaultWindow, Suspend::DidSuspend);
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
	BX_UNUSED(application);
	s_ctx->m_eventQueue.postSuspendEvent(s_defaultWindow, Suspend::WillResume);
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
	BX_UNUSED(application);
	s_ctx->m_eventQueue.postSuspendEvent(s_defaultWindow, Suspend::DidResume);
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
