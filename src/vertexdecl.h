/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_VERTEXDECL_H_HEADER_GUARD
#define BGFX_VERTEXDECL_H_HEADER_GUARD

#include <bgfx/bgfx.h>
#include <bx/readerwriter.h>

namespace bgfx
{
	///
	BGFX_SHARED_LIB_API void initAttribTypeSizeTable(RendererType::Enum _type);

	/// Returns attribute name.
	BGFX_SHARED_LIB_API const char* getAttribName(Attrib::Enum _attr);

	/// Dump vertex declaration into debug output.
	BGFX_SHARED_LIB_API void dump(const VertexDecl& _decl);

	///
	BGFX_SHARED_LIB_API Attrib::Enum idToAttrib(uint16_t id);

	///
	BGFX_SHARED_LIB_API uint16_t attribToId(Attrib::Enum _attr);

	///
	BGFX_SHARED_LIB_API AttribType::Enum idToAttribType(uint16_t id);

	///
	BGFX_SHARED_LIB_API int32_t write(bx::WriterI* _writer, const bgfx::VertexDecl& _decl, bx::Error* _err = NULL);

	///
	BGFX_SHARED_LIB_API int32_t read(bx::ReaderI* _reader, bgfx::VertexDecl& _decl, bx::Error* _err = NULL);

} // namespace bgfx

#endif // BGFX_VERTEXDECL_H_HEADER_GUARD
