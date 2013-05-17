// Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.

#ifndef __UTF8_H__
#define __UTF8_H__

#include <stdint.h>

#define UTF8_ACCEPT 0
#define UTF8_REJECT 1

uint32_t utf8_decode(uint32_t* _state, uint32_t* _codep, uint8_t _ch);

#endif // __UTF8_H_
