/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "codepage.h"

namespace bgfx {

	uint32_t CodePage::s_cache[CodePage::CACHESIZE];

	static inline int hash_unicode(int32_t unicode)
	{
		return (unicode ^ (unicode >> 10)) % CodePage::CACHESIZE;
	}

	int CodePage::index(int unicode)
	{
		int hash = hash_unicode(unicode);
		uint32_t id = s_cache[hash];
		int pageid = id & 0xff;
		int codeindex = id >> 8;

		// lookup cache, it's thread safe.
		if (pageid == m_id && m_codemap[codeindex] == unicode)
			return codeindex;
		if (pageid == NONEXIST_ID && codeindex == unicode)
			return -1;

		// cache miss, use binary search
		int begin = 0, end = m_size;
		while(begin < end) {
			int mid = (begin + end)/2;
			int u = m_codemap[mid];
			if (u == unicode) {
				// update cache, it's thread safe.
				s_cache[hash] = mid << 8 | m_id;
				return mid;
			} else if (u < unicode) {
				begin = mid + 1;
			} else {
				end = mid;
			}
		}
		return -1;
	}

	int CodePage::prefetch(int unicode)
	{
		int hash = hash_unicode(unicode);
		uint32_t id = s_cache[hash];
		int pageid = id & 0xff;
		int codeindex = id >> 8;
		if (pageid == NONEXIST_ID && codeindex == unicode) {
			return -1;
		}
		return pageid;
	}

	void CodePage::mark_nonexist(int unicode)
	{
		int hash = hash_unicode(unicode);
		s_cache[hash] = (uint32_t)(unicode << 8) | NONEXIST_ID;
	}

	const char * CodePage::utf8_decode(const char *o, int *val)
	{
		const uint8_t *s = (const uint8_t *)o;
		uint8_t c = s[0];
		int res = 0;  // final result

		int count = 0;  // to count number of continuation bytes
		while (c & 0x40) {  // still have continuation bytes?
			int cc = s[++count];  // read next byte
			if ((cc & 0xC0) != 0x80) { // not a continuation byte?
				return NULL;  // invalid utf8 byte sequence
			}
			res = (res << 6) | (cc & 0x3F);  // add lower 6 bits from cont. byte
			c <<= 1;  // to test next bit
		}
		res |= ((c & 0x7F) << (count * 5));  // add first byte
		s += count;  // skip continuation bytes read
		*val = res;
		return (const char *)s;  // +1 to include first byte
	}

	int CodePage::cp437(int unicode)
	{
		static const int cp437_unicode[] = {
			0x00a0,0x00a1,0x00a2,0x00a3,0x00a5,0x00aa,0x00ab,0x00ac,0x00b0,0x00b1,0x00b2,0x00b5,0x00b7,0x00ba,0x00bb,0x00bc,
			0x00bd,0x00bf,0x00c4,0x00c5,0x00c6,0x00c7,0x00c9,0x00d1,0x00d6,0x00dc,0x00df,0x00e0,0x00e1,0x00e2,0x00e4,0x00e5,
			0x00e6,0x00e7,0x00e8,0x00e9,0x00ea,0x00eb,0x00ec,0x00ed,0x00ee,0x00ef,0x00f1,0x00f2,0x00f3,0x00f4,0x00f6,0x00f7,
			0x00f9,0x00fa,0x00fb,0x00fc,0x00ff,0x0192,0x0393,0x0398,0x03a3,0x03a6,0x03a9,0x03b1,0x03b4,0x03b5,0x03c0,0x03c3,
			0x03c4,0x03c6,0x207f,0x20a7,0x2219,0x221a,0x221e,0x2229,0x2248,0x2261,0x2264,0x2265,0x2310,0x2320,0x2321,0x2500,
			0x2502,0x250c,0x2510,0x2514,0x2518,0x251c,0x2524,0x252c,0x2534,0x253c,0x2550,0x2551,0x2552,0x2553,0x2554,0x2555,
			0x2556,0x2557,0x2558,0x2559,0x255a,0x255b,0x255c,0x255d,0x255e,0x255f,0x2560,0x2561,0x2562,0x2563,0x2564,0x2565,
			0x2566,0x2567,0x2568,0x2569,0x256a,0x256b,0x256c,0x2580,0x2584,0x2588,0x258c,0x2590,0x2591,0x2592,0x2593,0x25a0,
		};
		static const uint8_t cp437_index[] = {
			255,173,155,156,157,166,174,170,248,241,253,230,250,167,175,172,
			171,168,142,143,146,128,144,165,153,154,225,133,160,131,132,134,
			145,135,138,130,136,137,141,161,140,139,164,149,162,147,148,246,
			151,163,150,129,152,159,226,233,228,232,234,224,235,238,227,229,
			231,237,252,158,249,251,236,239,247,240,243,242,169,244,245,196,
			179,218,191,192,217,195,180,194,193,197,205,186,213,214,201,184,
			183,187,212,211,200,190,189,188,198,199,204,181,182,185,209,210,
			203,207,208,202,216,215,206,223,220,219,221,222,176,177,178,254,
		};
		static CodePage s_cp437(0, cp437_unicode, 128);

		if (unicode > cp437_unicode[127])
			return 0;
		int index = s_cp437.index(unicode);
		if (index < 0)
			return 0;
		return cp437_index[index];
	}
}