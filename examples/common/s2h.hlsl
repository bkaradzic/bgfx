//////////////////////////////////////////////////////////////////////////
//   Shader To Human (S2H) - HLSL/GLSL library for debugging shaders    //
//  Copyright (c) 2024-2025 Electronic Arts Inc.  All rights reserved.  //
//////////////////////////////////////////////////////////////////////////

// pixel shader or compute shader looping through all pixels

// Example:
// #include "s2h/s2h.hlsl"
// {
//   ContextGather ui;
//   // pxPos is the integer pixel position + 0.5f (pixel centered)
//   s2h_init(ui, pxPos + 0.5f);	  // either this (CS)
//	 s2h_init(ui, input.position.xy); // or that (PS / FS)
//   // print AB 
//   s2h_printTxt(ui, _A, _B);
//   // background or former color in linear
//   float4 linearBackground = float4(0.1f, 0.1f, 0.1f, 1);
//   // Note: ui.dstColor is premultiplied
//   float4 linearColor = linearBackground * (1.0f - ui.dstColor.a) + ui.dstColor;
//   // for correct AntiAliasing 
//   srgbColor = float4(s2h_accurateLinearToSRGB(linearColor.rgb), linearColor.a);
// }

#ifndef S2H_INCLUDE
#define S2H_INCLUDE

// Any potentially API breaking update we should increase the version by 1 allowing other code to adapt to S2H.
#define S2H_VERSION 14

// documentation:
struct ContextGather
{
	// in pixels, no fractional part (half pixel offset)
	float2 pxCursor;
	// 1/2/3/4
	float scale;
	// .xy:-100,-100 if not yet set, .xy:absolutePos, z:leftMouse 0/1, w:rightMouse 0/1, no fractional part (half pixel offset)
	float4 mouseInput;

	// window left top, no fractional part (half pixel offset), set by s2h_setPos(), used by s2h_printLF()
	float pxLeftX;
	// in pixels, no fractional part (half pixel offset), set by s2h_init()
	float2 pxPos;
	// premultiplied RGBA, alpha 1 is assumed to be opaque, don't init with a color or s2h_button() will not work
	float4 dstColor;

	//

	// RGBA, alpha 1 is assumed to be opaque, s2h_progress()
	float4 textColor;
	// for s2h_frame()
	float4 frameFillColor;
	// for s2h_frame()
	float4 frameBorderColor;
	// for s2h_button(), s2h_checkbox(), s2h_radiobutton, s2h_progress(), s2h_sliderFloat()
	float4 buttonColor;
	//
	float lineWidth;

	// private ----------------------

	// for interactive UI, read int4 state from former frame
	int4 s2h_State;
};

struct s2h_Triangle
{
    float2 A;
    float2 B;
    float2 C;
};

// first call this
void s2h_init(out ContextGather ui);
// set text cursor position, next printLF() will reset to this x position
void s2h_setCursor(inout ContextGather ui, float2 inpxLeftTop);
// @param s2h_State write int4 state for next frame, don't call if you don't want UI State
void s2h_deinit(inout ContextGather ui, out int4 s2h_State);
// @param scale 1:pixel perfect, 2:2x, 3:3x, ..
void s2h_setScale(inout ContextGather ui, float scale);
// e.g. ui.s2h_printTxt('I', ' ', 'a', 'm');
// @param a ascii character or 0
void s2h_printTxt(inout ContextGather ui, uint a, uint b, uint c, uint d, uint e, uint f);
// useful for table headers and to center text
void s2h_printSpace(inout ContextGather ui, float numberOfChars);
// jump to next line (line feed)
void s2h_printLF(inout ContextGather ui);
// @param value e.g. 123, 0
void s2h_printInt(inout ContextGather ui, int value);
// print hexadecimal e.g. "0000aa34"
// @param value 32bit e.g. 0x123, 0xff00
void s2h_printHex(inout ContextGather ui, uint value);
// @param output e.g. g_output from RWTexture2D<float3> g_output : register(u0, space0);
// @param pos in pixels from left top, left top of the printout
// @param value
void s2h_printFloat(inout ContextGather ui, float value);
// don't use directly
void s2h_printCharacter(inout ContextGather ui, uint ascii);
// circle in a s2h_fontSize() x s2h_fontSize() character
void s2h_printDisc(inout ContextGather ui, float4 color);
// block in a s2h_fontSize() x s2h_fontSize() character
void s2h_printBox(inout ContextGather ui, float4 color);
// useful for table headers
// similar to s2h_button but not interactive, call after using s2h_printTxt()
void s2h_frame(inout ContextGather ui, uint widthInCharacters);

// draw anti aliased filled disc 
void s2h_drawDisc(inout ContextGather ui, float2 pxCenter, float pxRadius, float4 color);
// draw anti aliased circle
// uses ui.lineWidth
void s2h_drawCircle(inout ContextGather ui, float2 pxCenter, float pxRadius, float4 color);
// draw anti aliased half space
void s2h_drawHalfSpace(inout ContextGather ui, float3 halfSpace, float2 visualizePoint, float4 color, float pxCircleRadius, float pxLineRadius);
// draw not anti aliased rectangle (fast and simple), 
// @param pxLeftTop included
// @param pxBottomRight excluded
void s2h_drawRectangle(inout ContextGather ui, float2 pxLeftTop, float2 pxBottomRight, float4 color);
// border half inwards and half outwards, pxThickness >0 results in rounded corners
void s2h_drawRectangleAA(inout ContextGather ui, float2 pxA, float2 pxB, float4 borderColor, float4 innerColor, float pxThickness);
// anti aliased, px position should be pixel centered (+0.5)
// uses ui.lineWidth
void s2h_drawCrosshair(inout ContextGather ui, float2 pxCenter, float pxRadius, float4 color);
// hard edges, anti aliased, px position should be pixel centered (+0.5)
// uses ui.lineWidth
void s2h_drawLine(inout ContextGather ui, float2 pxBegin, float2 pxEnd, float4 color);
// anti aliased px position should be pixel centered (+0.5)
// uses ui.lineWidth
void s2h_drawArrow(inout ContextGather ui, float2 pxStart, float2 pxEnd, float4 color, float arrowHeadLength, float arrowHeadWidth);
// anti aliased px position should be pixel centered (+0.5)
void s2h_drawTriangle(inout ContextGather ui, s2h_Triangle tri, float4 color);
// 256x32 horizontal color ramp in sRGB space, 128 should be in the middle, RGB color gradient on outside
void s2h_drawSRGBRamp(inout ContextGather ui, float2 pxPos);
// draw a cartesian XY coordinate system with 2 arrows and unit markers
// using ui.textColor and ui.lineWidth
// @param pxOrigin position of 0,0 in pixel coordinates
// @param domain (minX, minY)-(maxX, maxY)
// @param pxScale one domain unit in pixels
// @param gridSize in unit space
// @param gridColor e.g. float4(1.0f, 1.0f, 1.0f, 0.25f) 
// @param flags defaut:0, add up bit values, 0x1:Y is up, 0x2:gridLines
void s2h_coordinateSystem(inout ContextGather ui, float2 pxOrigin, float4 domain, float pxScale, float gridSize, float4 gridColor, uint flags);

// ------------------------------------------

// for state-full UI:

// call after using s2h_printTxt()
// e.g. if(s2h_button(ui, 5, float4(1,0,1,1))) do();
bool s2h_button(inout ContextGather ui, uint widthInCharacters);
// circle in a s2h_fontSize() x s2h_fontSize() character with mouse over
// e.g. if(s2h_radioButton(ui, float4(1,0,0,1), UIState[0].SplatMode == 0) && leftMouse) UIState[0].SplatMode = 0;
// @param checked fill inside using textColor
// @return mouseOver (can be used as button or radio button)
bool s2h_radioButton(inout ContextGather ui, bool checked);
// e.g. if(s2h_checkBox(ui, UIState[0].UICheckboxState == 0) && leftMouseClicked) UIState[0].UICheckboxState = !UIState[0].UICheckboxState;
// @param checked fill inside using textColor
bool s2h_checkBox(inout ContextGather ui, bool checked);
// @param fraction 0..1
void s2h_progress(inout ContextGather ui, uint widthInCharacters, float fraction);
//
void s2h_sliderFloat(inout ContextGather ui, uint widthInCharacters, inout float value, float minValue, float maxValue);
// LDR color (0..1 range)
void s2h_sliderRGB(inout ContextGather ui, uint widthInCharacters, inout float3 value);
// LDR color (0..1 range) with alpha
void s2h_sliderRGBA(inout ContextGather ui, uint widthInCharacters, inout float4 value);

// not yet for GLSL 
// see s2h_tableLookupInt()
void s2h_tableInt(inout ContextGather ui, uint column, float4 backgroundColor, int2 sizeInCharacters, bool goRightNotDown);
// see s2h_tableLookupFloat()
void s2h_tableFloat(inout ContextGather ui, uint column, float4 backgroundColor, int2 sizeInCharacters, bool goRightNotDown);
// to be implemented by the user, for s2h_tableInt()
// @param row y coordinate, starting with 0
// @return true:valid, false: not valid e.g. outside of range
bool s2h_tableLookupInt(uint column, uint row, out int outValue);
// to be implemented by the user, for s2h_tableFloat()
// @param row y coordinate, starting with 0
// @return true:valid, false: not valid e.g. outside of range
bool s2h_tableLookupFloat(uint column, uint row, out float outValue);
// to be implemented by the user, for s2h_function()
float s2h_floatLookupFloat(uint functionId, float x);
// required you to implement s2h_floatLookupFloat()
// @param rangeX float2(left, right) e.g. float2(0, 2.0f * 3.1415f)
// @param rangeY float2(top, bottom) e.g. float2(-1, 1)
void s2h_function(inout ContextGather ui, uint functionId, float4 backgroundColor, int2 sizeInCharacters, float2 rangeX, float2 rangeY);

// helper functions ----------------------------------------------------------------------

// slow but accurate
float3 s2h_accurateLinearToSRGB(float3 linearCol);
// slow but accurate
float3 s2h_accurateSRGBToLinear(float3 sRGBCol);
// extremely different colors, 0 is black
// intentionally not randomized so small indices result in human recognizable colors
// repeats every 512 elements
float3 s2h_indexToColor(uint index);
// @param 0..1
// @return 0:red, 0.5:green, 1:blue, outside is clamped
float3 s2h_colorRampRGB(float value);


// implementation ----------------------------------------------------------------------

#ifndef S2H_FLT_MAX
	// can result in WebGL warning (Fragment Shader WARNING: 0:248: '3.40282347e+38' : Float overflow) but works
    // Slang: warning 39999: float literal '3.40282347e+38' unrepresentable, converted to 'inf'
//    static const float S2H_FLT_MAX = 3.40282347e+38;

	static const float S2H_FLT_MAX = asfloat(0x7F7FFFFFu);

	// works in most GLSL environments and no warning in WebGL
//    static const float S2H_FLT_MAX = intBitsToFloat(2139095039);
#endif

// You can define this to provide your own font (different size, visual or better lookup performance by using a texture)
#ifndef S2H_DISABLE_EMBEDDED_FONT
#define S2H_DISABLE_EMBEDDED_FONT 1

#if defined(S2H_BGFX) && BGFX_SHADER_LANGUAGE_GLSL

	// GLSL needs its array-constructor syntax, while shaderc's non-GLSL
	// backends need a static const table so the glyph data is embedded rather
	// than reflected as an uninitialized runtime global.
	const uint g_miniFont[192] = uint[](

#elif defined(S2H_BGFX)

	static const uint g_miniFont[192] = {

#elif defined(S2H_GLSL)

	#ifdef __SLANG__
		static const uint g_miniFont[] = {
	#else
		const uint g_miniFont[] = uint[](
	#endif

#else
	static const uint g_miniFont[] = {
#endif
    0x00306c6cu, 0x30003860u, 0x18600000u, 0x00000006u, 
    0x00786c6cu, 0x7cc66c60u, 0x30306630u, 0x0000000cu, 
    0x00786cfeu, 0xc0cc38c0u, 0x60183c30u, 0x00000018u, 
    0x0030006cu, 0x78187600u, 0x6018fffcu, 0x00fc0030u, 
    0x003000feu, 0x0c30dc00u, 0x60183c30u, 0x00000060u, 
    0x0000006cu, 0xf866cc00u, 0x30306630u, 0x300030c0u, 
    0x0030006cu, 0x30c67600u, 0x18600000u, 0x30003080u, 
    0x00000000u, 0x00000000u, 0x00000000u, 0x60000000u, 
    0x7c307878u, 0x1cfc38fcu, 0x78780000u, 0x18006078u, 
    0xc670ccccu, 0x3cc060ccu, 0xcccc3030u, 0x300030ccu, 
    0xce300c0cu, 0x6cf8c00cu, 0xcccc3030u, 0x60fc180cu, 
    0xde303838u, 0xcc0cf818u, 0x787c0000u, 0xc0000c18u, 
    0xf630600cu, 0xfe0ccc30u, 0xcc0c0000u, 0x60001830u, 
    0xe630ccccu, 0x0ccccc30u, 0xcc183030u, 0x30fc3000u, 
    0x7cfcfc78u, 0x1e787830u, 0x78703030u, 0x18006030u, 
    0x00000000u, 0x00000000u, 0x00000060u, 0x00000000u, 
    0x7c30fc3cu, 0xf8fefe3cu, 0xcc781ee6u, 0xf0c6c638u, 
    0xc6786666u, 0x6c626266u, 0xcc300c66u, 0x60eee66cu, 
    0xdecc66c0u, 0x666868c0u, 0xcc300c6cu, 0x60fef6c6u, 
    0xdecc7cc0u, 0x667878c0u, 0xfc300c78u, 0x60fedec6u,
    0xdefc66c0u, 0x666868ceu, 0xcc30cc6cu, 0x62d6cec6u,
    0xc0cc6666u, 0x6c626066u, 0xcc30cc66u, 0x66c6c66cu,
    0x78ccfc3cu, 0xf8fef03eu, 0xcc7878e6u, 0xfec6c638u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0xfc78fc78u, 0xfcccccc6u, 0xc6ccfe78u, 0xc0781000u,
    0x66cc66ccu, 0xb4ccccc6u, 0xc6ccc660u, 0x60183800u,
    0x66cc66e0u, 0x30ccccc6u, 0x6ccc8c60u, 0x30186c00u,
    0x7ccc7c70u, 0x30ccccd6u, 0x38781860u, 0x1818c600u,
    0x60dc6c1cu, 0x30ccccfeu, 0x38303260u, 0x0c180000u,
    0x607866ccu, 0x30cc78eeu, 0x6c306660u, 0x06180000u,
    0xf01ce678u, 0x78fc30c6u, 0xc678fe78u, 0x02780000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x000000ffu,
    0x3000e000u, 0x1c003800u, 0xe0300ce0u, 0x70000000u, 
    0x30006000u, 0x0c006c00u, 0x60000060u, 0x30000000u, 
    0x18786078u, 0x0c786076u, 0x6c700c66u, 0x30ccf878u, 
    0x000c7cccu, 0x7cccf0ccu, 0x76300c6cu, 0x30feccccu, 
    0x007c66c0u, 0xccfc60ccu, 0x66300c78u, 0x30feccccu, 
    0x00cc66ccu, 0xccc0607cu, 0x6630cc6cu, 0x30d6ccccu, 
    0x0076dc78u, 0x7678f00cu, 0xe678cce6u, 0x78c6cc78u, 
    0x00000000u, 0x000000f8u, 0x00007800u, 0x00000000u, 
    0x00000000u, 0x10000000u, 0x0000001cu, 0x18e076ffu, 
    0x00000000u, 0x30000000u, 0x00000030u, 0x1830dcffu, 
    0xdc76dc7cu, 0x7cccccc6u, 0xc6ccfc30u, 0x183000ffu,
    0x66cc76c0u, 0x30ccccd6u, 0x6ccc98e0u, 0x001c00ffu, 
    0x66cc6678u, 0x30ccccfeu, 0x38cc3030u, 0x183000ffu, 
    0x7c7c600cu, 0x34cc78feu, 0x6c7c6430u, 0x183000ffu, 
    0x600cf0f8u, 0x1876306cu, 0xc60cfc1cu, 0x18e000ffu, 
    0xf01e0000u, 0x00000000u, 0x00f80000u, 0x000000ffu
#if defined(S2H_BGFX) && BGFX_SHADER_LANGUAGE_GLSL
	);

#elif defined(S2H_BGFX)
	};

#elif defined(S2H_GLSL)
	#ifdef __SLANG__
	};
	#else
	);
	#endif
#else
	};
#endif

// todo: consider define or static cost int or float
// 8x8 font 
float s2h_fontSize() { return 8.0f; }

// don't use directly
// can be used for scatter and gather
// @param ascii 32..127 are valid characters
// @param pxPos int2(0..s2h_fontSize()-1, 0..s2h_fontSize-1)
// @return true if there should be a pixel, false if not or outside the valid range
bool s2h_fontLookup(uint ascii, int2 pxPos)
{
	if(uint(pxPos.x) >= 8u || uint(pxPos.y) >= 8u)
        return false;

    if (ascii <= 32u || ascii > 127u)
        return false;

    // 0..16*6-1
    uint chr = ascii - 32u;
    // uint2(0..127, 0..47) 
    uint2 chrPos = uint2(chr % 16u, chr / 16u);
    uint2 pixel = uint2(chrPos.x * 8u + uint(pxPos.x), chrPos.y * 8u + uint(pxPos.y));
    uint dwordId = pixel.x / 32u + (pixel.y * 4u);
    // 0..31
    uint bitId	= uint(pixel.x) & 0x1fu;

    // 0..ff
    uint dwordValue = g_miniFont[dwordId];

    return ((dwordValue >> (31u - bitId)) & 1u) != 0u;
}

void s2h_printCharacter(inout ContextGather ui, uint ascii)
{
	int2 pxLocal = int2(floor((ui.pxPos - ui.pxCursor) / ui.scale));

	if(s2h_fontLookup(ascii, pxLocal))
		ui.dstColor = lerp(ui.dstColor, float4(ui.textColor.rgb, 1), ui.textColor.a);

	ui.pxCursor.x += s2h_fontSize() * ui.scale;
}

#endif // S2H_EMBEDDED_FONT

static const uint _A = 65u;
static const uint _B = 66u;
static const uint _C = 67u;
static const uint _D = 68u;
static const uint _E = 69u;
static const uint _F = 70u;
static const uint _G = 71u;
static const uint _H = 72u;
static const uint _I = 73u;
static const uint _J = 74u;
static const uint _K = 75u;
static const uint _L = 76u;
static const uint _M = 77u;
static const uint _N = 78u;
static const uint _O = 79u;
static const uint _P = 80u;
static const uint _Q = 81u;
static const uint _R = 82u;
static const uint _S = 83u;
static const uint _T = 84u;
static const uint _U = 85u;
static const uint _V = 86u;
static const uint _W = 87u;
static const uint _X = 88u;
static const uint _Y = 89u;
static const uint _Z = 90u;

static const uint _a = (_A + 32u);
static const uint _b = (_B + 32u);
static const uint _c = (_C + 32u);
static const uint _d = (_D + 32u);
static const uint _e = (_E + 32u);
static const uint _f = (_F + 32u);
static const uint _g = (_G + 32u);
static const uint _h = (_H + 32u);
static const uint _i = (_I + 32u);
static const uint _j = (_J + 32u);
static const uint _k = (_K + 32u);
static const uint _l = (_L + 32u);
static const uint _m = (_M + 32u);
static const uint _n = (_N + 32u);
static const uint _o = (_O + 32u);
static const uint _p = (_P + 32u);
static const uint _q = (_Q + 32u);
static const uint _r = (_R + 32u);
static const uint _s = (_S + 32u);
static const uint _t = (_T + 32u);
static const uint _u = (_U + 32u);
static const uint _v = (_V + 32u);
static const uint _w = (_W + 32u);
static const uint _x = (_X + 32u);
static const uint _y = (_Y + 32u);
static const uint _z = (_Z + 32u);

static const uint _SINGLEQUOTE = 39u;   // '
static const uint _UNDERSCORE = 95u;    // _
static const uint _MINUS = 45u;         // -
static const uint _PLUS = 43u;          // +
static const uint _ASTERISK = 42u;      // *
static const uint _PERIOD = 46u;        // .
static const uint _COLON = 58u;         // :
static const uint _COMMA = 44u;         // ,
static const uint _SPACE = 32u;         //  
static const uint _LESS = 60u;          // <
static const uint _EQUAL = 61u;         // =
static const uint _GREATER = 62u;       // >
static const uint _SLASH = 47u;         // /
static const uint _BACKSLASH = 92u;     //
static const uint _0 = 48u;
static const uint _1 = 49u;
static const uint _2 = 50u;
static const uint _3 = 51u;
static const uint _4 = 52u;
static const uint _5 = 53u;
static const uint _6 = 54u;
static const uint _7 = 55u;
static const uint _8 = 56u;
static const uint _9 = 57u;
static const int _S2H_VERSION = S2H_VERSION;

void s2h_init(out ContextGather ui, float2 inPxPos)
{
	// white, opaque 
	ui.textColor = float4(1, 1, 1, 1); 
	ui.pxLeftX = 0.0f; 
	ui.pxCursor = float2(0, 0); 
	ui.scale = 1.0f;
	ui.mouseInput = float4(-100, -100, 0, 0); 

	ui.pxPos = inPxPos;
	// see through
	ui.dstColor = float4(0, 0, 0, 0);
	ui.s2h_State = int4(0, 0, 0, 0);

	ui.frameFillColor = float4(0.9f, 0.9f, 0.9f, 1);
	ui.frameBorderColor = float4(0.7f, 0.7f, 0.7f, 1);
	ui.buttonColor = float4(0.5f, 0.5f, 0.5f, 1);
	ui.lineWidth = 2.0f;
}

void s2h_setCursor(inout ContextGather ui, float2 inpxLeftTop)
{
	ui.pxCursor = inpxLeftTop; 
	ui.pxLeftX = inpxLeftTop.x;
}

void s2h_deinit(inout ContextGather ui, out int4 s2h_State)
{
	// if mouse input was set and mouse is released, we forget which button was active
	if(ui.mouseInput.x != -100.0f && ui.mouseInput.z == 0.0f)
		ui.s2h_State = int4(0,0,0,0);

	s2h_State = ui.s2h_State;
}

void s2h_setScale(inout ContextGather ui, float scale)
{
	ui.scale = scale;
}

void s2h_printTxt(inout ContextGather ui, uint a)
{
	s2h_printCharacter(ui, a);
}
// glsl has no default arguments to we implement multiple functions instead making porting easier
void s2h_printTxt(inout ContextGather ui, uint a, uint b)
{ s2h_printTxt(ui, a); s2h_printCharacter(ui, b); }
void s2h_printTxt(inout ContextGather ui, uint a, uint b, uint c)
{ s2h_printTxt(ui, a, b); s2h_printCharacter(ui, c); }
void s2h_printTxt(inout ContextGather ui, uint a, uint b, uint c, uint d)
{ s2h_printTxt(ui, a, b, c); s2h_printCharacter(ui, d); }
void s2h_printTxt(inout ContextGather ui, uint a, uint b, uint c, uint d, uint e)
{ s2h_printTxt(ui, a, b, c, d); s2h_printCharacter(ui, e); }
void s2h_printTxt(inout ContextGather ui, uint a, uint b, uint c, uint d, uint e, uint f)
{ s2h_printTxt(ui, a, b, c, d, e); s2h_printCharacter(ui, f); }

void s2h_printSpace(inout ContextGather ui, float numberOfChars)
{
	ui.pxCursor.x += s2h_fontSize() * numberOfChars * ui.scale;
}

void s2h_printLF(inout ContextGather ui)
{
	ui.pxCursor.x = ui.pxLeftX;
	ui.pxCursor.y += s2h_fontSize() * ui.scale;
}

void s2h_printInt(inout ContextGather ui, int value)
{
	// leading '-'
	if (value < 0)
	{
		s2h_printCharacter(ui, _MINUS);
		value = -value;
	}
	if (value == 0)
	{
		s2h_printCharacter(ui, _0);
		return;
	}
	// move to right depending on number length
	{
		uint tmp = uint(value);
		while (tmp != 0u)
		{
			ui.pxCursor.x += s2h_fontSize() * ui.scale;
			tmp /= 10u;
		}
	}
	// digits
	{
		float backup = ui.pxCursor.x;
		uint tmp = uint(value);
		while (tmp != 0u)
		{
			// 0..9
			uint digit = tmp % 10u;
			tmp /= 10u;
			// go backwards
			ui.pxCursor.x -= s2h_fontSize() * ui.scale;
			s2h_printCharacter(ui, _0 + digit);
			// counter +=s2h_fontSize() from printCharacter ()
			ui.pxCursor.x -= s2h_fontSize() * ui.scale;
		}
		ui.pxCursor.x = backup;
	}
}

void s2h_printHex(inout ContextGather ui, uint value)
{
	// 8 nibbles
	for(int i = 7; i >= 0; --i)
	{
		// 0..15
		uint nibble = (value >> (uint(i) * 4u)) & 0xfu;
		uint start = (nibble < 10u) ? _0 : (_A - 10u);
		s2h_printCharacter(ui, start + nibble);
	}
}

void s2h_printFloat(inout ContextGather ui, float value)
{
	s2h_printInt(ui, int(value));
	float fractional = frac(abs(value));

	s2h_printCharacter(ui, _PERIOD);

	uint digitCount = 3u;

	// todo: unit tests, this is likely wrong at lower precision

	// fractional digits
	for(uint i = 0u; i < digitCount; ++i)
	{
		fractional *= 10.0f;
		// 0..9
		uint digit = uint(fractional);
		fractional = frac(fractional);
		s2h_printCharacter(ui, _0 + digit);
	}
}

void s2h_printBox(inout ContextGather ui, float4 color)
{
	float2 pxLocal = float2(ui.pxPos - ui.pxCursor) / float(ui.scale) - float2(4, 4);

	float mask = saturate(4.0f - max(abs(pxLocal.x), abs(pxLocal.y)));

//	dstColor = lerp(dstColor, float4(color.rgb, 1), color.a * mask);
	if(mask > 0.0f)
		ui.dstColor = lerp(ui.dstColor, float4(color.rgb, 1), color.a);

	ui.pxCursor.x += s2h_fontSize() * ui.scale;
}

void s2h_drawDisc(inout ContextGather ui, float2 pxCenter, float pxRadius, float4 color)
{
	float2 pxLocal = ui.pxPos - pxCenter;

	float len = length(pxLocal);
	float mask = saturate(pxRadius - len);

	ui.dstColor = lerp(ui.dstColor, float4(color.rgb, 1), color.a * mask);
}

void s2h_drawCircle(inout ContextGather ui, float2 pxCenter, float pxRadius, float4 color)
{
	float r = ui.lineWidth * 0.5f;
	float2 pxLocal = ui.pxPos - pxCenter;

	float len = length(pxLocal);
	float mask = saturate(pxRadius - len + r) * (1.0f - saturate(pxRadius - len - r));

	ui.dstColor = lerp(ui.dstColor, float4(color.rgb, 1), color.a * mask);
}

void s2h_drawHalfSpace(inout ContextGather ui, float3 halfSpace, float2 visualizePoint, float4 color, float pxCircleRadius, float lineRadius)
{
    // normalize
    halfSpace /= length(halfSpace.xy);

    //
    float2 onPoint = visualizePoint - halfSpace.xy * dot(halfSpace, float3(visualizePoint, 1));

    float planeDist = dot(halfSpace, float3(ui.pxPos, 1));
    float diskDist = length(onPoint - ui.pxPos);

	// 0..1
    float sideMask = saturate(planeDist);
	// 0..1
    float lineMask = saturate(ui.lineWidth - abs(planeDist - ui.lineWidth)) * saturate(lineRadius - diskDist);
	// 0..1
    float semiDiskMask = saturate(pxCircleRadius - diskDist) * sideMask;
    float mask = max(semiDiskMask, lineMask);

	ui.dstColor = lerp(ui.dstColor, float4(color.rgb, 1), color.a * mask);
}

void s2h_drawRectangle(inout ContextGather ui, float2 pxLeftTop, float2 pxBottomRight, float4 color)
{
	if(ui.pxPos.x >= pxLeftTop.x && ui.pxPos.y >= pxLeftTop.y && ui.pxPos.x < pxBottomRight.x && ui.pxPos.y < pxBottomRight.y)
		ui.dstColor = lerp(ui.dstColor, float4(color.rgb, 1), color.a);
}

void s2h_drawRectangleAA(inout ContextGather ui, float2 pxA, float2 pxB, float4 borderColor, float4 innerColor, float pxThickness)
{
	float r = pxThickness * 0.5f;

	float2 pxCenter = (pxA + pxB) * 0.5f;
	float2 pxHalfSize = abs(pxB - pxA) * 0.5f;
	
	float2 pxLocalOuter = max(abs(ui.pxPos - pxCenter) - pxHalfSize, float2(0, 0));
	float2 pxLocalInner = max(abs(ui.pxPos - pxCenter) - pxHalfSize + r, float2(0, 0));

	float maskOuter = saturate(1.0f + r - length(pxLocalOuter));
	float maskInner = saturate(length(pxLocalInner) - 0.5f);

	float4 color = lerp(innerColor, float4(borderColor.rgb, 1), borderColor.a * maskInner);

	ui.dstColor = lerp(ui.dstColor, float4(color.rgb, 1), color.a * maskOuter);
}

void s2h_drawCrosshair(inout ContextGather ui, float2 pxCenter, float pxRadius, float4 color)
{
	float2 h = float2(pxRadius, 0);
	float2 v = float2(0, pxRadius);

	s2h_drawLine(ui, pxCenter - h, pxCenter + h, color);
	s2h_drawLine(ui, pxCenter - v, pxCenter + v, color);
}

void s2h_drawLine(inout ContextGather ui, float2 pxBegin, float2 pxEnd, float4 color)
{
	float pxThickness = ui.lineWidth + 1.0f;
	float r = pxThickness * 0.5f;
	float2 delta = pxEnd - pxBegin;
	float len = length(delta);
	if(len > 0.01f)
	{
		float2 tangent = delta / len;
		float2 normal = float2(tangent.y, -tangent.x);
		float2 local = float2(ui.pxPos) - pxBegin;
		float2 uv = float2(dot(local, tangent), dot(local, normal));
		// 0...1
		float mask = saturate(r - abs(uv.y)) * saturate(r - uv.x + len) * saturate(r + uv.x);

		ui.dstColor = lerp(ui.dstColor, float4(color.rgb, 1), color.a * mask);
	}
}

float3 s2h_getHalfSpacePlane(float2 pointA, float2 pointB)
{
    float2 pointDelta = pointA - pointB;
    float2 ab = pointDelta / max(length(pointDelta), 0.0001f);
    float3 abPlane = float3(-ab.y, ab.x, 0);
    abPlane.z = dot(abPlane.xy, -pointA);

    return abPlane;
}

void s2h_drawTriangle(inout ContextGather ui, s2h_Triangle tri, float4 color)
{
    float3 abPlane = s2h_getHalfSpacePlane(tri.A, tri.B);
    float abMask = saturate(dot(abPlane, float3(ui.pxPos, 1)) - 0.5f);

    float3 bcPlane = s2h_getHalfSpacePlane(tri.B, tri.C);
    float bcMask = saturate(dot(bcPlane, float3(ui.pxPos, 1))- 0.5f);

    float3 caPlane = s2h_getHalfSpacePlane(tri.C, tri.A);
    float caMask = saturate(dot(caPlane, float3(ui.pxPos, 1)) - 0.5f);
    
    float mask = abMask * bcMask * caMask;
    ui.dstColor = lerp(ui.dstColor, float4(color.rgb, 1), color.a * mask);
}

void s2h_drawArrow(inout ContextGather ui, float2 pxStart, float2 pxEnd, float4 color,  float arrowHeadLength, float arrowHeadWidth)
{
    float2 directionVector = pxEnd - pxStart;
    float directionLength = max(length(directionVector), 0.0001f);
    float2 direction = directionVector / directionLength;

    float2 lineStart = pxStart;
    // Subtract the arrow length from lineEnd - arrow fits in pxStart...pxEnd
    float2 lineEnd = pxEnd - direction * arrowHeadLength;

    float2 perpendicularDir = float2(direction.y, -direction.x);

	s2h_drawLine(ui, lineStart, lineEnd, color);

    s2h_Triangle triA;
    triA.A = lineEnd - perpendicularDir * arrowHeadWidth;
    triA.B = lineEnd + direction * arrowHeadLength;
    triA.C = lineEnd + perpendicularDir * arrowHeadWidth;
    s2h_drawTriangle(ui, triA, color);
}

void s2h_drawSRGBRamp(inout ContextGather ui, float2 pxPos)
{
	// snap to pixel center
	pxPos = floor(pxPos) + 0.5f;

	float2 local = ui.pxPos - pxPos;

	float u = local.x / 256.0f;

	if(local.y > 16.0f)
		u = floor(u * 16.0f) / 16.0f;

	float3 col = s2h_accurateSRGBToLinear(float3(u, u, u));

	s2h_drawRectangle(ui, pxPos - 2.0f, pxPos + float2(256, 32) + 2.0f, float4(s2h_colorRampRGB(u), 1));
	s2h_drawRectangle(ui, pxPos, pxPos + float2(256, 32), float4(col, 1));

	ContextGather backup = ui;
	s2h_setScale(ui, 1.0f);
	ui.textColor = float4(1, 1, 1, 1);
	s2h_setCursor(ui, pxPos + float2(2.0f, 22));
	s2h_printTxt(ui, _0);
	s2h_setCursor(ui, pxPos + float2(128.0f - 1.5f * 8.0f, 22));
	s2h_printTxt(ui, _1, _2, _7);
	ui.textColor = float4(0, 0, 0, 1);
	s2h_setCursor(ui, pxPos + float2(256.0f - 3.2f * 8.0f, 22));
	s2h_printTxt(ui, _2, _5, _5);

	ui.pxCursor = backup.pxCursor;
	ui.scale = backup.scale;
	ui.textColor = backup.textColor;
	ui.pxLeftX = backup.pxLeftX;
}

void s2h_coordinateSystem(inout ContextGather ui, float2 pxOrigin, float4 domain, float pxScale, float gridSize, float4 gridColor, uint flags)
{
	// floor() to snap to pixel grid for consistent visuals
	pxOrigin = floor(pxOrigin);

	bool yIsUp = (flags & 0x1u) != 0u;
	bool gridLines = (flags & 0x2u) != 0u;
	
	float4 color = ui.textColor;
	
	float pxDotSize = ui.lineWidth;
	// todo: refine math to be consistent in grid size
	float2 pxD = frac(floor(ui.pxPos - pxOrigin + pxDotSize / 2.0f) / gridSize) * gridSize;

	if (gridLines)
	{
		if (pxD.x > floor(pxDotSize) && pxD.y > floor(pxDotSize))
			gridColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		if (pxD.x > floor(pxDotSize) || pxD.y > floor(pxDotSize))
			gridColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	
	float4 pxDomain = domain * pxScale + float4(pxOrigin, pxOrigin);

	s2h_drawRectangle(ui, pxDomain.xy, pxDomain.zw, gridColor);
	
	float backupLineWidth = ui.lineWidth;

	// X axis
	if (pxD.x < backupLineWidth)
		ui.lineWidth *= 2.0f;
	s2h_drawArrow(ui, float2(pxDomain.x, pxOrigin.y), float2(pxDomain.z, pxOrigin.y), color, 16.0f, 8.0f);

	// Y axis
	ui.lineWidth = backupLineWidth;
	if (pxD.y < backupLineWidth)
		ui.lineWidth *= 2.0f;

	if (yIsUp)
		s2h_drawArrow(ui, float2(pxOrigin.x, pxDomain.w), float2(pxOrigin.x, pxDomain.y), color, 16.0f, 8.0f);
	else
		s2h_drawArrow(ui, float2(pxOrigin.x, pxDomain.y), float2(pxOrigin.x, pxDomain.w), color, 16.0f, 8.0f);

	ui.lineWidth = backupLineWidth;
}

void s2h_printDisc(inout ContextGather ui, float4 color) 
{ 
	float2 pxLocal = float2(ui.pxPos - ui.pxCursor) / float(ui.scale) - float2(4, 4); 
 
	float mask = saturate(4.0f - length(pxLocal)); 
 
//	dstColor = lerp(stColor, float4(color.rgb, 1), color.a * mask); 
	// no AA for now
	if(mask > 0.0f) 
		ui.dstColor = lerp(ui.dstColor, float4(color.rgb, 1), color.a);
 
	ui.pxCursor.x += s2h_fontSize() * ui.scale; 
}

float s2h_computeDistToBox(inout ContextGather ui, float2 p, float2 center, float2 halfSize)
{
	float2 pxLocal = float2(p - center);// - float2(3.5f, 3.5f) * ui.scale;
	float2 dist2 = max(float2(0, 0), abs(pxLocal) - halfSize);
	return max(dist2.x, dist2.y);
}

// @param aabb .x:minx, .y:miny, z:maxx, w:maxy
float s2h_computeDistToBox(inout ContextGather ui, float2 p, float4 aabb)
{
	float2 center = (aabb.xy + aabb.zw) * 0.5f; 
	float2 halfSize = (aabb.zw - aabb.xy) * 0.5f;
	float2 pxLocal = float2(p - center);// - float2(3.5f, 3.5f) / ui.scale;
	float2 dist2 = max(float2(0, 0), abs(pxLocal) - halfSize);
	return max(dist2.x, dist2.y);
}

void s2h_frame(inout ContextGather ui, uint widthInCharacters)
{
	float4 aabb = float4(ui.pxCursor - float2(widthInCharacters, 0) * s2h_fontSize() * ui.scale, ui.pxCursor);

	// shrink
	aabb += float4(4, 4, -4, 4) * ui.scale;

	float dist = s2h_computeDistToBox(ui, ui.pxPos, aabb) / ui.scale;

	float rimMask = saturate(3.0f - dist);
	float outerMask = saturate(4.0f - dist);

	float4 localColor = float4(0,0,0,0);

	// no AA for now
	if(outerMask > 0.0f)
		localColor = ui.frameBorderColor;

	if(rimMask > 0.0f)
		localColor = ui.frameFillColor;

	ui.dstColor = lerp(ui.dstColor, float4(localColor.rgb, 1), localColor.a * (1.0f - ui.dstColor.a));
}

bool s2h_button(inout ContextGather ui, uint widthInCharacters)
{
	float4 color = ui.buttonColor;
	const float border = 0.0f;

	float4 aabb = float4(ui.pxCursor - float2(widthInCharacters, 0) * s2h_fontSize() * ui.scale, ui.pxCursor);

	// shrink
	aabb += float4(4, 4, -4, 4) * ui.scale;

	float dist = s2h_computeDistToBox(ui, ui.pxPos, aabb) / ui.scale;
	bool mouseOver = s2h_computeDistToBox(ui, ui.mouseInput.xy, aabb) / ui.scale < 5.0f + border;

	float rimMask = saturate(5.0f - dist + border);
	float outerMask = saturate(4.0f - dist + border);

	float4 localColor = float4(0,0,0,0);

	if(mouseOver && rimMask > 0.0f)
		localColor = float4(1, 1, 1, 1);

	// no AA for now
	if(outerMask > 0.0f)
		localColor = color;

	ui.dstColor = lerp(ui.dstColor, float4(localColor.rgb, 1), localColor.a * (1.0f - ui.dstColor.a));

	float2 delta = round(ui.mouseInput.xy + 0.5f - ui.pxPos);

	return mouseOver && delta.x == 0.0f && delta.y == 0.0f;
}

bool s2h_radioButton(inout ContextGather ui, bool checked)
{
	float4 color = ui.buttonColor;

	float2 pxLocal = float2(ui.pxPos - ui.pxCursor - 0.5f) / float(ui.scale) - float2(3.5f, 3.5f);
	float dist = length(pxLocal);

	float rimMask = saturate(5.0f - dist);
	float outerMask = saturate(4.0f - dist);
	float innerMask = saturate(2.5f - dist);

	bool mouseOver = length(float2(ui.mouseInput.xy - ui.pxCursor) / float(ui.scale) - float2(3.5f, 3.5f)) < 4.0f;

	if(mouseOver && rimMask > 0.0f)
		ui.dstColor = float4(1, 1, 1 ,1);

	// no AA for now
	if(outerMask > 0.0f)
		ui.dstColor = lerp(ui.dstColor, float4(color.rgb, 1), color.a);
	if(checked && innerMask > 0.0f)
		ui.dstColor = lerp(ui.dstColor, float4(ui.textColor.rgb, 1), ui.textColor.a);

	ui.pxCursor.x += s2h_fontSize() * ui.scale;

	float2 delta = round(ui.mouseInput.xy + 0.5f - ui.pxPos);

	return mouseOver && delta.x == 0.0f && delta.y == 0.0f;
}

bool s2h_checkBox(inout ContextGather ui, bool checked)
{
	float4 color = ui.buttonColor;

	float2 pxLocal = float2(ui.pxPos - ui.pxCursor - 0.5f) / float(ui.scale) - float2(3.5f, 3.5f);
	float dist = max(abs(pxLocal.x), abs(pxLocal.y));

	float rimMask = saturate(5.0f - dist);
	float outerMask = saturate(4.0f - dist);
	float innerMask = saturate(2.5f - dist);

	bool mouseOver = length(float2(ui.mouseInput.xy - ui.pxCursor) / float(ui.scale) - float2(3.5f, 3.5f)) < 4.0f;

	if(mouseOver && rimMask > 0.0f)
		ui.dstColor = float4(1, 1, 1 ,1);

	// no AA for now
	if(outerMask > 0.0f)
		ui.dstColor = lerp(ui.dstColor, float4(color.rgb, 1), color.a);
	if(checked && innerMask > 0.0f)
		ui.dstColor = lerp(ui.dstColor, float4(ui.textColor.rgb, 1), ui.textColor.a);

	ui.pxCursor.x += s2h_fontSize() * ui.scale;

	float2 delta = round(ui.mouseInput.xy + 0.5f - ui.pxPos);

	return mouseOver && delta.x == 0.0f && delta.y == 0.0f;
}


void s2h_progress(inout ContextGather ui, uint widthInCharacters, float fraction)
{
	float4 color = ui.buttonColor;
	float4 outerAABB = float4(ui.pxCursor, ui.pxCursor + float2(float(widthInCharacters) * s2h_fontSize(), s2h_fontSize() - 2.0f) * ui.scale);
	outerAABB += 0.5f;

	// shrink
	float4 innerAABB = outerAABB + float4(1, 1, -1, -1) * ui.scale;

	innerAABB.z = lerp(innerAABB.x, innerAABB.z, saturate(fraction));

	float sliderDist = s2h_computeDistToBox(ui, ui.pxPos, outerAABB);
	float innerDist = s2h_computeDistToBox(ui, ui.pxPos, innerAABB);

	float4 localColor = float4(0,0,0,0);

	// no AA for now
	if(sliderDist <= 0.0f)
		localColor = color;

	if(innerDist <= 0.0f)
		localColor = lerp(localColor, float4(ui.textColor.rgb, 1), ui.textColor.a);

	ui.pxCursor.x += float(widthInCharacters) * s2h_fontSize() * ui.scale;

	ui.dstColor = lerp(ui.dstColor, float4(localColor.rgb, 1), localColor.a * (1.0f - ui.dstColor.a));
}


void s2h_sliderFloat(inout ContextGather ui, uint widthInCharacters, inout float value, float minValue, float maxValue)
{
	float4 color = ui.buttonColor; 
	float4 outerAABB = float4(ui.pxCursor, ui.pxCursor + float2(float(widthInCharacters) * s2h_fontSize(), s2h_fontSize() - 2.0f) * ui.scale);
 	outerAABB += 0.5f;

	float halfChar = s2h_fontSize() / 2.0f;
 
	// shrink 
	float4 innerAABB = outerAABB + float4(1, 1, -1, -1) * ui.scale;
 
	float sliderDist = s2h_computeDistToBox(ui, ui.pxPos, outerAABB);
 
	// todo: active button should be made for all UI interactive buttons (checkbox, radio, button)
	float2 currentMouse = (ui.s2h_State.x == 0 && ui.s2h_State.y == 0) ? ui.mouseInput.xy : float2(ui.s2h_State.xy);
 
	bool mouseOver = s2h_computeDistToBox(ui, currentMouse, outerAABB) <= 0.0f;
 
	float3 knobColor = ui.textColor.rgb; 

	// mouse over and left mouse button pressed
	if(mouseOver && ui.mouseInput.z != 0.0f)
	{ 
		float newFraction = saturate((ui.mouseInput.xy.x - innerAABB.x) / (innerAABB.z - innerAABB.x)); 
		value = lerp(minValue, maxValue, newFraction); 
 
		knobColor = float3(1, 1, 1); 
 
		// todo: active button should be made for all UI interactive buttons (checkbox, radio, button)
		if(ui.s2h_State.x == 0 && ui.s2h_State.y == 0)
			ui.s2h_State.xy = int2(ui.mouseInput.xy);
	} 
 
	float fraction = saturate((value - minValue) / (maxValue - minValue));

	float knobRange = (float(widthInCharacters) - 1.0f) * s2h_fontSize() * ui.scale;
	float2 knobPos = ui.pxCursor + float2(halfChar * ui.scale, 0.0f) + float2(fraction * knobRange, 3.0f * ui.scale);
	float2 knobSize = float2(s2h_fontSize() - 4.0f, s2h_fontSize() - 4.0f) * 0.5f * ui.scale;
	float4 knobAABB = float4(knobPos - knobSize, knobPos + knobSize);
 	knobAABB += 0.5f;

	float knobDist = s2h_computeDistToBox(ui, ui.pxPos, knobAABB);

	float4 localColor = float4(0,0,0,0);

	if(mouseOver && sliderDist <= 2.0)
		localColor = float4(1, 1, 1 ,1);

	// no AA for now
	if(sliderDist <= 0.0f)
		localColor = color;

//	if(innerDist <= 0.0f)
//		localColor = lerp(localColor, float4(ui.textColor.rgb, 1), ui.textColor.a);

	if(knobDist <= 0.0f)
		localColor = lerp(localColor, float4(knobColor, 1), ui.textColor.a);

	ui.pxCursor.x += float(widthInCharacters) * s2h_fontSize() * ui.scale;

	ui.dstColor = lerp(ui.dstColor, float4(localColor.rgb, 1), localColor.a * (1.0f - ui.dstColor.a));
} 

void s2h_sliderRGB(inout ContextGather ui, uint widthInCharacters, inout float3 value)
{
	float r = 3.0f * s2h_fontSize() * 0.5f * ui.scale - 1.0f;
	float4 backup = ui.buttonColor;

	float2 initialPos = ui.pxCursor;
	float2 pos = initialPos + float2(3.0f * s2h_fontSize() * ui.scale, 0.0f);

	ui.pxCursor.x = pos.x;
	ui.buttonColor = float4(1,0.1f,0.1f,1);
	s2h_sliderFloat(ui, widthInCharacters - 3u, value.r, 0.0f, 1.0f);
	s2h_printLF(ui);

	ui.pxCursor.x = pos.x;
	ui.buttonColor = float4(0,1,0,1);
	s2h_sliderFloat(ui, widthInCharacters - 3u, value.g, 0.0f, 1.0f);
	s2h_printLF(ui);

	ui.pxCursor.x = pos.x;
	ui.buttonColor = float4(0.2f,0.2f,1,1);
	s2h_sliderFloat(ui, widthInCharacters - 3u, value.b, 0.0f, 1.0f);
	s2h_printLF(ui);

	// todo: don't abuse circle drawing for disk drawing
	// todo: check if sRGB blending is right, it looks wrong with white
	s2h_drawDisc(ui, initialPos + r, r, float4(value, 1));

	ui.pxCursor = initialPos + float2(float(widthInCharacters) * s2h_fontSize() * ui.scale, 0.0f);

	ui.buttonColor = backup;
}

void s2h_sliderRGBA(inout ContextGather ui, uint widthInCharacters, inout float4 value)
{
	float r = 3.0f * s2h_fontSize() * 0.5f * ui.scale - 1.0f;
	float4 backup = ui.buttonColor;

	float2 initialPos = ui.pxCursor;
	float2 pos = initialPos + float2(3.0f * s2h_fontSize() * ui.scale, 0.0f);

	ui.pxCursor.x = pos.x;
	ui.buttonColor = float4(1,0.1f,0.1f,1);
	s2h_sliderFloat(ui, widthInCharacters - 3u, value.r, 0.0f, 1.0f);
	s2h_printLF(ui);

	ui.pxCursor.x = pos.x;
	ui.buttonColor = float4(0,1,0,1);
	s2h_sliderFloat(ui, widthInCharacters - 3u, value.g, 0.0f, 1.0f);
	s2h_printLF(ui);

	ui.pxCursor.x = pos.x;
	ui.buttonColor = float4(0.2f,0.2f,1,1);
	s2h_sliderFloat(ui, widthInCharacters - 3u, value.b, 0.0f, 1.0f);
	s2h_printLF(ui);

	ui.pxCursor.x = pos.x;
	ui.buttonColor = float4(0.5f,0.5f,0.5f,1);
	s2h_sliderFloat(ui, widthInCharacters - 3u, value.a, 0.0f, 1.0f);
	s2h_printLF(ui);

	// todo: don't abuse circle drawing for disk drawing
	// todo: check if sRGB blending is right, it looks wrong with white
	s2h_drawDisc(ui, initialPos + r, r, value);

	ui.pxCursor = initialPos + float2(float(widthInCharacters) * s2h_fontSize() * ui.scale, 0.0f);

	ui.buttonColor = backup;
}

void s2h_tableInt(inout ContextGather ui, uint column, float4 backgroundColor, int2 sizeInCharacters, bool goRightNotDown) 
{ 
	float pxCharSize = s2h_fontSize() * ui.scale;
	float2 backup = ui.pxCursor; 
	float2 localPos = ui.pxPos - ui.pxCursor; 
	float2 pxSize = float2(sizeInCharacters) * pxCharSize; 
 
	if(localPos.x >= 0.0f && localPos.y >= 0.0f && localPos.x < pxSize.x && localPos.y < pxSize.y) 
	{ 
		ui.dstColor = lerp(ui.dstColor, float4(backgroundColor.rgb, 1), backgroundColor.a * (1.0f - ui.dstColor.a)); 
	 
		int row = int(localPos.y / pxCharSize);
 
		ui.pxCursor.y = backup.y + floor(localPos.y / pxCharSize) * pxCharSize; 
 
		int value = 0; 
		if(s2h_tableLookupInt(column, row, value)) 
		{ 
			s2h_printInt(ui, value); 
		} 
	} 
	if(goRightNotDown) 
	{ 
		ui.pxCursor.x = backup.x + pxSize.x; 
	} 
	else 
	{ 
		s2h_printLF(ui); 
		ui.pxCursor.y = backup.y + pxSize.y; 
	} 
} 
 
void s2h_tableFloat(inout ContextGather ui, uint column, float4 backgroundColor, int2 sizeInCharacters, bool goRightNotDown) 
{ 
	float pxCharSize = s2h_fontSize() * ui.scale;
	float2 backup = ui.pxCursor;
	float2 localPos = ui.pxPos - ui.pxCursor;
	float2 pxSize = float2(sizeInCharacters) * pxCharSize;
 
	if(localPos.x >= 0.0f && localPos.y >= 0.0f && localPos.x < pxSize.x && localPos.y < pxSize.y) 
	{ 
		ui.dstColor = lerp(ui.dstColor, float4(backgroundColor.rgb, 1), backgroundColor.a * (1.0f - ui.dstColor.a)); 
	 
		int row = int(localPos.y / pxCharSize);
 
		ui.pxCursor.y = backup.y + floor(localPos.y / pxCharSize) * pxCharSize; 
 
		float value = 0.0f; 
		if(s2h_tableLookupFloat(column, row, value)) 
		{ 
			s2h_printFloat(ui, value); 
		} 
	} 
	if(goRightNotDown) 
	{ 
		ui.pxCursor.x = backup.x + pxSize.x; 
	} 
	else 
	{ 
		s2h_printLF(ui); 
		ui.pxCursor.y = backup.y + pxSize.y; 
	} 
} 
 
void s2h_function(inout ContextGather ui, uint functionId, float4 backgroundColor, int2 sizeInCharacters, float2 rangeX, float2 rangeY) 
{ 
	float scaledFontSize = s2h_fontSize() * ui.scale;

	float2 backup = ui.pxCursor; 
	float2 localPos = ui.pxPos - ui.pxCursor; 
	float2 pxSize = float2(sizeInCharacters) * scaledFontSize; 
 
	if(localPos.x >= 0.0f && localPos.y >= 0.0f && localPos.x < pxSize.x && localPos.y < pxSize.y) 
	{
		// rangeX.x .. rangeX.y
		float x = lerp(rangeX.x, rangeX.y, localPos.x / pxSize.x); 

		ui.dstColor = lerp(ui.dstColor, float4(backgroundColor.rgb, 1), backgroundColor.a * (1.0f - ui.dstColor.a)); 
 
		int row = int(localPos.y / scaledFontSize);
 
		ui.pxCursor.y = backup.y + floor(localPos.y / scaledFontSize) * scaledFontSize; 
 
		// rangeY.x .. rangeY.y
		float y = s2h_floatLookupFloat(functionId, x);
		// 0 .. pxSize.y
		float pxY = (1.0f - (y - rangeY.x) / (rangeY.y - rangeY.x)) * pxSize.y; 
 
		if(pxY < localPos.y) 
			ui.dstColor = lerp(ui.dstColor, float4(ui.textColor.rgb, 1), ui.textColor.a);
	} 
 
	s2h_printLF(ui); 
	ui.pxCursor.y = backup.y + pxSize.y; 
} 
float3 s2h_accurateLinearToSRGB(float3 linearCol)
{
	float3 sRGBLo = linearCol * 12.92;
	float3 sRGBHi = (pow(abs(linearCol), float3(1.0 / 2.4, 1.0 / 2.4, 1.0 / 2.4)) * 1.055) - 0.055;
	float3 sRGB;
	sRGB.r = linearCol.r <= 0.0031308 ? sRGBLo.r : sRGBHi.r;
	sRGB.g = linearCol.g <= 0.0031308 ? sRGBLo.g : sRGBHi.g;
	sRGB.b = linearCol.b <= 0.0031308 ? sRGBLo.b : sRGBHi.b;
	return sRGB;
}

float3 s2h_accurateSRGBToLinear(float3 sRGBCol)
{
	float3 linearRGBLo = sRGBCol / 12.92;
	float3 linearRGBHi = pow((sRGBCol + 0.055) / 1.055, float3(2.4, 2.4, 2.4));
	float3 linearRGB;
	linearRGB.r = sRGBCol.r <= 0.04045 ? linearRGBLo.r : linearRGBHi.r;
	linearRGB.g = sRGBCol.g <= 0.04045 ? linearRGBLo.g : linearRGBHi.g;
	linearRGB.b = sRGBCol.b <= 0.04045 ? linearRGBLo.b : linearRGBHi.b;
	return linearRGB;
}

float3 s2h_indexToColor(uint index)
{
	uint a = (index >> 0u) & 1u;
	uint d = (index >> 1u) & 1u;
	uint g = (index >> 2u) & 1u;

	uint b = (index >> 3u) & 1u;
	uint e = (index >> 4u) & 1u;
	uint h = (index >> 5u) & 1u;

	uint c = (index >> 6u) & 1u;
	uint f = (index >> 7u) & 1u;
	uint i = (index >> 8u) & 1u;

	return float3(a * 4u + b * 2u + c, d * 4u + e * 2u + f, g * 4u + h * 2u + i) / 7.0f;
}

float3 s2h_colorRampRGB(float value)
{
	return float3(
		saturate(1.0f - abs(value) * 2.0f),
		saturate(1.0f - abs(value - 0.5f) * 2.0f),
		saturate(1.0f - abs(value - 1.0f) * 2.0f));
}

#endif // S2H_INCLUDE 
