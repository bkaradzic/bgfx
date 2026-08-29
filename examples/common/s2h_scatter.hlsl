//////////////////////////////////////////////////////////////////////////
//   Shader To Human (S2H) - HLSL/GLSL library for debugging shaders    //
//  Copyright (c) 2024-2025 Electronic Arts Inc.  All rights reserved.  //
//////////////////////////////////////////////////////////////////////////

// Example:
// #include "s2h/s2h.hlsl"
// #include "s2h/s2h_scatter.hlsl"
// {
//   struct ContextScatter ui;
//   s2h_init(ui);
//   s2h_printTxt(ui, _A, _B);
// }
// void onGfxForAllScatter(int2 pxPos, float4 color) 
// {
//	 g_computeOutput[pxPos] = color;
// }

#ifndef S2H_SCATTER_INCLUDE
#define S2H_SCATTER_INCLUDE

// HLSL accepts loop attributes directly, while GLSL and bgfx use macros.
// s2h_bgfx.sh supplies S2H_LOOP as bgfx's portable LOOP macro.
#ifndef S2H_LOOP
	#ifdef S2H_GLSL
		#define S2H_LOOP
	#else
		#define S2H_LOOP [loop]
	#endif
#endif

// documentation:
struct ContextScatter
{
	// RGBA, alpha 1 is assumed to be opaque
	float4 textColor;

	// private, for internal use, might change --------

	// in pixels
	int2 pxCursor;
	// window left top, set by s2h_init()
	int pxLeftX;
	// 1/2/3/4, call s2h_setScale()
	int scale;
};

// first call this
void s2h_init(out ContextScatter ui);
// set text cursor position, next printLF() will reset to this x position
void s2h_setCursor(inout ContextScatter ui, float2 inpxLeftTop);
// @param scale 1:pixel perfect, 2:2x, 3:3x, ..
void s2h_setScale(inout ContextScatter ui, uint scale);
// e.g. ui.s2h_printTxt('I', ' ', 'a', 'm');
// @param a ascii character or 0
void s2h_printTxt(inout ContextScatter ui, uint a, uint b, uint c, uint d, uint e, uint f);
// jump to next line
void s2h_printLF(inout ContextScatter ui);
// @param value e.g. 123, 0
void s2h_printInt(inout ContextScatter ui, int value);
// print hexadecimal e.g. "0000aa34"
// @param value 32bit e.g. 0x123, 0xff00
void s2h_printHex(inout ContextScatter ui, uint value);
// @param output e.g. g_output from RWTexture2D<float3> g_output : register(u0, space0);
// @param pos in pixels from left top, left top of the printout
// @param value
void s2h_printFloat(inout ContextScatter ui, float value);
// block in a 8x8 character
void s2h_printBlock(inout ContextScatter ui, float4 color);
// circle in a 8x8 character
void s2h_printDisc(inout ContextScatter ui, float4 color);
// don't use directly
void s2h_printCharacter(inout ContextScatter ui, uint ascii);
// no AA
void s2h_drawCrosshair(inout ContextScatter ui, float2 pxCenter, float pxRadius, float4 color);

// implementation ----------------------------------------------------------------------

void s2h_init(out ContextScatter ui)
{ 
	// white, opaque
	ui.textColor = float4(1, 1, 1, 1);
	ui.pxCursor = int2(0, 0);
	ui.pxLeftX = int(ui.pxCursor.x);
	ui.scale = 1;
} 

void s2h_setCursor(inout ContextScatter ui, float2 inpxLeftTop)
{
	ui.pxCursor = int2(inpxLeftTop);
	ui.pxLeftX = int(inpxLeftTop.x);
}

void s2h_setScale(inout ContextScatter ui, uint scale)
{
	ui.scale = int(scale);
}

// implement this in your code
void onGfxForAllScatter(int2 pxPos, float4 color);

void s2h_printCharacter(inout ContextScatter ui, uint ascii)
{
	S2H_LOOP for(int y = 0; y < 8 * ui.scale; ++y)
	S2H_LOOP for(int x = 0; x < 8 * ui.scale; ++x)
		if(s2h_fontLookup(ascii, int2(x, y) / ui.scale))
			onGfxForAllScatter(ui.pxCursor + int2(x, y), ui.textColor);

	ui.pxCursor.x += 8 * ui.scale;
}

void s2h_drawCrosshair(inout ContextScatter ui, float2 pxCenter, float pxRadius, float4 color)
{
	// avoiding int math for better performance
	onGfxForAllScatter(int2(pxCenter), ui.textColor);

	S2H_LOOP for(float i = 1; i < pxRadius; ++i)
	{
		onGfxForAllScatter(int2(pxCenter + float2(i, 0)), color);
		onGfxForAllScatter(int2(pxCenter + float2(-i, 0)), color);
		onGfxForAllScatter(int2(pxCenter + float2(0, i)), color);
		onGfxForAllScatter(int2(pxCenter + float2(0, -i)), color);
	}
}

void s2h_printTxt(inout ContextScatter ui, uint a)
{
	s2h_printCharacter(ui, a); 
}
// glsl has no default arguments to we implement multiple functions instead making porting easier
void s2h_printTxt(inout ContextScatter ui, uint a, uint b)
{ s2h_printTxt(ui, a); s2h_printCharacter(ui, b); }
void s2h_printTxt(inout ContextScatter ui, uint a, uint b, uint c)
{ s2h_printTxt(ui, a, b); s2h_printCharacter(ui, c); }
void s2h_printTxt(inout ContextScatter ui, uint a, uint b, uint c, uint d)
{ s2h_printTxt(ui, a, b, c); s2h_printCharacter(ui, d); }
void s2h_printTxt(inout ContextScatter ui, uint a, uint b, uint c, uint d, uint e)
{ s2h_printTxt(ui, a, b, c, d); s2h_printCharacter(ui, e); }
void s2h_printTxt(inout ContextScatter ui, uint a, uint b, uint c, uint d, uint e, uint f)
{ s2h_printTxt(ui, a, b, c, d, e); s2h_printCharacter(ui, f); }

void s2h_printLF(inout ContextScatter ui)
{
	ui.pxCursor.x = ui.pxLeftX;
	ui.pxCursor.y += 8 * ui.scale;
}

void s2h_printInt(inout ContextScatter ui, int value)
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
			ui.pxCursor.x += 8 * ui.scale;
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
			ui.pxCursor.x -= 8 * ui.scale;
			s2h_printCharacter(ui, _0 + digit);
			// counter +=8 from printCharacter ()
			ui.pxCursor.x -= 8 * ui.scale;
		}
		ui.pxCursor.x = int(backup);
	}
}

void s2h_printHex(inout ContextScatter ui, uint value)
{
	// 8 nibbles
	for(int i = 7; i >= 0; --i)
	{
		// 0..15
		uint nibble = (value >> (i * 4)) & 0xf;
		uint start = (nibble < 10) ? _0 : (_A - 10u);
		s2h_printCharacter(ui, start + nibble);
	}
}

void s2h_printFloat(inout ContextScatter ui, float value)
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

void s2h_printBlock(inout ContextScatter ui, float4 color)
{
	S2H_LOOP for(int y = 0; y < 8 * ui.scale; ++y)
	S2H_LOOP for(int x = 0; x < 8 * ui.scale; ++x)
	{
		float2 pxLocal = (float2(x, y) ) / ui.scale - float2(3.5f, 3.5f);

		float mask = saturate(4 - max(abs(pxLocal.x), abs(pxLocal.y)));

		if(mask > 0.0f)
			onGfxForAllScatter(ui.pxCursor + int2(x,y), color);
	}

	ui.pxCursor.x += 8 * ui.scale;
}

void s2h_printDisc(inout ContextScatter ui, float4 color)
{
	S2H_LOOP for(int y = 0; y < 8 * ui.scale; ++y)
	S2H_LOOP for(int x = 0; x < 8 * ui.scale; ++x)
	{
		float2 pxLocal = (float2(x, y) ) / ui.scale - float2(3.5f, 3.5f);

		float mask = saturate(4 - length(pxLocal));

		if(mask > 0.0f)
			onGfxForAllScatter(ui.pxCursor + int2(x,y), color);
	}

	ui.pxCursor.x += 8 * ui.scale;
}

#endif // S2H_SCATTER_INCLUDE
