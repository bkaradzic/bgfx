/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_VIDEO_D3D11_H_HEADER_GUARD
#define BGFX_VIDEO_D3D11_H_HEADER_GUARD

struct ID3D11Device;
struct ID3D11DeviceContext;

namespace bgfx { namespace d3d11
{
	struct RendererContextD3D11;
	struct TextureD3D11;
	struct VideoDecoderD3D11;

	struct VideoBindingD3D11
	{
		ID3D11Device*        device;
		ID3D11DeviceContext* deviceCtx;
	};

	void initVideoDecoder(const VideoBindingD3D11& _binding);

	VideoDecoderD3D11* videoDecoderCreate(const VideoDecoderInit& _init, RendererContextD3D11* _renderer, uint16_t _width, uint16_t _height);
	void videoDecoderDestroy(VideoDecoderD3D11* _decoder);
	bool videoDecoderDecode(VideoDecoderD3D11* _decoder, const VideoDecoderFrame& _frame, TextureD3D11& _dst);

} } // namespace bgfx::d3d11

#endif // BGFX_VIDEO_D3D11_H_HEADER_GUARD
