/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __TEXT_BUFFER_MANAGER_H__
#define __TEXT_BUFFER_MANAGER_H__

#include "font_manager.h"

BGFX_HANDLE(TextBufferHandle);

/// type of vertex and index buffer to use with a TextBuffer
enum BufferType
{
	STATIC,
	DYNAMIC,
	TRANSIENT
};

/// special style effect (can be combined)
enum TextStyleFlags
{
	STYLE_NORMAL = 0,
	STYLE_OVERLINE = 1,
	STYLE_UNDERLINE = 1 << 1,
	STYLE_STRIKE_THROUGH = 1 << 2,
	STYLE_BACKGROUND = 1 << 3,
};

struct TextRectangle
{
	float width, height;
};

class TextBuffer;
class TextBufferManager
{
public:
	TextBufferManager(FontManager* _fontManager);
	~TextBufferManager();

	TextBufferHandle createTextBuffer(FontType _type, BufferType _bufferType);
	void destroyTextBuffer(TextBufferHandle _handle);
	void submitTextBuffer(TextBufferHandle _handle, uint8_t _id, int32_t _depth = 0);
	void submitTextBufferMask(TextBufferHandle _handle, uint32_t _viewMask, int32_t _depth = 0);

	void setStyle(TextBufferHandle _handle, uint32_t _flags = STYLE_NORMAL);
	void setTextColor(TextBufferHandle _handle, uint32_t _rgba = 0x000000FF);
	void setBackgroundColor(TextBufferHandle _handle, uint32_t _rgba = 0x000000FF);

	void setOverlineColor(TextBufferHandle _handle, uint32_t _rgba = 0x000000FF);
	void setUnderlineColor(TextBufferHandle _handle, uint32_t _rgba = 0x000000FF);
	void setStrikeThroughColor(TextBufferHandle _handle, uint32_t _rgba = 0x000000FF);

	void setPenPosition(TextBufferHandle _handle, float _x, float _y);

	/// append an ASCII/utf-8 string to the buffer using current pen position and color
	void appendText(TextBufferHandle _handle, FontHandle _fontHandle, const char* _string);

	/// append a wide char unicode string to the buffer using current pen position and color
	void appendText(TextBufferHandle _handle, FontHandle _fontHandle, const wchar_t* _string);

	/// Clear the text buffer and reset its state (pen/color)
	void clearTextBuffer(TextBufferHandle _handle);

	TextRectangle getRectangle(TextBufferHandle _handle) const;

	/// return the size of the text
	//Rectangle measureText(FontHandle fontHandle, const char * _string);
	//Rectangle measureText(FontHandle fontHandle, const wchar_t * _string);

private:

	struct BufferCache
	{
		uint16_t indexBufferHandle;
		uint16_t vertexBufferHandle;
		TextBuffer* textBuffer;
		BufferType bufferType;
		FontType fontType;
	};

	BufferCache* m_textBuffers;
	bx::HandleAlloc m_textBufferHandles;
	FontManager* m_fontManager;
	bgfx::VertexDecl m_vertexDecl;
	bgfx::UniformHandle u_texColor;
	bgfx::UniformHandle u_inverse_gamma;
	//shaders program
	bgfx::ProgramHandle m_basicProgram;
	bgfx::ProgramHandle m_distanceProgram;
	bgfx::ProgramHandle m_distanceSubpixelProgram;

	float m_height;
	float m_width;
};

#endif // __TEXT_BUFFER_MANAGER_H__
