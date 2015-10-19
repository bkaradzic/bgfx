/*
 * Copyright 2014-2015 Daniel Collin. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx/bgfx.h>
#include <bx/allocator.h>
#include <bx/fpumath.h>
#include <bx/timer.h>
#include <ocornut-imgui/imgui.h>
#include <ocornut-imgui/imgui_wm.h>
#include "imgui.h"
#include "ocornut_imgui.h"
#include <stb/stb_image.c>

#ifndef USE_ENTRY
#	define USE_ENTRY defined(SCI_NAMESPACE)
#endif // USE_ENTRY

#if USE_ENTRY
#	include "../entry/entry.h"
#endif // USE_ENTRY

#if defined(SCI_NAMESPACE)
#	include "../entry/input.h"
#	include "scintilla.h"
#endif // defined(SCI_NAMESPACE)

#include "vs_ocornut_imgui.bin.h"
#include "fs_ocornut_imgui.bin.h"

void viewCallback(const ImDrawList* _parentList, const ImDrawCmd* _cmd);

class PlatformWindow : public ImGuiWM::PlatformWindow
{
	typedef ImGuiWM::PlatformWindow Super;

public:
	PlatformWindow(bool _mainWindow, bool _isDragWindow)
		: ImGuiWM::PlatformWindow(_mainWindow, _isDragWindow)
		, m_pos(0.0f, 0.0f)
		, m_size(0.0f, 0.0f)
		, m_drag(false)
	{
#if USE_ENTRY
		if (!_mainWindow
		&&  !_isDragWindow)
		{
			m_window = entry::createWindow(0, 0, 640, 380);
			extern void pwToWindow(entry::WindowHandle _handle, PlatformWindow* _pw);
			pwToWindow(m_window, this);
		}
		else
		{
			m_window.idx = 0;
		}
#endif // USE_ENTRY
	}

	virtual ~PlatformWindow()
	{
	}

	virtual bool Init(ImGuiWM::PlatformWindow* /*_parent*/) BX_OVERRIDE
	{
		return true;
	}

	virtual const ImVec2& GetPosition() const BX_OVERRIDE
	{
		return m_pos;
	}

	virtual const ImVec2& GetSize() const BX_OVERRIDE
	{
		return m_size;
	}

	virtual void Show() BX_OVERRIDE
	{
	}

	virtual void Hide() BX_OVERRIDE
	{
	}

	virtual void SetSize(const ImVec2& _size) BX_OVERRIDE
	{
#if USE_ENTRY
		if (0 != m_window.idx
		&&  m_size.x != _size.x
		&&  m_size.y != _size.y)
		{
			entry::setWindowSize(m_window, int32_t(_size.x), int32_t(_size.y) );
		}
#endif // USE_ENTRY

		m_size = _size;
	}

	virtual void SetPosition(const ImVec2& _pos) BX_OVERRIDE
	{

#if USE_ENTRY
		if (0 != m_window.idx
		&&  m_pos.x != _pos.x
		&&  m_pos.y != _pos.y)
		{
			entry::setWindowPos(m_window, int32_t(_pos.x), int32_t(_pos.y) );
		}
#endif // USE_ENTRY

		m_pos = _pos;
	}

	virtual void SetTitle(const char* _title) BX_OVERRIDE
	{
#if USE_ENTRY
		entry::setWindowTitle(m_window, _title);
#else
		BX_UNUSED(_title);
#endif // USE_ENTRY
	}

	virtual void PreUpdate() BX_OVERRIDE
	{
	}

	virtual void PaintBegin()
	{
#if USE_ENTRY
		if (!m_bIsDragWindow)
		{
			ImDrawList* drawList = ImGui::GetWindowDrawList();
			union { entry::WindowHandle handle; void* ptr; } cast = { m_window };
			drawList->AddCallback(viewCallback, cast.ptr);
			drawList->PushClipRect(ImVec4(0.0f, 0.0f, m_size.x, m_size.y) );
		}
#endif // USE_ENTRY
	}

	virtual void Paint() BX_OVERRIDE
	{
		if (!m_bIsDragWindow)
		{
			Super::Paint();
		}
	}

	virtual void PaintEnd()
	{
#if USE_ENTRY
		if (!m_bIsDragWindow)
		{
			ImDrawList* drawList = ImGui::GetWindowDrawList();
			drawList->PopClipRect();
			drawList->AddCallback(viewCallback, NULL);
		}
#endif // USE_ENTRY
	}

	virtual void Destroy() BX_OVERRIDE
	{
	}

	virtual void StartDrag() BX_OVERRIDE
	{
		m_drag = true;
	}

	virtual void StopDrag() BX_OVERRIDE
	{
		m_drag = false;
	}

	virtual bool IsDraging() BX_OVERRIDE
	{
		return m_drag;
	}

private:
	ImVec2 m_pos;
	ImVec2 m_size;
	bool m_drag;

#if USE_ENTRY
	entry::WindowHandle m_window;
#endif // USE_ENTRY
};

class WindowManager : public ImGuiWM::WindowManager
{
	typedef ImGuiWM::WindowManager Super;

public:
	WindowManager()
	{
	}

	virtual ~WindowManager()
	{
	}

protected:
	virtual ImGuiWM::PlatformWindow* CreatePlatformWindow(bool _main, ImGuiWM::PlatformWindow* _parent, bool _isDragWindow) BX_OVERRIDE
	{
#if USE_ENTRY
#else
		if (!_main
		&&  !_isDragWindow)
		{
			return NULL;
		}
#endif // USE_ENTRY

		PlatformWindow* window = new (ImGui::MemAlloc(sizeof(PlatformWindow) ) ) PlatformWindow(_main, _isDragWindow);
		window->Init(_parent);
		return static_cast<ImGuiWM::PlatformWindow*>(window);
	}

	virtual void LogFormatted(const char* _str) BX_OVERRIDE
	{
		BX_TRACE("%s", _str); BX_UNUSED(_str);
	}

	virtual void InternalRun() BX_OVERRIDE
	{
		PreUpdate();
		Update();
	}
};

struct OcornutImguiContext
{
	static void* memAlloc(size_t _size);
	static void memFree(void* _ptr);
	static void renderDrawLists(ImDrawData* _drawData);

	void render(ImDrawData* _drawData)
	{
		const ImGuiIO& io = ImGui::GetIO();
		const float width  = io.DisplaySize.x;
		const float height = io.DisplaySize.y;

		{
			float ortho[16];
			bx::mtxOrtho(ortho, 0.0f, width, height, 0.0f, -1.0f, 1.0f);
			bgfx::setViewTransform(m_viewId, NULL, ortho);
		}

#if USE_ENTRY
		for (uint32_t ii = 1; ii < BX_COUNTOF(m_window); ++ii)
		{
			Window& window = m_window[ii];
			if (bgfx::isValid(window.m_fbh) )
			{
				const uint8_t viewId = window.m_viewId;
				bgfx::setViewClear(viewId
					, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
					, 0x303030ff + rand()
					, 1.0f
					, 0
					);
				bgfx::setViewFrameBuffer(viewId, window.m_fbh);
				bgfx::setViewRect(viewId
					, 0
					, 0
					, window.m_state.m_width
					, window.m_state.m_height
					);
				float ortho[16];
				bx::mtxOrtho(ortho
					, 0.0f
					, float(window.m_state.m_width)
					, float(window.m_state.m_height)
					, 0.0f
					, -1.0f
					, 1.0f
					);
				bgfx::setViewTransform(viewId
					, NULL
					, ortho
					);
			}
		}
#endif // USE_ENTRY

		// Render command lists
		for (int32_t ii = 0, num = _drawData->CmdListsCount; ii < num; ++ii)
		{
			bgfx::TransientVertexBuffer tvb;
			bgfx::TransientIndexBuffer tib;

			const ImDrawList* drawList = _drawData->CmdLists[ii];
			uint32_t numVertices = (uint32_t)drawList->VtxBuffer.size();
			uint32_t numIndices  = (uint32_t)drawList->IdxBuffer.size();

			if (!bgfx::checkAvailTransientVertexBuffer(numVertices, m_decl)
			||  !bgfx::checkAvailTransientIndexBuffer(numIndices) )
			{
				// not enough space in transient buffer just quit drawing the rest...
				break;
			}

			bgfx::allocTransientVertexBuffer(&tvb, numVertices, m_decl);
			bgfx::allocTransientIndexBuffer(&tib, numIndices);

			ImDrawVert* verts = (ImDrawVert*)tvb.data;
			memcpy(verts, drawList->VtxBuffer.begin(), numVertices * sizeof(ImDrawVert) );

			ImDrawIdx* indices = (ImDrawIdx*)tib.data;
			memcpy(indices, drawList->IdxBuffer.begin(), numIndices * sizeof(ImDrawIdx) );

			uint32_t offset = 0;
			for (const ImDrawCmd* cmd = drawList->CmdBuffer.begin(), *cmdEnd = drawList->CmdBuffer.end(); cmd != cmdEnd; ++cmd)
			{
				if (cmd->UserCallback)
				{
					cmd->UserCallback(drawList, cmd);
				}
				else if (0 != cmd->ElemCount)
				{
					uint64_t state = 0
						| BGFX_STATE_RGB_WRITE
						| BGFX_STATE_ALPHA_WRITE
						| BGFX_STATE_MSAA
						;

					bgfx::TextureHandle th = m_texture;

					if (NULL != cmd->TextureId)
					{
						union { ImTextureID ptr; struct { uint16_t flags; bgfx::TextureHandle handle; } s; } texture = { cmd->TextureId };
						state |= 0 != (IMGUI_FLAGS_ALPHA_BLEND & texture.s.flags)
							? BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
							: BGFX_STATE_NONE
							;
						th = texture.s.handle;
					}
					else
					{
						state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
					}

					const uint16_t xx = uint16_t(bx::fmax(cmd->ClipRect.x, 0.0f) );
					const uint16_t yy = uint16_t(bx::fmax(cmd->ClipRect.y, 0.0f) );
					bgfx::setScissor(xx, yy
							, uint16_t(bx::fmin(cmd->ClipRect.z, 65535.0f)-xx)
							, uint16_t(bx::fmin(cmd->ClipRect.w, 65535.0f)-yy)
							);

					bgfx::setState(state);
					bgfx::setTexture(0, s_tex, th);
					bgfx::setVertexBuffer(&tvb, 0, numVertices);
					bgfx::setIndexBuffer(&tib, offset, cmd->ElemCount);
					bgfx::submit(m_viewId, m_program);
				}

				offset += cmd->ElemCount;
			}
		}
	}

	void create(const void* _data, uint32_t _size, float _fontSize, bx::AllocatorI* _allocator)
	{
		m_viewId = 255;
		m_allocator = _allocator;
		m_lastScroll = 0;
		m_last = bx::getHPCounter();

		ImGuiIO& io = ImGui::GetIO();
		io.RenderDrawListsFn = renderDrawLists;
		if (NULL != m_allocator)
		{
			io.MemAllocFn = memAlloc;
			io.MemFreeFn  = memFree;
		}

		io.DisplaySize = ImVec2(1280.0f, 720.0f);
		io.DeltaTime   = 1.0f / 60.0f;
		io.IniFilename = NULL;

#if defined(SCI_NAMESPACE)
		io.KeyMap[ImGuiKey_Tab]        = (int)entry::Key::Tab;
		io.KeyMap[ImGuiKey_LeftArrow]  = (int)entry::Key::Left;
		io.KeyMap[ImGuiKey_RightArrow] = (int)entry::Key::Right;
		io.KeyMap[ImGuiKey_UpArrow]    = (int)entry::Key::Up;
		io.KeyMap[ImGuiKey_DownArrow]  = (int)entry::Key::Down;
		io.KeyMap[ImGuiKey_Home]       = (int)entry::Key::Home;
		io.KeyMap[ImGuiKey_End]        = (int)entry::Key::End;
		io.KeyMap[ImGuiKey_Delete]     = (int)entry::Key::Delete;
		io.KeyMap[ImGuiKey_Backspace]  = (int)entry::Key::Backspace;
		io.KeyMap[ImGuiKey_Enter]      = (int)entry::Key::Return;
		io.KeyMap[ImGuiKey_Escape]     = (int)entry::Key::Esc;
		io.KeyMap[ImGuiKey_A]          = (int)entry::Key::KeyA;
		io.KeyMap[ImGuiKey_C]          = (int)entry::Key::KeyC;
		io.KeyMap[ImGuiKey_V]          = (int)entry::Key::KeyV;
		io.KeyMap[ImGuiKey_X]          = (int)entry::Key::KeyX;
		io.KeyMap[ImGuiKey_Y]          = (int)entry::Key::KeyY;
		io.KeyMap[ImGuiKey_Z]          = (int)entry::Key::KeyZ;
#endif // defined(SCI_NAMESPACE)

		const bgfx::Memory* vsmem;
		const bgfx::Memory* fsmem;

		switch (bgfx::getRendererType() )
		{
		case bgfx::RendererType::Direct3D9:
			vsmem = bgfx::makeRef(vs_ocornut_imgui_dx9, sizeof(vs_ocornut_imgui_dx9) );
			fsmem = bgfx::makeRef(fs_ocornut_imgui_dx9, sizeof(fs_ocornut_imgui_dx9) );
			break;

		case bgfx::RendererType::Direct3D11:
		case bgfx::RendererType::Direct3D12:
			vsmem = bgfx::makeRef(vs_ocornut_imgui_dx11, sizeof(vs_ocornut_imgui_dx11) );
			fsmem = bgfx::makeRef(fs_ocornut_imgui_dx11, sizeof(fs_ocornut_imgui_dx11) );
			break;

		case bgfx::RendererType::Metal:
			vsmem = bgfx::makeRef(vs_ocornut_imgui_mtl, sizeof(vs_ocornut_imgui_mtl) );
			fsmem = bgfx::makeRef(fs_ocornut_imgui_mtl, sizeof(fs_ocornut_imgui_mtl) );
			break;

		default:
			vsmem = bgfx::makeRef(vs_ocornut_imgui_glsl, sizeof(vs_ocornut_imgui_glsl) );
			fsmem = bgfx::makeRef(fs_ocornut_imgui_glsl, sizeof(fs_ocornut_imgui_glsl) );
			break;
		}

		bgfx::ShaderHandle vsh = bgfx::createShader(vsmem);
		bgfx::ShaderHandle fsh = bgfx::createShader(fsmem);
		m_program = bgfx::createProgram(vsh, fsh, true);

		m_decl
			.begin()
			.add(bgfx::Attrib::Position,  2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
			.end();

		s_tex = bgfx::createUniform("s_tex", bgfx::UniformType::Int1);

		uint8_t* data;
		int32_t width;
		int32_t height;
		void* font = ImGui::MemAlloc(_size);
		memcpy(font, _data, _size);
		io.Fonts->AddFontFromMemoryTTF(font, _size, _fontSize);

		io.Fonts->GetTexDataAsRGBA32(&data, &width, &height);

		m_texture = bgfx::createTexture2D( (uint16_t)width
			, (uint16_t)height
			, 1
			, bgfx::TextureFormat::BGRA8
			, 0
			, bgfx::copy(data, width*height*4)
			);

		ImGuiStyle& style = ImGui::GetStyle();
		style.FrameRounding = 4.0f;

		m_wm = BX_NEW(m_allocator, WindowManager);
		m_wm->Init();

#if 0
		{
			class Window : public ImGuiWM::Window
			{
			public:
				Window(const char* _title)
					: ImGuiWM::Window()
				{
					SetTitle(_title);
				}

				virtual void OnGui() BX_OVERRIDE
				{
				}
			};

			class WindowX : public ImGuiWM::Window
			{
			public:
				WindowX(const char* _title)
					: ImGuiWM::Window()
				{
					SetTitle(_title);
				}

				virtual void OnGui() BX_OVERRIDE
				{
#if defined(SCI_NAMESPACE) && 0
					bool opened = true;
					ImGuiScintilla("Scintilla Editor", &opened, ImVec2(640.0f, 480.0f) );
#endif // 0
				}
			};

			Window*  w0 = new Window("test");
			WindowX* w1 = new WindowX("abcd");
			Window*  w2 = new Window("xyzw");
			Window*  w3 = new Window("0123");

			m_wm->Dock(w0);
			m_wm->DockWith(w1, w0, ImGuiWM::E_DOCK_ORIENTATION_RIGHT);
			m_wm->DockWith(w2, w1, ImGuiWM::E_DOCK_ORIENTATION_BOTTOM);
			m_wm->DockWith(w3, w0, ImGuiWM::E_DOCK_ORIENTATION_BOTTOM);
		}
#endif // 0
	}

	void destroy()
	{
		m_wm->Exit();
		BX_DELETE(m_allocator, m_wm);
		ImGui::Shutdown();

		bgfx::destroyUniform(s_tex);
		bgfx::destroyTexture(m_texture);
		bgfx::destroyProgram(m_program);

		m_allocator = NULL;
	}

	void beginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, int _width, int _height, char _inputChar, uint8_t _viewId)
	{
		m_viewId        = _viewId;
		m_defaultViewId = _viewId;

		ImGuiIO& io = ImGui::GetIO();
		if (_inputChar < 0x7f)
		{
			io.AddInputCharacter(_inputChar); // ASCII or GTFO! :(
		}

		io.DisplaySize = ImVec2( (float)_width, (float)_height);

		const int64_t now = bx::getHPCounter();
		const int64_t frameTime = now - m_last;
		m_last = now;
		const double freq = double(bx::getHPFrequency() );
		io.DeltaTime = float(frameTime/freq);

		io.MousePos = ImVec2( (float)_mx, (float)_my);
		io.MouseDown[0] = 0 != (_button & IMGUI_MBUT_LEFT);
		io.MouseDown[1] = 0 != (_button & IMGUI_MBUT_RIGHT);
		io.MouseDown[2] = 0 != (_button & IMGUI_MBUT_MIDDLE);
		io.MouseWheel = (float)(_scroll - m_lastScroll);
		m_lastScroll = _scroll;

#if defined(SCI_NAMESPACE)
		uint8_t modifiers = inputGetModifiersState();
		io.KeyShift = 0 != (modifiers & (entry::Modifier::LeftShift | entry::Modifier::RightShift) );
		io.KeyCtrl  = 0 != (modifiers & (entry::Modifier::LeftCtrl  | entry::Modifier::RightCtrl ) );
		io.KeyAlt   = 0 != (modifiers & (entry::Modifier::LeftAlt   | entry::Modifier::RightAlt  ) );
		for (int32_t ii = 0; ii < (int32_t)entry::Key::Count; ++ii)
		{
			io.KeysDown[ii] = inputGetKeyState(entry::Key::Enum(ii) );
		}
#endif // defined(SCI_NAMESPACE)

		ImGui::NewFrame();

#if 0
		ImGui::ShowTestWindow(); //Debug only.
#endif // 0

#if 0
		extern void ShowExampleAppCustomNodeGraph(bool* opened);
		bool opened = true;
		ShowExampleAppCustomNodeGraph(&opened);
#endif // 0
	}

	void endFrame()
	{
		m_wm->Run();
		ImGui::Render();
	}

	bx::AllocatorI*     m_allocator;
	bgfx::VertexDecl    m_decl;
	bgfx::ProgramHandle m_program;
	bgfx::TextureHandle m_texture;
	bgfx::UniformHandle s_tex;
	WindowManager* m_wm;
	int64_t m_last;
	int32_t m_lastScroll;
	uint8_t m_viewId;
	uint8_t m_defaultViewId;

#if USE_ENTRY
	struct Window
	{
		Window()
		{
			m_fbh.idx = bgfx::invalidHandle;
		}

		entry::WindowState m_state;
		PlatformWindow* m_pw;
		bgfx::FrameBufferHandle m_fbh;
		uint8_t m_viewId;
	};

	Window m_window[16];
#endif // USE_ENTRY
};

static OcornutImguiContext s_ctx;

#if USE_ENTRY

void viewCallback(const ImDrawList* /*_parentList*/, const ImDrawCmd* _cmd)
{
	union { void* ptr; entry::WindowHandle handle; } cast = { _cmd->UserCallbackData };

	if (0 != cast.handle.idx)
	{
		s_ctx.m_viewId = s_ctx.m_window[cast.handle.idx].m_viewId;
	}
	else
	{
		s_ctx.m_viewId = s_ctx.m_defaultViewId;
	}
}

void pwToWindow(entry::WindowHandle _handle, PlatformWindow* _pw)
{
	s_ctx.m_window[_handle.idx].m_pw = _pw;
}

void imguiUpdateWindow(const entry::WindowState& _state)
{
	OcornutImguiContext::Window& window = s_ctx.m_window[_state.m_handle.idx];

	if (window.m_state.m_nwh    != _state.m_nwh
	|| (window.m_state.m_width  != _state.m_width
	||  window.m_state.m_height != _state.m_height) )
	{
		// When window changes size or native window handle changed
		// frame buffer must be recreated.
		if (bgfx::isValid(window.m_fbh) )
		{
			bgfx::destroyFrameBuffer(window.m_fbh);
			window.m_fbh.idx = bgfx::invalidHandle;
		}

		if (NULL != _state.m_nwh)
		{
			window.m_fbh = bgfx::createFrameBuffer(_state.m_nwh, _state.m_width, _state.m_height);
			window.m_viewId = 200 + _state.m_handle.idx;
		}
		else
		{
			window.m_viewId = s_ctx.m_defaultViewId;
		}
	}

	memcpy(&window.m_state, &_state, sizeof(entry::WindowState) );
}
#endif // USE_ENTRY

void* OcornutImguiContext::memAlloc(size_t _size)
{
	return BX_ALLOC(s_ctx.m_allocator, _size);
}

void OcornutImguiContext::memFree(void* _ptr)
{
	BX_FREE(s_ctx.m_allocator, _ptr);
}

void OcornutImguiContext::renderDrawLists(ImDrawData* draw_data)
{
	s_ctx.render(draw_data);
}

void IMGUI_create(const void* _data, uint32_t _size, float _fontSize, bx::AllocatorI* _allocator)
{
	s_ctx.create(_data, _size, _fontSize, _allocator);
}

void IMGUI_destroy()
{
	s_ctx.destroy();
}

void IMGUI_beginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, int _width, int _height, char _inputChar, uint8_t _viewId)
{
	s_ctx.beginFrame(_mx, _my, _button, _scroll, _width, _height, _inputChar, _viewId);
}

void IMGUI_endFrame()
{
	s_ctx.endFrame();
}
