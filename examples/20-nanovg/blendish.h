/*
Blendish - Blender 2.5 UI based theming functions for NanoVG

Copyright (c) 2014 Leonard Ritter <leonard.ritter@duangle.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef BLENDISH_H
#define BLENDISH_H

#ifndef NANOVG_H
#error "nanovg.h must be included first."
#endif

#define fmaxf bx::fmax
#define fminf bx::fmin

#ifdef __cplusplus
extern "C" {
#endif

/*

Revision 3 (2014-07-08)

Summary
-------

Blendish is a small collection of drawing functions for NanoVG, designed to
replicate the look of the Blender 2.5+ User Interface. You can use these
functions to theme your UI library. Several metric constants for faithful
reproduction are also included.

Blendish supports the original Blender icon sheet; As the licensing of Blenders
icons is unclear, they are not included in Blendishes repository, but a SVG
template, "icons_template.svg" is provided, which you can use to build your own
icon sheet.

To use icons, you must first load the icon sheet using one of the
nvgCreateImage*() functions and then pass the image handle to bndSetIconImage();
otherwise, no icons will be drawn. See bndSetIconImage() for more information.

Blendish will not render text until a suitable UI font has been passed to
bndSetFont() has been called. See bndSetFont() for more information.


Drawbacks
---------

There is no support varying dpi resolutions yet. The library is hardcoded
to the equivalent of 72 dpi in the Blender system settings.

Support for label truncation is missing. Text rendering breaks when widgets are
too short to contain their labels.

Usage
-----

To use this header file in implementation mode, define BLENDISH_IMPLEMENTATION
before including blendish.h, otherwise the file will be in header-only mode.

*/

// if that typedef is provided elsewhere, you may define
// BLENDISH_NO_NVG_TYPEDEFS before including the header.
#ifndef BLENDISH_NO_NVG_TYPEDEFS
typedef struct NVGcontext NVGcontext;
typedef struct NVGcolor NVGcolor;
typedef struct NVGglyphPosition NVGglyphPosition;
#endif

// describes the theme used to draw a single widget or widget box;
// these values correspond to the same values that can be retrieved from
// the Theme panel in the Blender preferences
typedef struct BNDwidgetTheme {
    // color of widget box outline
    NVGcolor outlineColor;
    // color of widget item (meaning changes depending on class)
    NVGcolor itemColor;
    // fill color of widget box
    NVGcolor innerColor;
    // fill color of widget box when active
    NVGcolor innerSelectedColor;
    // color of text label
    NVGcolor textColor;
    // color of text label when active
    NVGcolor textSelectedColor;
    // delta modifier for upper part of gradient (-100 to 100)
    int shadeTop;
    // delta modifier for lower part of gradient (-100 to 100)
    int shadeDown;
} BNDwidgetTheme;

// describes the theme used to draw widgets
typedef struct BNDtheme {
    // the background color of panels and windows
    NVGcolor backgroundColor;
    // theme for labels
    BNDwidgetTheme regularTheme;
    // theme for tool buttons
    BNDwidgetTheme toolTheme;
    // theme for radio buttons
    BNDwidgetTheme radioTheme;
    // theme for text fields
    BNDwidgetTheme textFieldTheme;
    // theme for option buttons (checkboxes)
    BNDwidgetTheme optionTheme;
    // theme for choice buttons (comboboxes)
    // Blender calls them "menu buttons"
    BNDwidgetTheme choiceTheme;
    // theme for number fields
    BNDwidgetTheme numberFieldTheme;
    // theme for slider controls
    BNDwidgetTheme sliderTheme;
    // theme for scrollbars
    BNDwidgetTheme scrollBarTheme;
    // theme for tooltips
    BNDwidgetTheme tooltipTheme;
    // theme for menu backgrounds
    BNDwidgetTheme menuTheme;
    // theme for menu items
    BNDwidgetTheme menuItemTheme;
} BNDtheme;

// how text on a control is aligned
typedef enum BNDtextAlignment {
    BND_LEFT = 0,
    BND_CENTER,
} BNDtextAlignment;

// states altering the styling of a widget
typedef enum BNDwidgetState {
    // not interacting
    BND_DEFAULT = 0,
    // the mouse is hovering over the control
    BND_HOVER,
    // the widget is activated (pressed) or in an active state (toggled)
    BND_ACTIVE
} BNDwidgetState;

// flags indicating which corners are sharp (for grouping widgets)
typedef enum BNDcornerFlags {
    // all corners are round
    BND_CORNER_NONE = 0,
    // sharp top left corner
    BND_CORNER_TOP_LEFT = 1,
    // sharp top right corner
    BND_CORNER_TOP_RIGHT = 2,
    // sharp bottom right corner
    BND_CORNER_DOWN_RIGHT = 4,
    // sharp bottom left corner
    BND_CORNER_DOWN_LEFT = 8,
    // all corners are sharp;
    // you can invert a set of flags using ^= BND_CORNER_ALL
    BND_CORNER_ALL = 0xF,
    // top border is sharp
    BND_CORNER_TOP = 3,
    // bottom border is sharp
    BND_CORNER_DOWN = 0xC,
    // left border is sharp
    BND_CORNER_LEFT = 9,
    // right border is sharp
    BND_CORNER_RIGHT = 6
} BNDcornerFlags;

// build an icon ID from two coordinates into the icon sheet, where
// (0,0) designates the upper-leftmost icon, (1,0) the one right next to it,
// and so on.
#define BND_ICONID(x,y) ((x)|((y)<<8))

// default widget height
#define BND_WIDGET_HEIGHT 21
// default toolbutton width (if icon only)
#define BND_TOOL_WIDTH 20

// width of vertical scrollbar
#define BND_SCROLLBAR_WIDTH 13
// height of horizontal scrollbar
#define BND_SCROLLBAR_HEIGHT 14

////////////////////////////////////////////////////////////////////////////////

// set the current theme all widgets will be drawn with.
// the default Blender 2.6 theme is set by default.
void bndSetTheme(BNDtheme theme);

// Returns the currently set theme
const BNDtheme *bndGetTheme();

// designates an image handle as returned by nvgCreateImage*() as the themes'
// icon sheet. The icon sheet format must be compatible to Blender 2.6's icon
// sheet; the order of icons does not matter.
// A valid icon sheet is e.g. shown at
// http://wiki.blender.org/index.php/Dev:2.5/Doc/How_to/Add_an_icon
void bndSetIconImage(int image);

// designates an image handle as returned by nvgCreateFont*() as the themes'
// UI font. Blender's original UI font Droid Sans is perfectly suited and
// available here:
// https://svn.blender.org/svnroot/bf-blender/trunk/blender/release/datafiles/fonts/
void bndSetFont(int font);

////////////////////////////////////////////////////////////////////////////////

// High Level Functions
// --------------------
// Use these functions to draw themed widgets with your NVGcontext.

// Draw a label with its lower left origin at (x,y) and size of (w,h).
// if iconid >= 0, an icon will be added to the widget
// if label is not NULL, a label will be added to the widget
// widget looks best when height is BND_WIDGET_HEIGHT
void bndLabel(NVGcontext *ctx,
    float x, float y, float w, float h, int iconid, const char *label);

// Draw a tool button  with its lower left origin at (x,y) and size of (w,h),
// where flags is one or multiple flags from BNDcornerFlags and state denotes
// the widgets current UI state.
// if iconid >= 0, an icon will be added to the widget
// if label is not NULL, a label will be added to the widget
// widget looks best when height is BND_WIDGET_HEIGHT
void bndToolButton(NVGcontext *ctx,
    float x, float y, float w, float h, int flags, BNDwidgetState state,
    int iconid, const char *label);

// Draw a radio button with its lower left origin at (x,y) and size of (w,h),
// where flags is one or multiple flags from BNDcornerFlags and state denotes
// the widgets current UI state.
// if iconid >= 0, an icon will be added to the widget
// if label is not NULL, a label will be added to the widget
// widget looks best when height is BND_WIDGET_HEIGHT
void bndRadioButton(NVGcontext *ctx,
    float x, float y, float w, float h, int flags, BNDwidgetState state,
    int iconid, const char *label);

// Draw a text field with its lower left origin at (x,y) and size of (w,h),
// where flags is one or multiple flags from BNDcornerFlags and state denotes
// the widgets current UI state.
// if iconid >= 0, an icon will be added to the widget
// if text is not NULL, text will be printed to the widget
// cbegin must be >= 0 and <= strlen(text) and denotes the beginning of the caret
// cend must be >= cbegin and <= strlen(text) and denotes the end of the caret
// if cend < cbegin, then no caret will be drawn
// widget looks best when height is BND_WIDGET_HEIGHT
void bndTextField(NVGcontext *ctx,
    float x, float y, float w, float h, int flags, BNDwidgetState state,
    int iconid, const char *text, int cbegin, int cend);

// Draw an option button with its lower left origin at (x,y) and size of (w,h),
// where flags is one or multiple flags from BNDcornerFlags and state denotes
// the widgets current UI state.
// if label is not NULL, a label will be added to the widget
// widget looks best when height is BND_WIDGET_HEIGHT
void bndOptionButton(NVGcontext *ctx,
    float x, float y, float w, float h, BNDwidgetState state,
    const char *label);

// Draw a choice button with its lower left origin at (x,y) and size of (w,h),
// where flags is one or multiple flags from BNDcornerFlags and state denotes
// the widgets current UI state.
// if iconid >= 0, an icon will be added to the widget
// if label is not NULL, a label will be added to the widget
// widget looks best when height is BND_WIDGET_HEIGHT
void bndChoiceButton(NVGcontext *ctx,
    float x, float y, float w, float h, int flags, BNDwidgetState state,
    int iconid, const char *label);

// Draw a number field with its lower left origin at (x,y) and size of (w,h),
// where flags is one or multiple flags from BNDcornerFlags and state denotes
// the widgets current UI state.
// if label is not NULL, a label will be added to the widget
// if value is not NULL, a value will be added to the widget, along with
// a ":" separator
// widget looks best when height is BND_WIDGET_HEIGHT
void bndNumberField(NVGcontext *ctx,
    float x, float y, float w, float h, int flags, BNDwidgetState state,
    const char *label, const char *value);

// Draw slider control with its lower left origin at (x,y) and size of (w,h),
// where flags is one or multiple flags from BNDcornerFlags and state denotes
// the widgets current UI state.
// progress must be in the range 0..1 and controls the size of the slider bar
// if label is not NULL, a label will be added to the widget
// if value is not NULL, a value will be added to the widget, along with
// a ":" separator
// widget looks best when height is BND_WIDGET_HEIGHT
void bndSlider(NVGcontext *ctx,
    float x, float y, float w, float h, int flags, BNDwidgetState state,
    float progress, const char *label, const char *value);

// Draw scrollbar with its lower left origin at (x,y) and size of (w,h),
// where state denotes the widgets current UI state.
// offset is in the range 0..1 and controls the position of the scroll handle
// size is in the range 0..1 and controls the size of the scroll handle
// horizontal widget looks best when height is BND_SCROLLBAR_HEIGHT,
// vertical looks best when width is BND_SCROLLBAR_WIDTH
void bndScrollBar(NVGcontext *ctx,
    float x, float y, float w, float h, BNDwidgetState state,
    float offset, float size);

// Draw a menu background with its lower left origin at (x,y) and size of (w,h),
// where flags is one or multiple flags from BNDcornerFlags.
void bndMenuBackground(NVGcontext *ctx,
    float x, float y, float w, float h, int flags);

// Draw a menu label with its lower left origin at (x,y) and size of (w,h).
// if iconid >= 0, an icon will be added to the widget
// if label is not NULL, a label will be added to the widget
// widget looks best when height is BND_WIDGET_HEIGHT
void bndMenuLabel(NVGcontext *ctx,
    float x, float y, float w, float h, int iconid, const char *label);

// Draw a menu item with its lower left origin at (x,y) and size of (w,h),
// where state denotes the widgets current UI state.
// if iconid >= 0, an icon will be added to the widget
// if label is not NULL, a label will be added to the widget
// widget looks best when height is BND_WIDGET_HEIGHT
void bndMenuItem(NVGcontext *ctx,
    float x, float y, float w, float h, BNDwidgetState state,
    int iconid, const char *label);

// Draw a tooltip background with its lower left origin at (x,y) and size of (w,h)
void bndTooltipBackground(NVGcontext *ctx, float x, float y, float w, float h);

////////////////////////////////////////////////////////////////////////////////

// Low Level Functions
// -------------------
// these are part of the implementation detail and can be used to theme
// new kinds of controls in a similar fashion.

// make color transparent using the default alpha value
NVGcolor bndTransparent(NVGcolor color);

// offset a color by a given integer delta in the range -100 to 100
NVGcolor bndOffsetColor(NVGcolor color, int delta);

// assigns radius r to the four entries of array radiuses depending on whether
// the corner is marked as sharp or not; see BNDcornerFlags for possible
// flag values.
void bndSelectCorners(float *radiuses, float r, int flags);

// computes the upper and lower gradient colors for the inner box from a widget
// theme and the widgets state. If flipActive is set and the state is
// BND_ACTIVE, the upper and lower colors will be swapped.
void bndInnerColors(NVGcolor *shade_top, NVGcolor *shade_down,
    const BNDwidgetTheme *theme, BNDwidgetState state, int flipActive);

// computes the text color for a widget label from a widget theme and the
// widgets state.
NVGcolor bndTextColor(const BNDwidgetTheme *theme, BNDwidgetState state);

// computes the bounds of the scrollbar handle from the scrollbar size
// and the handles offset and size.
// offset is in the range 0..1 and defines the position of the scroll handle
// size is in the range 0..1 and defines the size of the scroll handle
void bndScrollHandleRect(float *x, float *y, float *w, float *h,
    float offset, float size);

// Add a rounded box path at position (x,y) with size (w,h) and a separate
// radius for each corner listed in clockwise order, so that cr0 = top left,
// cr1 = top right, cr2 = bottom right, cr3 = bottom left;
// this is a low level drawing function: the path must be stroked or filled
// to become visible.
void bndRoundedBox(NVGcontext *ctx, float x, float y, float w, float h,
    float cr0, float cr1, float cr2, float cr3);

// Draw a flat panel without any decorations at position (x,y) with size (w,h)
// and fills it with backgroundColor
void bndBackground(NVGcontext *ctx, float x, float y, float w, float h);

// Draw a lower inset for a rounded box at position (x,y) with size (w,h)
// that gives the impression the surface has been pushed in.
// cr2 and cr3 contain the radiuses of the bottom right and bottom left
// corners of the rounded box.
void bndBevelInset(NVGcontext *ctx, float x, float y, float w, float h,
    float cr2, float cr3);

// Draw an icon with (x,y) as its upper left coordinate; the iconid selects
// the icon from the sheet; use the BND_ICONID macro to build icon IDs.
void bndIcon(NVGcontext *ctx, float x, float y, int iconid);

// Draw a drop shadow around the rounded box at (x,y) with size (w,h) and
// radius r, with feather as its maximum range in pixels.
// No shadow will be painted inside the rounded box.
void bndDropShadow(NVGcontext *ctx, float x, float y, float w, float h,
    float r, float feather, float alpha);

// Draw the inner part of a widget box, with a gradient from shade_top to
// shade_down. If h>w, the gradient will be horizontal instead of
// vertical.
void bndInnerBox(NVGcontext *ctx, float x, float y, float w, float h,
    float cr0, float cr1, float cr2, float cr3,
    NVGcolor shade_top, NVGcolor shade_down);

// Draw the outline part of a widget box with the given color
void bndOutlineBox(NVGcontext *ctx, float x, float y, float w, float h,
    float cr0, float cr1, float cr2, float cr3, NVGcolor color);

// Draw an optional icon specified by <iconid> and an optional label with
// given alignment (BNDtextAlignment), fontsize and color within a widget box.
// if iconid is >= 0, an icon will be drawn and the labels remaining space
// will be adjusted.
// if label is not NULL, it will be drawn with the specified alignment, fontsize
// and color.
// if value is not NULL, label and value will be drawn with a ":" separator
// inbetween.
void bndIconLabelValue(NVGcontext *ctx, float x, float y, float w, float h,
    int iconid, NVGcolor color, int align, float fontsize, const char *label,
    const char *value);

// Draw an optional icon specified by <iconid>, an optional label and
// a caret with given fontsize and color within a widget box.
// if iconid is >= 0, an icon will be drawn and the labels remaining space
// will be adjusted.
// if label is not NULL, it will be drawn with the specified alignment, fontsize
// and color.
// cbegin must be >= 0 and <= strlen(text) and denotes the beginning of the caret
// cend must be >= cbegin and <= strlen(text) and denotes the end of the caret
// if cend < cbegin, then no caret will be drawn
void bndIconLabelCaret(NVGcontext *ctx, float x, float y, float w, float h,
    int iconid, NVGcolor color, float fontsize, const char *label,
    NVGcolor caretcolor, int cbegin, int cend);

// Draw a checkmark for an option box with the given upper left coordinates
// (ox,oy) with the specified color.
void bndCheck(NVGcontext *ctx, float ox, float oy, NVGcolor color);

// Draw a horizontal arrow for a number field with its center at (x,y) and
// size s; if s is negative, the arrow points to the left.
void bndArrow(NVGcontext *ctx, float x, float y, float s, NVGcolor color);

// Draw an up/down arrow for a choice box with its center at (x,y) and size s
void bndUpDownArrow(NVGcontext *ctx, float x, float y, float s, NVGcolor color);

#ifdef __cplusplus
};
#endif

#endif // BLENDISH_H

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifdef BLENDISH_IMPLEMENTATION

#include <memory.h>
#include <math.h>

#ifdef _MSC_VER
	#pragma warning (push)
	#pragma warning (disable: 4996) // Switch off security warnings
	#pragma warning (disable: 4100) // Switch off unreferenced formal parameter warnings
	#pragma warning (disable: 4244) // warning C4244: 'argument' : conversion from 'double' to 'float', possible loss of data
	#pragma warning (disable: 4305) // warning C4305: 'initializing' : truncation from 'double' to 'float'
	#ifdef __cplusplus
	#define BND_INLINE inline
	#else
	#define BND_INLINE
	#endif
#else
	#define BND_INLINE inline
#endif

////////////////////////////////////////////////////////////////////////////////

// default text size
#define BND_LABEL_FONT_SIZE 13

// default text padding in inner box
#define BND_PAD_LEFT 8
#define BND_PAD_RIGHT 8

// label: value separator string
#define BND_LABEL_SEPARATOR ": "

// alpha intensity of transparent items (0xa4)
#define BND_TRANSPARENT_ALPHA 0.643

// shade intensity of beveled insets
#define BND_BEVEL_SHADE 30
// shade intensity of hovered inner boxes
#define BND_HOVER_SHADE 30

// width of icon sheet
#define BND_ICON_SHEET_WIDTH 602
// height of icon sheet
#define BND_ICON_SHEET_HEIGHT 640
// gridsize of icon sheet in both dimensions
#define BND_ICON_SHEET_GRID 21
// offset of first icon tile relative to left border
#define BND_ICON_SHEET_OFFSET_X 5
// offset of first icon tile relative to top border
#define BND_ICON_SHEET_OFFSET_Y 10
// resolution of single icon
#define BND_ICON_SHEET_RES 16

// size of number field arrow
#define BND_NUMBER_ARROW_SIZE 4

// default text color
#define BND_COLOR_TEXT {{{ 0,0,0,1 }}}
// default highlighted text color
#define BND_COLOR_TEXT_SELECTED {{{ 1,1,1,1 }}}

// radius of tool button
#define BND_TOOL_RADIUS 4

// radius of option button
#define BND_OPTION_RADIUS 4
// width of option button checkbox
#define BND_OPTION_WIDTH 14
// height of option button checkbox
#define BND_OPTION_HEIGHT 15

// radius of text field
#define BND_TEXT_RADIUS 4

// radius of number button
#define BND_NUMBER_RADIUS 10

// radius of menu popup
#define BND_MENU_RADIUS 3
// feather of menu popup shadow
#define BND_SHADOW_FEATHER 12
// alpha of menu popup shadow
#define BND_SHADOW_ALPHA 0.5

// radius of scrollbar
#define BND_SCROLLBAR_RADIUS 7
// shade intensity of active scrollbar
#define BND_SCROLLBAR_ACTIVE_SHADE 15

// max glyphs for position testing
#define BND_MAX_GLYPHS 1024

////////////////////////////////////////////////////////////////////////////////

BND_INLINE float bnd_clamp(float v, float mn, float mx) {
    return (v > mx)?mx:(v < mn)?mn:v;
}

////////////////////////////////////////////////////////////////////////////////

// the initial theme
static BNDtheme bnd_theme = {
    // backgroundColor
    {{{ 0.447, 0.447, 0.447, 1.0 }}},
    // regularTheme
    {
        {{{ 0.098,0.098,0.098,1 }}}, // color_outline
        {{{ 0.098,0.098,0.098,1 }}}, // color_item
        {{{ 0.6,0.6,0.6,1 }}}, // color_inner
        {{{ 0.392,0.392,0.392,1 }}}, // color_inner_selected
        BND_COLOR_TEXT, // color_text
        BND_COLOR_TEXT_SELECTED, // color_text_selected
        0, // shade_top
        0, // shade_down
    },
    // toolTheme
    {
        {{{ 0.098,0.098,0.098,1 }}}, // color_outline
        {{{ 0.098,0.098,0.098,1 }}}, // color_item
        {{{ 0.6,0.6,0.6,1 }}}, // color_inner
        {{{ 0.392,0.392,0.392,1 }}}, // color_inner_selected
        BND_COLOR_TEXT, // color_text
        BND_COLOR_TEXT_SELECTED, // color_text_selected
        15, // shade_top
        -15, // shade_down
    },
    // radioTheme
    {
        {{{ 0,0,0,1 }}}, // color_outline
        {{{ 1,1,1,1 }}}, // color_item
        {{{ 0.275,0.275,0.275,1 }}}, // color_inner
        {{{ 0.337,0.502,0.761,1 }}}, // color_inner_selected
        BND_COLOR_TEXT_SELECTED, // color_text
        BND_COLOR_TEXT, // color_text_selected
        15, // shade_top
        -15, // shade_down
    },
    // textFieldTheme
    {
        {{{ 0.098,0.098,0.098,1 }}}, // color_outline
        {{{ 0.353, 0.353, 0.353,1 }}}, // color_item
        {{{ 0.6, 0.6, 0.6,1 }}}, // color_inner
        {{{ 0.6, 0.6, 0.6,1 }}}, // color_inner_selected
        BND_COLOR_TEXT, // color_text
        BND_COLOR_TEXT_SELECTED, // color_text_selected
        0, // shade_top
        25, // shade_down
    },
    // optionTheme
    {
        {{{ 0,0,0,1 }}}, // color_outline
        {{{ 1,1,1,1 }}}, // color_item
        {{{ 0.275,0.275,0.275,1 }}}, // color_inner
        {{{ 0.275,0.275,0.275,1 }}}, // color_inner_selected
        BND_COLOR_TEXT, // color_text
        BND_COLOR_TEXT_SELECTED, // color_text_selected
        15, // shade_top
        -15, // shade_down
    },
    // choiceTheme
    {
        {{{ 0,0,0,1 }}}, // color_outline
        {{{ 1,1,1,1 }}}, // color_item
        {{{ 0.275,0.275,0.275,1 }}}, // color_inner
        {{{ 0.275,0.275,0.275,1 }}}, // color_inner_selected
        BND_COLOR_TEXT_SELECTED, // color_text
        {{{ 0.8,0.8,0.8,1 }}}, // color_text_selected
        15, // shade_top
        -15, // shade_down
    },
    // numberFieldTheme
    {
        {{{ 0.098,0.098,0.098,1 }}}, // color_outline
        {{{ 0.353, 0.353, 0.353,1 }}}, // color_item
        {{{ 0.706, 0.706, 0.706,1 }}}, // color_inner
        {{{ 0.6, 0.6, 0.6,1 }}}, // color_inner_selected
        BND_COLOR_TEXT, // color_text
        BND_COLOR_TEXT_SELECTED, // color_text_selected
        -20, // shade_top
        0, // shade_down
    },
    // sliderTheme
    {
        {{{ 0.098,0.098,0.098,1 }}}, // color_outline
        {{{ 0.502,0.502,0.502,1 }}}, // color_item
        {{{ 0.706, 0.706, 0.706,1 }}}, // color_inner
        {{{ 0.6, 0.6, 0.6,1 }}}, // color_inner_selected
        BND_COLOR_TEXT, // color_text
        BND_COLOR_TEXT_SELECTED, // color_text_selected
        -20, // shade_top
        0, // shade_down
    },
    // scrollBarTheme
    {
        {{{ 0.196,0.196,0.196,1 }}}, // color_outline
        {{{ 0.502,0.502,0.502,1 }}}, // color_item
        {{{ 0.314, 0.314, 0.314,0.706 }}}, // color_inner
        {{{ 0.392, 0.392, 0.392,0.706 }}}, // color_inner_selected
        BND_COLOR_TEXT, // color_text
        BND_COLOR_TEXT_SELECTED, // color_text_selected
        5, // shade_top
        -5, // shade_down
    },
    // tooltipTheme
    {
        {{{ 0,0,0,1 }}}, // color_outline
        {{{ 0.392,0.392,0.392,1 }}}, // color_item
        {{{ 0.098, 0.098, 0.098, 0.902 }}}, // color_inner
        {{{ 0.176, 0.176, 0.176, 0.902 }}}, // color_inner_selected
        {{{ 0.627, 0.627, 0.627, 1 }}}, // color_text
        BND_COLOR_TEXT_SELECTED, // color_text_selected
        0, // shade_top
        0, // shade_down
    },
    // menuTheme
    {
        {{{ 0,0,0,1 }}}, // color_outline
        {{{ 0.392,0.392,0.392,1 }}}, // color_item
        {{{ 0.098, 0.098, 0.098, 0.902 }}}, // color_inner
        {{{ 0.176, 0.176, 0.176, 0.902 }}}, // color_inner_selected
        {{{ 0.627, 0.627, 0.627, 1 }}}, // color_text
        BND_COLOR_TEXT_SELECTED, // color_text_selected
        0, // shade_top
        0, // shade_down
    },
    // menuItemTheme
    {
        {{{ 0,0,0,1 }}}, // color_outline
        {{{ 0.675,0.675,0.675,0.502 }}}, // color_item
        {{{ 0,0,0,0 }}}, // color_inner
        {{{ 0.337,0.502,0.761,1 }}}, // color_inner_selected
        BND_COLOR_TEXT_SELECTED, // color_text
        BND_COLOR_TEXT, // color_text_selected
        38, // shade_top
        0, // shade_down
    },
};

////////////////////////////////////////////////////////////////////////////////

void bndSetTheme(BNDtheme theme) {
    bnd_theme = theme;
}

const BNDtheme *bndGetTheme() {
    return &bnd_theme;
}

// the handle to the image containing the icon sheet
static int bnd_icon_image = -1;

void bndSetIconImage(int image) {
    bnd_icon_image = image;
}

// the handle to the UI font
static int bnd_font = -1;

void bndSetFont(int font) {
    bnd_font = font;
}

////////////////////////////////////////////////////////////////////////////////

void bndLabel(NVGcontext *ctx,
    float x, float y, float w, float h, int iconid, const char *label) {
    bndIconLabelValue(ctx,x,y,w,h,iconid,
        bnd_theme.regularTheme.textColor, BND_LEFT,
        BND_LABEL_FONT_SIZE, label, NULL);
}

void bndToolButton(NVGcontext *ctx,
    float x, float y, float w, float h, int flags, BNDwidgetState state,
    int iconid, const char *label) {
    float cr[4];
    NVGcolor shade_top, shade_down;

    bndSelectCorners(cr, BND_TOOL_RADIUS, flags);
    bndBevelInset(ctx,x,y,w,h,cr[2],cr[3]);
    bndInnerColors(&shade_top, &shade_down, &bnd_theme.toolTheme, state, 1);
    bndInnerBox(ctx,x,y,w,h,cr[0],cr[1],cr[2],cr[3], shade_top, shade_down);
    bndOutlineBox(ctx,x,y,w,h,cr[0],cr[1],cr[2],cr[3],
        bndTransparent(bnd_theme.toolTheme.outlineColor));
    bndIconLabelValue(ctx,x,y,w,h,iconid,
        bndTextColor(&bnd_theme.toolTheme, state), BND_CENTER,
        BND_LABEL_FONT_SIZE, label, NULL);
}

void bndRadioButton(NVGcontext *ctx,
    float x, float y, float w, float h, int flags, BNDwidgetState state,
    int iconid, const char *label) {
    float cr[4];
    NVGcolor shade_top, shade_down;

    bndSelectCorners(cr, BND_OPTION_RADIUS, flags);
    bndBevelInset(ctx,x,y,w,h,cr[2],cr[3]);
    bndInnerColors(&shade_top, &shade_down, &bnd_theme.radioTheme, state, 1);
    bndInnerBox(ctx,x,y,w,h,cr[0],cr[1],cr[2],cr[3], shade_top, shade_down);
    bndOutlineBox(ctx,x,y,w,h,cr[0],cr[1],cr[2],cr[3],
        bndTransparent(bnd_theme.radioTheme.outlineColor));
    bndIconLabelValue(ctx,x,y,w,h,iconid,
        bndTextColor(&bnd_theme.radioTheme, state), BND_CENTER,
        BND_LABEL_FONT_SIZE, label, NULL);
}

void bndTextField(NVGcontext *ctx,
    float x, float y, float w, float h, int flags, BNDwidgetState state,
    int iconid, const char *text, int cbegin, int cend) {
    float cr[4];
    NVGcolor shade_top, shade_down;

    bndSelectCorners(cr, BND_TEXT_RADIUS, flags);
    bndBevelInset(ctx,x,y,w,h,cr[2],cr[3]);
    bndInnerColors(&shade_top, &shade_down, &bnd_theme.textFieldTheme, state, 0);
    bndInnerBox(ctx,x,y,w,h,cr[0],cr[1],cr[2],cr[3], shade_top, shade_down);
    bndOutlineBox(ctx,x,y,w,h,cr[0],cr[1],cr[2],cr[3],
        bndTransparent(bnd_theme.textFieldTheme.outlineColor));
    if (state != BND_ACTIVE) {
        cend = -1;
    }
    bndIconLabelCaret(ctx,x,y,w,h,iconid,
        bndTextColor(&bnd_theme.textFieldTheme, state), BND_LABEL_FONT_SIZE,
        text, bnd_theme.textFieldTheme.itemColor, cbegin, cend);
}

void bndOptionButton(NVGcontext *ctx,
    float x, float y, float w, float h, BNDwidgetState state,
    const char *label) {
    float ox, oy;
    NVGcolor shade_top, shade_down;

    ox = x;
    oy = y+h-BND_OPTION_HEIGHT-3;

    bndBevelInset(ctx,ox,oy,
        BND_OPTION_WIDTH,BND_OPTION_HEIGHT,
        BND_OPTION_RADIUS,BND_OPTION_RADIUS);
    bndInnerColors(&shade_top, &shade_down, &bnd_theme.optionTheme, state, 1);
    bndInnerBox(ctx,ox,oy,
        BND_OPTION_WIDTH,BND_OPTION_HEIGHT,
        BND_OPTION_RADIUS,BND_OPTION_RADIUS,BND_OPTION_RADIUS,BND_OPTION_RADIUS,
        shade_top, shade_down);
    bndOutlineBox(ctx,ox,oy,
        BND_OPTION_WIDTH,BND_OPTION_HEIGHT,
        BND_OPTION_RADIUS,BND_OPTION_RADIUS,BND_OPTION_RADIUS,BND_OPTION_RADIUS,
        bndTransparent(bnd_theme.optionTheme.outlineColor));
    if (state == BND_ACTIVE) {
        bndCheck(ctx,ox,oy, bndTransparent(bnd_theme.optionTheme.itemColor));
    }
    bndIconLabelValue(ctx,x+12,y,w-12,h,-1,
        bndTextColor(&bnd_theme.optionTheme, state), BND_LEFT,
        BND_LABEL_FONT_SIZE, label, NULL);
}

void bndChoiceButton(NVGcontext *ctx,
    float x, float y, float w, float h, int flags, BNDwidgetState state,
    int iconid, const char *label) {
    float cr[4];
    NVGcolor shade_top, shade_down;

    bndSelectCorners(cr, BND_OPTION_RADIUS, flags);
    bndBevelInset(ctx,x,y,w,h,cr[2],cr[3]);
    bndInnerColors(&shade_top, &shade_down, &bnd_theme.choiceTheme, state, 1);
    bndInnerBox(ctx,x,y,w,h,cr[0],cr[1],cr[2],cr[3], shade_top, shade_down);
    bndOutlineBox(ctx,x,y,w,h,cr[0],cr[1],cr[2],cr[3],
        bndTransparent(bnd_theme.choiceTheme.outlineColor));
    bndIconLabelValue(ctx,x,y,w,h,iconid,
        bndTextColor(&bnd_theme.choiceTheme, state), BND_LEFT,
        BND_LABEL_FONT_SIZE, label, NULL);
    bndUpDownArrow(ctx,x+w-10,y+10,5,
        bndTransparent(bnd_theme.choiceTheme.itemColor));
}

void bndNumberField(NVGcontext *ctx,
    float x, float y, float w, float h, int flags, BNDwidgetState state,
    const char *label, const char *value) {
    float cr[4];
    NVGcolor shade_top, shade_down;

    bndSelectCorners(cr, BND_NUMBER_RADIUS, flags);
    bndBevelInset(ctx,x,y,w,h,cr[2],cr[3]);
    bndInnerColors(&shade_top, &shade_down, &bnd_theme.numberFieldTheme, state, 0);
    bndInnerBox(ctx,x,y,w,h,cr[0],cr[1],cr[2],cr[3], shade_top, shade_down);
    bndOutlineBox(ctx,x,y,w,h,cr[0],cr[1],cr[2],cr[3],
        bndTransparent(bnd_theme.numberFieldTheme.outlineColor));
    bndIconLabelValue(ctx,x,y,w,h,-1,
        bndTextColor(&bnd_theme.numberFieldTheme, state), BND_CENTER,
        BND_LABEL_FONT_SIZE, label, value);
    bndArrow(ctx,x+8,y+10,-BND_NUMBER_ARROW_SIZE,
        bndTransparent(bnd_theme.numberFieldTheme.itemColor));
    bndArrow(ctx,x+w-8,y+10,BND_NUMBER_ARROW_SIZE,
        bndTransparent(bnd_theme.numberFieldTheme.itemColor));
}

void bndSlider(NVGcontext *ctx,
    float x, float y, float w, float h, int flags, BNDwidgetState state,
    float progress, const char *label, const char *value) {
    float cr[4];
    NVGcolor shade_top, shade_down;

    bndSelectCorners(cr, BND_NUMBER_RADIUS, flags);
    bndBevelInset(ctx,x,y,w,h,cr[2],cr[3]);
    bndInnerColors(&shade_top, &shade_down, &bnd_theme.sliderTheme, state, 0);
    bndInnerBox(ctx,x,y,w,h,cr[0],cr[1],cr[2],cr[3], shade_top, shade_down);

    if (state == BND_ACTIVE) {
        shade_top = bndOffsetColor(
            bnd_theme.sliderTheme.itemColor, bnd_theme.sliderTheme.shadeTop);
        shade_down = bndOffsetColor(
            bnd_theme.sliderTheme.itemColor, bnd_theme.sliderTheme.shadeDown);
    } else {
        shade_top = bndOffsetColor(
            bnd_theme.sliderTheme.itemColor, bnd_theme.sliderTheme.shadeDown);
        shade_down = bndOffsetColor(
            bnd_theme.sliderTheme.itemColor, bnd_theme.sliderTheme.shadeTop);
    }
    nvgScissor(ctx,x,y,8+(w-8)*bnd_clamp(progress,0,1),h);
    bndInnerBox(ctx,x,y,w,h,cr[0],cr[1],cr[2],cr[3], shade_top, shade_down);
    nvgResetScissor(ctx);

    bndOutlineBox(ctx,x,y,w,h,cr[0],cr[1],cr[2],cr[3],
        bndTransparent(bnd_theme.sliderTheme.outlineColor));
    bndIconLabelValue(ctx,x,y,w,h,-1,
        bndTextColor(&bnd_theme.sliderTheme, state), BND_CENTER,
        BND_LABEL_FONT_SIZE, label, value);
}

void bndScrollBar(NVGcontext *ctx,
    float x, float y, float w, float h, BNDwidgetState state,
    float offset, float size) {

    bndBevelInset(ctx,x,y,w,h,
        BND_SCROLLBAR_RADIUS, BND_SCROLLBAR_RADIUS);
    bndInnerBox(ctx,x,y,w,h,
        BND_SCROLLBAR_RADIUS,BND_SCROLLBAR_RADIUS,
        BND_SCROLLBAR_RADIUS,BND_SCROLLBAR_RADIUS,
        bndOffsetColor(
            bnd_theme.scrollBarTheme.innerColor, 3*bnd_theme.scrollBarTheme.shadeDown),
        bndOffsetColor(
            bnd_theme.scrollBarTheme.innerColor, 3*bnd_theme.scrollBarTheme.shadeTop));
    bndOutlineBox(ctx,x,y,w,h,
        BND_SCROLLBAR_RADIUS,BND_SCROLLBAR_RADIUS,
        BND_SCROLLBAR_RADIUS,BND_SCROLLBAR_RADIUS,
        bndTransparent(bnd_theme.scrollBarTheme.outlineColor));

    NVGcolor itemColor = bndOffsetColor(
        bnd_theme.scrollBarTheme.itemColor,
        (state == BND_ACTIVE)?BND_SCROLLBAR_ACTIVE_SHADE:0);

    bndScrollHandleRect(&x,&y,&w,&h,offset,size);

    bndInnerBox(ctx,x,y,w,h,
        BND_SCROLLBAR_RADIUS,BND_SCROLLBAR_RADIUS,
        BND_SCROLLBAR_RADIUS,BND_SCROLLBAR_RADIUS,
        bndOffsetColor(
            itemColor, 3*bnd_theme.scrollBarTheme.shadeTop),
        bndOffsetColor(
            itemColor, 3*bnd_theme.scrollBarTheme.shadeDown));
    bndOutlineBox(ctx,x,y,w,h,
        BND_SCROLLBAR_RADIUS,BND_SCROLLBAR_RADIUS,
        BND_SCROLLBAR_RADIUS,BND_SCROLLBAR_RADIUS,
        bndTransparent(bnd_theme.scrollBarTheme.outlineColor));
}

void bndMenuBackground(NVGcontext *ctx,
    float x, float y, float w, float h, int flags) {
    float cr[4];
    NVGcolor shade_top, shade_down;

    bndSelectCorners(cr, BND_MENU_RADIUS, flags);
    bndInnerColors(&shade_top, &shade_down, &bnd_theme.menuTheme,
        BND_DEFAULT, 0);
    bndInnerBox(ctx,x,y,w,h+1,cr[0],cr[1],cr[2],cr[3], shade_top, shade_down);
    bndOutlineBox(ctx,x,y,w,h+1,cr[0],cr[1],cr[2],cr[3],
        bndTransparent(bnd_theme.menuTheme.outlineColor));
    bndDropShadow(ctx,x,y,w,h,BND_MENU_RADIUS,
        BND_SHADOW_FEATHER,BND_SHADOW_ALPHA);
}

void bndTooltipBackground(NVGcontext *ctx, float x, float y, float w, float h) {
    NVGcolor shade_top, shade_down;

    bndInnerColors(&shade_top, &shade_down, &bnd_theme.tooltipTheme,
        BND_DEFAULT, 0);
    bndInnerBox(ctx,x,y,w,h+1,
        BND_MENU_RADIUS,BND_MENU_RADIUS,BND_MENU_RADIUS,BND_MENU_RADIUS,
        shade_top, shade_down);
    bndOutlineBox(ctx,x,y,w,h+1,
        BND_MENU_RADIUS,BND_MENU_RADIUS,BND_MENU_RADIUS,BND_MENU_RADIUS,
        bndTransparent(bnd_theme.tooltipTheme.outlineColor));
    bndDropShadow(ctx,x,y,w,h,BND_MENU_RADIUS,
        BND_SHADOW_FEATHER,BND_SHADOW_ALPHA);
}

void bndMenuLabel(NVGcontext *ctx,
    float x, float y, float w, float h, int iconid, const char *label) {
    bndIconLabelValue(ctx,x,y,w,h,iconid,
        bnd_theme.menuTheme.textColor, BND_LEFT,
        BND_LABEL_FONT_SIZE, label, NULL);
}

void bndMenuItem(NVGcontext *ctx,
    float x, float y, float w, float h, BNDwidgetState state,
    int iconid, const char *label) {
    if (state != BND_DEFAULT) {
        bndInnerBox(ctx,x,y,w,h,0,0,0,0,
            bndOffsetColor(bnd_theme.menuItemTheme.innerSelectedColor,
                bnd_theme.menuItemTheme.shadeTop),
            bndOffsetColor(bnd_theme.menuItemTheme.innerSelectedColor,
                bnd_theme.menuItemTheme.shadeDown));
        state = BND_ACTIVE;
    }
    bndIconLabelValue(ctx,x,y,w,h,iconid,
        bndTextColor(&bnd_theme.menuItemTheme, state), BND_LEFT,
        BND_LABEL_FONT_SIZE, label, NULL);
}

////////////////////////////////////////////////////////////////////////////////

void bndRoundedBox(NVGcontext *ctx, float x, float y, float w, float h,
    float cr0, float cr1, float cr2, float cr3) {
    float d;

    w = fmaxf(0, w);
    h = fmaxf(0, h);
    d = fminf(w, h);

    nvgMoveTo(ctx, x,y+h*0.5f);
    nvgArcTo(ctx, x,y, x+w,y, fminf(cr0, d/2));
    nvgArcTo(ctx, x+w,y, x+w,y+h, fminf(cr1, d/2));
    nvgArcTo(ctx, x+w,y+h, x,y+h, fminf(cr2, d/2));
    nvgArcTo(ctx, x,y+h, x,y, fminf(cr3, d/2));
    nvgClosePath(ctx);
}

NVGcolor bndTransparent(NVGcolor color) {
    color.a *= BND_TRANSPARENT_ALPHA;
    return color;
}

NVGcolor bndOffsetColor(NVGcolor color, int delta) {
    float offset = (float)delta / 255.0f;
    return delta?(
        nvgRGBAf(
            bnd_clamp(color.r+offset,0,1),
            bnd_clamp(color.g+offset,0,1),
            bnd_clamp(color.b+offset,0,1),
            color.a)
    ):color;
}

void bndBevelInset(NVGcontext *ctx, float x, float y, float w, float h,
    float cr2, float cr3) {
    float d;

    y -= 0.5f;
    d = fminf(w, h);
    cr2 = fminf(cr2, d/2);
    cr3 = fminf(cr3, d/2);

    nvgBeginPath(ctx);
    nvgMoveTo(ctx, x+w,y+h-cr2);
    nvgArcTo(ctx, x+w,y+h, x,y+h, cr2);
    nvgArcTo(ctx, x,y+h, x,y, cr3);

    NVGcolor bevelColor = bndOffsetColor(bnd_theme.backgroundColor,
        BND_BEVEL_SHADE);

    nvgStrokeWidth(ctx, 1);
    nvgStrokePaint(ctx,
        nvgLinearGradient(ctx,
            x,y+h-fmaxf(cr2,cr3)-1,
            x,y+h-1,
        nvgRGBAf(bevelColor.r, bevelColor.g, bevelColor.b, 0),
        bevelColor));
    nvgStroke(ctx);
}

void bndBackground(NVGcontext *ctx, float x, float y, float w, float h) {
    nvgBeginPath(ctx);
    nvgRect(ctx, x, y, w, h);
    nvgFillColor(ctx, bnd_theme.backgroundColor);
    nvgFill(ctx);
}

void bndIcon(NVGcontext *ctx, float x, float y, int iconid) {
    int ix, iy, u, v;
    if (bnd_icon_image < 0) return; // no icons loaded

    ix = iconid & 0xff;
    iy = (iconid>>8) & 0xff;
    u = BND_ICON_SHEET_OFFSET_X + ix*BND_ICON_SHEET_GRID;
    v = BND_ICON_SHEET_OFFSET_Y + iy*BND_ICON_SHEET_GRID;

    nvgBeginPath(ctx);
    nvgRect(ctx,x,y,BND_ICON_SHEET_RES,BND_ICON_SHEET_RES);
    nvgFillPaint(ctx,
        nvgImagePattern(ctx,x-u,y-v,
        BND_ICON_SHEET_WIDTH,
        BND_ICON_SHEET_HEIGHT,
        0,bnd_icon_image,0));
    nvgFill(ctx);
}

void bndDropShadow(NVGcontext *ctx, float x, float y, float w, float h,
    float r, float feather, float alpha) {

    nvgBeginPath(ctx);
    y += feather;
    h -= feather;

    nvgMoveTo(ctx, x-feather, y-feather);
    nvgLineTo(ctx, x, y-feather);
    nvgLineTo(ctx, x, y+h-feather);
    nvgArcTo(ctx, x,y+h,x+r,y+h,r);
    nvgArcTo(ctx, x+w,y+h,x+w,y+h-r,r);
    nvgLineTo(ctx, x+w, y-feather);
    nvgLineTo(ctx, x+w+feather, y-feather);
    nvgLineTo(ctx, x+w+feather, y+h+feather);
    nvgLineTo(ctx, x-feather, y+h+feather);
    nvgClosePath(ctx);

    nvgFillPaint(ctx, nvgBoxGradient(ctx,
        x - feather*0.5f,y - feather*0.5f,
        w + feather,h+feather,
        r+feather*0.5f,
        feather,
        nvgRGBAf(0,0,0,alpha*alpha),
        nvgRGBAf(0,0,0,0)));
    nvgFill(ctx);
}

void bndInnerBox(NVGcontext *ctx, float x, float y, float w, float h,
    float cr0, float cr1, float cr2, float cr3,
    NVGcolor shade_top, NVGcolor shade_down) {
    nvgBeginPath(ctx);
    bndRoundedBox(ctx,x+1,y+1,w-2,h-3,
        fmaxf(0,cr0-1),fmaxf(0,cr1-1),fmaxf(0,cr2-1),fmaxf(0,cr3-1));
    nvgFillPaint(ctx,((h-2)>w)?
        nvgLinearGradient(ctx,x,y,x+w,y,shade_top,shade_down):
        nvgLinearGradient(ctx,x,y,x,y+h,shade_top,shade_down));
    nvgFill(ctx);
}

void bndOutlineBox(NVGcontext *ctx, float x, float y, float w, float h,
    float cr0, float cr1, float cr2, float cr3, NVGcolor color) {
    nvgBeginPath(ctx);
    bndRoundedBox(ctx,x+0.5f,y+0.5f,w-1,h-2,cr0,cr1,cr2,cr3);
    nvgStrokeColor(ctx,color);
    nvgStrokeWidth(ctx,1);
    nvgStroke(ctx);
}

void bndSelectCorners(float *radiuses, float r, int flags) {
    radiuses[0] = (flags & BND_CORNER_TOP_LEFT)?0:r;
    radiuses[1] = (flags & BND_CORNER_TOP_RIGHT)?0:r;
    radiuses[2] = (flags & BND_CORNER_DOWN_RIGHT)?0:r;
    radiuses[3] = (flags & BND_CORNER_DOWN_LEFT)?0:r;
}

void bndInnerColors(
    NVGcolor *shade_top, NVGcolor *shade_down,
    const BNDwidgetTheme *theme, BNDwidgetState state, int flipActive) {

    switch(state) {
    default:
    case BND_DEFAULT: {
        *shade_top = bndOffsetColor(theme->innerColor, theme->shadeTop);
        *shade_down = bndOffsetColor(theme->innerColor, theme->shadeDown);
    } break;
    case BND_HOVER: {
        NVGcolor color = bndOffsetColor(theme->innerColor, BND_HOVER_SHADE);
        *shade_top = bndOffsetColor(color, theme->shadeTop);
        *shade_down = bndOffsetColor(color, theme->shadeDown);
    } break;
    case BND_ACTIVE: {
        *shade_top = bndOffsetColor(theme->innerSelectedColor,
            flipActive?theme->shadeDown:theme->shadeTop);
        *shade_down = bndOffsetColor(theme->innerSelectedColor,
            flipActive?theme->shadeTop:theme->shadeDown);
    } break;
    }
}

NVGcolor bndTextColor(const BNDwidgetTheme *theme, BNDwidgetState state) {
    return (state == BND_ACTIVE)?theme->textSelectedColor:theme->textColor;
}

void bndIconLabelValue(NVGcontext *ctx, float x, float y, float w, float h,
    int iconid, NVGcolor color, int align, float fontsize, const char *label,
    const char *value) {
    float pleft = BND_PAD_LEFT;
    if (label) {
        if (iconid >= 0) {
            bndIcon(ctx,x+4,y+2,iconid);
            pleft += BND_ICON_SHEET_RES;
        }

        if (bnd_font < 0) return;
        nvgFontFaceId(ctx, bnd_font);
        nvgFontSize(ctx, fontsize);
        nvgBeginPath(ctx);
        nvgFillColor(ctx, color);
        if (value) {
            float label_width = nvgTextBounds(ctx, 1, 1, label, NULL, NULL);
            float sep_width = nvgTextBounds(ctx, 1, 1,
                BND_LABEL_SEPARATOR, NULL, NULL);

            nvgTextAlign(ctx, NVG_ALIGN_LEFT|NVG_ALIGN_BASELINE);
            x += pleft;
            if (align == BND_CENTER) {
                float width = label_width + sep_width
                    + nvgTextBounds(ctx, 1, 1, value, NULL, NULL);
                x += ((w-BND_PAD_RIGHT-pleft)-width)*0.5f;
            }
            y += h-6;
            nvgText(ctx, x, y, label, NULL);
            x += label_width;
            nvgText(ctx, x, y, BND_LABEL_SEPARATOR, NULL);
            x += sep_width;
            nvgText(ctx, x, y, value, NULL);
        } else {
            nvgTextAlign(ctx,
                (align==BND_LEFT)?(NVG_ALIGN_LEFT|NVG_ALIGN_BASELINE):
                (NVG_ALIGN_CENTER|NVG_ALIGN_BASELINE));
            nvgTextBox(ctx,x+pleft,y+h-6,w-BND_PAD_RIGHT-pleft,label, NULL);
        }
    } else if (iconid >= 0) {
        bndIcon(ctx,x+2,y+2,iconid);
    }
}

void bndIconLabelCaret(NVGcontext *ctx, float x, float y, float w, float h,
    int iconid, NVGcolor color, float fontsize, const char *label,
    NVGcolor caretcolor, int cbegin, int cend) {
    float bounds[4];
    float pleft = BND_TEXT_RADIUS;
    if (!label) return;
    if (iconid >= 0) {
        bndIcon(ctx,x+4,y+2,iconid);
        pleft += BND_ICON_SHEET_RES;
    }

    if (bnd_font < 0) return;

    x+=pleft;
    y+=h-6;

    nvgFontFaceId(ctx, bnd_font);
    nvgFontSize(ctx, fontsize);
    nvgTextAlign(ctx, NVG_ALIGN_LEFT|NVG_ALIGN_BASELINE);

    if (cend >= cbegin) {
        float c0,c1;
        const char *cb;const char *ce;
        static NVGglyphPosition glyphs[BND_MAX_GLYPHS];
        int nglyphs = nvgTextGlyphPositions(
            ctx, x, y, label, label+cend+1, glyphs, BND_MAX_GLYPHS);
        c0=glyphs[0].x;
        c1=glyphs[nglyphs-1].x;
        cb = label+cbegin; ce = label+cend;
        // TODO: this is slow
        for (int i=0; i < nglyphs; ++i) {
            if (glyphs[i].str == cb)
                c0 = glyphs[i].x;
            if (glyphs[i].str == ce)
                c1 = glyphs[i].x;
        }

        nvgTextBounds(ctx,x,y,label,NULL, bounds);
        nvgBeginPath(ctx);
        if (cbegin == cend) {
            nvgFillColor(ctx, nvgRGBf(0.337,0.502,0.761));
            nvgRect(ctx, c0-1, bounds[1], 2, bounds[3]-bounds[1]);
        } else {
            nvgFillColor(ctx, caretcolor);
            nvgRect(ctx, c0-1, bounds[1], c1-c0+1, bounds[3]-bounds[1]);
        }
        nvgFill(ctx);
    }

    nvgBeginPath(ctx);
    nvgFillColor(ctx, color);
    nvgTextBox(ctx,x,y,w-BND_TEXT_RADIUS-pleft,label, NULL);
}

void bndCheck(NVGcontext *ctx, float ox, float oy, NVGcolor color) {
    nvgBeginPath(ctx);
    nvgStrokeWidth(ctx,2);
    nvgStrokeColor(ctx,color);
    nvgLineCap(ctx,NVG_BUTT);
    nvgLineJoin(ctx,NVG_MITER);
    nvgMoveTo(ctx,ox+4,oy+5);
    nvgLineTo(ctx,ox+7,oy+8);
    nvgLineTo(ctx,ox+14,oy+1);
    nvgStroke(ctx);
}

void bndArrow(NVGcontext *ctx, float x, float y, float s, NVGcolor color) {
    nvgBeginPath(ctx);
    nvgMoveTo(ctx,x,y);
    nvgLineTo(ctx,x-s,y+s);
    nvgLineTo(ctx,x-s,y-s);
    nvgClosePath(ctx);
    nvgFillColor(ctx,color);
    nvgFill(ctx);
}

void bndUpDownArrow(NVGcontext *ctx, float x, float y, float s, NVGcolor color) {
    float w;

    nvgBeginPath(ctx);
    w = 1.1f*s;
    nvgMoveTo(ctx,x,y-1);
    nvgLineTo(ctx,x+0.5*w,y-s-1);
    nvgLineTo(ctx,x+w,y-1);
    nvgClosePath(ctx);
    nvgMoveTo(ctx,x,y+1);
    nvgLineTo(ctx,x+0.5*w,y+s+1);
    nvgLineTo(ctx,x+w,y+1);
    nvgClosePath(ctx);
    nvgFillColor(ctx,color);
    nvgFill(ctx);
}

void bndScrollHandleRect(float *x, float *y, float *w, float *h,
    float offset, float size) {
    size = bnd_clamp(size,0,1);
    offset = bnd_clamp(offset,0,1);
    if ((*h) > (*w)) {
        float hs = fmaxf(size*(*h), (*w)+1);
        *y = (*y) + ((*h)-hs)*offset;
        *h = hs;
    } else {
        float ws = fmaxf(size*(*w), (*h)-1);
        *x = (*x) + ((*w)-ws)*offset;
        *w = ws;
    }
}

////////////////////////////////////////////////////////////////////////////////

#ifdef BND_INLINE
#undef BND_INLINE
#endif

#ifdef _MSC_VER
#	pragma warning (pop)
#endif

#endif // BLENDISH_IMPLEMENTATION
