/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_VERTEXDECL_H_HEADER_GUARD
#define BGFX_VERTEXDECL_H_HEADER_GUARD

#include <bgfx/bgfx.h>
#include <bx/readerwriter.h>

namespace bgfx
{
	///
	void initAttribTypeSizeTable(RendererType::Enum _type);

	///
	bool isFloat(AttribType::Enum _type);

	/// Returns attribute name.
	const char* getAttribName(Attrib::Enum _attr);

	///
	const char* getAttribNameShort(Attrib::Enum _attr);

	///
	Attrib::Enum idToAttrib(uint16_t id);

	///
	uint16_t attribToId(Attrib::Enum _attr);

	///
	AttribType::Enum idToAttribType(uint16_t id);

	///
	int32_t write(bx::WriterI* _writer, const bgfx::VertexLayout& _layout, bx::Error* _err = NULL);

	///
	int32_t read(bx::ReaderI* _reader, bgfx::VertexLayout& _layout, bx::Error* _err = NULL);

	///
	uint32_t weldVertices(void* _output, const VertexLayout& _layout, const void* _data, uint32_t _num, bool _index32, float _epsilon, bx::AllocatorI* _allocator);

} // namespace bgfx

#endif // BGFX_VERTEXDECL_H_HEADER_GUARD
