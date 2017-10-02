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
		CodePage(int id, const int * codemap, int size) :
			m_codemap(codemap) , m_size(size), m_id(id) {}

		int index(int unicode);
		static const char *utf8_decode(const char *o, int *val);
		static int cp437(int unicode);
		static int doublewidth(int unicode) {
			// todo: support multi-codepage
			return unicode > 127;
		}
		static int prefetch(int unicode);
		static void mark_nonexist(int unicode);
		static const int CACHESIZE = 1024;
		void init(int id) { m_id = id; }
	private:
		static const int NONEXIST_ID = 255;
		static uint32_t s_cache[CACHESIZE];

		const int * m_codemap;
		const int m_size;
		int m_id;
	};

} // namespace bgfx

#endif // BGFX_CODEPAGE_H_HEADER_GUARD
