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

#include <nv/nv_MemoryManagement.h>

namespace entry
{
	struct MainThreadEntry
	{
		int m_argc;
		const char* const* m_argv;

		static int32_t threadFunc(bx::Thread* _thread, void* _userData);
	};

	struct Context
	{
		struct NvAllocator
		{
			void* mSystemMemory = nullptr;
			void* mGraphicsMemory = nullptr;
			void* mDevToolsMemory = nullptr;

			nn::mem::StandardAllocator mGraphicsAllocator;
			nn::mem::StandardAllocator mDevToolsAllocator;

			bx::DefaultAllocator mAllocator;

			void init()
			{
				constexpr int systemMemSize = 16 * 1024 * 1024;
				constexpr int graphicsMemSize = 1024 * 1024 * 1024; // 1GB memory allocated?
				constexpr int devToolsMemSize = 512 * 1024 * 1024; // graphics tools require 512MB

				mSystemMemory = BX_ALLOC(&mAllocator, systemMemSize);
				mGraphicsMemory = BX_ALLOC(&mAllocator, graphicsMemSize);
				mDevToolsMemory = BX_ALLOC(&mAllocator, devToolsMemSize);

				mGraphicsAllocator.Initialize(mGraphicsMemory, graphicsMemSize);
				mDevToolsAllocator.Initialize(mDevToolsMemory, devToolsMemSize);

				nv::SetGraphicsAllocator(NvAllocator::nvAllocateFunction, NvAllocator::nvFreeFunction, NvAllocator::nvReallocateFunction, &mGraphicsAllocator);
				nv::SetGraphicsDevtoolsAllocator(NvAllocator::nvAllocateFunction, NvAllocator::nvFreeFunction, NvAllocator::nvReallocateFunction, &mDevToolsAllocator);

				nv::InitializeGraphics(mSystemMemory, systemMemSize);
			}

			void shutdown()
			{
				mGraphicsAllocator.Finalize();
				mDevToolsAllocator.Finalize();

				BX_FREE(&mAllocator, mDevToolsMemory);
				BX_FREE(&mAllocator, mGraphicsMemory);
				BX_FREE(&mAllocator, mSystemMemory);

				mDevToolsMemory = nullptr;
				mGraphicsMemory = nullptr;
				mSystemMemory = nullptr;
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

		void _shutdownFileSystem()
		{
			nn::fs::Unmount("rom");
			BX_FREE(&mNvAllocator.mAllocator, mMountRomCacheBuffer);
		}

		void run(int _argc, char* _argv[])
		{
			nn::os::SetThreadName((nn::os::ThreadType*)nn::os::GetCurrentThread(), "MAIN");
			nn::os::ChangeThreadPriority((nn::os::ThreadType*)nn::os::GetCurrentThread(), nn::os::DefaultThreadPriority - 2);

			int width, height;
			nn::oe::GetDefaultDisplayResolution(&width, &height); // configure entry::s_width/entry::s_height to use this

			_initWindow();
			_initMemory();
			_initFileSystem();

			MainThreadEntry mte;
			mte.m_argc = _argc;
			mte.m_argv = _argv;

			bgfx::renderFrame();

			bx::Thread thread;
			thread.init(mte.threadFunc, &mte);
			m_init = true;

			while (!m_exit)
			{
				bgfx::renderFrame();

				// poll messages for exit?
				nn::os::YieldThread();
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
	};

	static Context s_ctx;

	const Event* poll()
	{
		return NULL;
	}

	const Event* poll(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
		return NULL;
	}

	void release(const Event* _event)
	{
		BX_UNUSED(_event);
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
		nn::os::SetThreadName((nn::os::ThreadType*)nn::os::GetCurrentThread(), "EXAMPLE");

		MainThreadEntry* self = (MainThreadEntry*)_userData;
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
