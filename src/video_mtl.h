/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_VIDEO_MTL_H_HEADER_GUARD
#define BGFX_VIDEO_MTL_H_HEADER_GUARD

namespace MTL { class Device; class Texture; }

namespace bgfx { namespace mtl
{
	struct RendererContextMtl;
	struct VideoDecoderMtl;

	void initVideoDecoder();

	VideoDecoderMtl* videoDecoderCreate(const VideoDecoderInit& _init, RendererContextMtl* _renderer, MTL::Device* _device, uint16_t _width, uint16_t _height);
	void videoDecoderDestroy(VideoDecoderMtl* _decoder);
	bool videoDecoderDecode(VideoDecoderMtl* _decoder, const VideoDecoderFrame& _frame, MTL::Texture* _dst);

} } // namespace bgfx::mtl

#endif // BGFX_VIDEO_MTL_H_HEADER_GUARD
