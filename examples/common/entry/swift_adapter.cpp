#include "entry_p.h"

#if ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_VISIONOS

#include "swift_adapter.h"

#include <bgfx/platform.h>
#include <bx/uint32_t.h>
#include <bx/thread.h>

namespace entry
{
  struct MainThreadEntry
  {
    int m_argc;
    const char* const* m_argv;

    static int32_t threadFunc(bx::Thread* _thread, void* _userData);
  };

  static WindowHandle s_defaultWindow = { 0 };

  struct Context
  {
    Context(uint32_t _width, uint32_t _height)
    {
      static const char* const argv[] = { "visionos" };
      m_mte.m_argc = BX_COUNTOF(argv);
      m_mte.m_argv = argv;

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
    void* m_window;

    EventQueue m_eventQueue;
  };

  static Context* s_ctx;

  int32_t MainThreadEntry::threadFunc(bx::Thread* _thread, void* _userData)
  {
    BX_UNUSED(_thread);

    if (_thread != NULL) {
      _thread->setThreadName("Main Thread BGFX");
    }

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

  void setWindowFlags(WindowHandle _handle, uint32_t _flags, bool _enabled)
  {
    BX_UNUSED(_handle, _flags, _enabled);
  }

  void toggleFullscreen(WindowHandle _handle)
  {
    BX_UNUSED(_handle);
  }

  void setMouseLock(WindowHandle _handle, bool _lock)
  {
    BX_UNUSED(_handle, _lock);
  }

  void* getNativeWindowHandle(WindowHandle _handle)
  {
    if (kDefaultWindowHandle.idx == _handle.idx)
    {
      return s_ctx->m_window;
    }

    return NULL;
  }

  void* getNativeDisplayHandle()
  {
    return NULL;
  }

  bgfx::NativeWindowHandleType::Enum getNativeWindowHandleType()
  {
    return bgfx::NativeWindowHandleType::Default;
  }

} // namespace entry

using namespace entry;

bool BgfxAdapter::initialize(void) {
  if (!m_initialized) {
    // Set context width and height to default visionOS resolution. It's different for the headset and device.
#if TARGET_OS_SIMULATOR
	s_ctx = new Context(2732, 2048);
#else
	s_ctx = new Context(1920, 1824);
#endif
    s_ctx->m_window = m_layerRenderer;
    m_initialized = true;
  }

  return m_initialized;
}

void BgfxAdapter::shutdown(void) {
  if (m_initialized) {
    s_ctx->m_eventQueue.postExitEvent();
    s_ctx = NULL;
  }

  m_initialized = false;
}

void BgfxAdapter::render() {
  if (!m_initialized) {
    return;
  }
  bgfx::renderFrame();
}

void BgfxAdapter::renderLoop() {
	bool isRendering = true;
	while (isRendering) {
		switch (cp_layer_renderer_get_state(m_layerRenderer)) {
			case cp_layer_renderer_state_paused:
				cp_layer_renderer_wait_until_running(m_layerRenderer);
				break;
				
			case cp_layer_renderer_state_running:
				this->initialize();
				this->render();
				break;
				
			case cp_layer_renderer_state_invalidated:
				isRendering = false;
				break;
		}
	}
	
	this->shutdown();
}

#endif // BX_PLATFORM_VISIONOS
