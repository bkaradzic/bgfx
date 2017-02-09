/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "entry_p.h"

#if BX_PLATFORM_EMSCRIPTEN

#include <emscripten.h>
#include <emscripten/html5.h>

extern "C" void entry_emscripten_yield()
{
//	emscripten_sleep(0);
}

namespace entry
{
	static WindowHandle s_defaultWindow = { 0 };

	static uint8_t s_translateKey[256];

	struct Context
	{
		Context()
			: m_scrollf(0.0f)
			, m_mx(0)
			, m_my(0)
			, m_scroll(0)
		{
			bx::memSet(s_translateKey, 0, sizeof(s_translateKey));
			s_translateKey[27]             = Key::Esc;
			s_translateKey[uint8_t('\n')]  =
			s_translateKey[uint8_t('\r')]  = Key::Return;
			s_translateKey[uint8_t('\t')]  = Key::Tab;
			s_translateKey[127]            = Key::Backspace;
			s_translateKey[uint8_t(' ')]   = Key::Space;
			s_translateKey[38]             = Key::Up;
			s_translateKey[40]             = Key::Down;
			s_translateKey[37]             = Key::Left;
			s_translateKey[39]             = Key::Right;

			s_translateKey[uint8_t('+')]   =
			s_translateKey[uint8_t('=')]   = Key::Plus;
			s_translateKey[uint8_t('_')]   =
			s_translateKey[uint8_t('-')]   = Key::Minus;

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

			s_translateKey[uint8_t('~')]   =
			s_translateKey[uint8_t('`')]   = Key::Tilde;

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
		}

		int32_t run(int _argc, char** _argv)
		{
			emscripten_set_mousedown_callback("#canvas", this, true, mouseCb);
			emscripten_set_mouseup_callback("#canvas", this, true, mouseCb);
			emscripten_set_mousemove_callback("#canvas", this, true, mouseCb);

			emscripten_set_wheel_callback("#canvas", this, true, wheelCb);

			emscripten_set_keypress_callback(NULL, this, true, keyCb);
			emscripten_set_keydown_callback(NULL, this, true, keyCb);
			emscripten_set_keyup_callback(NULL, this, true, keyCb);

			emscripten_set_resize_callback(0, this, true, resizeCb);

			EmscriptenFullscreenStrategy fullscreenStrategy = {};
			fullscreenStrategy.scaleMode = EMSCRIPTEN_FULLSCREEN_SCALE_DEFAULT;
			fullscreenStrategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE;
			fullscreenStrategy.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;
			fullscreenStrategy.canvasResizedCallback = canvasResizeCb;
			fullscreenStrategy.canvasResizedCallbackUserData = this;

			emscripten_request_fullscreen_strategy("#canvas", false, &fullscreenStrategy);

			emscripten_set_focus_callback(NULL, this, true, focusCb);
			emscripten_set_focusin_callback(NULL, this, true, focusCb);
			emscripten_set_focusout_callback(NULL, this, true, focusCb);

			int32_t result = main(_argc, _argv);
			return result;
		}

		static EM_BOOL mouseCb(int eventType, const EmscriptenMouseEvent* event, void* userData);
		static EM_BOOL wheelCb(int eventType, const EmscriptenWheelEvent* event, void* userData);
		static EM_BOOL keyCb(int eventType, const EmscriptenKeyboardEvent* event, void* userData);
		static EM_BOOL resizeCb(int eventType, const EmscriptenUiEvent* event, void* userData);
		static EM_BOOL canvasResizeCb(int eventType, const void* reserved, void* userData);
		static EM_BOOL focusCb(int eventType, const EmscriptenFocusEvent* event, void* userData);

		EventQueue m_eventQueue;

		float   m_scrollf;
		int32_t m_mx;
		int32_t m_my;
		int32_t m_scroll;
	};

	static Context s_ctx;

	EM_BOOL Context::mouseCb(int eventType, const EmscriptenMouseEvent* event, void* userData)
	{
		BX_UNUSED(userData);

		if (event)
		{
			switch (eventType)
			{
				case EMSCRIPTEN_EVENT_MOUSEMOVE:
				{
					s_ctx.m_mx = event->canvasX;
					s_ctx.m_my = event->canvasY;
					s_ctx.m_eventQueue.postMouseEvent(s_defaultWindow, s_ctx.m_mx, s_ctx.m_my, s_ctx.m_scroll);
					return true;
				}
				case EMSCRIPTEN_EVENT_MOUSEDOWN:
				case EMSCRIPTEN_EVENT_MOUSEUP:
				case EMSCRIPTEN_EVENT_DBLCLICK:
				{
					s_ctx.m_mx = event->canvasX;
					s_ctx.m_my = event->canvasY;
					MouseButton::Enum mb = (event->button == 2) ? MouseButton::Right : ((event->button == 1) ? MouseButton::Middle : MouseButton::Left);
					s_ctx.m_eventQueue.postMouseEvent(s_defaultWindow, s_ctx.m_mx, s_ctx.m_my, s_ctx.m_scroll, mb, (eventType != EMSCRIPTEN_EVENT_MOUSEUP));
					return true;
				}
			}
		}

		return false;
	}

	EM_BOOL Context::wheelCb(int eventType, const EmscriptenWheelEvent* event, void* userData)
	{
		BX_UNUSED(userData);

		if (event)
		{
			switch (eventType)
			{
				case EMSCRIPTEN_EVENT_WHEEL:
				{
					s_ctx.m_scrollf += event->deltaY;

					s_ctx.m_scroll = (int32_t)s_ctx.m_scrollf;
					s_ctx.m_eventQueue.postMouseEvent(s_defaultWindow, s_ctx.m_mx, s_ctx.m_my, s_ctx.m_scroll);
					return true;
				}
			}
		}

		return false;
	}

	uint8_t translateModifiers(const EmscriptenKeyboardEvent* event)
	{
		uint8_t mask = 0;

		if (event->shiftKey)
			mask |= Modifier::LeftShift | Modifier::RightShift;

		if (event->altKey)
			mask |= Modifier::LeftAlt | Modifier::RightAlt;

		if (event->ctrlKey)
			mask |= Modifier::LeftCtrl | Modifier::RightCtrl;

		if (event->metaKey)
			mask |= Modifier::LeftMeta | Modifier::RightMeta;

		return mask;
	}

	Key::Enum handleKeyEvent(const EmscriptenKeyboardEvent* event, uint8_t* specialKeys, uint8_t* _pressedChar)
	{
		*_pressedChar = (uint8_t)event->keyCode;

		int keyCode = (int)event->keyCode;
		*specialKeys = translateModifiers(event);

		if (event->charCode == 0)
		{
			switch (keyCode)
			{
				case 112:  return Key::F1;
				case 113:  return Key::F2;
				case 114:  return Key::F3;
				case 115:  return Key::F4;
				case 116:  return Key::F5;
				case 117:  return Key::F6;
				case 118:  return Key::F7;
				case 119:  return Key::F8;
				case 120:  return Key::F9;
				case 121:  return Key::F10;
				case 122:  return Key::F11;
				case 123:  return Key::F12;

				case 37:   return Key::Left;
				case 39:   return Key::Right;
				case 38:   return Key::Up;
				case 40:   return Key::Down;
			}
		}

		// if this is a unhandled key just return None
		if (keyCode < 256)
		{
			return (Key::Enum)s_translateKey[keyCode];
		}

		return Key::None;
	}

	EM_BOOL Context::keyCb(int eventType, const EmscriptenKeyboardEvent *event, void *userData)
	{
		BX_UNUSED(userData);

		if (event)
		{
			uint8_t modifiers = 0;
			uint8_t pressedChar[4];
			Key::Enum key = handleKeyEvent(event, &modifiers, &pressedChar[0]);

			// Returning true means that we take care of the key (instead of the default behavior)
			if (key != Key::None)
			{
				switch (eventType)
				{
					case EMSCRIPTEN_EVENT_KEYPRESS:
					case EMSCRIPTEN_EVENT_KEYDOWN:
					{
						if (key == Key::KeyQ && (modifiers & Modifier::RightMeta) )
						{
							s_ctx.m_eventQueue.postExitEvent();
						}
						else
						{
							enum { ShiftMask = Modifier::LeftShift|Modifier::RightShift };
							s_ctx.m_eventQueue.postCharEvent(s_defaultWindow, 1, pressedChar);
							s_ctx.m_eventQueue.postKeyEvent(s_defaultWindow, key, modifiers, true);
							return true;
						}
						break;
					}
					case EMSCRIPTEN_EVENT_KEYUP:
					{
						s_ctx.m_eventQueue.postKeyEvent(s_defaultWindow, key, modifiers, false);
						return true;
					}
				}
			}

		}
		return false;
	}

	EM_BOOL Context::resizeCb(int eventType, const EmscriptenUiEvent* event, void* userData)
	{
		BX_UNUSED(eventType, event, userData);
		return false;
	}

	EM_BOOL Context::canvasResizeCb(int eventType, const void* reserved, void* userData)
	{
		BX_UNUSED(eventType, reserved, userData);
		return false;
	}

	EM_BOOL Context::focusCb(int eventType, const EmscriptenFocusEvent* event, void* userData)
	{
		printf("focusCb %d", eventType);
		BX_UNUSED(event, userData);

		if (event)
		{
			switch (eventType)
			{
				case EMSCRIPTEN_EVENT_BLUR:
				{
					s_ctx.m_eventQueue.postSuspendEvent(s_defaultWindow, Suspend::DidSuspend);
					return true;
				}
				case EMSCRIPTEN_EVENT_FOCUS:
				{
					s_ctx.m_eventQueue.postSuspendEvent(s_defaultWindow, Suspend::DidResume);
					return true;
				}
				case EMSCRIPTEN_EVENT_FOCUSIN:
				{
					s_ctx.m_eventQueue.postSuspendEvent(s_defaultWindow, Suspend::WillResume);
					return true;
				}
				case EMSCRIPTEN_EVENT_FOCUSOUT:
				{
					s_ctx.m_eventQueue.postSuspendEvent(s_defaultWindow, Suspend::WillSuspend);
					return true;
				}
			}
		}

		return false;
	}

	const Event* poll()
	{
		entry_emscripten_yield();
		return s_ctx.m_eventQueue.poll();
	}

	const Event* poll(WindowHandle _handle)
	{
		entry_emscripten_yield();
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

	void toggleFullscreen(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
	}

	void setMouseLock(WindowHandle _handle, bool _lock)
	{
		BX_UNUSED(_handle, _lock);
	}
}

int main(int _argc, char** _argv)
{
	using namespace entry;
	return s_ctx.run(_argc, _argv);
}

#endif // BX_PLATFORM_EMSCRIPTEN
