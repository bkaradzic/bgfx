/*
 * Copyright 2014 Kai Jourdan. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

// Reference(s):
// - Based on code from Brian Luczkiewicz
//   https://github.com/blucz/Vector
// - Uses the SIMPLEX-Font which is a variant of the Hershey font (public domain)
//   https://web.archive.org/web/20120313001837/http://paulbourke.net/dataformats/hershey/
//
#include <float.h>  // FLT_EPSILON
#include <alloca.h> // alloca

#include <bx/math.h>

#include "vectordisplay.h"
#include "bgfx_utils.h"

//Config stuff
const int MAX_NUMBER_VERTICES = 20000;

const int MAX_DECAY_STEPS = 60;
const int DEFAULT_DECAY_STEPS = 5;
const float DEFAULT_DECAY_VALUE = 0.8f;
const float DEFAULT_INITIAL_DECAY = 0.04f;
const float DEFAULT_DRAW_OFFSET_X = 0.0f;
const float DEFAULT_DRAW_OFFSET_Y = 0.0f;
const float DEFAULT_DRAW_SCALE = 1.0f;
const float DEFAULT_BRIGHTNESS = 1.0f;

//internal config
const int TEXTURE_SIZE = 64;
const int HALF_TEXTURE_SIZE = TEXTURE_SIZE / 2;

void PosColorUvVertex::init()
{
	ms_layout
		.begin()
		.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
		.end();
}

bgfx::VertexLayout PosColorUvVertex::ms_layout;

inline float normalizef(float _a)
{
	return bx::wrap(_a, 2.0f * bx::kPi);
}

VectorDisplay::VectorDisplay()
	: m_originBottomLeft(false)
	, m_texelHalf(false)
{
}

void VectorDisplay::init(bool _originBottomLeft, float _texelHalf)
{
	m_originBottomLeft = _originBottomLeft;
	m_texelHalf = _texelHalf;
}


void VectorDisplay::setup(uint16_t _width, uint16_t _height, uint8_t _view)
{
	PosColorUvVertex::init();

	m_decayValue = DEFAULT_DECAY_VALUE;
	setDrawColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_screenWidth  = _width;
	m_screenHeight = _height;
	m_glowWidth    = m_screenWidth / 3;
	m_glowHeight   = m_screenHeight / 3;
	m_initialDecay = DEFAULT_INITIAL_DECAY;

	m_drawOffsetX = DEFAULT_DRAW_OFFSET_X;
	m_drawOffsetY = DEFAULT_DRAW_OFFSET_Y;
	m_drawScale   = DEFAULT_DRAW_SCALE;
	m_brightness  = DEFAULT_BRIGHTNESS;

	m_currentDrawStep = 0;

	setDefaultThickness();

	setDecaySteps(DEFAULT_DECAY_STEPS);

	m_view = _view;

	m_drawToScreenShader = loadProgram("vs_vectordisplay_fb", "fs_vectordisplay_fb");
	m_blurShader         = loadProgram("vs_vectordisplay_fb", "fs_vectordisplay_blur");
	m_blitShader         = loadProgram("vs_vectordisplay_fb", "fs_vectordisplay_blit");

	u_params   = bgfx::createUniform("u_params",   bgfx::UniformType::Vec4);
	s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);

	genLinetex();

	bgfx::setViewClear(_view, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000ff, 1.0f, 0);

	setupResDependent();
}

void VectorDisplay::resize(uint16_t _width, uint16_t _height)
{
	teardownResDependent();
	m_screenWidth = _width;
	m_screenHeight = _height;
	m_glowWidth = _width / 3;
	m_glowHeight = _height / 3;
	setupResDependent();
}

void VectorDisplay::teardown()
{
	for (size_t i = 0; i < m_vertexBuffers.size(); ++i)
	{
		bgfx::destroy(m_vertexBuffers[i]);
	}

	teardownResDependent();

	bgfx::destroy(m_drawToScreenShader);
	bgfx::destroy(m_blurShader);
	bgfx::destroy(m_blitShader);

	bgfx::destroy(u_params);
	bgfx::destroy(s_texColor);

	bgfx::destroy(m_lineTexId);
}

void VectorDisplay::beginFrame()
{
	m_points.clear();
}

void VectorDisplay::endFrame()
{
	const bgfx::Caps* caps = bgfx::getCaps();

	float proj[16];
	bx::mtxOrtho(
		  proj
		, 0.0f
		, (float)m_screenWidth
		, (float)m_screenHeight
		, 0.0f
		, 0.0f
		, 1000.0f
		, 0.0f
		, caps->homogeneousDepth
		);

	bgfx::setViewRect(m_view, 0, 0, m_screenWidth, m_screenHeight);
	bgfx::setViewFrameBuffer(m_view, m_sceneFrameBuffer);
	bgfx::setViewTransform(m_view, NULL, proj);

	// advance step
	m_currentDrawStep = (m_currentDrawStep + 1) % m_numberDecaySteps;

	BX_ASSERT(m_points.size() < MAX_NUMBER_VERTICES, "");

	bgfx::update(
		  m_vertexBuffers[m_currentDrawStep]
		, 0
		, bgfx::copy(m_points.data(), (uint32_t)m_points.size() * sizeof(PosColorUvVertex) )
		);
	m_vertexBuffersSize[m_currentDrawStep] = (uint32_t)m_points.size();

	for (int loopvar = 0; loopvar < m_numberDecaySteps; loopvar++)
	{
		int stepi = m_numberDecaySteps - loopvar - 1;
		int i = (m_currentDrawStep + m_numberDecaySteps - stepi) % m_numberDecaySteps;

		if (m_vertexBuffersSize[i] != 0)
		{
			float alpha;
			if (stepi == 0)
			{
				alpha = 1.0f;
			}
			else if (stepi == 1)
			{
				alpha = m_initialDecay;
			}
			else
			{
				alpha = bx::pow(m_decayValue, stepi - 1.0f) * m_initialDecay;
			}

			float params[4] = { 0.0f, 0.0f, 0.0f, alpha };
			bgfx::setUniform(u_params, &params);

			bgfx::setTexture(0, s_texColor, m_lineTexId);

			bgfx::setVertexBuffer(0, m_vertexBuffers[i], 0, m_vertexBuffersSize[i]); // explicitly feed vertex number!

			bgfx::setState(0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_DST_ALPHA)
				| BGFX_STATE_BLEND_EQUATION_SEPARATE(BGFX_STATE_BLEND_EQUATION_ADD, BGFX_STATE_BLEND_EQUATION_MAX)
				);

			bgfx::setViewName(m_view, "RenderVectorDisplay");
			bgfx::submit(m_view, m_drawToScreenShader);
		}
	}

	uint8_t viewCounter = m_view + 1;

	bx::mtxOrtho(proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f, 0.0f, caps->homogeneousDepth);

	float glow_iter_mult = 1.05f + ( (m_brightness - 1.0f) / 5.0f);
	float glow_fin_mult  = 1.25f + ( (m_brightness - 1.0f) / 2.0f);
	float params[4] =  { 0.0f, 0.0f, glow_iter_mult, 1.0f };

	if (m_brightness > 0)
	{
		bgfx::setTexture(0, s_texColor, bgfx::getTexture(m_sceneFrameBuffer) );

		int npasses = (int)(m_brightness * 4);
		for (int pass = 0; pass < npasses; pass++)
		{
			// render the glow1 texture to the glow0 buffer with horizontal blur

			bgfx::setViewFrameBuffer(viewCounter, m_glow0FrameBuffer);
			bgfx::setViewRect(viewCounter, 0, 0, m_glowWidth, m_glowHeight);
			bgfx::setState(0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				);
			params[0] = 1.0f / m_glowWidth;
			params[1] = 0.0f;
			bgfx::setUniform(u_params, &params);

			bgfx::setViewTransform(viewCounter, NULL, proj);
			screenSpaceQuad(m_glowWidth, m_glowHeight);
			bgfx::setViewName(viewCounter, "BlendPassA");
			bgfx::submit(viewCounter, m_blurShader);

			viewCounter++;

			bgfx::setViewFrameBuffer(viewCounter, m_glow1FrameBuffer);
			bgfx::setViewRect(viewCounter, 0, 0, m_glowWidth, m_glowHeight);
			bgfx::setTexture(0, s_texColor, bgfx::getTexture(m_glow0FrameBuffer) );

			bgfx::setViewTransform(viewCounter, NULL, proj);
			screenSpaceQuad(m_glowWidth, m_glowHeight);

			params[0] = 0.0f;
			params[1] = 1.0f / m_glowHeight;
			params[2] = glow_iter_mult;
			params[3] = 1.0f;
			bgfx::setUniform(u_params, params);

			bgfx::setState(0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				);

			bgfx::setViewName(viewCounter, "BlendPassB");
			bgfx::submit(viewCounter, m_blurShader);

			viewCounter++;

			//set for next iteration
			bgfx::setTexture(0, s_texColor, bgfx::getTexture(m_glow1FrameBuffer) );
		}
	}

	bgfx::discard();

	//now do last pass, combination of blur and normal buffer to screen
	bgfx::setViewTransform(viewCounter, NULL, proj);
	bgfx::setViewRect(viewCounter, 0, 0, m_screenWidth, m_screenHeight);
	bgfx::setTexture(0, s_texColor, bgfx::getTexture(m_sceneFrameBuffer) );
	bgfx::setState(0
		| BGFX_STATE_WRITE_RGB
		| BGFX_STATE_WRITE_A
		| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE)
		);

	params[2] = 1.0f;
	params[3] = 1.0f;
	bgfx::setUniform(u_params, params);
	bgfx::setViewName(viewCounter, "BlendVectorToDisplay");
	screenSpaceQuad(m_screenWidth, m_screenHeight);
	bgfx::submit(viewCounter, m_blitShader);
	viewCounter++;

	if (m_brightness > 0)
	{
		// blend in the glow
		bgfx::setViewTransform(viewCounter, NULL, proj);
		bgfx::setViewRect(viewCounter, 0, 0, m_screenWidth, m_screenHeight);
		bgfx::setTexture(0, s_texColor, bgfx::getTexture(m_glow1FrameBuffer) );
		bgfx::setState(0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE)
			);

		params[2] = glow_fin_mult;
		bgfx::setUniform(u_params, params);
		bgfx::setViewName(viewCounter, "BlendBlurToDisplay");
		screenSpaceQuad(m_screenWidth, m_screenHeight);
		bgfx::submit(viewCounter, m_blitShader);
		viewCounter++;
	}
}

void VectorDisplay::beginDraw(float _x, float _y)
{
	BX_ASSERT(0 == m_pendingPoints.size(), "Begin draw on already filled buffer!");

	PendingPoint point;
	point.x = _x * m_drawScale + m_drawOffsetX;
	point.y = _y * m_drawScale + m_drawOffsetY;
	m_pendingPoints.push_back(point);
}

void VectorDisplay::drawTo(float _x, float _y)
{
	PendingPoint point;
	point.x = _x * m_drawScale + m_drawOffsetX;
	point.y = _y * m_drawScale + m_drawOffsetY;
	m_pendingPoints.push_back(point);
}

void VectorDisplay::endDraw()
{
	if (m_pendingPoints.size() < 2)
	{
		m_pendingPoints.clear();
		return;
	}

	// from the list of points, build a list of lines
	uint32_t nlines = (uint32_t)m_pendingPoints.size() - 1;
	Line* lines = (Line*)alloca(nlines * sizeof(Line) );

	float t = effectiveThickness();
	int first_last_same = true
		&& bx::abs(m_pendingPoints[0].x - m_pendingPoints[m_pendingPoints.size() - 1].x) < 0.1
		&& bx::abs(m_pendingPoints[0].y - m_pendingPoints[m_pendingPoints.size() - 1].y) < 0.1
		;

	// compute basics
	for (size_t i = 1; i < m_pendingPoints.size(); i++)
	{
		Line* line = &lines[i - 1];
		line->is_first = i == 1;
		line->is_last = i == nlines;

		// precomputed info for current line
		line->x0 = m_pendingPoints[i - 1].x;
		line->y0 = m_pendingPoints[i - 1].y;
		line->x1 = m_pendingPoints[i].x;
		line->y1 = m_pendingPoints[i].y;
		line->a     = bx::atan2(line->y1 - line->y0, line->x1 - line->x0); // angle from positive x axis, increasing ccw, [-pi, pi]
		line->sin_a = bx::sin(line->a);
		line->cos_a = bx::cos(line->a);
		line->len   = bx::sqrt( (line->x1 - line->x0) * (line->x1 - line->x0) + (line->y1 - line->y0) * (line->y1 - line->y0) );

		// figure out what connections we have
		line->has_prev = (!line->is_first
		                 || (line->is_first
		                    && first_last_same) );
		line->has_next = (!line->is_last
		                 || (line->is_last
		                    && first_last_same) );

		// initialize thicknesses/shortens to default values
		line->tl0 = line->tl1 = line->tr0 = line->tr1 = t;
		line->s0 = line->s1 = 0.0;
	}

	// compute adjustments for connected line segments
	for (size_t i = 0; i < nlines; i++)
	{
		Line* line = &lines[i], * pline = &lines[(nlines + i - 1) % nlines];

		if (line->has_prev)
		{
			float pa2a = normalizef(pline->a - line->a);
			float a2pa = normalizef(line->a - pline->a);
			float maxshorten = bx::min(line->len, pline->len) / 2.0f;

			if (bx::min(a2pa, pa2a) <= (bx::kPi / 2.0f + FLT_EPSILON) )
			{
				if (a2pa < pa2a)
				{
					float shorten = t * bx::sin(a2pa / 2.0f) / bx::cos(a2pa / 2.0f);
					float a = (bx::kPi - a2pa) / 2.0f;
					if (shorten > maxshorten)
					{
						line->s0 = pline->s1 = maxshorten;
						line->tr0 = pline->tr1 = maxshorten * bx::sin(a) / bx::cos(a);
					}
					else
					{
						line->s0 = pline->s1 = shorten;
					}

					//vector_display_debugf("ad =  %f, shorten by %f (len=%f), rthickness %f (from %f)", a, line->s0, line->len, line->tr0, t);
				}
				else
				{
					float shorten = t * bx::sin(pa2a / 2.0f) / bx::cos(pa2a / 2.0f);
					float a = (bx::kPi - pa2a) / 2.0f;
					if (shorten > maxshorten)
					{
						line->s0  = pline->s1 = maxshorten;
						line->tl0 =
							pline->tl1 = maxshorten * bx::sin(a) / bx::cos(a);
					}
					else
					{
						line->s0 = pline->s1 = shorten;
					}

					//vector_display_debugf("ad =  %f, shorten by %f (len=%f), rthickness by %f (from %f)", a, line->s0, line->len, line->tl0, t);
				}
			}
			else
			{
				line->has_prev = 0;
			}
		}

		if (!line->has_prev)
		{
			pline->has_next = 0;
		}
	}

	// compute line geometry
	for (size_t i = 0; i < nlines; i++)
	{
		Line* line = &lines[i];

		// shorten lines if needed
		line->x0 = line->x0 + line->s0 * line->cos_a;
		line->y0 = line->y0 + line->s0 * line->sin_a;
		line->x1 = line->x1 - line->s1 * line->cos_a;
		line->y1 = line->y1 - line->s1 * line->sin_a;

		// compute initial values for left,right,leftcenter,rightcenter points
		line->xl0 = line->x0 + line->tl0 * line->sin_a;
		line->yl0 = line->y0 - line->tl0 * line->cos_a;
		line->xr0 = line->x0 - line->tr0 * line->sin_a;
		line->yr0 = line->y0 + line->tr0 * line->cos_a;
		line->xl1 = line->x1 + line->tl1 * line->sin_a;
		line->yl1 = line->y1 - line->tl1 * line->cos_a;
		line->xr1 = line->x1 - line->tr1 * line->sin_a;
		line->yr1 = line->y1 + line->tr1 * line->cos_a;

		// compute tips
		line->xlt0 = line->xl0 - t * line->cos_a;
		line->ylt0 = line->yl0 - t * line->sin_a;
		line->xrt0 = line->xr0 - t * line->cos_a;
		line->yrt0 = line->yr0 - t * line->sin_a;
		line->xlt1 = line->xl1 + t * line->cos_a;
		line->ylt1 = line->yl1 + t * line->sin_a;
		line->xrt1 = line->xr1 + t * line->cos_a;
		line->yrt1 = line->yr1 + t * line->sin_a;
	}

	// draw the lines
	drawLines(lines, nlines);
	m_pendingPoints.clear();
}

void VectorDisplay::drawLine(float _x0, float _y0, float _x1, float _y1)
{
	beginDraw(_x0, _y0);
	drawTo(_x1, _y1);
	endDraw();
}

void VectorDisplay::drawBox(float _x, float _y, float _w, float _h)
{
	beginDraw(_x, _y);
	drawTo(_x + _w, _y);
	drawTo(_x + _w, _y + _h);
	drawTo(_x, _y + _h);
	drawTo(_x, _y);
	endDraw();
}

void VectorDisplay::drawCircle(float _x, float _y, float _radius, float _steps)
{
	float edgeangle = 0.0f;
	float angadjust = 0.0f;

	float step = bx::kPi * 2.0f / _steps;

	beginDraw(_x + _radius * bx::sin(edgeangle + angadjust),
	          _y - _radius * bx::cos(edgeangle + angadjust) );
	for (edgeangle = 0; edgeangle < 2.0f * bx::kPi - 0.001; edgeangle += step)
	{
		drawTo(_x + _radius * bx::sin(edgeangle + step - angadjust),
		       _y - _radius * bx::cos(edgeangle + step - angadjust) );
	}

	endDraw();
}

void VectorDisplay::drawWheel(float _angle, float _x, float _y, float _radius)
{
	float spokeradius = _radius - 2.0f;
	// draw spokes
	drawLine(_x + spokeradius * bx::sin(_angle),
	         _y - spokeradius * bx::cos(_angle),
	         _x - spokeradius * bx::sin(_angle),
	         _y + spokeradius * bx::cos(_angle)
	         );
	drawLine(_x + spokeradius * bx::sin(_angle +        bx::kPi / 4.0f),
	         _y - spokeradius * bx::cos(_angle +        bx::kPi / 4.0f),
	         _x - spokeradius * bx::sin(_angle +        bx::kPi / 4.0f),
	         _y + spokeradius * bx::cos(_angle +        bx::kPi / 4.0f)
	         );
	drawLine(_x + spokeradius * bx::sin(_angle +        bx::kPi / 2.0f),
	         _y - spokeradius * bx::cos(_angle +        bx::kPi / 2.0f),
	         _x - spokeradius * bx::sin(_angle +        bx::kPi / 2.0f),
	         _y + spokeradius * bx::cos(_angle +        bx::kPi / 2.0f)
	         );
	drawLine(_x + spokeradius * bx::sin(_angle + 3.0f * bx::kPi / 4.0f),
	         _y - spokeradius * bx::cos(_angle + 3.0f * bx::kPi / 4.0f),
	         _x - spokeradius * bx::sin(_angle + 3.0f * bx::kPi / 4.0f),
	         _y + spokeradius * bx::cos(_angle + 3.0f * bx::kPi / 4.0f)
	         );

	float edgeangle = 0.0f;
	float angadjust = 0.0f;

	beginDraw(
		  _x + _radius * bx::sin(_angle + edgeangle + angadjust)
		, _y - _radius * bx::cos(_angle + edgeangle + angadjust)
		);

	for (edgeangle = 0; edgeangle < 2.0f * bx::kPi - 0.001f; edgeangle += bx::kPi / 4.0f)
	{
		drawTo(_x + _radius * bx::sin(_angle + edgeangle + bx::kPi / 4.0f - angadjust),
		       _y - _radius * bx::cos(_angle + edgeangle + bx::kPi / 4.0f - angadjust) );
	}

	endDraw();
}

float VectorDisplay::effectiveThickness()
{
	if (m_customThicknessEnabled)
	{
		return m_thickness * m_drawScale / 2.0f;
	}

	// this makes thickness=16 at 2048x1536
	float vv = (0.01f * (m_screenWidth + m_screenHeight) / 2.0f) * m_drawScale / 2.0f;
	return bx::max(vv, 6.0f);
}

void VectorDisplay::setTransform(float _offsetX, float _offsetY, float _scale)
{
	m_drawOffsetX = _offsetX;
	m_drawOffsetY = _offsetY;
	m_drawScale   = _scale;
}

bool VectorDisplay::setInitialDecay(float _initialDecay)
{
	if (_initialDecay < 0.0f
	   || _initialDecay >= 1.0f)
	{
		return false;
	}

	m_initialDecay = _initialDecay;
	return true;
}

bool VectorDisplay::setThickness(float _thickness)
{
	if (_thickness <= 0)
	{
		return false;
	}

	m_customThicknessEnabled = true;
	m_thickness = _thickness;
	return true;
}

void VectorDisplay::setDefaultThickness()
{
	m_customThicknessEnabled = false;
}

void VectorDisplay::setDrawColor(float _r, float _g, float _b, float _a)
{
	m_drawColorR = (uint8_t)(_r * 255);
	m_drawColorG = (uint8_t)(_g * 255);
	m_drawColorB = (uint8_t)(_b * 255);
	m_drawColorA = (uint8_t)(_a * 255);
}

void VectorDisplay::appendTexpoint(float _x, float _y, float _u, float _v)
{
	PosColorUvVertex point;
	point.m_x = _x;
	point.m_y = _y;
	point.m_z = 0.0;
	point.m_abgr = (m_drawColorA << 24) | (m_drawColorB << 16) | (m_drawColorG << 8) | m_drawColorR;
	point.m_u = _u / TEXTURE_SIZE;
	point.m_v = 1.0f - _v / TEXTURE_SIZE;
	m_points.push_back(point);
}

void VectorDisplay::drawFan(float _cx, float _cy, float _pa, float _a, float _t, float _s, float _e)
{
	float* angles;
	int nsteps;
	float pa2a = normalizef(_a - _pa);
	float a2pa = normalizef(_pa - _a);

	int i;
	if (a2pa < pa2a)
	{
		_t = -_t;
		nsteps = (int32_t)bx::max(1.0f, bx::round(a2pa / (bx::kPi / 8.0f) ) );
		angles = (float*)alloca(sizeof(float) * (nsteps + 1) );
		for (i = 0; i <= nsteps; i++)
		{
			angles[i] = _a + i * a2pa / nsteps;
		}
	}
	else
	{
		nsteps = (int32_t)bx::max(1.0f, bx::round(pa2a / (bx::kPi / 8.0f) ) );
		angles = (float*)alloca(sizeof(float) * (nsteps + 1) );
		for (i = 0; i <= nsteps; i++)
		{
			angles[i] = _pa + i * pa2a / nsteps;
		}
	}

	for (i = 1; i <= nsteps; i++)
	{
		appendTexpoint(_cx + _t * bx::sin(angles[i - 1]), _cy - _t * bx::cos(angles[i - 1]), _e, (float)HALF_TEXTURE_SIZE);
		appendTexpoint(_cx, _cy, _s, (float)HALF_TEXTURE_SIZE);
		appendTexpoint(_cx + _t * bx::sin(angles[i]), _cy - _t * bx::cos(angles[i]), _e, (float)HALF_TEXTURE_SIZE);
	}
}

void VectorDisplay::drawLines(Line* _lines, int _numberLines)
{
	int i;
	float t = effectiveThickness();

	for (i = 0; i < _numberLines; i++)
	{
		Line* line = &_lines[i], * pline = &_lines[(_numberLines + i - 1) % _numberLines];

		if (line->has_prev)     // draw fan for connection to previous
		{
			float pa2a = normalizef(pline->a - line->a);
			float a2pa = normalizef(line->a - pline->a);
			if (a2pa < pa2a)    // inside of fan on right
			{
				drawFan(line->xr0, line->yr0, pline->a, line->a, line->tl0 + line->tr0, (float)HALF_TEXTURE_SIZE + (line->tr0 / t * (float)HALF_TEXTURE_SIZE), 0);
			}
			else                // inside of fan on left
			{
				drawFan(line->xl0, line->yl0, pline->a, line->a, line->tl0 + line->tr0, (float)HALF_TEXTURE_SIZE - (line->tl0 / t * (float)HALF_TEXTURE_SIZE), (float)TEXTURE_SIZE);
			}
		}

		float tl0 = (float)HALF_TEXTURE_SIZE - (line->tl0 / t) * (float)HALF_TEXTURE_SIZE;
		float tl1 = (float)HALF_TEXTURE_SIZE - (line->tl1 / t) * (float)HALF_TEXTURE_SIZE;

		float tr0 = (float)HALF_TEXTURE_SIZE + (line->tr0 / t) * (float)HALF_TEXTURE_SIZE;
		float tr1 = (float)HALF_TEXTURE_SIZE + (line->tr1 / t) * (float)HALF_TEXTURE_SIZE;

		appendTexpoint(line->xr0, line->yr0, tr0, (float)HALF_TEXTURE_SIZE);
		appendTexpoint(line->xr1, line->yr1, tr1, (float)HALF_TEXTURE_SIZE);
		appendTexpoint(line->xl1, line->yl1, tl1, (float)HALF_TEXTURE_SIZE);
		appendTexpoint(line->xl0, line->yl0, tl0, (float)HALF_TEXTURE_SIZE);
		appendTexpoint(line->xr0, line->yr0, tr0, (float)HALF_TEXTURE_SIZE);
		appendTexpoint(line->xl1, line->yl1, tl1, (float)HALF_TEXTURE_SIZE);

		if (!line->has_prev)   // draw startcap
		{
			appendTexpoint(line->xl0, line->yl0, tl0, (float)HALF_TEXTURE_SIZE);
			appendTexpoint(line->xlt0, line->ylt0, tl0, 0.0f);
			appendTexpoint(line->xr0, line->yr0, tr0, (float)HALF_TEXTURE_SIZE);
			appendTexpoint(line->xr0, line->yr0, tr0, (float)HALF_TEXTURE_SIZE);
			appendTexpoint(line->xlt0, line->ylt0, tl0, 0.0f);
			appendTexpoint(line->xrt0, line->yrt0, tr0, 0.0f);
		}

		if (!line->has_next)   // draw endcap
		{
			appendTexpoint(line->xlt1, line->ylt1, tl1, 0.0f);
			appendTexpoint(line->xl1, line->yl1, tl1, (float)HALF_TEXTURE_SIZE);
			appendTexpoint(line->xr1, line->yr1, tr1, (float)HALF_TEXTURE_SIZE);
			appendTexpoint(line->xlt1, line->ylt1, tl1, 0.0f);
			appendTexpoint(line->xr1, line->yr1, tr1, (float)HALF_TEXTURE_SIZE);
			appendTexpoint(line->xrt1, line->yrt1, tr1, 0.0f);
		}
	}
}

bool VectorDisplay::setDecaySteps(int _steps)
{
	if (_steps < 0
	||  _steps > MAX_DECAY_STEPS)
	{
		return false;
	}

	m_numberDecaySteps = _steps;

	if (m_vertexBuffers.size() != 0)
	{
		for (size_t i = 0; i < m_vertexBuffers.size(); ++i)
		{
			bgfx::destroy(m_vertexBuffers[i]);
		}

		m_vertexBuffers.clear();
		m_vertexBuffersSize.clear();
	}

	for (int i = 0; i < m_numberDecaySteps; ++i)
	{
		m_vertexBuffers.push_back(bgfx::createDynamicVertexBuffer(MAX_NUMBER_VERTICES, PosColorUvVertex::ms_layout) );
		m_vertexBuffersSize.push_back(0);
	}

	return true;
}

bool VectorDisplay::setDecay(float _decay)
{
	if (_decay < 0.0f
	||  _decay >= 1.0f)
	{
		return false;
	}

	m_decayValue = _decay;
	return true;
}

void VectorDisplay::setBrightness(float _brightness)
{
	m_brightness = _brightness;
}

void VectorDisplay::getSize(float* _outWidth, float* _outHeight)
{
	*_outWidth = m_screenWidth;
	*_outHeight = m_screenHeight;
}

void VectorDisplay::screenSpaceQuad(float _textureWidth, float _textureHeight, float _width, float _height)
{
	if (3 == getAvailTransientVertexBuffer(3, PosColorUvVertex::ms_layout) )
	{
		bgfx::TransientVertexBuffer vb;
		bgfx::allocTransientVertexBuffer(&vb, 3, PosColorUvVertex::ms_layout);
		PosColorUvVertex* vertex = (PosColorUvVertex*)vb.data;

		const float zz = 0.0f;

		const float minx = -_width;
		const float maxx = _width;
		const float miny = 0.0f;
		const float maxy = _height * 2.0f;

		const float texelHalfW = m_texelHalf / _textureWidth;
		const float texelHalfH = m_texelHalf / _textureHeight;
		const float minu = -1.0f + texelHalfW;
		const float maxu = 1.0f + texelHalfW;

		float minv = texelHalfH;
		float maxv = 2.0f + texelHalfH;

		if (m_originBottomLeft)
		{
			float temp = minv;
			minv = maxv;
			maxv = temp;

			minv -= 1.0f;
			maxv -= 1.0f;
		}

		vertex[0].m_x = minx;
		vertex[0].m_y = miny;
		vertex[0].m_z = zz;
		vertex[0].m_abgr = 0xffffffff;
		vertex[0].m_u = minu;
		vertex[0].m_v = minv;

		vertex[1].m_x = maxx;
		vertex[1].m_y = miny;
		vertex[1].m_z = zz;
		vertex[1].m_abgr = 0xffffffff;
		vertex[1].m_u = maxu;
		vertex[1].m_v = minv;

		vertex[2].m_x = maxx;
		vertex[2].m_y = maxy;
		vertex[2].m_z = zz;
		vertex[2].m_abgr = 0xffffffff;
		vertex[2].m_u = maxu;
		vertex[2].m_v = maxv;

		bgfx::setVertexBuffer(0, &vb);
	}
}

void VectorDisplay::setupResDependent()
{
	const uint64_t tsFlags = 0
		| BGFX_TEXTURE_RT
		| BGFX_SAMPLER_MIN_POINT
		| BGFX_SAMPLER_MAG_POINT
		| BGFX_SAMPLER_MIP_POINT
		| BGFX_SAMPLER_U_CLAMP
		| BGFX_SAMPLER_V_CLAMP
		;
	m_sceneFrameBuffer = bgfx::createFrameBuffer(m_screenWidth, m_screenHeight, bgfx::TextureFormat::BGRA8, tsFlags);

	m_glowWidth = m_screenWidth / 3;
	m_glowHeight = m_screenHeight / 3;

	m_glow0FrameBuffer = bgfx::createFrameBuffer(m_glowWidth, m_glowHeight, bgfx::TextureFormat::BGRA8, tsFlags);
	m_glow1FrameBuffer = bgfx::createFrameBuffer(m_glowWidth, m_glowHeight, bgfx::TextureFormat::BGRA8, tsFlags);
}

void VectorDisplay::teardownResDependent()
{
	bgfx::destroy(m_sceneFrameBuffer);
	bgfx::destroy(m_glow0FrameBuffer);
	bgfx::destroy(m_glow1FrameBuffer);
}

void VectorDisplay::genLinetex()                                    // generate the texture
{
	const bgfx::Memory* mem = bgfx::alloc(TEXTURE_SIZE * TEXTURE_SIZE * 4);
	unsigned char* texbuf = (unsigned char*)mem->data;

	bx::memSet(texbuf, 0xff, mem->size);
	int x, y;
	for (x = 0; x < TEXTURE_SIZE; x++)
	{
		for (y = 0; y < TEXTURE_SIZE; y++)
		{
			float distance = bx::min(1.0f
				, bx::sqrt( (float)( (x - HALF_TEXTURE_SIZE) * (x - HALF_TEXTURE_SIZE) + (y - HALF_TEXTURE_SIZE) * (y - HALF_TEXTURE_SIZE) ) ) / (float)HALF_TEXTURE_SIZE
				);

			float line = bx::pow(16.0f, -2.0f * distance);
			float glow = bx::pow( 2.0f, -4.0f * distance) / 10.0f;
			glow = 0;
			float val = bx::clamp(line + glow, 0.0f, 1.0f);

			texbuf[(x + y * TEXTURE_SIZE) * 4 + 0] = 0xff;
			texbuf[(x + y * TEXTURE_SIZE) * 4 + 1] = 0xff;
			texbuf[(x + y * TEXTURE_SIZE) * 4 + 2] = 0xff;
			texbuf[(x + y * TEXTURE_SIZE) * 4 + 3] = (unsigned char)(val * 0xff);
		}
	}

	const uint32_t flags = 0
		| BGFX_SAMPLER_U_CLAMP
		| BGFX_SAMPLER_V_CLAMP
		| BGFX_SAMPLER_MIN_POINT
		| BGFX_SAMPLER_MAG_POINT
		;

	m_lineTexId = bgfx::createTexture2D(TEXTURE_SIZE, TEXTURE_SIZE, false, 1, bgfx::TextureFormat::BGRA8, flags, mem);
}

static const int8_t simplex[95][112] =
{
	{
		 0, 16, /* Ascii 32 */
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 8, 10, /* Ascii 33 */
		 5, 21,  5,  7, -1, -1,  5,  2,  4,  1,  5,  0,  6,  1,  5,  2, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 5, 16, /* Ascii 34 */
		 4, 21,  4, 14, -1, -1, 12, 21, 12, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		11, 21, /* Ascii 35 */
		11, 25,  4, -7, -1, -1, 17, 25, 10, -7, -1, -1,  4, 12, 18, 12, -1, -1,  3,  6, 17,  6, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		26, 20, /* Ascii 36 */
		 8, 25,  8, -4, -1, -1, 12, 25, 12, -4, -1, -1, 17, 18, 15, 20, 12, 21,  8, 21,  5, 20,  3,
		18,  3, 16,  4, 14,  5, 13,  7, 12, 13, 10, 15,  9, 16,  8, 17,  6, 17,  3, 15,  1, 12,  0,
		 8,  0,  5,  1,  3,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		31, 24, /* Ascii 37 */
		21, 21,  3,  0, -1, -1,  8, 21, 10, 19, 10, 17,  9, 15,  7, 14,  5, 14,  3, 16,  3, 18,  4,
		20,  6, 21,  8, 21, 10, 20, 13, 19, 16, 19, 19, 20, 21, 21, -1, -1, 17,  7, 15,  6, 14,  4,
		14,  2, 16,  0, 18,  0, 20,  1, 21,  3, 21,  5, 19,  7, 17,  7, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		34, 26, /* Ascii 38 */
		23, 12, 23, 13, 22, 14, 21, 14, 20, 13, 19, 11, 17,  6, 15,  3, 13,  1, 11,  0,  7,  0,  5,
		 1,  4,  2,  3,  4,  3,  6,  4,  8,  5,  9, 12, 13, 13, 14, 14, 16, 14, 18, 13, 20, 11, 21,
		 9, 20,  8, 18,  8, 16,  9, 13, 11, 10, 16,  3, 18,  1, 20,  0, 22,  0, 23,  1, 23,  2, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 7, 10, /* Ascii 39 */
		 5, 19,  4, 20,  5, 21,  6, 20,  6, 18,  5, 16,  4, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		10, 14, /* Ascii 40 */
		11, 25,  9, 23,  7, 20,  5, 16,  4, 11,  4,  7,  5,  2,  7, -2,  9, -5, 11, -7, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		10, 14, /* Ascii 41 */
		 3, 25,  5, 23,  7, 20,  9, 16, 10, 11, 10,  7,  9,  2,  7, -2,  5, -5,  3, -7, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 8, 16, /* Ascii 42 */
		 8, 21,  8,  9, -1, -1,  3, 18, 13, 12, -1, -1, 13, 18,  3, 12, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 5, 26, /* Ascii 43 */
		13, 18, 13,  0, -1, -1,  4,  9, 22,  9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 8, 10, /* Ascii 44 */
		 6,  1,  5,  0,  4,  1,  5,  2,  6,  1,  6, -1,  5, -3,  4, -4, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 2, 26, /* Ascii 45 */
		 4,  9, 22,  9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 5, 10, /* Ascii 46 */
		 5,  2,  4,  1,  5,  0,  6,  1,  5,  2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 2, 22, /* Ascii 47 */
		20, 25,  2, -7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		17, 20, /* Ascii 48 */
		 9, 21,  6, 20,  4, 17,  3, 12,  3,  9,  4,  4,  6,  1,  9,  0, 11,  0, 14,  1, 16,  4, 17,
		 9, 17, 12, 16, 17, 14, 20, 11, 21,  9, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 4, 20, /* Ascii 49 */
		 6, 17,  8, 18, 11, 21, 11,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		14, 20, /* Ascii 50 */
		 4, 16,  4, 17,  5, 19,  6, 20,  8, 21, 12, 21, 14, 20, 15, 19, 16, 17, 16, 15, 15, 13, 13,
		10,  3,  0, 17,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		15, 20, /* Ascii 51 */
		 5, 21, 16, 21, 10, 13, 13, 13, 15, 12, 16, 11, 17,  8, 17,  6, 16,  3, 14,  1, 11,  0,  8,
		 0,  5,  1,  4,  2,  3,  4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		6, 20, /* Ascii 52 */
		13, 21,  3,  7, 18,  7, -1, -1, 13, 21, 13,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		17, 20, /* Ascii 53 */
		15, 21,  5, 21,  4, 12,  5, 13,  8, 14, 11, 14, 14, 13, 16, 11, 17,  8, 17,  6, 16,  3, 14,
		 1, 11,  0,  8,  0,  5,  1,  4,  2,  3,  4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		23, 20, /* Ascii 54 */
		16, 18, 15, 20, 12, 21, 10, 21,  7, 20,  5, 17,  4, 12,  4,  7,  5,  3,  7,  1, 10,  0, 11,
		 0, 14,  1, 16,  3, 17,  6, 17,  7, 16, 10, 14, 12, 11, 13, 10, 13,  7, 12,  5, 10,  4,  7,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		5, 20, /* Ascii 55 */
		17, 21,  7,  0, -1, -1,  3, 21, 17, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		29, 20, /* Ascii 56 */
		 8, 21,  5, 20,  4, 18,  4, 16,  5, 14,  7, 13, 11, 12, 14, 11, 16,  9, 17,  7, 17,  4, 16,
		 2, 15,  1, 12,  0,  8,  0,  5,  1,  4,  2,  3,  4,  3,  7,  4,  9,  6, 11,  9, 12, 13, 13,
		15, 14, 16, 16, 16, 18, 15, 20, 12, 21,  8, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		23, 20, /* Ascii 57 */
		16, 14, 15, 11, 13,  9, 10,  8,  9,  8,  6,  9,  4, 11,  3, 14,  3, 15,  4, 18,  6, 20,  9,
		21, 10, 21, 13, 20, 15, 18, 16, 14, 16,  9, 15,  4, 13,  1, 10,  0,  8,  0,  5,  1,  4,  3,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		11, 10, /* Ascii 58 */
		 5, 14,  4, 13,  5, 12,  6, 13,  5, 14, -1, -1,  5,  2,  4,  1,  5,  0,  6,  1,  5,  2, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		14, 10, /* Ascii 59 */
		 5, 14,  4, 13,  5, 12,  6, 13,  5, 14, -1, -1,  6,  1,  5,  0,  4,  1,  5,  2,  6,  1,  6,
		-1,  5, -3,  4, -4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 3, 24, /* Ascii 60 */
		20, 18,  4,  9, 20,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 5, 26, /* Ascii 61 */
		 4, 12, 22, 12, -1, -1,  4,  6, 22,  6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 3, 24, /* Ascii 62 */
		 4, 18, 20,  9,  4,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		20, 18, /* Ascii 63 */
		 3, 16,  3, 17,  4, 19,  5, 20,  7, 21, 11, 21, 13, 20, 14, 19, 15, 17, 15, 15, 14, 13, 13,
		12,  9, 10,  9,  7, -1, -1,  9,  2,  8,  1,  9,  0, 10,  1,  9,  2, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		55, 27, /* Ascii 64 */
		18, 13, 17, 15, 15, 16, 12, 16, 10, 15,  9, 14,  8, 11,  8,  8,  9,  6, 11,  5, 14,  5, 16,
		 6, 17,  8, -1, -1, 12, 16, 10, 14,  9, 11,  9,  8, 10,  6, 11,  5, -1, -1, 18, 16, 17,  8,
		17,  6, 19,  5, 21,  5, 23,  7, 24, 10, 24, 12, 23, 15, 22, 17, 20, 19, 18, 20, 15, 21, 12,
		21,  9, 20,  7, 19,  5, 17,  4, 15,  3, 12,  3,  9,  4,  6,  5,  4,  7,  2,  9,  1, 12,  0,
		15,  0, 18,  1, 20,  2, 21,  3, -1, -1, 19, 16, 18,  8, 18,  6, 19,  5
	},
	{
		 8, 18, /* Ascii 65 */
		 9, 21,  1,  0, -1, -1,  9, 21, 17,  0, -1, -1,  4,  7, 14,  7, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		23, 21, /* Ascii 66 */
		 4, 21,  4,  0, -1, -1,  4, 21, 13, 21, 16, 20, 17, 19, 18, 17, 18, 15, 17, 13, 16, 12, 13,
		11, -1, -1,  4, 11, 13, 11, 16, 10, 17,  9, 18,  7, 18,  4, 17,  2, 16,  1, 13,  0,  4,  0,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		18, 21, /* Ascii 67 */
		18, 16, 17, 18, 15, 20, 13, 21,  9, 21,  7, 20,  5, 18,  4, 16,  3, 13,  3,  8,  4,  5,  5,
		 3,  7,  1,  9,  0, 13,  0, 15,  1, 17,  3, 18,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		15, 21, /* Ascii 68 */
		 4, 21,  4,  0, -1, -1,  4, 21, 11, 21, 14, 20, 16, 18, 17, 16, 18, 13, 18,  8, 17,  5, 16,
		 3, 14,  1, 11,  0,  4,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		11, 19, /* Ascii 69 */
		 4, 21,  4,  0, -1, -1,  4, 21, 17, 21, -1, -1,  4, 11, 12, 11, -1, -1,  4,  0, 17,  0, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 8, 18, /* Ascii 70 */
		 4, 21,  4,  0, -1, -1,  4, 21, 17, 21, -1, -1,  4, 11, 12, 11, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		22, 21, /* Ascii 71 */
		18, 16, 17, 18, 15, 20, 13, 21,  9, 21,  7, 20,  5, 18,  4, 16,  3, 13,  3,  8,  4,  5,  5,
		 3,  7,  1,  9,  0, 13,  0, 15,  1, 17,  3, 18,  5, 18,  8, -1, -1, 13,  8, 18,  8, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 8, 22, /* Ascii 72 */
		 4, 21,  4,  0, -1, -1, 18, 21, 18,  0, -1, -1,  4, 11, 18, 11, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 2,  8, /* Ascii 73 */
		 4, 21,  4,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		10, 16, /* Ascii 74 */
		12, 21, 12,  5, 11,  2, 10,  1,  8,  0,  6,  0,  4,  1,  3,  2,  2,  5,  2,  7, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 8, 21, /* Ascii 75 */
		 4, 21,  4,  0, -1, -1, 18, 21,  4,  7, -1, -1,  9, 12, 18,  0, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 5, 17, /* Ascii 76 */
		 4, 21,  4,  0, -1, -1,  4,  0, 16,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		11, 24, /* Ascii 77 */
		 4, 21,  4,  0, -1, -1,  4, 21, 12,  0, -1, -1, 20, 21, 12,  0, -1, -1, 20, 21, 20,  0, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 8, 22, /* Ascii 78 */
		 4, 21,  4,  0, -1, -1,  4, 21, 18,  0, -1, -1, 18, 21, 18,  0, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		21, 22, /* Ascii 79 */
		 9, 21,  7, 20,  5, 18,  4, 16,  3, 13,  3,  8,  4,  5,  5,  3,  7,  1,  9,  0, 13,  0, 15,
		 1, 17,  3, 18,  5, 19,  8, 19, 13, 18, 16, 17, 18, 15, 20, 13, 21,  9, 21, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		13, 21, /* Ascii 80 */
		4, 21, 4, 0, -1, -1, 4, 21, 13, 21, 16, 20, 17, 19, 18, 17, 18, 14, 17, 12, 16, 11, 13,
		10, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		24, 22, /* Ascii 81 */
		 9, 21,  7, 20,  5, 18,  4, 16,  3, 13,  3,  8,  4,  5,  5,  3,  7,  1,  9,  0, 13,  0, 15,
		 1, 17,  3, 18,  5, 19,  8, 19, 13, 18, 16, 17, 18, 15, 20, 13, 21,  9, 21, -1, -1, 12,  4,
		18, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		16, 21, /* Ascii 82 */
		 4, 21,  4,  0, -1, -1,  4, 21, 13, 21, 16, 20, 17, 19, 18, 17, 18, 15, 17, 13, 16, 12, 13,
		11,  4, 11, -1, -1, 11, 11, 18,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		20, 20, /* Ascii 83 */
		17, 18, 15, 20, 12, 21,  8, 21,  5, 20,  3, 18,  3, 16,  4, 14,  5, 13,  7, 12, 13, 10, 15,
		 9, 16,  8, 17,  6, 17,  3, 15,  1, 12,  0,  8,  0,  5,  1,  3,  3, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 5, 16, /* Ascii 84 */
		 8, 21,  8,  0, -1, -1,  1, 21, 15, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		10, 22, /* Ascii 85 */
		 4, 21,  4,  6,  5,  3,  7,  1, 10,  0, 12,  0, 15,  1, 17,  3, 18,  6, 18, 21, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 5, 18, /* Ascii 86 */
		 1, 21,  9,  0, -1, -1, 17, 21,  9,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		11, 24, /* Ascii 87 */
		 2, 21,  7,  0, -1, -1, 12, 21,  7,  0, -1, -1, 12, 21, 17,  0, -1, -1, 22, 21, 17,  0, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 5, 20, /* Ascii 88 */
		 3, 21, 17,  0, -1, -1, 17, 21,  3,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 6, 18, /* Ascii 89 */
		 1, 21,  9, 11,  9,  0, -1, -1, 17, 21,  9, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 8, 20, /* Ascii 90 */
		17, 21,  3,  0, -1, -1,  3, 21, 17, 21, -1, -1,  3,  0, 17,  0, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		11, 14, /* Ascii 91 */
		 4, 25,  4, -7, -1, -1,  5, 25,  5, -7, -1, -1,  4, 25, 11, 25, -1, -1,  4, -7, 11, -7, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 2, 14, /* Ascii 92 */
		 0, 21, 14, -3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		11, 14, /* Ascii 93 */
		 9, 25,  9, -7, -1, -1, 10, 25, 10, -7, -1, -1,  3, 25, 10, 25, -1, -1,  3, -7, 10, -7, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		10, 16, /* Ascii 94 */
		 6, 15,  8, 18, 10, 15, -1, -1,  3, 12,  8, 17, 13, 12, -1, -1,  8, 17,  8,  0, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 2, 16, /* Ascii 95 */
		 0, -2, 16, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 7, 10, /* Ascii 96 */
		 6, 21,  5, 20,  4, 18,  4, 16,  5, 15,  6, 16,  5, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		17, 19, /* Ascii 97 */
		15, 14, 15,  0, -1, -1, 15, 11, 13, 13, 11, 14,  8, 14,  6, 13,  4, 11,  3,  8,  3,  6,  4,
		 3,  6,  1,  8,  0, 11,  0, 13,  1, 15,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		17, 19, /* Ascii 98 */
		 4, 21,  4,  0, -1, -1,  4, 11,  6, 13,  8, 14, 11, 14, 13, 13, 15, 11, 16,  8, 16,  6, 15,
		 3, 13,  1, 11,  0,  8,  0,  6,  1,  4,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		14, 18, /* Ascii 99 */
		15, 11, 13, 13, 11, 14,  8, 14,  6, 13,  4, 11,  3,  8,  3,  6,  4,  3,  6,  1,  8,  0, 11,
		 0, 13,  1, 15,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		17, 19, /* Ascii 100 */
		15, 21, 15,  0, -1, -1, 15, 11, 13, 13, 11, 14,  8, 14,  6, 13,  4, 11,  3,  8,  3,  6,  4,
		 3,  6,  1,  8,  0, 11,  0, 13,  1, 15,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		17, 18, /* Ascii 101 */
		 3,  8, 15,  8, 15, 10, 14, 12, 13, 13, 11, 14,  8, 14,  6, 13,  4, 11,  3,  8,  3,  6,  4,
		 3,  6,  1,  8,  0, 11,  0, 13,  1, 15,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 8, 12, /* Ascii 102 */
		10, 21,  8, 21,  6, 20,  5, 17,  5,  0, -1, -1,  2, 14,  9, 14, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		22, 19, /* Ascii 103 */
		15, 14, 15, -2, 14, -5, 13, -6, 11, -7,  8, -7,  6, -6, -1, -1, 15, 11, 13, 13, 11, 14,  8,
		14,  6, 13,  4, 11,  3,  8,  3,  6,  4,  3,  6,  1,  8,  0, 11,  0, 13,  1, 15,  3, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		10, 19, /* Ascii 104 */
		 4, 21,  4,  0, -1, -1,  4, 10,  7, 13,  9, 14, 12, 14, 14, 13, 15, 10, 15,  0, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 8,  8, /* Ascii 105 */
		 3, 21,  4, 20,  5, 21,  4, 22,  3, 21, -1, -1,  4, 14,  4,  0, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		11, 10, /* Ascii 106 */
		 5, 21,  6, 20,  7, 21,  6, 22,  5, 21, -1, -1,  6, 14,  6, -3,  5, -6,  3, -7,  1, -7, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 8, 17, /* Ascii 107 */
		 4, 21,  4,  0, -1, -1, 14, 14,  4,  4, -1, -1,  8,  8, 15,  0, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 2,  8, /* Ascii 108 */
		 4, 21,  4,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		18, 30, /* Ascii 109 */
		 4, 14,  4,  0, -1, -1,  4, 10,  7, 13,  9, 14, 12, 14, 14, 13, 15, 10, 15,  0, -1, -1, 15,
		10, 18, 13, 20, 14, 23, 14, 25, 13, 26, 10, 26,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		10, 19, /* Ascii 110 */
		 4, 14,  4,  0, -1, -1,  4, 10,  7, 13,  9, 14, 12, 14, 14, 13, 15, 10, 15,  0, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		17, 19, /* Ascii 111 */
		 8, 14,  6, 13,  4, 11,  3,  8,  3,  6,  4,  3,  6,  1,  8,  0, 11,  0, 13,  1, 15,  3, 16,
		 6, 16,  8, 15, 11, 13, 13, 11, 14,  8, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		17, 19, /* Ascii 112 */
		 4, 14,  4, -7, -1, -1,  4, 11,  6, 13,  8, 14, 11, 14, 13, 13, 15, 11, 16,  8, 16,  6, 15,
		 3, 13,  1, 11,  0,  8,  0,  6,  1,  4,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		17, 19, /* Ascii 113 */
		15, 14, 15, -7, -1, -1, 15, 11, 13, 13, 11, 14,  8, 14,  6, 13,  4, 11,  3,  8,  3,  6,  4,
		 3,  6,  1,  8,  0, 11,  0, 13,  1, 15,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 8, 13, /* Ascii 114 */
		 4, 14,  4,  0, -1, -1,  4,  8,  5, 11,  7, 13,  9, 14, 12, 14, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		17, 17, /* Ascii 115 */
		14, 11, 13, 13, 10, 14,  7, 14,  4, 13,  3, 11,  4,  9,  6,  8, 11,  7, 13,  6, 14,  4, 14,
		 3, 13,  1, 10,  0,  7,  0,  4,  1,  3,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 8, 12, /* Ascii 116 */
		 5, 21,  5,  4,  6,  1,  8,  0, 10,  0, -1, -1,  2, 14,  9, 14, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		10, 19, /* Ascii 117 */
		 4, 14,  4,  4,  5,  1,  7,  0, 10,  0, 12,  1, 15,  4, -1, -1, 15, 14, 15,  0, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 5, 16, /* Ascii 118 */
		 2, 14,  8,  0, -1, -1, 14, 14,  8,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		11, 22, /* Ascii 119 */
		 3, 14,  7,  0, -1, -1, 11, 14,  7,  0, -1, -1, 11, 14, 15,  0, -1, -1, 19, 14, 15,  0, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 5, 17, /* Ascii 120 */
		 3, 14, 14,  0, -1, -1, 14, 14,  3,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 9, 16, /* Ascii 121 */
		 2, 14,  8,  0, -1, -1, 14, 14,  8,  0,  6, -4,  4, -6,  2, -7,  1, -7, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		8, 17, /* Ascii 122 */
		14, 14,  3,  0, -1, -1,  3, 14, 14, 14, -1, -1,  3,  0, 14,  0, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		39, 14, /* Ascii 123 */
		 9, 25,  7, 24,  6, 23,  5, 21,  5, 19,  6, 17,  7, 16,  8, 14,  8, 12,  6, 10, -1, -1,  7,
		24,  6, 22,  6, 20,  7, 18,  8, 17,  9, 15,  9, 13,  8, 11,  4,  9,  8,  7,  9,  5,  9,  3,
		 8,  1,  7,  0,  6, -2,  6, -4,  7, -6, -1, -1,  6,  8,  8,  6,  8,  4,  7,  2,  6,  1,  5,
		-1,  5, -3,  6, -5,  7, -6,  9, -7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		 2,  8, /* Ascii 124 */
		 4, 25,  4, -7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		39, 14, /* Ascii 125 */
		 5, 25,  7, 24,  8, 23,  9, 21,  9, 19,  8, 17,  7, 16,  6, 14,  6, 12,  8, 10, -1, -1,  7,
		24,  8, 22,  8, 20,  7, 18,  6, 17,  5, 15,  5, 13,  6, 11, 10,  9,  6,  7,  5,  5,  5,  3,
		 6,  1,  7,  0,  8, -2,  8, -4,  7, -6, -1, -1,  8,  8,  6,  6,  6,  4,  7,  2,  8,  1,  9,
		-1,  9, -3,  8, -5,  7, -6,  5, -7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	},
	{
		23, 24, /* Ascii 126 */
		 3,  6,  3,  8,  4, 11,  6, 12,  8, 12, 10, 11, 14,  8, 16,  7, 18,  7, 20,  8, 21, 10, -1,
		-1,  3,  8,  4, 10,  6, 11,  8, 11, 10, 10, 14,  7, 16,  6, 18,  6, 20,  7, 21, 10, 21, 12,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	}
};

void VectorDisplay::drawSimplexFont(float _x, float _y, float _scale, const char* _string)
{
	for (;;)
	{
		char c = *_string++;
		if (!c)
		{
			break;
		}

		if (c < 32
		||  c > 126)
		{
			continue;
		}

		const int8_t* chr = simplex[c - 32];

		int nvertices = chr[0];
		int spacing = chr[1];

		bool isDrawing = false;
		int i;
		for (i = 0; i < nvertices; i++)
		{
			int vx = chr[2 + i * 2];
			int vy = chr[2 + i * 2 + 1];
			if (vx == -1
			   && vy == -1)
			{
				if (isDrawing)
				{
					endDraw();
					isDrawing = false;
				}
			}
			else if (!isDrawing)
			{
				beginDraw(_x + vx * _scale, _y - vy * _scale);
				isDrawing = true;
			}
			else
			{
				drawTo(_x + vx * _scale, _y - vy * _scale);
			}
		}

		_x += spacing * _scale;
		if (isDrawing)
		{
			endDraw();
		}
	}
}
