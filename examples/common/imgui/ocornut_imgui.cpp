/*
 * Copyright 2014-2015 Daniel Collin. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx.h>
#include <bx/fpumath.h>
#include <ocornut-imgui/imgui.h>
#include "ocornut_imgui.h"
#include <stb/stb_image.c>

#include "vs_ocornut_imgui.bin.h"
#include "fs_ocornut_imgui.bin.h"

static bgfx::VertexDecl s_vertexDecl;
static bgfx::ProgramHandle s_imguiProgram;
static bgfx::TextureHandle s_textureId;
static bgfx::UniformHandle s_tex;
static bgfx::UniformHandle u_viewSize;
static uint8_t s_viewId;

static void imguiRender(ImDrawList** const cmd_lists, int cmd_lists_count)
{
	(void)cmd_lists;
	(void)cmd_lists_count;

	const float width  = ImGui::GetIO().DisplaySize.x;
	const float height = ImGui::GetIO().DisplaySize.y;

	float ortho[16];
	bx::mtxOrtho(ortho, 0.0f, width, height, 0.0f, -1.0f, 1.0f);

	bgfx::setViewTransform(0, NULL, ortho);

	// Render command lists

	for (int n = 0; n < cmd_lists_count; n++)
	{
		bgfx::TransientVertexBuffer tvb;

		uint32_t vtx_size = 0;

		const ImDrawList* cmd_list = cmd_lists[n];
		const ImDrawVert* vtx_buffer = cmd_list->vtx_buffer.begin();
		(void)vtx_buffer;

		const ImDrawCmd* pcmd_end_t = cmd_list->commands.end();

		for (const ImDrawCmd* pcmd = cmd_list->commands.begin(); pcmd != pcmd_end_t; pcmd++)
			vtx_size += (uint32_t)pcmd->vtx_count;

		bgfx::allocTransientVertexBuffer(&tvb, vtx_size, s_vertexDecl);

		ImDrawVert* verts = (ImDrawVert*)tvb.data;

		memcpy(verts, vtx_buffer, vtx_size * sizeof(ImDrawVert));

		uint32_t vtx_offset = 0;
		const ImDrawCmd* pcmd_end = cmd_list->commands.end();
		for (const ImDrawCmd* pcmd = cmd_list->commands.begin(); pcmd != pcmd_end; pcmd++)
		{
			bgfx::setState(0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
				| BGFX_STATE_MSAA);
			bgfx::setTexture(0, s_tex, s_textureId);
			bgfx::setVertexBuffer(&tvb, vtx_offset, pcmd->vtx_count);
			bgfx::setProgram(s_imguiProgram);
			bgfx::submit(s_viewId);

			vtx_offset += pcmd->vtx_count;
		}
	}
}

void IMGUI_setup(int _width, int _height, uint8_t _viewId)
{
	s_viewId = _viewId;
	const void* png_data;
	unsigned int png_size;
	ImGuiIO& io = ImGui::GetIO();

	io.DisplaySize = ImVec2((float)_width, (float)_height);
	io.DeltaTime = 1.0f / 60.0f;
	io.PixelCenterOffset = 0.0f;

	const bgfx::Memory* vs_imgui2;
	const bgfx::Memory* fs_imgui2;

	switch (bgfx::getRendererType())
	{
	case bgfx::RendererType::Direct3D9:
		vs_imgui2 = bgfx::makeRef(vs_ocornut_imgui_dx9, sizeof(vs_ocornut_imgui_dx9));
		fs_imgui2 = bgfx::makeRef(fs_ocornut_imgui_dx9, sizeof(fs_ocornut_imgui_dx9));
		break;

	case bgfx::RendererType::Direct3D11:
		vs_imgui2 = bgfx::makeRef(vs_ocornut_imgui_dx11, sizeof(vs_ocornut_imgui_dx11));
		fs_imgui2 = bgfx::makeRef(fs_ocornut_imgui_dx11, sizeof(fs_ocornut_imgui_dx11));
		break;

	default:
		vs_imgui2 = bgfx::makeRef(vs_ocornut_imgui_glsl, sizeof(vs_ocornut_imgui_glsl));
		fs_imgui2 = bgfx::makeRef(fs_ocornut_imgui_glsl, sizeof(fs_ocornut_imgui_glsl));
		break;
	}

	bgfx::ShaderHandle vsh;
	bgfx::ShaderHandle fsh;

	vsh = bgfx::createShader(vs_imgui2);
	fsh = bgfx::createShader(fs_imgui2);
	s_imguiProgram = bgfx::createProgram(vsh, fsh);
	bgfx::destroyShader(vsh);
	bgfx::destroyShader(fsh);

	s_vertexDecl
		.begin()
		.add(bgfx::Attrib::Position,  2, bgfx::AttribType::Float)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
		.end();

	u_viewSize = bgfx::createUniform("viewSize", bgfx::UniformType::Uniform2fv);
	s_tex = bgfx::createUniform("s_tex", bgfx::UniformType::Uniform1i);

	ImGui::GetDefaultFontData(NULL, NULL, &png_data, &png_size);
	int tex_x, tex_y, pitch, tex_comp;

	void* tex_data = stbi_load_from_memory((const unsigned char*)png_data, (int)png_size, &tex_x, &tex_y, &tex_comp, 0);

	pitch = tex_x * 4;

	const bgfx::Memory* mem = bgfx::alloc((uint32_t)(tex_y * pitch));
	memcpy(mem->data, tex_data, size_t(pitch * tex_y));

	s_textureId = bgfx::createTexture2D((uint16_t)tex_x, (uint16_t)tex_y, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_MIN_POINT | BGFX_TEXTURE_MAG_POINT, mem);

	stbi_image_free(tex_data);

	io.RenderDrawListsFn = imguiRender;
}

void IMGUI_updateSize(int width, int height)
{
	ImGuiIO& io = ImGui::GetIO();

	io.DisplaySize = ImVec2((float)width, (float)height);
	io.DeltaTime = 1.0f / 60.0f;
	io.PixelCenterOffset = 0.0f;
}

void IMGUI_preUpdate(float x, float y, int mouseLmb, int keyDown, int keyMod)
{
	(void)keyDown;
	(void)keyMod;
	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = 1.0f / 120.0f;    // TODO: Fix me
	io.MousePos = ImVec2(x, y);
	io.MouseDown[0] = !!mouseLmb;

	ImGui::NewFrame();
}

void IMGUI_setMouse(float x, float y, int mouseLmb)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2(x, y);
	io.MouseDown[0] = !!mouseLmb;
}

void IMGUI_setKeyDown(int key, int /*modifier*/)
{
	ImGuiIO& io = ImGui::GetIO();
//	assert(key >= 0 && key <= (int)sizeof_array(io.KeysDown));
	io.KeysDown[key] = true;
// 	io.KeyCtrl = !!(modifier & PDKEY_CTRL);
// 	io.KeyShift = !!(modifier & PDKEY_SHIFT);
}

void IMGUI_setKeyUp(int key, int /*modifier*/)
{
	ImGuiIO& io = ImGui::GetIO();
//	assert(key >= 0 && key <= (int)sizeof_array(io.KeysDown));
	io.KeysDown[key] = false;
// 	io.KeyCtrl = !!(modifier & PDKEY_CTRL);
// 	io.KeyShift = !!(modifier & PDKEY_SHIFT);
}

void IMGUI_postUpdate()
{
	ImGui::Render();
}
