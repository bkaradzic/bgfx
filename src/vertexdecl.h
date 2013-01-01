/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx.h>

namespace bgfx
{
	/// Returns attribute name.
	const char* getAttribName(Attrib::Enum _attr);

	/// Dump vertex declaration into debug output.
	void dump(const VertexDecl& _decl);

} // namespace bgfx
