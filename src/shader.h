/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_SHADER_H
#define BGFX_SHADER_H

#include <bx/readerwriter.h>

namespace bgfx
{
	///
	void disassemble(bx::WriterI* _writer, bx::ReaderSeekerI* _reader, bx::Error* _err = NULL);

	///
	void disassemble(bx::WriterI* _writer, const void* _data, uint32_t _size, bx::Error* _err = NULL);

} // namespace bgfx

#endif // BGFX_SHADER_H
