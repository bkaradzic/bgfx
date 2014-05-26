/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_VERTEXDECL_H_HEADER_GUARD
#define BGFX_VERTEXDECL_H_HEADER_GUARD

#include <bgfx.h>

namespace bgfx
{
	///
	void initAttribTypeSizeTable(RendererType::Enum _type);

	/// Returns attribute name.
	const char* getAttribName(Attrib::Enum _attr);

	/// Dump vertex declaration into debug output.
	void dump(const VertexDecl& _decl);

} // namespace bgfx

#endif // BGFX_VERTEXDECL_H_HEADER_GUARD
