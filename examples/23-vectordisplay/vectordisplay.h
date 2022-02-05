/*
 * Copyright 2014 Kai Jourdan. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef __VECTORDISPLAY_H__
#define __VECTORDISPLAY_H__

#include <bgfx/bgfx.h>

#include <tinystl/allocator.h>
#include <tinystl/vector.h>
namespace stl = tinystl;

struct PosColorUvVertex
{
	float m_x;
	float m_y;
	float m_z;
	float m_u;
	float m_v;
	uint32_t m_abgr;

	static void init();
	static bgfx::VertexLayout ms_layout;
};

class VectorDisplay
{
public:
	VectorDisplay();

	~VectorDisplay()
	{
	}

	void init(bool _originBottomLeft, float _texelHalf);

	void setup(uint16_t _width, uint16_t _height, uint8_t _view = 2);
	void resize(uint16_t _width, uint16_t _height);
	void teardown();

	void beginFrame();
	void endFrame();

	// Draw a series of connected line segments.
	void beginDraw(float _x, float _y);
	void drawTo(float _x, float _y);
	void endDraw();

	//HighLevel draw functions
	void drawLine(float _x0, float _y0, float _x1, float _y1);
	void drawBox(float _x, float _y, float _w, float _h);
	void drawCircle(float _x, float _y, float _radius, float _steps);
	void drawWheel(float _spokeangle, float _x, float _y, float _radius);

	//Font Stuff (Simplex)
	//void simplexMeasure(float _scale, const char *_string, float *_outWidth, float *_outHeight);
	void drawSimplexFont(float _x, float _y, float _scale, const char* _string);

	// Set the current drawing color
	void setDrawColor(float _r, float _g, float _b, float _a = 1.0f);

	// Set the number of frames of decay/fade to apply to the scene.
	bool setDecaySteps(int _steps);

	// Set the brightness multiplier applied on each decay frame after the first.
	bool setDecay(float _decay);

	// Set the brightness multiplier applied on the first decay frame.
	bool setInitialDecay(float _initialDecay);

	// Set a 2d transformation for the display.
	//
	// This relates logical coordinates, as passed to vector_display_begin_draw,
	// vector_display_draw_to, and vector_display_draw, to coordinates from (0,0)
	// to (width,height) in the destination framebuffer.
	//
	// The parameters impact coordinates as follows:
	//
	//      framebuffer_x = x * scale + offset_x
	//      framebuffer_y = y * scale + offset_y
	//
	void setTransform(float _offsetX, float _offsetY, float _scale);

	// Set the line thickness.
	//
	// The line thickness is measured in scene coordinates, and includes all pixels lit by
	// the line before any post-processing. The apparent width of the line to the viewer
	// is significantly narrower, since brightness decays exponentially to zero within the
	// bounds of the line.
	//
	// Thickness, by default, is guessed based on width and height.
	//
	// This function clears the display.
	bool setThickness(float _thickness);
	void setDefaultThickness();

	// Set the "brightness" of the display
	//
	// useful values range from [0.5, 1.5]. 0.0 disables all glow effects.
	//
	// Due to implementation details of the glow effect, glow is related to
	// the pixel density of the framebuffer. It may require adjustment,
	// particularly when moving between devices of very different pixel density.
	//
	void setBrightness(float _brightness);

	// Get the size from a vector display.
	void getSize(float* _outWidth, float* _outHeight);

protected:
	void screenSpaceQuad(float _textureWidth, float _textureHeight, float _width = 1.0f, float _height = 1.0f);

	struct PendingPoint
	{
		float x, y;
	};

	struct Line
	{
		float x0, y0, x1, y1;                     // nominal points
		float a;                                  // angle
		float sin_a, cos_a;                       // precomputed trig

		float xl0, yl0, xl1, yl1;                 // left side of the box
		float xr0, yr0, xr1, yr1;                 // right side of the box

		int is_first, is_last;
		int has_next, has_prev;                    // booleans indicating whether this line connects to prev/next

		float xlt0, ylt0, xlt1, ylt1;             // coordinates of endcaps (if !has_prev/!has_next)
		float xrt0, yrt0, xrt1, yrt1;             // coordinates of endcaps (if !has_prev/!has_next)

		float tl0, tl1, tr0, tr1;

		float s0, s1;                             // shorten line by this amount

		float len;
	};

	float effectiveThickness();
	void setupResDependent();
	void teardownResDependent();

	void appendTexpoint(float _x, float _y, float _u, float _v);

	void drawFan(float _cx, float _cy, float _pa, float _a, float _t, float _s, float _e);
	void drawLines(Line* _lines, int _numberLines);
	void genLinetex();

	bool m_originBottomLeft;
	float m_texelHalf;

	bgfx::ProgramHandle m_drawToScreenShader;   // program for drawing to the framebuffer
	bgfx::ProgramHandle m_blurShader;           // program for gaussian blur
	bgfx::ProgramHandle m_blitShader;

	bgfx::UniformHandle u_params;
	bgfx::UniformHandle s_texColor;

	bgfx::FrameBufferHandle m_sceneFrameBuffer;
	bgfx::FrameBufferHandle m_glow0FrameBuffer; // framebuffer for glow pass 0
	bgfx::FrameBufferHandle m_glow1FrameBuffer; // framebuffer for glow pass 1

	uint8_t m_view;

	uint16_t m_screenWidth, m_screenHeight;
	uint16_t m_glowWidth, m_glowHeight;

	int m_numberDecaySteps;
	float m_decayValue;
	uint8_t m_drawColorR;
	uint8_t m_drawColorG;
	uint8_t m_drawColorB;
	uint8_t m_drawColorA;

	stl::vector<PosColorUvVertex> m_points;
	stl::vector<PendingPoint> m_pendingPoints;

	int m_currentDrawStep;
	stl::vector<bgfx::DynamicVertexBufferHandle> m_vertexBuffers;
	stl::vector<int> m_vertexBuffersSize;

	bgfx::TextureHandle m_lineTexId;

	float m_initialDecay;

	float m_thickness;
	bool m_customThicknessEnabled;

	float m_brightness;

	float m_drawOffsetX, m_drawOffsetY;
	float m_drawScale;
};

#endif // __VECTORDISPLAY_H__
