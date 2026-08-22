/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "entry_p.h"

#if BX_PLATFORM_EMSCRIPTEN

#include <bgfx/bgfx.h>

#include <emscripten.h>
#include <emscripten/html5.h>

extern "C" void entry_emscripten_yield()
{
//	emscripten_sleep(0);
}

#define _EMSCRIPTEN_CHECK(_check, _call)                                                                  \
	BX_MACRO_BLOCK_BEGIN                                                                                  \
		EMSCRIPTEN_RESULT __result__ = _call;                                                             \
		_check(EMSCRIPTEN_RESULT_SUCCESS == __result__, #_call " FAILED 0x%08x\n", (uint32_t)__result__); \
		BX_UNUSED(__result__);                                                                            \
	BX_MACRO_BLOCK_END

#define EMSCRIPTEN_CHECK(_call) _EMSCRIPTEN_CHECK(BX_ASSERT, _call)

namespace entry
{
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

			// Note: Keyboard events carry DOM `KeyboardEvent.keyCode`, which is
			//   layout independent, and it's not a character code.
			//
			// Reference(s):
			//  - https://web.archive.org/web/20250808182750/https://developer.mozilla.org/en-US/docs/Web/API/UI_Events/Keyboard_event_code_values
			//
			s_translateKey[  8] = Key::Backspace;
			s_translateKey[  9] = Key::Tab;
			s_translateKey[ 13] = Key::Return;
			s_translateKey[ 27] = Key::Esc;
			s_translateKey[ 32] = Key::Space;
			s_translateKey[ 33] = Key::PageUp;
			s_translateKey[ 34] = Key::PageDown;
			s_translateKey[ 35] = Key::End;
			s_translateKey[ 36] = Key::Home;
			s_translateKey[ 37] = Key::Left;
			s_translateKey[ 38] = Key::Up;
			s_translateKey[ 39] = Key::Right;
			s_translateKey[ 40] = Key::Down;
			s_translateKey[ 44] = Key::Print;
			s_translateKey[ 45] = Key::Insert;
			s_translateKey[ 46] = Key::Delete;

			s_translateKey[107] = Key::Plus;
			s_translateKey[109] = Key::Minus;
			s_translateKey[110] = Key::Period;
			s_translateKey[111] = Key::Slash;

			s_translateKey[186] = Key::Semicolon;
			s_translateKey[187] = Key::Plus;
			s_translateKey[188] = Key::Comma;
			s_translateKey[189] = Key::Minus;
			s_translateKey[190] = Key::Period;
			s_translateKey[191] = Key::Slash;
			s_translateKey[192] = Key::Tilde;
			s_translateKey[219] = Key::LeftBracket;
			s_translateKey[220] = Key::Backslash;
			s_translateKey[221] = Key::RightBracket;
			s_translateKey[222] = Key::Quote;

			for (uint8_t ii = 0; ii < 10; ++ii)
			{
				s_translateKey[uint8_t('0')+ii] = uint8_t(Key::Key0    + ii);
				s_translateKey[96+ii]           = uint8_t(Key::NumPad0 + ii);
			}

			for (uint8_t ii = 0; ii < 26; ++ii)
			{
				s_translateKey[uint8_t('A')+ii] = uint8_t(Key::KeyA + ii);
			}

			for (uint8_t ii = 0; ii < 12; ++ii)
			{
				s_translateKey[112+ii] = uint8_t(Key::F1 + ii);
			}
		}

		int32_t run(int _argc, const char* const* _argv)
		{
			static const char* canvas = "#canvas";

			EMSCRIPTEN_CHECK(emscripten_set_mousedown_callback(canvas, this, true, mouseCb) );
			EMSCRIPTEN_CHECK(emscripten_set_mouseup_callback(canvas, this, true, mouseCb) );
			EMSCRIPTEN_CHECK(emscripten_set_mousemove_callback(canvas, this, true, mouseCb) );

			EMSCRIPTEN_CHECK(emscripten_set_wheel_callback(canvas, this, true, wheelCb) );

			EMSCRIPTEN_CHECK(emscripten_set_keypress_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, true, keyCb) );
			EMSCRIPTEN_CHECK(emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, true, keyCb) );
			EMSCRIPTEN_CHECK(emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, true, keyCb) );

			EMSCRIPTEN_CHECK(emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, true, resizeCb) );

			EmscriptenFullscreenStrategy fullscreenStrategy = {};
			fullscreenStrategy.scaleMode = EMSCRIPTEN_FULLSCREEN_SCALE_DEFAULT;
			fullscreenStrategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE;
			fullscreenStrategy.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;
			fullscreenStrategy.canvasResizedCallback = canvasResizeCb;
			fullscreenStrategy.canvasResizedCallbackUserData = this;

			EMSCRIPTEN_CHECK(emscripten_request_fullscreen_strategy(canvas, false, &fullscreenStrategy) );

			EMSCRIPTEN_CHECK(emscripten_set_focus_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, true, focusCb) );
			EMSCRIPTEN_CHECK(emscripten_set_focusin_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, true, focusCb) );
			EMSCRIPTEN_CHECK(emscripten_set_focusout_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, true, focusCb) );

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

	EM_BOOL Context::mouseCb(int32_t _eventType, const EmscriptenMouseEvent* _event, void* _userData)
	{
		BX_UNUSED(_userData);

		if (_event)
		{
			switch (_eventType)
			{
				case EMSCRIPTEN_EVENT_MOUSEMOVE:
					s_ctx.m_mx = _event->targetX;
					s_ctx.m_my = _event->targetY;
					s_ctx.m_eventQueue.postMouseEvent(kDefaultWindowHandle, s_ctx.m_mx, s_ctx.m_my, s_ctx.m_scroll);
					return true;

				case EMSCRIPTEN_EVENT_MOUSEDOWN:
				case EMSCRIPTEN_EVENT_MOUSEUP:
				case EMSCRIPTEN_EVENT_DBLCLICK:
					s_ctx.m_mx = _event->targetX;
					s_ctx.m_my = _event->targetY;
					MouseButton::Enum mb = _event->button == 2
						? MouseButton::Right  : ( (_event->button == 1)
						? MouseButton::Middle : MouseButton::Left)
						;
					s_ctx.m_eventQueue.postMouseEvent(
						  kDefaultWindowHandle
						, s_ctx.m_mx
						, s_ctx.m_my
						, s_ctx.m_scroll
						, mb
						, (_eventType != EMSCRIPTEN_EVENT_MOUSEUP)
						);
					return true;
			}
		}

		return false;
	}

	EM_BOOL Context::wheelCb(int32_t _eventType, const EmscriptenWheelEvent* _event, void* _userData)
	{
		BX_UNUSED(_userData);

		if (_event)
		{
			switch (_eventType)
			{
				case EMSCRIPTEN_EVENT_WHEEL:
				{
					s_ctx.m_scrollf += _event->deltaY;

					s_ctx.m_scroll = (int32_t)s_ctx.m_scrollf;
					s_ctx.m_eventQueue.postMouseEvent(kDefaultWindowHandle, s_ctx.m_mx, s_ctx.m_my, s_ctx.m_scroll);
					return true;
				}
			}
		}

		return false;
	}

	uint8_t translateModifiers(const EmscriptenKeyboardEvent* _event)
	{
		uint8_t mask = 0;

		if (_event->shiftKey)
		{
			mask |= Modifier::LeftShift | Modifier::RightShift;
		}

		if (_event->altKey)
		{
			mask |= Modifier::LeftAlt | Modifier::RightAlt;
		}

		if (_event->ctrlKey)
		{
			mask |= Modifier::LeftCtrl | Modifier::RightCtrl;
		}

		if (_event->metaKey)
		{
			mask |= Modifier::LeftMeta | Modifier::RightMeta;
		}

		return mask;
	}

	Key::Enum handleKeyEvent(const EmscriptenKeyboardEvent* _event, uint8_t* _specialKeys, uint8_t* _pressedChar)
	{
		*_pressedChar = uint8_t(_event->keyCode);

		int32_t keyCode = int32_t(_event->keyCode);
		*_specialKeys = translateModifiers(_event);

		// if this is a unhandled key just return None
		if (keyCode < 256)
		{
			return Key::Enum(s_translateKey[keyCode]);
		}

		return Key::None;
	}

	EM_BOOL Context::keyCb(int32_t _eventType, const EmscriptenKeyboardEvent* _event, void* _userData)
	{
		BX_UNUSED(_userData);

		if (_event)
		{
			uint8_t modifiers = 0;
			uint8_t pressedChar[4];
			Key::Enum key = handleKeyEvent(_event, &modifiers, &pressedChar[0]);

			// Returning true means that we take care of the key (instead of the default behavior)
			if (key != Key::None)
			{
				switch (_eventType)
				{
					case EMSCRIPTEN_EVENT_KEYPRESS:
					case EMSCRIPTEN_EVENT_KEYDOWN:
						if (key == Key::KeyQ && (modifiers & Modifier::RightMeta) )
						{
							s_ctx.m_eventQueue.postExitEvent();
						}
						else
						{
							enum { ShiftMask = Modifier::LeftShift|Modifier::RightShift };
							s_ctx.m_eventQueue.postCharEvent(kDefaultWindowHandle, 1, pressedChar);
							s_ctx.m_eventQueue.postKeyEvent(kDefaultWindowHandle, key, modifiers, true);
							return true;
						}
						break;

					case EMSCRIPTEN_EVENT_KEYUP:
						s_ctx.m_eventQueue.postKeyEvent(kDefaultWindowHandle, key, modifiers, false);
						return true;
				}
			}

		}
		return false;
	}

	EM_BOOL Context::resizeCb(int32_t _eventType, const EmscriptenUiEvent* _event, void* _userData)
	{
		BX_UNUSED(_eventType, _event, _userData);
		return false;
	}

	EM_BOOL Context::canvasResizeCb(int32_t _eventType, const void* _reserved, void* _userData)
	{
		BX_UNUSED(_eventType, _reserved, _userData);
		return false;
	}

	EM_BOOL Context::focusCb(int32_t _eventType, const EmscriptenFocusEvent* _event, void* _userData)
	{
		BX_UNUSED(_event, _userData);

		if (_event)
		{
			switch (_eventType)
			{
				case EMSCRIPTEN_EVENT_BLUR:
					s_ctx.m_eventQueue.postSuspendEvent(kDefaultWindowHandle, Suspend::DidSuspend);
					return true;

				case EMSCRIPTEN_EVENT_FOCUS:
					s_ctx.m_eventQueue.postSuspendEvent(kDefaultWindowHandle, Suspend::DidResume);
					return true;

				case EMSCRIPTEN_EVENT_FOCUSIN:
					s_ctx.m_eventQueue.postSuspendEvent(kDefaultWindowHandle, Suspend::WillResume);
					return true;

				case EMSCRIPTEN_EVENT_FOCUSOUT:
					s_ctx.m_eventQueue.postSuspendEvent(kDefaultWindowHandle, Suspend::WillSuspend);
					return true;
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
			return (void*)"#canvas";
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
}

int main(int _argc, const char* const* _argv)
{
	using namespace entry;
	return s_ctx.run(_argc, _argv);
}

#endif // BX_PLATFORM_EMSCRIPTEN
