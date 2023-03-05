/*
 * Copyright 2011-2023 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "shaderc.h"

namespace bgfx
{
	bool compilePSSLShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer, bx::WriterI* _messages)
	{
		BX_UNUSED(_options, _version, _code, _writer);
		bx::Error messageErr;
		bx::write(_messages, &messageErr, "PSSL compiler is not supported.\n");
		return false;
	}

	const char* getPsslPreamble()
	{
		return "";
	}

} // namespace bgfx
