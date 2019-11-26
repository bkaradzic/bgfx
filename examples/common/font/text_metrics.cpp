/*
* Copyright 2013 Jeremie Roy. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "text_metrics.h"
#include "utf8.h"

TextMetrics::TextMetrics(FontManager* _fontManager)
	: m_fontManager(_fontManager)
{
	clearText();
}

void TextMetrics::clearText()
{
	m_width = m_height = m_x = m_lineHeight = m_lineGap = 0;
}

void TextMetrics::appendText(FontHandle _fontHandle, const char* _string)
{
	const FontInfo& font = m_fontManager->getFontInfo(_fontHandle);

	if (font.lineGap > m_lineGap)
	{
		m_lineGap = font.lineGap;
	}

	if ( (font.ascender - font.descender) > m_lineHeight)
	{
		m_height -= m_lineHeight;
		m_lineHeight = font.ascender - font.descender;
		m_height += m_lineHeight;
	}

	CodePoint codepoint = 0;
	uint32_t state = 0;

	for (; *_string; ++_string)
	{
		if (!utf8_decode(&state, (uint32_t*)&codepoint, *_string) )
		{
			const GlyphInfo* glyph = m_fontManager->getGlyphInfo(_fontHandle, codepoint);
			if (NULL != glyph)
			{
				if (codepoint == L'\n')
				{
					m_height += m_lineGap + font.ascender - font.descender;
					m_lineGap = font.lineGap;
					m_lineHeight = font.ascender - font.descender;
					m_x = 0;
				}

				m_x += glyph->advance_x;
				if(m_x > m_width)
				{
					m_width = m_x;
				}
			}
			else
			{
				BX_CHECK(false, "Glyph not found");
			}
		}
	}

	BX_CHECK(state == UTF8_ACCEPT, "The string is not well-formed");
}

TextLineMetrics::TextLineMetrics(const FontInfo& _fontInfo)
{
	m_lineHeight = _fontInfo.ascender - _fontInfo.descender + _fontInfo.lineGap;
}

uint32_t TextLineMetrics::getLineCount(const bx::StringView& _str) const
{
	CodePoint codepoint = 0;
	uint32_t state = 0;
	uint32_t lineCount = 1;
	for (const char* ptr = _str.getPtr(); ptr != _str.getTerm(); ++ptr)
	{
		if (utf8_decode(&state, (uint32_t*)&codepoint, *ptr) == UTF8_ACCEPT)
		{
			if (codepoint == L'\n')
			{
				++lineCount;
			}
		}
	}

	BX_CHECK(state == UTF8_ACCEPT, "The string is not well-formed");
	return lineCount;
}

void TextLineMetrics::getSubText(const bx::StringView& _str, uint32_t _firstLine, uint32_t _lastLine, const char*& _begin, const char*& _end)
{
	CodePoint codepoint = 0;
	uint32_t state = 0;
	// y is bottom of a text line
	uint32_t currentLine = 0;

	const char* ptr = _str.getPtr();

	while (ptr != _str.getTerm()
	   && (currentLine < _firstLine) )
	{
		for (; ptr != _str.getTerm(); ++ptr)
		{
			if (utf8_decode(&state, (uint32_t*)&codepoint, *ptr) == UTF8_ACCEPT)
			{
				if (codepoint == L'\n')
				{
					++currentLine;
					++ptr;
					break;
				}
			}
		}
	}

	BX_CHECK(state == UTF8_ACCEPT, "The string is not well-formed");
	_begin = ptr;

	while (ptr != _str.getTerm()
	   && (currentLine < _lastLine) )
	{
		for (; ptr != _str.getTerm(); ++ptr)
		{
			if(utf8_decode(&state, (uint32_t*)&codepoint, *ptr) == UTF8_ACCEPT)
			{
				if(codepoint == L'\n')
				{
					++currentLine;
					++ptr;
					break;
				}
			}
		}
	}

	BX_CHECK(state == UTF8_ACCEPT, "The string is not well-formed");
	_end = ptr;
}
