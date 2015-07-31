/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef TEXT_BUFFER_MANAGER_H_HEADER_GUARD
#define TEXT_BUFFER_MANAGER_H_HEADER_GUARD

#include "font_manager.h"

BGFX_HANDLE(TextBufferHandle);

#define MAX_TEXT_BUFFER_COUNT 64

/// type of vertex and index buffer to use with a TextBuffer
struct BufferType
{
	enum Enum
	{
		Static,
		Dynamic,
		Transient,
	};
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

	TextBufferHandle createTextBuffer(uint32_t _type, BufferType::Enum _bufferType);
	void destroyTextBuffer(TextBufferHandle _handle);
	void submitTextBuffer(TextBufferHandle _handle, uint8_t _id, int32_t _depth = 0);

	void setStyle(TextBufferHandle _handle, uint32_t _flags = STYLE_NORMAL);
	void setTextColor(TextBufferHandle _handle, uint32_t _rgba = 0x000000FF);
	void setBackgroundColor(TextBufferHandle _handle, uint32_t _rgba = 0x000000FF);

	void setOverlineColor(TextBufferHandle _handle, uint32_t _rgba = 0x000000FF);
	void setUnderlineColor(TextBufferHandle _handle, uint32_t _rgba = 0x000000FF);
	void setStrikeThroughColor(TextBufferHandle _handle, uint32_t _rgba = 0x000000FF);

	void setPenPosition(TextBufferHandle _handle, float _x, float _y);

	/// Append an ASCII/utf-8 string to the buffer using current pen position and color.
	void appendText(TextBufferHandle _handle, FontHandle _fontHandle, const char* _string, const char* _end = NULL);

	/// Append a wide char unicode string to the buffer using current pen position and color.
	void appendText(TextBufferHandle _handle, FontHandle _fontHandle, const wchar_t* _string, const wchar_t* _end = NULL);
		
	/// Append a whole face of the atlas cube, mostly used for debugging and visualizing atlas.
	void appendAtlasFace(TextBufferHandle _handle, uint16_t _faceIndex);

	/// Clear the text buffer and reset its state (pen/color).
	void clearTextBuffer(TextBufferHandle _handle);
	
	/// Return the rectangular size of the current text buffer (including all its content).
	TextRectangle getRectangle(TextBufferHandle _handle) const;	
	
private:
	struct BufferCache
	{
		uint16_t indexBufferHandleIdx;
		uint16_t vertexBufferHandleIdx;
		TextBuffer* textBuffer;
		BufferType::Enum bufferType;
		uint32_t fontType;
	};

	BufferCache* m_textBuffers;
	bx::HandleAllocT<MAX_TEXT_BUFFER_COUNT> m_textBufferHandles;
	FontManager* m_fontManager;
	bgfx::VertexDecl m_vertexDecl;
	bgfx::UniformHandle s_texColor;
	bgfx::ProgramHandle m_basicProgram;
	bgfx::ProgramHandle m_distanceProgram;
	bgfx::ProgramHandle m_distanceSubpixelProgram;
};

#endif // TEXT_BUFFER_MANAGER_H_HEADER_GUARD
