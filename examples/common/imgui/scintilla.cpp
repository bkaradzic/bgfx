/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#if defined(SCI_NAMESPACE)

#include <bx/bx.h>

#include <algorithm>
#include <map>

#if BX_PLATFORM_EMSCRIPTEN
#	include <compat/ctype.h>
#endif // BX_PLATFORM_EMSCRIPTEN

#include <string>
#include <vector>
#include <string.h>

#include "scintilla/include/Platform.h"
#include "scintilla/include/Scintilla.h"
#include "scintilla/include/ILexer.h"
#include "scintilla/include/SciLexer.h"
#include "scintilla/lexlib/LexerModule.h"
#include "scintilla/src/SplitVector.h"
#include "scintilla/src/Partitioning.h"
#include "scintilla/src/RunStyles.h"
#include "scintilla/src/Catalogue.h"
#include "scintilla/src/ContractionState.h"
#include "scintilla/src/CellBuffer.h"
#include "scintilla/src/KeyMap.h"
#include "scintilla/src/Indicator.h"
#include "scintilla/src/XPM.h"
#include "scintilla/src/LineMarker.h"
#include "scintilla/src/Style.h"
#include "scintilla/src/ViewStyle.h"
#include "scintilla/src/Decoration.h"
#include "scintilla/src/CharClassify.h"
#include "scintilla/src/CaseFolder.h"
#include "scintilla/src/Document.h"
#include "scintilla/src/Selection.h"
#include "scintilla/src/PositionCache.h"
#include "scintilla/src/EditModel.h"
#include "scintilla/src/MarginView.h"
#include "scintilla/src/EditView.h"
#include "scintilla/src/Editor.h"
#include "scintilla/src/AutoComplete.h"
#include "scintilla/src/CallTip.h"
#include "scintilla/src/ScintillaBase.h"

#include <bx/debug.h>
#include <bx/macros.h>
#include <bx/string.h>
#include <bx/uint32_t.h>

#define STBTT_DEF extern
#include <stb/stb_truetype.h>

#include "imgui.h"
#include "../bgfx_utils.h"
#include "scintilla.h"

#include "../entry/input.h"

#define IMGUI_NEW(type)         new (ImGui::MemAlloc(sizeof(type) ) ) type
#define IMGUI_DELETE(type, obj) reinterpret_cast<type*>(obj)->~type(), ImGui::MemFree(obj)

static void fillRectangle(Scintilla::PRectangle _rc, Scintilla::ColourDesired _color)
{
	const uint32_t abgr = (uint32_t)_color.AsLong();

	ImVec2 pos = ImGui::GetCursorScreenPos();

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->AddDrawCmd();
	drawList->AddRectFilled(
		  ImVec2(_rc.left  + pos.x, _rc.top    + pos.y)
		, ImVec2(_rc.right + pos.x, _rc.bottom + pos.y)
		, abgr
		);
}

static inline uint32_t makeRgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a = 0xFF)
{
	return a << 24 | b << 16 | g << 8 | r;
}

struct FontInt
{
	ImFont* m_font;
	float m_scale;
	float m_fontSize;
};

class SurfaceInt : public Scintilla::Surface
{
public:
	SurfaceInt()
	{
	}

	virtual ~SurfaceInt()
	{
	}

	virtual void Init(Scintilla::WindowID /*_wid*/) BX_OVERRIDE
	{
	}

	virtual void Init(Scintilla::SurfaceID /*_sid*/, Scintilla::WindowID /*_wid*/) BX_OVERRIDE
	{
	}

	virtual void InitPixMap(int /*_width*/, int /*_height*/, Scintilla::Surface* /*_surface*/, Scintilla::WindowID /*_wid*/) BX_OVERRIDE
	{
	}

	virtual void Release() BX_OVERRIDE
	{
	}

	virtual bool Initialised() BX_OVERRIDE
	{
		return true;
	}

	virtual void PenColour(Scintilla::ColourDesired /*_fore*/) BX_OVERRIDE
	{
	}

	virtual int LogPixelsY() BX_OVERRIDE
	{
		return 72;
	}

	virtual int DeviceHeightFont(int /*points*/) BX_OVERRIDE
	{
		return 1500;
	}

	virtual void MoveTo(int _x, int _y) BX_OVERRIDE
	{
		BX_UNUSED(_x, _y);
	}

	virtual void LineTo(int _x, int _y) BX_OVERRIDE
	{
		BX_UNUSED(_x, _y);
	}

	virtual void Polygon(Scintilla::Point *pts, int npts, Scintilla::ColourDesired fore, Scintilla::ColourDesired back) BX_OVERRIDE
	{
		BX_UNUSED(pts, npts, fore, back);
	}

	virtual void RectangleDraw(Scintilla::PRectangle rc, Scintilla::ColourDesired fore, Scintilla::ColourDesired back) BX_OVERRIDE
	{
		BX_UNUSED(fore);

		FillRectangle(rc, back);
	}

	virtual void FillRectangle(Scintilla::PRectangle rc, Scintilla::ColourDesired back) BX_OVERRIDE
	{
		fillRectangle(rc, back);
	}

	virtual void FillRectangle(Scintilla::PRectangle rc, Scintilla::Surface& surfacePattern) BX_OVERRIDE
	{
		BX_UNUSED(rc, surfacePattern);
	}

	virtual void RoundedRectangle(Scintilla::PRectangle rc, Scintilla::ColourDesired fore, Scintilla::ColourDesired back) BX_OVERRIDE
	{
		BX_UNUSED(rc, fore, back);
	}

	virtual void AlphaRectangle(Scintilla::PRectangle _rc, int /*_cornerSize*/, Scintilla::ColourDesired _fill, int _alphaFill, Scintilla::ColourDesired /*_outline*/, int /*_alphaOutline*/, int /*_flags*/) BX_OVERRIDE
	{
		unsigned int back = 0
			| (uint32_t)( (_fill.AsLong() & 0xffffff)
			| ( (_alphaFill & 0xff) << 24) )
			;

		FillRectangle(_rc, Scintilla::ColourDesired(back) );
	}


	virtual void DrawRGBAImage(Scintilla::PRectangle /*_rc*/, int /*_width*/, int /*_height*/, const unsigned char* /*_pixelsImage*/) BX_OVERRIDE
	{
	}

	virtual void Ellipse(Scintilla::PRectangle rc, Scintilla::ColourDesired fore, Scintilla::ColourDesired /*back*/) BX_OVERRIDE
	{
		FillRectangle(rc, fore);
	}

	virtual void Copy(Scintilla::PRectangle /*_rc*/, Scintilla::Point /*_from*/, Scintilla::Surface& /*_surfaceSource*/) BX_OVERRIDE
	{
	}

	virtual void DrawTextNoClip(Scintilla::PRectangle rc, Scintilla::Font& _font, Scintilla::XYPOSITION ybase, const char *s, int len, Scintilla::ColourDesired fore, Scintilla::ColourDesired back) BX_OVERRIDE
	{
		BX_UNUSED(back);
		DrawTextBase(rc, _font, ybase, s, len, fore);
	}

	virtual void DrawTextClipped(Scintilla::PRectangle rc, Scintilla::Font& _font, Scintilla::XYPOSITION ybase, const char *s, int len, Scintilla::ColourDesired fore, Scintilla::ColourDesired back) BX_OVERRIDE
	{
		BX_UNUSED(back);
		DrawTextBase(rc, _font, ybase, s, len, fore);
	}

	virtual void DrawTextTransparent(Scintilla::PRectangle rc, Scintilla::Font& _font, Scintilla::XYPOSITION ybase, const char *s, int len, Scintilla::ColourDesired fore) BX_OVERRIDE
	{
		DrawTextBase(rc, _font, ybase, s, len, fore);
	}

	virtual void MeasureWidths(Scintilla::Font& /*_font*/, const char* _str, int _len, Scintilla::XYPOSITION* _positions) BX_OVERRIDE
	{
		float position = 0;

		ImFont* imFont = ImGui::GetWindowFont();

		while (_len--)
		{
			position     += imFont->GetCharAdvance( (unsigned short)*_str++);
			*_positions++ = position;
		}
	}

	virtual Scintilla::XYPOSITION WidthText(Scintilla::Font& /*_font*/, const char* _str, int _len) BX_OVERRIDE
	{
		ImVec2 t = ImGui::CalcTextSize(_str, _str + _len);
		return t.x;
	}

	virtual Scintilla::XYPOSITION WidthChar(Scintilla::Font& _font, char ch) BX_OVERRIDE
	{
		FontInt* fi = (FontInt*)_font.GetID();
		return fi->m_font->GetCharAdvance( (unsigned int)ch) * fi->m_scale;
	}

	virtual Scintilla::XYPOSITION Ascent(Scintilla::Font& _font) BX_OVERRIDE
	{
		FontInt* fi = (FontInt*)_font.GetID();
		return fi->m_font->Ascent * fi->m_scale;
	}

	virtual Scintilla::XYPOSITION Descent(Scintilla::Font& _font) BX_OVERRIDE
	{
		FontInt* fi = (FontInt*)_font.GetID();
		return -fi->m_font->Descent * fi->m_scale;
	}

		virtual Scintilla::XYPOSITION InternalLeading(Scintilla::Font& /*_font*/) BX_OVERRIDE
	{
		return 0;
	}

	virtual Scintilla::XYPOSITION ExternalLeading(Scintilla::Font& /*_font*/) BX_OVERRIDE
	{
		return 0;
	}

	virtual Scintilla::XYPOSITION Height(Scintilla::Font& _font) BX_OVERRIDE
	{
		return Ascent(_font) + Descent(_font);
	}

	virtual Scintilla::XYPOSITION AverageCharWidth(Scintilla::Font& _font) BX_OVERRIDE
	{
		return WidthChar(_font, 'n');
	}

	virtual void SetClip(Scintilla::PRectangle /*_rc*/) BX_OVERRIDE
	{
	}

	virtual void FlushCachedState() BX_OVERRIDE
	{
	}

	virtual void SetUnicodeMode(bool /*_unicodeMode*/) BX_OVERRIDE
	{
	}

	virtual void SetDBCSMode(int /*_codePage*/) BX_OVERRIDE
	{
	}

private:
	void DrawTextBase(Scintilla::PRectangle _rc, Scintilla::Font& _font, float _ybase, const char* _str, int _len, Scintilla::ColourDesired _fore)
	{
		float xt = _rc.left;
		float yt = _ybase;

		uint32_t fore = (uint32_t)_fore.AsLong();
		FontInt* fi = (FontInt*)_font.GetID();

		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		drawList->AddText(fi->m_font
			, fi->m_fontSize
			, ImVec2(xt + pos.x, yt + pos.y - fi->m_fontSize)
			, fore
			, _str
			, _str + _len
			);
	}

	Scintilla::ColourDesired m_penColour;
};

struct WindowInt
{
	WindowInt()
		: m_show(false)
	{
	}

	Scintilla::PRectangle position;
	bool m_show;
};

WindowInt* AllocateWindowInt()
{
	return new WindowInt;
}

inline WindowInt* GetWindow(Scintilla::WindowID id)
{
	return (WindowInt*)id;
}

class ListBoxInt : public Scintilla::ListBox
{
public:
	ListBoxInt()
		: m_maxStrWidth(0)
		, m_lineHeight(10)
		, m_desiredVisibleRows(5)
		, m_aveCharWidth(8)
		, m_unicodeMode(false)
	{
	}

	~ListBoxInt()
	{
	}

	virtual void SetFont(Scintilla::Font& /*_font*/) BX_OVERRIDE
	{
	}

	virtual void Create(Scintilla::Window& /*_parent*/, int /*_ctrlID*/, Scintilla::Point _location, int _lineHeight, bool _unicodeMode, int /*_technology*/) BX_OVERRIDE
	{
		m_location    = _location;
		m_lineHeight  = _lineHeight;
		m_unicodeMode = _unicodeMode;
		m_maxStrWidth = 0;
		wid = Scintilla::WindowID(4);
	}

	virtual void SetAverageCharWidth(int width) BX_OVERRIDE
	{
		m_aveCharWidth = width;
	}

	virtual void SetVisibleRows(int rows) BX_OVERRIDE
	{
		m_desiredVisibleRows = rows;
	}

	virtual int GetVisibleRows() const BX_OVERRIDE
	{
		return m_desiredVisibleRows;
	}

	virtual Scintilla::PRectangle GetDesiredRect() BX_OVERRIDE
	{
		Scintilla::PRectangle rc;
		rc.top    = 0;
		rc.left   = 0;
		rc.right  = 350;
		rc.bottom = 140;
		return rc;
	}

	virtual int CaretFromEdge() BX_OVERRIDE
	{
		return 4 + 16;
	}

	virtual void Clear() BX_OVERRIDE
	{
	}

	virtual void Append(char* /*s*/, int /*type = -1*/) BX_OVERRIDE
	{
	}

	virtual int Length() BX_OVERRIDE
	{
		return 0;
	}

	virtual void Select(int /*n*/) BX_OVERRIDE
	{
	}

	virtual int GetSelection() BX_OVERRIDE
	{
		return 0;
	}

	virtual int Find(const char* /*prefix*/) BX_OVERRIDE
	{
		return 0;
	}

	virtual void GetValue(int /*n*/, char* value, int /*len*/) BX_OVERRIDE
	{
		value[0] = '\0';
	}

	virtual void RegisterImage(int /*type*/, const char* /*xpm_data*/) BX_OVERRIDE
	{
	}

	virtual void RegisterRGBAImage(int /*type*/, int /*width*/, int /*height*/, const unsigned char* /*pixelsImage*/) BX_OVERRIDE
	{
	}

	virtual void ClearRegisteredImages() BX_OVERRIDE
	{
	}

	virtual void SetDoubleClickAction(Scintilla::CallBackAction, void*) BX_OVERRIDE
	{
	}

	virtual void SetList(const char* /*list*/, char /*separator*/, char /*typesep*/) BX_OVERRIDE
	{
	}

private:
	Scintilla::Point m_location;
	size_t m_maxStrWidth;
	int    m_lineHeight;
	int    m_desiredVisibleRows;
	int    m_aveCharWidth;
	bool   m_unicodeMode;
};

struct Editor : public Scintilla::ScintillaBase
{
public:
	Editor()
		: m_width(0)
		, m_height(0)
		, m_searchResultIndication(0xff5A5A5A)
		, m_filteredSearchResultIndication(0xff5a5a5a)
		, m_occurrenceIndication(0xff5a5a5a)
		, m_writeOccurrenceIndication(0xff5a5a5a)
		, m_findScope(0xffddf0ff)
		, m_sourceHoverBackground(0xff000000)
		, m_singleLineComment(0xffa8a8a8)
		, m_multiLineComment(0xffa8a8a8)
		, m_commentTaskTag(0xffa8a8a8)
		, m_javadoc(0xffa8a8a8)
		, m_javadocLink(0xff548fa0)
		, m_javadocTag(0xffa8a8a8)
		, m_javadocKeyword(0xffea9c77)
		, m_class(0xfff9f9f9)
		, m_interface(0xfff9f9f9)
		, m_method(0xfff9f9f9)
		, m_methodDeclaration(0xfff9f9f9)
		, m_bracket(0xfff9f9f9)
		, m_number(0xfff9f9f9)
		, m_string(0xff76ba53)
		, m_operator(0xfff9f9f9)
		, m_keyword(0xffea9c77)
		, m_annotation(0xffa020f0)
		, m_staticMethod(0xfff9f9f9)
		, m_localVariable(0xff4b9ce9)
		, m_localVariableDeclaration(0xff4b9ce9)
		, m_field(0xff4b9ce9)
		, m_staticField(0xff4b9ce9)
		, m_staticFinalField(0xff4b9ce9)
		, m_deprecatedMember(0xfff9f9f9)
		, m_foreground(0xffffffff)
		, m_lineNumber(0xff00ffff)
	{
	}

	virtual ~Editor()
	{
	}

	virtual void Initialise() BX_OVERRIDE
	{
		wMain = AllocateWindowInt();

		ImGuiIO& io = ImGui::GetIO();
		wMain.SetPosition(Scintilla::PRectangle::FromInts(0, 0, int(io.DisplaySize.x), int(io.DisplaySize.y) ) );

		view.bufferedDraw = false;

		command(SCI_SETLEXER, SCLEX_CPP);
		command(SCI_SETSTYLEBITS, 7);

		const int   fontSize = 15;
		const char* fontName = "";

		setStyle(STYLE_DEFAULT, m_foreground, m_background, fontSize, fontName);
		command(SCI_STYLECLEARALL);

		setStyle(STYLE_INDENTGUIDE, 0xffc0c0c0, m_background, fontSize, fontName);
		setStyle(STYLE_BRACELIGHT, m_bracket, m_background, fontSize, fontName);
		setStyle(STYLE_BRACEBAD, m_bracket, m_background, fontSize, fontName);
		setStyle(STYLE_LINENUMBER, m_lineNumber, 0xd0333333, fontSize, fontName);

		setStyle(SCE_C_DEFAULT, m_foreground, m_background, fontSize, fontName);
		setStyle(SCE_C_STRING, m_string, m_background);
		setStyle(SCE_C_IDENTIFIER, m_method, m_background);
		setStyle(SCE_C_CHARACTER, m_string, m_background);
		setStyle(SCE_C_WORD, m_keyword, m_background);
		setStyle(SCE_C_WORD2, m_keyword, m_background);
		setStyle(SCE_C_GLOBALCLASS, m_class, m_background);
		setStyle(SCE_C_PREPROCESSOR, m_annotation, m_background);
		setStyle(SCE_C_NUMBER, m_number, m_background);
		setStyle(SCE_C_OPERATOR, m_operator, m_background);
		setStyle(SCE_C_COMMENT, m_multiLineComment, m_background);
		setStyle(SCE_C_COMMENTLINE, m_singleLineComment, m_background);
		setStyle(SCE_C_COMMENTDOC, m_multiLineComment, m_background);

		command(SCI_SETSELBACK, 1, m_background.AsLong() );
		command(SCI_SETCARETFORE, UINT32_MAX, 0);
		command(SCI_SETCARETLINEVISIBLE, 1);
		command(SCI_SETCARETLINEBACK, UINT32_MAX);
		command(SCI_SETCARETLINEBACKALPHA, 0x20);

		command(SCI_SETUSETABS, 1);
		command(SCI_SETTABWIDTH, 4);
		command(SCI_SETINDENTATIONGUIDES, SC_IV_REAL);

		command(SCI_MARKERSETBACK, 0, 0xff6a6a6a);
		command(SCI_MARKERSETFORE, 0, 0xff0000ff);

		command(SCI_SETMARGINWIDTHN, 0, 44);
		command(SCI_SETMARGINTYPEN, 1, SC_MARGIN_SYMBOL);
		command(SCI_SETMARGINMASKN, 1, ~SC_MASK_FOLDERS);
		command(SCI_RGBAIMAGESETSCALE, 100);
		command(SCI_SETMARGINWIDTHN, 1, 0);
		command(SCI_MARKERDEFINE, 0, SC_MARK_RGBAIMAGE);

		SetFocusState(true);
		CaretSetPeriod(0);
	}

	virtual void CreateCallTipWindow(Scintilla::PRectangle /*_rc*/) BX_OVERRIDE
	{
		if (!ct.wCallTip.Created() )
		{
			ct.wCallTip = AllocateWindowInt();
			ct.wDraw = ct.wCallTip;
		}
	}

	virtual void AddToPopUp(const char* /*_label*/, int /*_cmd*/, bool /*_enabled*/) BX_OVERRIDE
	{
	}

	void Resize(int /*_x*/, int /*_y*/, int _width, int _height)
	{
		m_width  = _width;
		m_height = _height;

		wMain.SetPosition(Scintilla::PRectangle::FromInts(0, 0, m_width, m_height) );
	}

	virtual void SetVerticalScrollPos() BX_OVERRIDE
	{
	}

	virtual void SetHorizontalScrollPos() BX_OVERRIDE
	{
		xOffset = 0;
	}

	virtual bool ModifyScrollBars(int /*nMax*/, int /*nPage*/) BX_OVERRIDE
	{
		return false;
	}

	void ClaimSelection()
	{
	}

	virtual void Copy() BX_OVERRIDE
	{
	}

	virtual void Paste() BX_OVERRIDE
	{
	}

	virtual void NotifyChange() BX_OVERRIDE
	{
	}

	virtual void NotifyParent(Scintilla::SCNotification /*scn*/) BX_OVERRIDE
	{
	}

	virtual void CopyToClipboard(const Scintilla::SelectionText& /*selectedText*/) BX_OVERRIDE
	{
	}


	virtual void SetMouseCapture(bool /*on*/) BX_OVERRIDE
	{
	}

	virtual bool HaveMouseCapture() BX_OVERRIDE
	{
		return false;
	}

	virtual sptr_t DefWndProc(unsigned int /*iMessage*/, uptr_t /*wParam*/, sptr_t /*lParam*/) BX_OVERRIDE
	{
		return 0;
	}

	intptr_t command(unsigned int _msg, uintptr_t _p0 = 0, intptr_t _p1 = 0)
	{
		return WndProc(_msg, _p0, _p1);
	}

	void draw()
	{
		ImVec2 cursorPos = ImGui::GetCursorPos();
		ImVec2 regionMax = ImGui::GetWindowContentRegionMax();
		ImVec2 size = ImVec2( regionMax.x - cursorPos.x - 32
							, regionMax.y - cursorPos.y
							);

		Resize(0, 0, (int)size.x, (int)size.y);

		uint8_t modifiers = inputGetModifiersState();
		const bool shift = 0 != (modifiers & (entry::Modifier::LeftShift | entry::Modifier::RightShift) );
		const bool ctrl  = 0 != (modifiers & (entry::Modifier::LeftCtrl  | entry::Modifier::RightCtrl ) );
		const bool alt   = 0 != (modifiers & (entry::Modifier::LeftAlt   | entry::Modifier::RightAlt  ) );

		if (ImGui::IsKeyPressed(entry::Key::Tab) )
		{
			Editor::KeyDown(SCK_TAB, shift, ctrl, alt);
		}
		else if (ImGui::IsKeyPressed(entry::Key::Left) )
		{
			Editor::KeyDown(SCK_LEFT, shift, ctrl, alt);
		}
		else if (ImGui::IsKeyPressed(entry::Key::Right) )
		{
			Editor::KeyDown(SCK_RIGHT, shift, ctrl, alt);
		}
		else if (ImGui::IsKeyPressed(entry::Key::Up) )
		{
			Editor::KeyDown(SCK_UP, shift, ctrl, alt);
		}
		else if (ImGui::IsKeyPressed(entry::Key::Down) )
		{
			Editor::KeyDown(SCK_DOWN, shift, ctrl, alt);
		}
		else if (ImGui::IsKeyPressed(entry::Key::PageUp) )
		{
			Editor::KeyDown(SCK_PRIOR, shift, ctrl, alt);
		}
		else if (ImGui::IsKeyPressed(entry::Key::PageDown) )
		{
			Editor::KeyDown(SCK_NEXT, shift, ctrl, alt);
		}
		else if (ImGui::IsKeyPressed(entry::Key::Home) )
		{
			Editor::KeyDown(SCK_HOME, shift, ctrl, alt);
		}
		else if (ImGui::IsKeyPressed(entry::Key::End) )
		{
			Editor::KeyDown(SCK_END, shift, ctrl, alt);
		}
		else if (ImGui::IsKeyPressed(entry::Key::Delete) )
		{
			Editor::KeyDown(SCK_DELETE, shift, ctrl, alt);
		}
		else if (ImGui::IsKeyPressed(entry::Key::Backspace) )
		{
			Editor::KeyDown(SCK_BACK, shift, ctrl, alt); inputGetChar();
		}
		else if (ImGui::IsKeyPressed(entry::Key::Return) )
		{
			Editor::KeyDown(SCK_RETURN, shift, ctrl, alt); inputGetChar();
		}
		else if (ImGui::IsKeyPressed(entry::Key::Esc) )
		{
			Editor::KeyDown(SCK_ESCAPE, shift, ctrl, alt);
		}
		else if (ctrl && ImGui::IsKeyPressed(entry::Key::KeyA) )
		{
			Editor::KeyDown('A', shift, ctrl, alt); inputGetChar();
		}
		else if (ctrl && ImGui::IsKeyPressed(entry::Key::KeyC) )
		{
			Editor::KeyDown('C', shift, ctrl, alt); inputGetChar();
		}
		else if (ctrl && ImGui::IsKeyPressed(entry::Key::KeyV) )
		{
			Editor::KeyDown('V', shift, ctrl, alt); inputGetChar();
		}
		else if (ctrl && ImGui::IsKeyPressed(entry::Key::KeyX) )
		{
			Editor::KeyDown('X', shift, ctrl, alt); inputGetChar();
		}
		else if (ctrl && ImGui::IsKeyPressed(entry::Key::KeyY) )
		{
			Editor::KeyDown('Y', shift, ctrl, alt); inputGetChar();
		}
		else if (ctrl && ImGui::IsKeyPressed(entry::Key::KeyZ) )
		{
			Editor::KeyDown('Z', shift, ctrl, alt);	inputGetChar();
		}
		else if (ctrl || alt)
		{
			// ignore...
		}
		else
		{
			for (const uint8_t* ch = inputGetChar(); NULL != ch; ch = inputGetChar() )
			{
				switch (*ch)
				{
				case '\b': Editor::KeyDown(SCK_BACK,   shift, ctrl, alt); break;
				case '\n': Editor::KeyDown(SCK_RETURN, shift, ctrl, alt); break;
				default:   Editor::AddCharUTF( (const char*)ch, 1);       break;
				}
			}
		}

		int32_t lineCount = int32_t(command(SCI_GETLINECOUNT) );
		int32_t firstVisibleLine = int32_t(command(SCI_GETFIRSTVISIBLELINE) );
		float fontHeight = ImGui::GetWindowFontSize();

		if (ImGui::IsMouseClicked(0) )
		{
			ImGuiIO& io = ImGui::GetIO();
			Scintilla::Point pt = Scintilla::Point::FromInts( (int)io.MouseClickedPos[0].x, (int)io.MouseClickedPos[0].y);

			ButtonDown(pt, (unsigned int)io.MouseDownDuration[0], false, false, false);
		}

		Tick();

		ImGui::BeginGroup();
			ImGui::BeginChild("##editor", ImVec2(size.x, size.y-20) );
				Scintilla::AutoSurface surfaceWindow(this);
				if (surfaceWindow)
				{
					Paint(surfaceWindow, GetClientRectangle() );
					surfaceWindow->Release();
				}
			ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("##scroll");
				ImGuiListClipper clipper;
				clipper.Begin(lineCount, fontHeight*2.0f);

				if (m_lastFirstVisibleLine != firstVisibleLine)
				{
					m_lastFirstVisibleLine = firstVisibleLine;
					ImGui::SetScrollY(firstVisibleLine * fontHeight*2.0f);
				}
				else if (firstVisibleLine != clipper.DisplayStart)
				{
					command(SCI_SETFIRSTVISIBLELINE, clipper.DisplayStart);
				}

				clipper.End();
			ImGui::EndChild();

		ImGui::EndGroup();
	}

	void setStyle(int style, Scintilla::ColourDesired fore, Scintilla::ColourDesired back = UINT32_MAX, int size = -1, const char* face = NULL)
	{
		command(SCI_STYLESETFORE, uptr_t(style), fore.AsLong() );
		command(SCI_STYLESETBACK, uptr_t(style), back.AsLong() );

		if (size >= 1)
		{
			command(SCI_STYLESETSIZE, uptr_t(style), size);
		}

		if (face)
		{
			command(SCI_STYLESETFONT, uptr_t(style), reinterpret_cast<sptr_t>(face) );
		}
	}

private:
	int m_width;
	int m_height;
	int m_lastFirstVisibleLine;

	Scintilla::ColourDesired m_searchResultIndication;
	Scintilla::ColourDesired m_filteredSearchResultIndication;
	Scintilla::ColourDesired m_occurrenceIndication;
	Scintilla::ColourDesired m_writeOccurrenceIndication;
	Scintilla::ColourDesired m_findScope;
	Scintilla::ColourDesired m_sourceHoverBackground;
	Scintilla::ColourDesired m_singleLineComment;
	Scintilla::ColourDesired m_multiLineComment;
	Scintilla::ColourDesired m_commentTaskTag;
	Scintilla::ColourDesired m_javadoc;
	Scintilla::ColourDesired m_javadocLink;
	Scintilla::ColourDesired m_javadocTag;
	Scintilla::ColourDesired m_javadocKeyword;
	Scintilla::ColourDesired m_class;
	Scintilla::ColourDesired m_interface;
	Scintilla::ColourDesired m_method;
	Scintilla::ColourDesired m_methodDeclaration;
	Scintilla::ColourDesired m_bracket;
	Scintilla::ColourDesired m_number;
	Scintilla::ColourDesired m_string;
	Scintilla::ColourDesired m_operator;
	Scintilla::ColourDesired m_keyword;
	Scintilla::ColourDesired m_annotation;
	Scintilla::ColourDesired m_staticMethod;
	Scintilla::ColourDesired m_localVariable;
	Scintilla::ColourDesired m_localVariableDeclaration;
	Scintilla::ColourDesired m_field;
	Scintilla::ColourDesired m_staticField;
	Scintilla::ColourDesired m_staticFinalField;
	Scintilla::ColourDesired m_deprecatedMember;
	Scintilla::ColourDesired m_background;
	Scintilla::ColourDesired m_currentLine;
	Scintilla::ColourDesired m_foreground;
	Scintilla::ColourDesired m_lineNumber;
	Scintilla::ColourDesired m_selectionBackground;
	Scintilla::ColourDesired m_selectionForeground;
};

ScintillaEditor* ScintillaEditor::create(int _width, int _height)
{
	Editor* editor = IMGUI_NEW(Editor);

	editor->Initialise();
	editor->Resize(0, 0, _width, _height);

	return reinterpret_cast<ScintillaEditor*>(editor);
}

void ScintillaEditor::destroy(ScintillaEditor* _scintilla)
{
	IMGUI_DELETE(Editor, _scintilla);
}

intptr_t ScintillaEditor::command(unsigned int _msg, uintptr_t _p0, intptr_t _p1)
{
	Editor* editor = reinterpret_cast<Editor*>(this);
	return editor->command(_msg, _p0, _p1);
}

void ScintillaEditor::draw()
{
	Editor* editor = reinterpret_cast<Editor*>(this);
	return editor->draw();
}

// Scintilla hooks
namespace Scintilla
{
	Font::Font()
		: fid(0)
	{
	}

	Font::~Font()
	{
	}

	void Font::Create(const FontParameters& fp)
	{
		FontInt* newFont = (FontInt*)ImGui::MemAlloc(sizeof(FontInt) );
		fid = newFont;
		newFont->m_font = ImGui::GetIO().Fonts->Fonts[0];
		newFont->m_fontSize = fp.size;
		newFont->m_scale = fp.size / newFont->m_font->FontSize;
	}

	void Font::Release()
	{
		if (fid)
		{
			ImGui::MemFree( (FontInt*)fid);
		}
	}

	ColourDesired Platform::Chrome()
	{
		return makeRgba(0xe0, 0xe0, 0xe0);
	}

	ColourDesired Platform::ChromeHighlight()
	{
		return makeRgba(0xff, 0xff, 0xff);
	}

	const char* Platform::DefaultFont()
	{
		return "";
	}

	int Platform::DefaultFontSize()
	{
		return 15;
	}

	unsigned int Platform::DoubleClickTime()
	{
		return 500;
	}

	bool Platform::MouseButtonBounce()
	{
		return true;
	}

	void Platform::Assert(const char* _error, const char* _filename, int _line)
	{
		DebugPrintf("%s(%d): %s", _filename, _line, _error);
	}

	int Platform::Minimum(int a, int b)
	{
		return (int)bx::uint32_imin(a, b);
	}

	int Platform::Maximum(int a, int b)
	{
		return (int)bx::uint32_imax(a, b);
	}

	int Platform::Clamp(int val, int minVal, int maxVal)
	{
		return (int)bx::uint32_iclamp(val, minVal, maxVal);
	}

	void Platform::DebugPrintf(const char* _format, ...)
	{
		char temp[8192];
		char* out = temp;
		va_list argList;
		va_start(argList, _format);
		int32_t len = bx::vsnprintf(out, sizeof(temp), _format, argList);
		if ( (int32_t)sizeof(temp) < len)
		{
			out = (char*)alloca(len+1);
			len = bx::vsnprintf(out, len, _format, argList);
		}
		va_end(argList);
		out[len] = '\0';
		bx::debugOutput(out);
	}

	Menu::Menu()
		: mid(0)
	{
	}

	void Menu::CreatePopUp()
	{
		Destroy();
		mid = MenuID(1);
	}

	void Menu::Destroy()
	{
		mid = 0;
	}

	void Menu::Show(Point /*_pt*/, Window& /*_w*/)
	{
		Destroy();
	}

	Surface* Surface::Allocate(int)
	{
		return IMGUI_NEW(SurfaceInt);
	}

	Window::~Window()
	{
	}

	void Window::Destroy()
	{
		if (wid)
		{
			Show(false);
			WindowInt* wi = GetWindow(wid);
			IMGUI_DELETE(WindowInt, wi);
		}

		wid = 0;
	}

	bool Window::HasFocus()
	{
		return true;
	}

	PRectangle Window::GetPosition()
	{
		if (0 == wid)
		{
			return PRectangle();
		}

		return GetWindow(wid)->position;
	}

	void Window::SetPosition(PRectangle rc)
	{
		GetWindow(wid)->position = rc;
	}

	void Window::SetPositionRelative(PRectangle _rc, Window /*_w*/)
	{
		SetPosition(_rc);
	}

	PRectangle Window::GetClientPosition()
	{
		if (0 == wid)
		{
			return PRectangle();
		}

		return GetWindow(wid)->position;
	}

	void Window::Show(bool _show)
	{
		if (0 != wid)
		{
			GetWindow(wid)->m_show = _show;
		}
	}

	void Window::InvalidateAll()
	{
	}

	void Window::InvalidateRectangle(PRectangle /*_rc*/)
	{
	}

	void Window::SetFont(Font& /*_font*/)
	{
	}

	void Window::SetCursor(Cursor /*_curs*/)
	{
		cursorLast = cursorText;
	}

	void Window::SetTitle(const char* /*_str*/)
	{
	}

	PRectangle Window::GetMonitorRect(Point /*_pt*/)
	{
		return PRectangle();
	}

	ListBox::ListBox()
	{
	}

	ListBox::~ListBox()
	{
	}

	ListBox* ListBox::Allocate()
	{
		return IMGUI_NEW(ListBoxInt);
	}

} // namespace Scintilla

ScintillaEditor* ImGuiScintilla(const char* _name, bool* _opened, const ImVec2& _size)
{
	ScintillaEditor* sci = NULL;

//	if (ImGui::Begin(_name, _opened, _size) )
	{
		ImGuiStorage* storage = ImGui::GetStateStorage();

		ImGuiID id = ImGui::GetID(_name);
		sci = (ScintillaEditor*)storage->GetVoidPtr(id);
		if (NULL == sci)
		{
			ImVec2 size = ImGui::GetWindowSize();
			sci = ScintillaEditor::create(size.x, size.y);
			storage->SetVoidPtr(id, (void*)sci);
		}

		sci->draw();
	}

//	ImGui::End();
	return sci;
}

#endif // defined(SCI_NAMESPACE)
