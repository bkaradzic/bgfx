/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_VERTEXDECL_H_HEADER_GUARD
#define BGFX_VERTEXDECL_H_HEADER_GUARD

#include <bgfx/bgfx.h>
#include <bx/readerwriter.h>

namespace bgfx
{
	///
	void initAttribTypeSizeTable(RendererType::Enum _type);

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

} // namespace bgfx

#endif // BGFX_VERTEXDECL_H_HEADER_GUARD
