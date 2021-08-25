/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_NX

#include <bgfx/platform.h>

#include <bx/mutex.h>
#include <bx/handlealloc.h>
#include <bx/os.h>
#include <bx/thread.h>
#include <bx/timer.h>
#include <bx/uint32_t.h>

#include <nn/fs.h>
#include <nn/mem.h>
#include <nn/nn_Abort.h>
#include <nn/nn_Assert.h>
#include <nn/nn_Common.h>
#include <nn/nn_Log.h>
#include <nn/os.h>
#include <nn/oe.h>

#include <nn/vi.h>
#include <nn/hid.h>

#include <nv/nv_MemoryManagement.h>

namespace entry
{
	struct MainThreadEntry
	{
		bool m_running = false;

		int m_argc;
		const char* const* m_argv;

		static int32_t threadFunc(bx::Thread* _thread, void* _userData);
	};

	struct Context
	{
		struct NvAllocator
		{
			bx::DefaultAllocator mAllocator;

			void* mSystemMemory = nullptr;
			void* mGraphicsMemory = nullptr;

			nn::mem::StandardAllocator mGraphicsAllocator;

			void* mDevToolsMemory = nullptr;
			nn::mem::StandardAllocator mDevToolsAllocator;

			void init()
			{
				constexpr int systemMemSize = 16 * 1024 * 1024;
				constexpr int graphicsMemSize = 8 * 1024 * 1024; // used during device init

				mSystemMemory = BX_ALLOC(&mAllocator, systemMemSize);
				mGraphicsMemory = BX_ALLOC(&mAllocator, graphicsMemSize);

				mGraphicsAllocator.Initialize(mGraphicsMemory, graphicsMemSize);
				nv::SetGraphicsAllocator(NvAllocator::nvAllocateFunction, NvAllocator::nvFreeFunction, NvAllocator::nvReallocateFunction, &mGraphicsAllocator);

				constexpr int devToolsMemSize = 512 * 1024 * 1024; // graphics tools require 512MB
				mDevToolsMemory = BX_ALLOC(&mAllocator, devToolsMemSize);
				mDevToolsAllocator.Initialize(mDevToolsMemory, devToolsMemSize);
				nv::SetGraphicsDevtoolsAllocator(NvAllocator::nvAllocateFunction, NvAllocator::nvFreeFunction, NvAllocator::nvReallocateFunction, &mDevToolsAllocator);

				nv::InitializeGraphics(mSystemMemory, systemMemSize);
			}

			void shutdown()
			{
				BX_FREE(&mAllocator, mSystemMemory);
				mSystemMemory = nullptr;

				mGraphicsAllocator.Finalize();
				BX_FREE(&mAllocator, mGraphicsMemory);
				mGraphicsMemory = nullptr;

				mDevToolsAllocator.Finalize();
				BX_FREE(&mAllocator, mDevToolsMemory);
				mDevToolsMemory = nullptr;
			}

			// Graphics allocation functions
			static void* nvAllocateFunction(size_t size, size_t alignment, void* userPtr)
			{
				return reinterpret_cast<nn::mem::StandardAllocator*>(userPtr)->Allocate(size, alignment);
			}

			static void nvFreeFunction(void* addr, void* userPtr)
			{
				reinterpret_cast<nn::mem::StandardAllocator*>(userPtr)->Free(addr);
			}

			static void* nvReallocateFunction(void* addr, size_t newSize, void* userPtr)
			{
				return reinterpret_cast<nn::mem::StandardAllocator*>(userPtr)->Reallocate(addr, newSize); return reinterpret_cast<nn::mem::StandardAllocator*>(userPtr)->Reallocate(addr, newSize);
			}
		};

		void _initWindow()
		{
			nn::vi::Initialize();

			NN_ABORT_UNLESS_RESULT_SUCCESS(nn::vi::OpenDefaultDisplay(&mDisplay));
			NN_ABORT_UNLESS_RESULT_SUCCESS(nn::vi::CreateLayer(&mLayer, mDisplay));
			NN_ABORT_UNLESS_RESULT_SUCCESS(nn::vi::GetNativeWindow(&mNWH, mLayer));

			bgfx::PlatformData pd;
			bx::memSet(&pd, 0, sizeof(pd));
			pd.nwh = mNWH;
			bgfx::setPlatformData(pd);
		}

		void _initMemory()
		{
			mNvAllocator.init();
		}

		void _initFileSystem()
		{
			size_t cacheSize = 0;
			nn::Result result = nn::fs::QueryMountRomCacheSize(&cacheSize);
			BX_ASSERT(result.IsSuccess(), "Couldn't query rom cache size.");

			mMountRomCacheBuffer = (char*)BX_ALLOC(&mNvAllocator.mAllocator, cacheSize);
			BX_ASSERT(mMountRomCacheBuffer != nullptr, "Failed to initialize filesystem cache.");

			result = nn::fs::MountRom("rom", mMountRomCacheBuffer, cacheSize);
			BX_ASSERT(result.IsSuccess(), "Couldn't mount rom.");
		}

		void _initInput()
		{
			nn::hid::InitializeTouchScreen();
		}

		void _updateInput()
		{
			m_prevTouchState = m_touchState;
			nn::hid::GetTouchScreenState(&m_touchState);

			bool hasInput = m_touchState.count > 0;
			bool hadInput = m_prevTouchState.count > 0;

			if (hasInput)
			{
				int32_t x = m_touchState.touches[0].x;
				int32_t y = m_touchState.touches[0].y;
				int32_t mw = 0;

				if (!hadInput)
				{
					m_eventQueue.postMouseEvent({ UINT16_MAX }, x, y, mw);
				}

				m_eventQueue.postMouseEvent({ UINT16_MAX }, x, y, mw, MouseButton::Enum::Left, true);
			}
			else if (hadInput)
			{
				int32_t x = m_prevTouchState.touches[0].x;
				int32_t y = m_prevTouchState.touches[0].y;
				int32_t mw = 0;

				m_eventQueue.postMouseEvent({ UINT16_MAX }, x, y, mw, MouseButton::Enum::Left, false);
				m_eventQueue.postMouseEvent({ UINT16_MAX }, x, y, mw);
			}
		}

		void _shutdownFileSystem()
		{
			nn::fs::Unmount("rom");
			BX_FREE(&mNvAllocator.mAllocator, mMountRomCacheBuffer);
		}

		void run(int _argc, char* _argv[])
		{
			nn::os::SetThreadName((nn::os::ThreadType*)nn::os::GetCurrentThread(), "MAIN");

			int width, height;
			nn::oe::GetDefaultDisplayResolution(&width, &height); // configure entry::s_width/entry::s_height to use this

			nn::oe::SetPerformanceConfiguration(nn::oe::PerformanceMode_Normal, nn::oe::PerformanceConfiguration_Cpu1020MhzGpu384MhzEmc1331Mhz);

			_initWindow();
			_initMemory();
			_initFileSystem();
			_initInput();

			MainThreadEntry mte;
			mte.m_argc = _argc;
			mte.m_argv = _argv;

			bgfx::renderFrame();

			bx::Thread thread;
			thread.init(mte.threadFunc, &mte);
			m_init = true;

			// wait for thread to start and change its affinity
			while (!mte.m_running)
			{
				nn::os::YieldThread();
			}

			while (!m_exit)
			{
				_updateInput();
				bgfx::renderFrame();

				// poll messages for exit?
			}

			while (bgfx::RenderFrame::NoContext != bgfx::renderFrame()) {};

			thread.shutdown();

			nn::vi::DestroyLayer(mLayer);
			nn::vi::CloseDisplay(mDisplay);

			_shutdownFileSystem();

			mNvAllocator.shutdown();
		}

		bool m_init = false;
		bool m_exit = false;

		nn::vi::Display* mDisplay;
		nn::vi::Layer* mLayer;
		nn::vi::NativeWindowHandle mNWH;

		NvAllocator mNvAllocator;
		char* mGraphicsMemory = nullptr;
		char* mMountRomCacheBuffer = nullptr;

		EventQueue m_eventQueue;
		nn::hid::TouchScreenState<1> m_touchState;
		nn::hid::TouchScreenState<1> m_prevTouchState;
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

	int32_t MainThreadEntry::threadFunc(bx::Thread* /*_thread*/, void* _userData)
	{
		// change this thread to run on the second core
		int idealCore = 1;
		nn::os::SetThreadName((nn::os::ThreadType*)nn::os::GetCurrentThread(), "EXAMPLE");
		nn::os::SetThreadCoreMask((nn::os::ThreadType*)nn::os::GetCurrentThread(), idealCore, (1 << idealCore));

		MainThreadEntry* self = (MainThreadEntry*)_userData;
		self->m_running = true; // let the main thread continue
		int32_t result = main(self->m_argc, self->m_argv);
		//PostMessage(s_ctx.m_hwnd[0], WM_QUIT, 0, 0);
		return result;
	}

} // namespace entry

extern "C" void nnMain(int _argc, char* _argv[])
{
	using namespace entry;
	s_ctx.run(_argc, _argv);
}

#endif // ENTRY_CONFIG_USE_NOOP
