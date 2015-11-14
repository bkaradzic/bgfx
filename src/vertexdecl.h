/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
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

	/// Dump vertex declaration into debug output.
	void dump(const VertexDecl& _decl);

	///
	Attrib::Enum idToAttrib(uint16_t id);

	///
	uint16_t attribToId(Attrib::Enum _attr);

	///
	AttribType::Enum idToAttribType(uint16_t id);

	///
	int32_t write(bx::WriterI* _writer, const bgfx::VertexDecl& _decl);

	///
	int32_t read(bx::ReaderI* _reader, bgfx::VertexDecl& _decl);

} // namespace bgfx

#endif // BGFX_VERTEXDECL_H_HEADER_GUARD
