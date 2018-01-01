/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "shaderc.h"

namespace bgfx
{
	bool compilePSSLShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer)
	{
		BX_UNUSED(_options, _version, _code, _writer);
		fprintf(stderr, "PSSL compiler is not supported.\n");
		return false;
	}

} // namespace bgfx
