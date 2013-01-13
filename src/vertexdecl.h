/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __VERTEXDECL_H__
#define __VERTEXDECL_H__

#include <bgfx.h>

namespace bgfx
{
	/// Returns attribute name.
	const char* getAttribName(Attrib::Enum _attr);

	/// Dump vertex declaration into debug output.
	void dump(const VertexDecl& _decl);

} // namespace bgfx

#endif // __VERTEXDECL_H__
