/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_CODEPAGE_H_HEADER_GUARD
#define BGFX_CODEPAGE_H_HEADER_GUARD

#include "bgfx_p.h"

namespace bgfx {

	class CodePage {
	public:
		CodePage(int id, const int32_t * codemap, int size) :
			m_codemap(codemap) , m_size(size), m_id(id) {}

		int index(int32_t unicode);
		static const char *utf8_decode(const char *o, int *val);
		static int cp437(int unicode);
		static int doublewidth(int unicode) {
			// todo: support multi-codepage
			return unicode > 127;
		}
		static const int CACHESIZE = 1024;
	private:
		static uint32_t s_cache[CACHESIZE];

		const int32_t * m_codemap;
		const int m_size;
		const int m_id;
	};

} // namespace bgfx

#endif // BGFX_CODEPAGE_H_HEADER_GUARD
