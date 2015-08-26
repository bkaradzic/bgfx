/*
 * Copyright 2014-2015 Daniel Collin. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx.h>
#include <bx/allocator.h>
#include <bx/fpumath.h>
#include <bx/timer.h>
#include <ocornut-imgui/imgui.h>
#include "imgui.h"
#include "ocornut_imgui.h"
#include <stb/stb_image.c>

#if defined(SCI_NAMESPACE)
#	include "../entry/input.h"
#	include "scintilla.h"
#endif // defined(SCI_NAMESPACE)

#include "vs_ocornut_imgui.bin.h"
#include "fs_ocornut_imgui.bin.h"

struct OcornutImguiContext
{
	static void* memAlloc(size_t _size);
	static void memFree(void* _ptr);
	static void renderDrawLists(ImDrawData* draw_data);

	void render(ImDrawData* draw_data)
	{
		const float width  = ImGui::GetIO().DisplaySize.x;
		const float height = ImGui::GetIO().DisplaySize.y;

		float ortho[16];
		bx::mtxOrtho(ortho, 0.0f, width, height, 0.0f, -1.0f, 1.0f);

		bgfx::setViewTransform(m_viewId, NULL, ortho);

		// Render command lists
		for (int32_t ii = 0; ii < draw_data->CmdListsCount; ++ii)
		{
			bgfx::TransientVertexBuffer tvb;
			bgfx::TransientIndexBuffer tib;

			const ImDrawList* cmd_list   = draw_data->CmdLists[ii];
			uint32_t vtx_size = (uint32_t)cmd_list->VtxBuffer.size();
			uint32_t idx_size = (uint32_t)cmd_list->IdxBuffer.size();

			if (!bgfx::checkAvailTransientVertexBuffer(vtx_size, m_decl) || !bgfx::checkAvailTransientIndexBuffer(idx_size) )
			{
				// not enough space in transient buffer just quit drawing the rest...
				break;
			}

			bgfx::allocTransientVertexBuffer(&tvb, vtx_size, m_decl);
			bgfx::allocTransientIndexBuffer(&tib, idx_size);

			ImDrawVert* verts = (ImDrawVert*)tvb.data;
			memcpy(verts, cmd_list->VtxBuffer.begin(), vtx_size * sizeof(ImDrawVert) );

			ImDrawIdx* indices = (ImDrawIdx*)tib.data;
			memcpy(indices, cmd_list->IdxBuffer.begin(), idx_size * sizeof(ImDrawIdx) );

			uint32_t elem_offset = 0;
			const ImDrawCmd* pcmd_begin = cmd_list->CmdBuffer.begin();
			const ImDrawCmd* pcmd_end   = cmd_list->CmdBuffer.end();
			for (const ImDrawCmd* pcmd = pcmd_begin; pcmd != pcmd_end; pcmd++)
			{
				if (pcmd->UserCallback)
				{
					pcmd->UserCallback(cmd_list, pcmd);
					elem_offset += pcmd->ElemCount;
					continue;
				}
				if (0 == pcmd->ElemCount)
				{
					continue;
				}

				bgfx::setState(0
					| BGFX_STATE_RGB_WRITE
					| BGFX_STATE_ALPHA_WRITE
					| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
					| BGFX_STATE_MSAA
					);
				bgfx::setScissor(uint16_t(bx::fmax(pcmd->ClipRect.x, 0.0f) )
					, uint16_t(bx::fmax(pcmd->ClipRect.y, 0.0f) )
					, uint16_t(bx::fmin(pcmd->ClipRect.z, 65535.0f)-bx::fmax(pcmd->ClipRect.x, 0.0f) )
					, uint16_t(bx::fmin(pcmd->ClipRect.w, 65535.0f)-bx::fmax(pcmd->ClipRect.y, 0.0f) )
					);
				union { void* ptr; bgfx::TextureHandle handle; } texture = { pcmd->TextureId };

				bgfx::setTexture(0, s_tex, 0 != texture.handle.idx
					? texture.handle
					: m_texture
					);

				bgfx::setVertexBuffer(&tvb, 0, vtx_size);
				bgfx::setIndexBuffer(&tib, elem_offset, pcmd->ElemCount);
				bgfx::submit(m_viewId, m_program);

				elem_offset += pcmd->ElemCount;
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
			.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
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
	}

	void destroy()
	{
		ImGui::Shutdown();

		bgfx::destroyUniform(s_tex);
		bgfx::destroyTexture(m_texture);
		bgfx::destroyProgram(m_program);

		m_allocator = NULL;
	}

	void beginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, int _width, int _height, char _inputChar, uint8_t _viewId)
	{
		m_viewId = _viewId;
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

#if defined(SCI_NAMESPACE) && 0
		bool opened = true;
		ImGuiScintilla("Scintilla Editor", &opened, ImVec2(640.0f, 480.0f) );
#endif // 0
	}

	void endFrame()
	{
		ImGui::Render();
	}

	bx::AllocatorI*     m_allocator;
	bgfx::VertexDecl    m_decl;
	bgfx::ProgramHandle m_program;
	bgfx::TextureHandle m_texture;
	bgfx::UniformHandle s_tex;
	int64_t m_last;
	int32_t m_lastScroll;
	uint8_t m_viewId;
};

static OcornutImguiContext s_ctx;

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
