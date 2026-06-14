/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_VIDEO_D3D12_H_HEADER_GUARD
#define BGFX_VIDEO_D3D12_H_HEADER_GUARD

struct ID3D12Device;
struct ID3D12RootSignature;
struct ID3D12DescriptorHeap;
struct ID3D12CommandQueue;

namespace bgfx { namespace d3d12
{
	struct RendererContextD3D12;
	struct TextureD3D12;
	struct VideoDecoderD3D12;

	struct VideoBindingD3D12
	{
		ID3D12Device*         device;
		ID3D12RootSignature*  computeRootSignature;
		ID3D12DescriptorHeap* samplerHeap;
		ID3D12CommandQueue*   commandQueue;
		uint16_t              vendorId;
	};

	void initVideoDecoder(const VideoBindingD3D12& _binding);

	VideoDecoderD3D12* videoDecoderCreate(const VideoDecoderInit& _init, RendererContextD3D12* _renderer, uint16_t _width, uint16_t _height);
	void videoDecoderDestroy(VideoDecoderD3D12* _decoder);
	bool videoDecoderDecode(VideoDecoderD3D12* _decoder, const VideoDecoderFrame& _frame, TextureD3D12& _dst);

} } // namespace bgfx::d3d12

#endif // BGFX_VIDEO_D3D12_H_HEADER_GUARD
