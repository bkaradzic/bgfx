/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "entry_p.h"

#if BX_PLATFORM_WINRT

#include <bgfxplatform.h>
#include <bx/thread.h>

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Platform;

static char* g_emptyArgs[] = { "" };
static entry::WindowHandle g_defaultWindow = { 0 };
static entry::EventQueue g_eventQueue;

ref class App sealed : public IFrameworkView
{
public:
	App()
		: m_windowVisible(true)
		, m_windowClosed(false)
	{
	}

	// IFrameworkView Methods.
	virtual void Initialize(CoreApplicationView^ applicationView)
	{
		applicationView->Activated += ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &App::OnActivated);
	}

	virtual void SetWindow(CoreWindow^ window)
	{
		window->VisibilityChanged += ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &App::OnVisibilityChanged);
		window->Closed += ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &App::OnWindowClosed);

		bgfx::winrtSetWindow(reinterpret_cast<IUnknown*>(window) );
	}

	virtual void Load(String^ entryPoint)
	{
	}

	virtual void Run()
	{
		bx::Thread thread;
		thread.init(MainThreadFunc, nullptr);

		CoreWindow^ window = CoreWindow::GetForCurrentThread();
		auto bounds = window->Bounds;
		auto dpi = DisplayInformation::GetForCurrentView()->LogicalDpi;

		static const float dipsPerInch = 96.0f;
		g_eventQueue.postSizeEvent(g_defaultWindow
			, lround(floorf(bounds.Width * dpi / dipsPerInch + 0.5f) )
			, lround(floorf(bounds.Height * dpi / dipsPerInch + 0.5f) )
			);

		while (!m_windowClosed)
		{
			if (m_windowVisible)
			{
				window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
			}
			else
			{
				window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
			}
		}

		g_eventQueue.postExitEvent();

		thread.shutdown();
	}

	virtual void Uninitialize()
	{
	}

private:
	bool m_windowVisible;
	bool m_windowClosed;

	void OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
	{
		CoreWindow::GetForCurrentThread()->Activate();
	}

	void OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
	{
		m_windowVisible = args->Visible;
	}

	void OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
	{
		m_windowClosed = true;
	}

	static int32_t MainThreadFunc(void*)
	{
		return entry::main(0, g_emptyArgs);
	}
};

ref class AppSource sealed : IFrameworkViewSource
{
public:
	virtual IFrameworkView^ CreateView()
	{
		return ref new App();
	}
};

namespace entry
{
	const Event* poll()
	{
		return g_eventQueue.poll();
	}

	const Event* poll(WindowHandle _handle)
	{
		return g_eventQueue.poll(_handle);
	}

	void release(const Event* _event)
	{
		g_eventQueue.release(_event);
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
}

[MTAThread]
int main(Array<String^>^)
{
	auto appSource = ref new AppSource();
	CoreApplication::Run(appSource);
	return 0;
}

#endif // BX_PLATFORM_WINRT
