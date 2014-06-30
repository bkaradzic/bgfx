//
// Copyright (c) 2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "nanovg.h"
#define FONTSTASH_IMPLEMENTATION
#include "fontstash.h"
#include <stb_image/stb_image.c>


#define NVG_INIT_PATH_SIZE 256
#define NVG_MAX_STATES 32

#define NVG_KAPPA90 0.5522847493f	// Lenght proportional to radius of a cubic bezier handle for 90deg arcs.

#define NVG_COUNTOF(arr) (sizeof(arr) / sizeof(0[arr]))


enum NVGcommands {
	NVG_MOVETO = 0,
	NVG_LINETO = 1,
	NVG_BEZIERTO = 2,
	NVG_CLOSE = 3,
	NVG_WINDING = 4,
};

enum NVGpointFlags
{
	NVG_PT_CORNER = 0x01,
	NVG_PT_LEFT = 0x02,
	NVG_PT_BEVEL = 0x04,
	NVG_PR_INNERBEVEL = 0x08,
};

enum NVGexpandFeatures {
	NVG_FILL = 0x01,
	NVG_STROKE = 0x02,
	NVG_CAPS = 0x04,
};

struct NVGstate {
	struct NVGpaint fill;
	struct NVGpaint stroke;
	float strokeWidth;
	float miterLimit;
	int lineJoin;
	int lineCap;
	float xform[6];
	struct NVGscissor scissor;
	float fontSize;
	float letterSpacing;
	float lineHeight;
	float fontBlur;
	int textAlign;
	int fontId;
};

struct NVGpoint {
	float x,y;
	float dx, dy;
	float len;
	float dmx, dmy;
	unsigned char flags;
};

struct NVGpathCache {
	struct NVGpoint* points;
	int npoints;
	int cpoints;
	struct NVGpath* paths;
	int npaths;
	int cpaths;
	struct NVGvertex* verts;
	int nverts;
	int cverts;
	float bounds[4];
};

struct NVGcontext {
	struct NVGparams params;
	float* commands;
	int ccommands;
	int ncommands;
	float commandx, commandy;
	struct NVGstate states[NVG_MAX_STATES];
	int nstates;
	struct NVGpathCache* cache;
	float tessTol;
	float distTol;
	float fringeWidth;
	float devicePxRatio;
	struct FONScontext* fs;
	int fontImage;
	int alphaBlend;
	int drawCallCount;
	int fillTriCount;
	int strokeTriCount;
	int textTriCount;
};

static float nvg__sqrtf(float a) { return sqrtf(a); }
static float nvg__modf(float a, float b) { return fmodf(a, b); }
static float nvg__sinf(float a) { return sinf(a); }
static float nvg__cosf(float a) { return cosf(a); }
static float nvg__tanf(float a) { return tanf(a); }
static float nvg__atan2f(float a,float b) { return atan2f(a, b); }
static float nvg__acosf(float a) { return acosf(a); }

static int nvg__mini(int a, int b) { return a < b ? a : b; }
static int nvg__maxi(int a, int b) { return a > b ? a : b; }
static int nvg__clampi(int a, int mn, int mx) { return a < mn ? mn : (a > mx ? mx : a); }
static float nvg__minf(float a, float b) { return a < b ? a : b; }
static float nvg__maxf(float a, float b) { return a > b ? a : b; }
static float nvg__absf(float a) { return a >= 0.0f ? a : -a; }
static float nvg__clampf(float a, float mn, float mx) { return a < mn ? mn : (a > mx ? mx : a); }
static float nvg__cross(float dx0, float dy0, float dx1, float dy1) { return dx1*dy0 - dx0*dy1; }

static float nvg__normalize(float *x, float* y)
{
	float d = nvg__sqrtf((*x)*(*x) + (*y)*(*y));
	if (d > 1e-6f) {
		float id = 1.0f / d;
		*x *= id;
		*y *= id;
	}
	return d;
}


static void nvg__deletePathCache(struct NVGpathCache* c)
{
	if (c == NULL) return;
	if (c->points != NULL) free(c->points);
	if (c->paths != NULL) free(c->paths);
	if (c->verts != NULL) free(c->verts);
	free(c);
}

static struct NVGpathCache* nvg__allocPathCache()
{
	struct NVGpathCache* c = (struct NVGpathCache*)malloc(sizeof(struct NVGpathCache));
	if (c == NULL) goto error;
	memset(c, 0, sizeof(struct NVGpathCache));

	c->points = (struct NVGpoint*)malloc(sizeof(struct NVGpoint)*4);
	if (!c->points) goto error;
	c->npoints = 0;
	c->cpoints = 4;

	c->paths = (struct NVGpath*)malloc(sizeof(struct NVGpath)*4);
	if (!c->paths) goto error;
	c->npaths = 0;
	c->cpaths = 4;

	c->verts = (struct NVGvertex*)malloc(sizeof(struct NVGvertex)*4);
	if (!c->verts) goto error;
	c->nverts = 0;
	c->cverts = 4;

	return c;
error:
	nvg__deletePathCache(c);
	return NULL;
}

static void nvg__setDevicePixelRatio(struct NVGcontext* ctx, float ratio)
{
	ctx->tessTol = 1.0f / ratio;
	ctx->distTol = 0.01f / ratio;
	ctx->fringeWidth = 1.0f / ratio;
	ctx->devicePxRatio = ratio;
}

struct NVGcontext* nvgCreateInternal(struct NVGparams* params)
{
	struct FONSparams fontParams;
	struct NVGcontext* ctx = (struct NVGcontext*)malloc(sizeof(struct NVGcontext));
	if (ctx == NULL) goto error;
	memset(ctx, 0, sizeof(struct NVGcontext));

	ctx->params = *params;

	ctx->commands = (float*)malloc(sizeof(float)*NVG_INIT_PATH_SIZE);
	if (!ctx->commands) goto error;
	ctx->ncommands = 0;
	ctx->ccommands = NVG_INIT_PATH_SIZE;

	ctx->alphaBlend = NVG_STRAIGHT_ALPHA;

	ctx->cache = nvg__allocPathCache();
	if (ctx->cache == NULL) goto error;

	nvgSave(ctx);
	nvgReset(ctx);

	nvg__setDevicePixelRatio(ctx, 1.0f);

	if (ctx->params.renderCreate(ctx->params.userPtr) == 0) goto error;

	// Init font rendering
	memset(&fontParams, 0, sizeof(fontParams));
	fontParams.width = params->atlasWidth;
	fontParams.height = params->atlasHeight;
	fontParams.flags = FONS_ZERO_TOPLEFT;
	fontParams.renderCreate = NULL;
	fontParams.renderUpdate = NULL;
	fontParams.renderDraw = NULL;
	fontParams.renderDelete = NULL;
	fontParams.userPtr = NULL;
	ctx->fs = fonsCreateInternal(&fontParams);
	if (ctx->fs == NULL) goto error;

	// Create font texture
	ctx->fontImage = ctx->params.renderCreateTexture(ctx->params.userPtr, NVG_TEXTURE_ALPHA, fontParams.width, fontParams.height, NULL);
	if (ctx->fontImage == 0) goto error;

	return ctx;

error:
	nvgDeleteInternal(ctx);
	return 0;
}

void nvgDeleteInternal(struct NVGcontext* ctx)
{
	if (ctx == NULL) return;
	if (ctx->commands != NULL) free(ctx->commands);
	if (ctx->cache != NULL) nvg__deletePathCache(ctx->cache);

	if (ctx->fs)
		fonsDeleteInternal(ctx->fs);

	if (ctx->params.renderDelete != NULL)
		ctx->params.renderDelete(ctx->params.userPtr);

	free(ctx);
}

void nvgBeginFrame(struct NVGcontext* ctx, int windowWidth, int windowHeight, float devicePixelRatio, int alphaBlend)
{
/*	printf("Tris: draws:%d  fill:%d  stroke:%d  text:%d  TOT:%d\n",
		ctx->drawCallCount, ctx->fillTriCount, ctx->strokeTriCount, ctx->textTriCount,
		ctx->fillTriCount+ctx->strokeTriCount+ctx->textTriCount);*/

	ctx->nstates = 0;
	nvgSave(ctx);
	nvgReset(ctx);

	nvg__setDevicePixelRatio(ctx, devicePixelRatio);
	ctx->alphaBlend = alphaBlend;
	
	ctx->params.renderViewport(ctx->params.userPtr, windowWidth, windowHeight, ctx->alphaBlend);

	ctx->drawCallCount = 0;
	ctx->fillTriCount = 0;
	ctx->strokeTriCount = 0;
	ctx->textTriCount = 0;
}

void nvgEndFrame(struct NVGcontext* ctx)
{
	ctx->params.renderFlush(ctx->params.userPtr, ctx->alphaBlend);
}

struct NVGcolor nvgRGB(unsigned char r, unsigned char g, unsigned char b)
{
	return nvgRGBA(r,g,b,255);
}

struct NVGcolor nvgRGBf(float r, float g, float b)
{
	return nvgRGBAf(r,g,b,1.0f);
}

struct NVGcolor nvgRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	struct NVGcolor color;
	// Use longer initialization to suppress warning.
	color.r = r / 255.0f;
	color.g = g / 255.0f;
	color.b = b / 255.0f;
	color.a = a / 255.0f;
	return color;
}

struct NVGcolor nvgRGBAu(unsigned int abgr)
{
	struct NVGcolor color;
	// Use longer initialization to suppress warning.
	color.r = ( (abgr>> 0)&0xff) / 255.0f;
	color.g = ( (abgr>> 8)&0xff) / 255.0f;
	color.b = ( (abgr>>16)&0xff) / 255.0f;
	color.a = ( (abgr>>24)&0xff) / 255.0f;
	return color;
}

struct NVGcolor nvgRGBAf(float r, float g, float b, float a)
{
	struct NVGcolor color;
	// Use longer initialization to suppress warning.
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}

struct NVGcolor nvgTransRGBA(struct NVGcolor c, unsigned char a)
{
	c.a = a / 255.0f;
	return c;
}

struct NVGcolor nvgTransRGBAf(struct NVGcolor c, float a)
{
	c.a = a;
	return c;
}

struct NVGcolor nvgLerpRGBA(struct NVGcolor c0, struct NVGcolor c1, float u)
{
	int i;
	float oneminu;
	struct NVGcolor cint;

	u = nvg__clampf(u, 0.0f, 1.0f);
	oneminu = 1.0f - u;
	for( i = 0; i <4; ++i )
	{
		cint.rgba[i] = c0.rgba[i] * oneminu + c1.rgba[i] * u;
	}
	 
	return cint;
}

struct NVGcolor nvgHSL(float h, float s, float l)
{
	return nvgHSLA(h,s,l,255);
}

static float nvg__hue(float h, float m1, float m2)
{
	if (h < 0) h += 1;
	if (h > 1) h -= 1;
	if (h < 1.0f/6.0f)
		return m1 + (m2 - m1) * h * 6.0f;
	else if (h < 3.0f/6.0f)
		return m2;
	else if (h < 4.0f/6.0f)
		return m1 + (m2 - m1) * (2.0f/3.0f - h) * 6.0f;
	return m1;
}

struct NVGcolor nvgHSLA(float h, float s, float l, unsigned char a)
{
	float m1, m2;
	struct NVGcolor col;
	h = nvg__modf(h, 1.0f);
	if (h < 0.0f) h += 1.0f;
	s = nvg__clampf(s, 0.0f, 1.0f);
	l = nvg__clampf(l, 0.0f, 1.0f);
	m2 = l <= 0.5f ? (l * (1 + s)) : (l + s - l * s);
	m1 = 2 * l - m2;
	col.r = nvg__clampf(nvg__hue(h + 1.0f/3.0f, m1, m2), 0.0f, 1.0f);
	col.g = nvg__clampf(nvg__hue(h, m1, m2), 0.0f, 1.0f);
	col.b = nvg__clampf(nvg__hue(h - 1.0f/3.0f, m1, m2), 0.0f, 1.0f);
	col.a = a/255.0f;
	return col;
}



static struct NVGstate* nvg__getState(struct NVGcontext* ctx)
{
	return &ctx->states[ctx->nstates-1];
}

static void nvg__xformIdentity(float* t)
{
	t[0] = 1.0f; t[1] = 0.0f;
	t[2] = 0.0f; t[3] = 1.0f;
	t[4] = 0.0f; t[5] = 0.0f;
}

static void nvg__xformTranslate(float* t, float tx, float ty)
{
	t[0] = 1.0f; t[1] = 0.0f;
	t[2] = 0.0f; t[3] = 1.0f;
	t[4] = tx; t[5] = ty;
}

static void nvg__xformScale(float* t, float sx, float sy)
{
	t[0] = sx; t[1] = 0.0f;
	t[2] = 0.0f; t[3] = sy;
	t[4] = 0.0f; t[5] = 0.0f;
}

static void nvg__xformRotate(float* t, float a)
{
	float cs = nvg__cosf(a), sn = nvg__sinf(a);
	t[0] = cs; t[1] = sn;
	t[2] = -sn; t[3] = cs;
	t[4] = 0.0f; t[5] = 0.0f;
}

static void nvg__xformMultiply(float* t, float* s)
{
	float t0 = t[0] * s[0] + t[1] * s[2];
	float t2 = t[2] * s[0] + t[3] * s[2];
	float t4 = t[4] * s[0] + t[5] * s[2] + s[4];
	t[1] = t[0] * s[1] + t[1] * s[3];
	t[3] = t[2] * s[1] + t[3] * s[3];
	t[5] = t[4] * s[1] + t[5] * s[3] + s[5];
	t[0] = t0;
	t[2] = t2;
	t[4] = t4;
}

static void nvg__xformPremultiply(float* t, float* s)
{
	float s2[6];
	memcpy(s2, s, sizeof(float)*6);
	nvg__xformMultiply(s2, t);
	memcpy(t, s2, sizeof(float)*6);
}

static void nvg__setPaintColor(struct NVGpaint* p, struct NVGcolor color)
{
	memset(p, 0, sizeof(*p));
	nvg__xformIdentity(p->xform);
	p->radius = 0.0f;
	p->feather = 1.0f;
	p->innerColor = color;
	p->outerColor = color;
}


// State handling
void nvgSave(struct NVGcontext* ctx)
{
	if (ctx->nstates >= NVG_MAX_STATES)
		return;
	if (ctx->nstates > 0)
		memcpy(&ctx->states[ctx->nstates], &ctx->states[ctx->nstates-1], sizeof(struct NVGstate));
	ctx->nstates++;
}

void nvgRestore(struct NVGcontext* ctx)
{
	if (ctx->nstates <= 1)
		return;
	ctx->nstates--;
}

void nvgReset(struct NVGcontext* ctx)
{
	struct NVGstate* state = nvg__getState(ctx);
	memset(state, 0, sizeof(*state));

	nvg__setPaintColor(&state->fill, nvgRGBA(255,255,255,255));
	nvg__setPaintColor(&state->stroke, nvgRGBA(0,0,0,255));
	state->strokeWidth = 1.0f;
	state->miterLimit = 10.0f;
	state->lineCap = NVG_BUTT;
	state->lineJoin = NVG_MITER;
	nvg__xformIdentity(state->xform);

	state->scissor.extent[0] = 0.0f;
	state->scissor.extent[1] = 0.0f;

	state->fontSize = 16.0f;
	state->letterSpacing = 0.0f;
	state->lineHeight = 0.0f;
	state->fontBlur = 0.0f;
	state->textAlign = NVG_ALIGN_LEFT | NVG_ALIGN_BASELINE;
	state->fontId = 0;
}

// State setting
void nvgStrokeWidth(struct NVGcontext* ctx, float width)
{
	struct NVGstate* state = nvg__getState(ctx);
	state->strokeWidth = width;
}

void nvgMiterLimit(struct NVGcontext* ctx, float limit)
{
	struct NVGstate* state = nvg__getState(ctx);
	state->miterLimit = limit;
}

void nvgLineCap(struct NVGcontext* ctx, int cap)
{
	struct NVGstate* state = nvg__getState(ctx);
	state->lineCap = cap;
}

void nvgLineJoin(struct NVGcontext* ctx, int join)
{
	struct NVGstate* state = nvg__getState(ctx);
	state->lineJoin = join;
}


void nvgTransform(struct NVGcontext* ctx, float a, float b, float c, float d, float e, float f)
{
	struct NVGstate* state = nvg__getState(ctx);
	float t[6] = { a, b, c, d, e, f };
	nvg__xformPremultiply(state->xform, t);
}

void nvgResetTransform(struct NVGcontext* ctx)
{
	struct NVGstate* state = nvg__getState(ctx);
	nvg__xformIdentity(state->xform);
}

void nvgTranslate(struct NVGcontext* ctx, float x, float y)
{
	struct NVGstate* state = nvg__getState(ctx);
	float t[6];
	nvg__xformTranslate(t, x,y);
	nvg__xformPremultiply(state->xform, t);
}

void nvgRotate(struct NVGcontext* ctx, float angle)
{
	struct NVGstate* state = nvg__getState(ctx);
	float t[6];
	nvg__xformRotate(t, angle);
	nvg__xformPremultiply(state->xform, t);
}

void nvgScale(struct NVGcontext* ctx, float x, float y)
{
	struct NVGstate* state = nvg__getState(ctx);
	float t[6];
	nvg__xformScale(t, x,y);
	nvg__xformPremultiply(state->xform, t);
}


void nvgStrokeColor(struct NVGcontext* ctx, struct NVGcolor color)
{
	struct NVGstate* state = nvg__getState(ctx);
	nvg__setPaintColor(&state->stroke, color);
}

void nvgStrokePaint(struct NVGcontext* ctx, struct NVGpaint paint)
{
	struct NVGstate* state = nvg__getState(ctx);
	state->stroke = paint;
	nvg__xformMultiply(state->stroke.xform, state->xform);
}

void nvgFillColor(struct NVGcontext* ctx, struct NVGcolor color)
{
	struct NVGstate* state = nvg__getState(ctx);
	nvg__setPaintColor(&state->fill, color);
}

void nvgFillPaint(struct NVGcontext* ctx, struct NVGpaint paint)
{
	struct NVGstate* state = nvg__getState(ctx);
	state->fill = paint;
	nvg__xformMultiply(state->fill.xform, state->xform);
}

int nvgCreateImage(struct NVGcontext* ctx, const char* filename)
{
	int w, h, n, image;
	unsigned char* img = stbi_load(filename, &w, &h, &n, 4);
	if (img == NULL) {
//		printf("Failed to load %s - %s\n", filename, stbi_failure_reason());
		return 0;
	}
	image = nvgCreateImageRGBA(ctx, w, h, img);
	stbi_image_free(img);
	return image;
}

int nvgCreateImageMem(struct NVGcontext* ctx, unsigned char* data, int ndata)
{
	int w, h, n, image;
	unsigned char* img = stbi_load_from_memory(data, ndata, &w, &h, &n, 4);
	if (img == NULL) {
//		printf("Failed to load %s - %s\n", filename, stbi_failure_reason());
		return 0;
	}
	image = nvgCreateImageRGBA(ctx, w, h, img);
	stbi_image_free(img);
	return image;
}

int nvgCreateImageRGBA(struct NVGcontext* ctx, int w, int h, const unsigned char* data)
{
	return ctx->params.renderCreateTexture(ctx->params.userPtr, NVG_TEXTURE_RGBA, w, h, data);
}

void nvgUpdateImage(struct NVGcontext* ctx, int image, const unsigned char* data)
{
	int w, h;
	ctx->params.renderGetTextureSize(ctx->params.userPtr, image, &w, &h);
	ctx->params.renderUpdateTexture(ctx->params.userPtr, image, 0,0, w,h, data);
}

void nvgImageSize(struct NVGcontext* ctx, int image, int* w, int* h)
{
	ctx->params.renderGetTextureSize(ctx->params.userPtr, image, w, h);
}

void nvgDeleteImage(struct NVGcontext* ctx, int image)
{
	ctx->params.renderDeleteTexture(ctx->params.userPtr, image);
}

struct NVGpaint nvgLinearGradient(struct NVGcontext* ctx,
								  float sx, float sy, float ex, float ey,
								  struct NVGcolor icol, struct NVGcolor ocol)
{
	struct NVGpaint p;
	float dx, dy, d;
	const float large = 1e5;
	NVG_NOTUSED(ctx);
	memset(&p, 0, sizeof(p));

	// Calculate transform aligned to the line
	dx = ex - sx;
	dy = ey - sy;
	d = sqrtf(dx*dx + dy*dy);
	if (d > 0.0001f) {
		dx /= d;
		dy /= d;
	} else {
		dx = 0;
		dy = 1;
	}

	p.xform[0] = dy; p.xform[1] = -dx;
	p.xform[2] = dx; p.xform[3] = dy;
	p.xform[4] = sx - dx*large; p.xform[5] = sy - dy*large;

	p.extent[0] = large;
	p.extent[1] = large + d*0.5f;

	p.radius = 0.0f;

	p.feather = nvg__maxf(1.0f, d);

	p.innerColor = icol;
	p.outerColor = ocol;

	return p;
}

struct NVGpaint nvgRadialGradient(struct NVGcontext* ctx,
								  float cx, float cy, float inr, float outr,
								  struct NVGcolor icol, struct NVGcolor ocol)
{
	struct NVGpaint p;
	float r = (inr+outr)*0.5f;
	float f = (outr-inr);
	NVG_NOTUSED(ctx);
	memset(&p, 0, sizeof(p));

	nvg__xformIdentity(p.xform);
	p.xform[4] = cx;
	p.xform[5] = cy;

	p.extent[0] = r;
	p.extent[1] = r;

	p.radius = r;

	p.feather = nvg__maxf(1.0f, f);

	p.innerColor = icol;
	p.outerColor = ocol;

	return p;
}

struct NVGpaint nvgBoxGradient(struct NVGcontext* ctx,
							   float x, float y, float w, float h, float r, float f,
							   struct NVGcolor icol, struct NVGcolor ocol)
{
	struct NVGpaint p;
	NVG_NOTUSED(ctx);
	memset(&p, 0, sizeof(p));

	nvg__xformIdentity(p.xform);
	p.xform[4] = x+w*0.5f;
	p.xform[5] = y+h*0.5f;

	p.extent[0] = w*0.5f;
	p.extent[1] = h*0.5f;

	p.radius = r;

	p.feather = nvg__maxf(1.0f, f);

	p.innerColor = icol;
	p.outerColor = ocol;

	return p;
}


struct NVGpaint nvgImagePattern(struct NVGcontext* ctx,
								float cx, float cy, float w, float h, float angle,
								int image, int repeat)
{
	struct NVGpaint p;
	NVG_NOTUSED(ctx);
	memset(&p, 0, sizeof(p));

	nvg__xformRotate(p.xform, angle);
	p.xform[4] = cx;
	p.xform[5] = cy;

	p.extent[0] = w;
	p.extent[1] = h;

	p.image = image;
	p.repeat = repeat;

	return p;
}

// Scissoring
void nvgScissor(struct NVGcontext* ctx, float x, float y, float w, float h)
{
	struct NVGstate* state = nvg__getState(ctx);

	nvg__xformIdentity(state->scissor.xform);
	state->scissor.xform[4] = x+w*0.5f;
	state->scissor.xform[5] = y+h*0.5f;
	nvg__xformMultiply(state->scissor.xform, state->xform);

	state->scissor.extent[0] = w*0.5f;
	state->scissor.extent[1] = h*0.5f;
}

void nvgResetScissor(struct NVGcontext* ctx)
{
	struct NVGstate* state = nvg__getState(ctx);
	memset(state->scissor.xform, 0, sizeof(state->scissor.xform));
	state->scissor.extent[0] = 0;
	state->scissor.extent[1] = 0;
}

static void nvg__xformPt(float* dx, float* dy, float sx, float sy, const float* t)
{
	*dx = sx*t[0] + sy*t[2] + t[4];
	*dy = sx*t[1] + sy*t[3] + t[5];
}

static int nvg__ptEquals(float x1, float y1, float x2, float y2, float tol)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	return dx*dx + dy*dy < tol*tol;
}

static float nvg__distPtSeg(float x, float y, float px, float py, float qx, float qy)
{
	float pqx, pqy, dx, dy, d, t;
	pqx = qx-px;
	pqy = qy-py;
	dx = x-px;
	dy = y-py;
	d = pqx*pqx + pqy*pqy;
	t = pqx*dx + pqy*dy;
	if (d > 0) t /= d;
	if (t < 0) t = 0;
	else if (t > 1) t = 1;
	dx = px + t*pqx - x;
	dy = py + t*pqy - y;
	return dx*dx + dy*dy;
}

static void nvg__appendCommands(struct NVGcontext* ctx, float* vals, int nvals)
{
	struct NVGstate* state = nvg__getState(ctx);
	int i;

	if (ctx->ncommands+nvals > ctx->ccommands) {
		if (ctx->ccommands == 0) ctx->ccommands = 8;
		while (ctx->ccommands < ctx->ncommands+nvals)
			ctx->ccommands *= 2;
		ctx->commands = (float*)realloc(ctx->commands, ctx->ccommands*sizeof(float));
		if (ctx->commands == NULL) return;
	}

	// transform commands
	i = 0;
	while (i < nvals) {
		int cmd = (int)vals[i];
		switch (cmd) {
		case NVG_MOVETO:
			nvg__xformPt(&vals[i+1],&vals[i+2], vals[i+1],vals[i+2], state->xform);
			i += 3;
			break;
		case NVG_LINETO:
			nvg__xformPt(&vals[i+1],&vals[i+2], vals[i+1],vals[i+2], state->xform);
			i += 3;
			break;
		case NVG_BEZIERTO:
			nvg__xformPt(&vals[i+1],&vals[i+2], vals[i+1],vals[i+2], state->xform);
			nvg__xformPt(&vals[i+3],&vals[i+4], vals[i+3],vals[i+4], state->xform);
			nvg__xformPt(&vals[i+5],&vals[i+6], vals[i+5],vals[i+6], state->xform);
			i += 7;
			break;
		case NVG_CLOSE:
			i++;
			break;
		case NVG_WINDING:
			i += 2;
			break;
		default:
			i++;
		}
	}

	memcpy(&ctx->commands[ctx->ncommands], vals, nvals*sizeof(float));

	ctx->ncommands += nvals;

	if ((int)vals[0] != NVG_CLOSE && (int)vals[0] != NVG_WINDING) {
		ctx->commandx = vals[nvals-2];
		ctx->commandy = vals[nvals-1];
	}
}


static void nvg__clearPathCache(struct NVGcontext* ctx)
{
	ctx->cache->npoints = 0;
	ctx->cache->npaths = 0;
}

static struct NVGpath* nvg__lastPath(struct NVGcontext* ctx)
{
	if (ctx->cache->npaths > 0)
		return &ctx->cache->paths[ctx->cache->npaths-1];
	return NULL;
}

static void nvg__addPath(struct NVGcontext* ctx)
{
	struct NVGpath* path;
	if (ctx->cache->npaths+1 > ctx->cache->cpaths) {
		ctx->cache->cpaths = (ctx->cache->cpaths == 0) ? 8 : (ctx->cache->cpaths*2);
		ctx->cache->paths = (struct NVGpath*)realloc(ctx->cache->paths, sizeof(struct NVGpath)*ctx->cache->cpaths);
		if (ctx->cache->paths == NULL) return;
	}
	path = &ctx->cache->paths[ctx->cache->npaths];
	memset(path, 0, sizeof(*path));
	path->first = ctx->cache->npoints;
	path->winding = NVG_CCW;

	ctx->cache->npaths++;
}

static struct NVGpoint* nvg__lastPoint(struct NVGcontext* ctx)
{
	if (ctx->cache->npoints > 0)
		return &ctx->cache->points[ctx->cache->npoints-1];
	return NULL;
}

static void nvg__addPoint(struct NVGcontext* ctx, float x, float y, int flags)
{
	struct NVGpath* path = nvg__lastPath(ctx);
	struct NVGpoint* pt;
	if (path == NULL) return;

	if (ctx->cache->npoints > 0) {
		pt = nvg__lastPoint(ctx);
		if (nvg__ptEquals(pt->x,pt->y, x,y, ctx->distTol)) {
			pt->flags |= flags;
			return;
		}
	}

	if (ctx->cache->npoints+1 > ctx->cache->cpoints) {
		ctx->cache->cpoints = (ctx->cache->cpoints == 0) ? 8 : (ctx->cache->cpoints*2);
		ctx->cache->points = (struct NVGpoint*)realloc(ctx->cache->points, sizeof(struct NVGpoint)*ctx->cache->cpoints);
		if (ctx->cache->points == NULL) return;
	}

	pt = &ctx->cache->points[ctx->cache->npoints];
	memset(pt, 0, sizeof(*pt));
	pt->x = x;
	pt->y = y;
	pt->flags = flags;

	ctx->cache->npoints++;
	path->count++;
}

static void nvg__closePath(struct NVGcontext* ctx)
{
	struct NVGpath* path = nvg__lastPath(ctx);
	if (path == NULL) return;
	path->closed = 1;
}

static void nvg__pathWinding(struct NVGcontext* ctx, int winding)
{
	struct NVGpath* path = nvg__lastPath(ctx);
	if (path == NULL) return;
	path->winding = winding;
}

static float nvg__getAverageScale(float *t)
{
	float sx = sqrtf(t[0]*t[0] + t[2]*t[2]);
	float sy = sqrtf(t[1]*t[1] + t[3]*t[3]);
	return (sx + sy) * 0.5f;
}

static struct NVGvertex* nvg__allocTempVerts(struct NVGcontext* ctx, int nverts)
{
	if (nverts > ctx->cache->cverts) {
		if (ctx->cache->cverts == 0) ctx->cache->cverts = 8;
		while (ctx->cache->cverts < nverts)
			ctx->cache->cverts *= 2;
		ctx->cache->verts = (struct NVGvertex*)realloc(ctx->cache->verts, sizeof(struct NVGvertex)*ctx->cache->cverts);
		if (ctx->cache->verts == NULL) return NULL;
	}
	return ctx->cache->verts;
}

static float nvg__triarea2(float ax, float ay, float bx, float by, float cx, float cy)
{
	float abx = bx - ax;
	float aby = by - ay;
	float acx = cx - ax;
	float acy = cy - ay;
	return acx*aby - abx*acy;
}

static float nvg__polyArea(struct NVGpoint* pts, int npts)
{
	int i;
	float area = 0;
	for (i = 2; i < npts; i++) {
		struct NVGpoint* a = &pts[0];
		struct NVGpoint* b = &pts[i-1];
		struct NVGpoint* c = &pts[i];
		area += nvg__triarea2(a->x,a->y, b->x,b->y, c->x,c->y);
	}
	return area * 0.5f;
}

static void nvg__polyReverse(struct NVGpoint* pts, int npts)
{
	struct NVGpoint tmp;
	int i = 0, j = npts-1;
	while (i < j) {
		tmp = pts[i];
		pts[i] = pts[j];
		pts[j] = tmp;
		i++;
		j--;
	}
}


static void nvg__vset(struct NVGvertex* vtx, float x, float y, float u, float v)
{
	vtx->x = x;
	vtx->y = y;
	vtx->u = u;
	vtx->v = v;
}

static void nvg__tesselateBezier(struct NVGcontext* ctx,
								 float x1, float y1, float x2, float y2,
								 float x3, float y3, float x4, float y4,
								 int level, int type)
{
	float x12,y12,x23,y23,x34,y34,x123,y123,x234,y234,x1234,y1234;
	float dx,dy,d2,d3;
	
	if (level > 10) return;

	x12 = (x1+x2)*0.5f;
	y12 = (y1+y2)*0.5f;
	x23 = (x2+x3)*0.5f;
	y23 = (y2+y3)*0.5f;
	x34 = (x3+x4)*0.5f;
	y34 = (y3+y4)*0.5f;
	x123 = (x12+x23)*0.5f;
	y123 = (y12+y23)*0.5f;

	dx = x3 - x1;
	dy = y3 - y1;
	d2 = nvg__absf(((x2 - x4) * dy - (y2 - y4) * dx));
	d3 = nvg__absf(((x3 - x4) * dy - (y3 - y4) * dx));

	if ((d2 + d3)*(d2 + d3) < ctx->tessTol * (dx*dx + dy*dy)) {
		nvg__addPoint(ctx, x4, y4, type);
		return;
	}

/*	if (nvg__absf(x1+x3-x2-x2) + nvg__absf(y1+y3-y2-y2) + nvg__absf(x2+x4-x3-x3) + nvg__absf(y2+y4-y3-y3) < ctx->tessTol) {
		nvg__addPoint(ctx, x4, y4, type);
		return;
	}*/

	x234 = (x23+x34)*0.5f;
	y234 = (y23+y34)*0.5f;
	x1234 = (x123+x234)*0.5f;
	y1234 = (y123+y234)*0.5f;

	nvg__tesselateBezier(ctx, x1,y1, x12,y12, x123,y123, x1234,y1234, level+1, 0); 
	nvg__tesselateBezier(ctx, x1234,y1234, x234,y234, x34,y34, x4,y4, level+1, type); 
}

static void nvg__flattenPaths(struct NVGcontext* ctx)
{
	struct NVGpathCache* cache = ctx->cache;
//	struct NVGstate* state = nvg__getState(ctx);
	struct NVGpoint* last;
	struct NVGpoint* p0;
	struct NVGpoint* p1;
	struct NVGpoint* pts;
	struct NVGpath* path;
	int i, j;
	float* cp1;
	float* cp2;
	float* p;
	float area;

	if (cache->npaths > 0)
		return;

	// Flatten
	i = 0;
	while (i < ctx->ncommands) {
		int cmd = (int)ctx->commands[i];
		switch (cmd) {
		case NVG_MOVETO:
			nvg__addPath(ctx);
			p = &ctx->commands[i+1];
			nvg__addPoint(ctx, p[0], p[1], NVG_PT_CORNER);
			i += 3;
			break;
		case NVG_LINETO:
			p = &ctx->commands[i+1];
			nvg__addPoint(ctx, p[0], p[1], NVG_PT_CORNER);
			i += 3;
			break;
		case NVG_BEZIERTO:
			last = nvg__lastPoint(ctx);
			if (last != NULL) {
				cp1 = &ctx->commands[i+1];
				cp2 = &ctx->commands[i+3];
				p = &ctx->commands[i+5];
				nvg__tesselateBezier(ctx, last->x,last->y, cp1[0],cp1[1], cp2[0],cp2[1], p[0],p[1], 0, NVG_PT_CORNER);
			}
			i += 7;
			break;
		case NVG_CLOSE:
			nvg__closePath(ctx);
			i++;
			break;
		case NVG_WINDING:
			nvg__pathWinding(ctx, (int)ctx->commands[i+1]);
			i += 2;
			break;
		default:
			i++;
		}
	}

	cache->bounds[0] = cache->bounds[1] = 1e6f;
	cache->bounds[2] = cache->bounds[3] = -1e6f;

	// Calculate the direction and length of line segments.
	for (j = 0; j < cache->npaths; j++) {
		path = &cache->paths[j];
		pts = &cache->points[path->first];

		// If the first and last points are the same, remove the last, mark as closed path.
		p0 = &pts[path->count-1];
		p1 = &pts[0];
		if (nvg__ptEquals(p0->x,p0->y, p1->x,p1->y, ctx->distTol)) {
			path->count--;
			p0 = &pts[path->count-1];
			path->closed = 1;
		}

		// Enforce winding.
		if (path->count > 2) {
			area = nvg__polyArea(pts, path->count);
			if (path->winding == NVG_CCW && area < 0.0f)
				nvg__polyReverse(pts, path->count);
			if (path->winding == NVG_CW && area > 0.0f)
				nvg__polyReverse(pts, path->count);
		}

		for(i = 0; i < path->count; ++i) {
			// Calculate segment direction and length
			p0->dx = p1->x - p0->x;
			p0->dy = p1->y - p0->y;
			p0->len = nvg__normalize(&p0->dx, &p0->dy);
			// Update bounds
			cache->bounds[0] = nvg__minf(cache->bounds[0], p0->x);
			cache->bounds[1] = nvg__minf(cache->bounds[1], p0->y);
			cache->bounds[2] = nvg__maxf(cache->bounds[2], p0->x);
			cache->bounds[3] = nvg__maxf(cache->bounds[3], p0->y);
			// Advance
			p0 = p1++;
		}
	}
}

static int nvg__curveDivs(float r, float arc, float tol)
{
	float da = acosf(r / (r + tol)) * 2.0f;
	return nvg__maxi(2, (int)ceilf(arc / da));
}

static void nvg__chooseBevel(int bevel, struct NVGpoint* p0, struct NVGpoint* p1, float w,
							float* x0, float* y0, float* x1, float* y1)
{
	if (bevel) {
		*x0 = p1->x + p0->dy * w;
		*y0 = p1->y - p0->dx * w;
		*x1 = p1->x + p1->dy * w;
		*y1 = p1->y - p1->dx * w;
	} else {
		*x0 = p1->x + p1->dmx * w;
		*y0 = p1->y + p1->dmy * w;
		*x1 = p1->x + p1->dmx * w;
		*y1 = p1->y + p1->dmy * w;
	}
}

static struct NVGvertex* nvg__roundJoin(struct NVGvertex* dst, struct NVGpoint* p0, struct NVGpoint* p1,
										float lw, float rw, float lu, float ru, int ncap, float fringe)
{
	int i, n;
	float dlx0 = p0->dy;
	float dly0 = -p0->dx;
	float dlx1 = p1->dy;
	float dly1 = -p1->dx;
	NVG_NOTUSED(fringe);

	if (p1->flags & NVG_PT_LEFT) {
		float lx0,ly0,lx1,ly1,a0,a1;
		nvg__chooseBevel(p1->flags & NVG_PR_INNERBEVEL, p0, p1, lw, &lx0,&ly0, &lx1,&ly1);
		a0 = atan2f(-dly0, -dlx0);
		a1 = atan2f(-dly1, -dlx1);
		if (a1 > a0) a1 -= NVG_PI*2;

		nvg__vset(dst, lx0, ly0, lu,1); dst++;
		nvg__vset(dst, p1->x - dlx0*rw, p1->y - dly0*rw, ru,1); dst++;

		n = nvg__clampi((int)ceilf(((a0 - a1) / NVG_PI) * ncap), 2, ncap);
		for (i = 0; i < n; i++) {
			float u = i/(float)(n-1);
			float a = a0 + u*(a1-a0);
			float rx = p1->x + cosf(a) * rw;
			float ry = p1->y + sinf(a) * rw;
			nvg__vset(dst, p1->x, p1->y, 0.5f,1); dst++;
			nvg__vset(dst, rx, ry, ru,1); dst++;
		}

		nvg__vset(dst, lx1, ly1, lu,1); dst++;
		nvg__vset(dst, p1->x - dlx1*rw, p1->y - dly1*rw, ru,1); dst++;

	} else {
		float rx0,ry0,rx1,ry1,a0,a1;
		nvg__chooseBevel(p1->flags & NVG_PR_INNERBEVEL, p0, p1, -rw, &rx0,&ry0, &rx1,&ry1);
		a0 = atan2f(dly0, dlx0);
		a1 = atan2f(dly1, dlx1);
		if (a1 < a0) a1 += NVG_PI*2;

		nvg__vset(dst, p1->x + dlx0*rw, p1->y + dly0*rw, lu,1); dst++;
		nvg__vset(dst, rx0, ry0, ru,1); dst++;

		n = nvg__clampi((int)ceilf(((a1 - a0) / NVG_PI) * ncap), 2, ncap);
		for (i = 0; i < n; i++) {
			float u = i/(float)(n-1);
			float a = a0 + u*(a1-a0);
			float lx = p1->x + cosf(a) * lw;
			float ly = p1->y + sinf(a) * lw;
			nvg__vset(dst, lx, ly, lu,1); dst++;
			nvg__vset(dst, p1->x, p1->y, 0.5f,1); dst++;
		}

		nvg__vset(dst, p1->x + dlx1*rw, p1->y + dly1*rw, lu,1); dst++;
		nvg__vset(dst, rx1, ry1, ru,1); dst++;

	}
	return dst;
}

static struct NVGvertex* nvg__bevelJoin(struct NVGvertex* dst, struct NVGpoint* p0, struct NVGpoint* p1,
										float lw, float rw, float lu, float ru, float fringe)
{
	float rx0,ry0,rx1,ry1;
	float lx0,ly0,lx1,ly1;
	float mx,my,len,mu;
	float dlx0 = p0->dy;
	float dly0 = -p0->dx;
	float dlx1 = p1->dy;
	float dly1 = -p1->dx;
	NVG_NOTUSED(fringe);
	NVG_NOTUSED(mu);

	if (p1->flags & NVG_PT_LEFT) {
		nvg__chooseBevel(p1->flags & NVG_PR_INNERBEVEL, p0, p1, lw, &lx0,&ly0, &lx1,&ly1);

		nvg__vset(dst, lx0, ly0, lu,1); dst++;
		nvg__vset(dst, p1->x - dlx0*rw, p1->y - dly0*rw, ru,1); dst++;

		if (p1->flags & NVG_PT_BEVEL) {
			// TODO: this needs more work.
			mx = (dlx0 + dlx1) * 0.5f;
			my = (dly0 + dly1) * 0.5f;
			len = sqrtf(mx*mx + my*my);
			mu = ru + len*(lu-ru)*0.5f;

			nvg__vset(dst, lx0, ly0, lu,1); dst++;
			nvg__vset(dst, p1->x - dlx0*rw, p1->y - dly0*rw, ru,1); dst++;

			nvg__vset(dst, lx1, ly1, lu,1); dst++;
			nvg__vset(dst, p1->x - dlx1*rw, p1->y - dly1*rw, ru,1); dst++;
		} else {
			rx0 = p1->x - p1->dmx * rw;
			ry0 = p1->y - p1->dmy * rw;

			nvg__vset(dst, p1->x, p1->y, 0.5f,1); dst++;
			nvg__vset(dst, p1->x - dlx0*rw, p1->y - dly0*rw, ru,1); dst++;

			nvg__vset(dst, rx0, ry0, ru,1); dst++;
			nvg__vset(dst, rx0, ry0, ru,1); dst++;

			nvg__vset(dst, p1->x, p1->y, 0.5f,1); dst++;
			nvg__vset(dst, p1->x - dlx1*rw, p1->y - dly1*rw, ru,1); dst++;
		}

		nvg__vset(dst, lx1, ly1, lu,1); dst++;
		nvg__vset(dst, p1->x - dlx1*rw, p1->y - dly1*rw, ru,1); dst++;

	} else {
		nvg__chooseBevel(p1->flags & NVG_PR_INNERBEVEL, p0, p1, -rw, &rx0,&ry0, &rx1,&ry1);

		nvg__vset(dst, p1->x + dlx0*lw, p1->y + dly0*lw, lu,1); dst++;
		nvg__vset(dst, rx0, ry0, ru,1); dst++;

		if (p1->flags & NVG_PT_BEVEL) {
			// TODO: this needs more work.
			mx = (dlx0 + dlx1) * 0.5f;
			my = (dly0 + dly1) * 0.5f;
			len = sqrtf(mx*mx + my*my);
			mu = lu + len*(ru-lu)*0.5f;

			nvg__vset(dst, p1->x + dlx0*lw, p1->y + dly0*lw, lu,1); dst++;
			nvg__vset(dst, rx0, ry0, ru,1); dst++;

			nvg__vset(dst, p1->x + dlx1*lw, p1->y + dly1*lw, lu,1); dst++;
			nvg__vset(dst, rx1, ry1, ru,1); dst++;
		} else {
			lx0 = p1->x + p1->dmx * lw;
			ly0 = p1->y + p1->dmy * lw;

			nvg__vset(dst, p1->x + dlx0*lw, p1->y + dly0*lw, lu,1); dst++;
			nvg__vset(dst, p1->x, p1->y, 0.5f,1); dst++;

			nvg__vset(dst, lx0, ly0, lu,1); dst++;
			nvg__vset(dst, lx0, ly0, lu,1); dst++;

			nvg__vset(dst, p1->x + dlx1*lw, p1->y + dly1*lw, lu,1); dst++;
			nvg__vset(dst, p1->x, p1->y, 0.5f,1); dst++;
		}

		nvg__vset(dst, p1->x + dlx1*rw, p1->y + dly1*rw, lu,1); dst++;
		nvg__vset(dst, rx1, ry1, ru,1); dst++;
	}

	return dst;
}

static int nvg__expandStrokeAndFill(struct NVGcontext* ctx, int feats, float w, int lineCap, int lineJoin, float miterLimit)
{
	struct NVGpathCache* cache = ctx->cache;
	struct NVGpath* path;
	struct NVGpoint* pts;
	struct NVGvertex* verts;
	struct NVGvertex* dst;
	struct NVGpoint* p0;
	struct NVGpoint* p1;
	int cverts, convex, i, j, s, e;
	float wo = 0, iw = 0, aa = ctx->fringeWidth;
	int ncap = nvg__curveDivs(w, NVG_PI, ctx->tessTol / 4.0f);
	int nleft = 0;

	if (w > 0.0f) iw = 1.0f / w;

	// Calculate which joins needs extra vertices to append, and gather vertex count.
	for (i = 0; i < cache->npaths; i++) {
		path = &cache->paths[i];
		pts = &cache->points[path->first];
		path->nbevel = 0;
		nleft = 0;

		p0 = &pts[path->count-1];
		p1 = &pts[0];
		for (j = 0; j < path->count; j++) {
			float dlx0, dly0, dlx1, dly1, dmr2, cross, limit;
			dlx0 = p0->dy;
			dly0 = -p0->dx;
			dlx1 = p1->dy;
			dly1 = -p1->dx;
			// Calculate extrusions
			p1->dmx = (dlx0 + dlx1) * 0.5f;
			p1->dmy = (dly0 + dly1) * 0.5f;
			dmr2 = p1->dmx*p1->dmx + p1->dmy*p1->dmy;
			if (dmr2 > 0.000001f) {
				float scale = 1.0f / dmr2;
				if (scale > 600.0f) {
					scale = 600.0f;
				}
				p1->dmx *= scale;
				p1->dmy *= scale;
			}

			// Clear flags, but keep the corner.
			p1->flags = (p1->flags & NVG_PT_CORNER) ? NVG_PT_CORNER : 0;

			// Keep track of left turns.
			cross = p1->dx * p0->dy - p0->dx * p1->dy;
			if (cross > 0.0f) {
				nleft++;
				p1->flags |= NVG_PT_LEFT;
			}

			// Calculate if we should use bevel or miter for inner join.
			limit = nvg__maxf(1.01f, nvg__minf(p0->len, p1->len) * iw);
			if ((dmr2 * limit*limit) < 1.0f)
				p1->flags |= NVG_PR_INNERBEVEL;

			// Check to see if the corner needs to be beveled.
			if (p1->flags & NVG_PT_CORNER) {
				if ((dmr2 * miterLimit*miterLimit) < 1.0f || lineJoin == NVG_BEVEL || lineJoin == NVG_ROUND) {
					p1->flags |= NVG_PT_BEVEL;
				}
			}

			if ((p1->flags & (NVG_PT_BEVEL | NVG_PR_INNERBEVEL)) != 0)
				path->nbevel++;

			p0 = p1++;
		}

		path->convex = (nleft == path->count) ? 1 : 0;
	}

	// Calculate max vertex usage.
	cverts = 0;
	for (i = 0; i < cache->npaths; i++) {
		path = &cache->paths[i];
		if (feats & NVG_FILL)
			cverts += path->count + path->nbevel + 1;
		if (feats & NVG_STROKE) {
			int loop = ((feats & NVG_CAPS) && path->closed == 0) ? 0 : 1;
			if (lineCap == NVG_ROUND)
				cverts += (path->count + path->nbevel*(ncap+2) + 1) * 2; // plus one for loop
			else
				cverts += (path->count + path->nbevel*5 + 1) * 2; // plus one for loop
			if (loop == 0) {
				// space for caps
				if (lineCap == NVG_ROUND) {
					cverts += (ncap*2 + 2)*2;
				} else {
					cverts += (3+3)*2;
				}
			}
		}
	}

	verts = nvg__allocTempVerts(ctx, cverts);
	if (verts == NULL) return 0;

	if ((feats & NVG_FILL) && cache->npaths == 1 && cache->paths[0].convex)
		convex = 1;
	else
		convex = 0;

	for (i = 0; i < cache->npaths; i++) {
		path = &cache->paths[i];
		pts = &cache->points[path->first];

		// Calculate shape vertices.
		if (feats & NVG_FILL) {
			wo = 0.5f*aa;
			dst = verts;
			path->fill = dst;

			if (w == 0.0f) {
				for (j = 0; j < path->count; ++j) {
					nvg__vset(dst, pts[j].x, pts[j].y, 0.5f,1);
					dst++;
				}
			} else {
				// Looping
				p0 = &pts[path->count-1];
				p1 = &pts[0];
				for (j = 0; j < path->count; ++j) {
					if (p1->flags & NVG_PT_BEVEL) {
						float dlx0 = p0->dy;
						float dly0 = -p0->dx;
						float dlx1 = p1->dy;
						float dly1 = -p1->dx;
						if (p1->flags & NVG_PT_LEFT) {
							float lx = p1->x + p1->dmx * wo;
							float ly = p1->y + p1->dmy * wo;
							nvg__vset(dst, lx, ly, 0.5f,1); dst++;
						} else {
							float lx0 = p1->x + dlx0 * wo;
							float ly0 = p1->y + dly0 * wo;
							float lx1 = p1->x + dlx1 * wo;
							float ly1 = p1->y + dly1 * wo;
							nvg__vset(dst, lx0, ly0, 0.5f,1); dst++;
							nvg__vset(dst, lx1, ly1, 0.5f,1); dst++;
						}
					} else {
						nvg__vset(dst, p1->x + (p1->dmx * wo), p1->y + (p1->dmy * wo), 0.5f,1); dst++;
					}
					p0 = p1++;
				}
			}

			path->nfill = (int)(dst - verts);
			verts = dst;
		} else {
			wo = 0.0f;
			path->fill = 0;
			path->nfill = 0;
		}

		// Calculate fringe or stroke
		if (feats & NVG_STROKE) {
			float lw = w + wo, rw = w - wo;
			float lu = 0, ru = 1;
			int loop = ((feats & NVG_CAPS) && path->closed == 0) ? 0 : 1;
			dst = verts;
			path->stroke = dst;

			// Create only half a fringe for convex shapes so that
			// the shape can be rendered without stenciling.
			if (convex) {
				lw = wo;	// This should generate the same vertex as fill inset above.
				lu = 0.5f;	// Set outline fade at middle.
			}

			if (loop) {
				// Looping
				p0 = &pts[path->count-1];
				p1 = &pts[0];
				s = 0;
				e = path->count;
			} else {
				// Add cap
				p0 = &pts[0];
				p1 = &pts[1];
				s = 1;
				e = path->count-1;
			}

			if (loop == 0) {
				// Add cap
				float dx, dy, dlx, dly, px, py;
				dx = p1->x - p0->x;
				dy = p1->y - p0->y;
				nvg__normalize(&dx, &dy);
				dlx = dy;
				dly = -dx;
				if (lineCap == NVG_BUTT || lineCap == NVG_SQUARE) {
					if (lineCap == NVG_BUTT) {
						px = p0->x;
						py = p0->y;
					} else /*if (lineCap == NVG_SQUARE)*/ {
						px = p0->x - dx*w;
						py = p0->y - dy*w;
					}
					nvg__vset(dst, px + dlx*lw - dx*aa, py + dly*lw - dy*aa, lu,0); dst++;
					nvg__vset(dst, px - dlx*rw - dx*aa, py - dly*rw - dy*aa, ru,0); dst++;
					nvg__vset(dst, px + dlx*lw, py + dly * lw, lu,1); dst++;
					nvg__vset(dst, px - dlx*rw, py - dly * rw, ru,1); dst++;
				} else if (lineCap == NVG_ROUND) {
					px = p0->x;
					py = p0->y;
					for (j = 0; j < ncap; j++) {
						float a = j/(float)(ncap-1)*NVG_PI;
						float ax = cosf(a) * w, ay = sinf(a) * w;
						nvg__vset(dst, px - dlx*ax - dx*ay, py - dly*ax - dy*ay, lu,1); dst++;
						nvg__vset(dst, px, py, 0.5f,1); dst++;
					}
					nvg__vset(dst, px + dlx*lw, py + dly * lw, lu,1); dst++;
					nvg__vset(dst, px - dlx*rw, py - dly * rw, ru,1); dst++;
				}
			}

			for (j = s; j < e; ++j) {
				if ((p1->flags & (NVG_PT_BEVEL | NVG_PR_INNERBEVEL)) != 0) {
					if (lineJoin == NVG_ROUND) {
						dst = nvg__roundJoin(dst, p0, p1, lw, rw, lu, ru, ncap, ctx->fringeWidth);
					} else {
						dst = nvg__bevelJoin(dst, p0, p1, lw, rw, lu, ru, ctx->fringeWidth);
					}
				} else {
					nvg__vset(dst, p1->x + (p1->dmx * lw), p1->y + (p1->dmy * lw), lu,1); dst++;
					nvg__vset(dst, p1->x - (p1->dmx * rw), p1->y - (p1->dmy * rw), ru,1); dst++;
				}
				p0 = p1++;
			}

			if (loop) {
				// Loop it
				nvg__vset(dst, verts[0].x, verts[0].y, lu,1); dst++;
				nvg__vset(dst, verts[1].x, verts[1].y, ru,1); dst++;
			} else {
				// Add cap
				float dx, dy, dlx, dly, px, py;
				dx = p1->x - p0->x;
				dy = p1->y - p0->y;
				nvg__normalize(&dx, &dy);
				dlx = dy;
				dly = -dx;
				if (lineCap == NVG_BUTT || lineCap == NVG_SQUARE) {
					if (lineCap == NVG_BUTT) {
						px = p1->x;
						py = p1->y;
					} else /*if (lineCap == NVG_SQUARE)*/ {
						px = p1->x + dx*w;
						py = p1->y + dy*w;
					}
					nvg__vset(dst, px + dlx*lw, py + dly * lw, lu,1); dst++;
					nvg__vset(dst, px - dlx*rw, py - dly * rw, ru,1); dst++;
					nvg__vset(dst, px + dlx*lw + dx*aa, py + dly*lw + dy*aa, lu,0); dst++;
					nvg__vset(dst, px - dlx*rw + dx*aa, py - dly*rw + dy*aa, ru,0); dst++;
				} else if (lineCap == NVG_ROUND) {
					px = p1->x;
					py = p1->y;
					nvg__vset(dst, px + dlx*lw, py + dly * lw, lu,1); dst++;
					nvg__vset(dst, px - dlx*rw, py - dly * rw, ru,1); dst++;
					for (j = 0; j < ncap; j++) {
						float a = j/(float)(ncap-1)*NVG_PI;
						float ax = cosf(a) * w, ay = sinf(a) * w;
						nvg__vset(dst, px, py, 0.5f,1); dst++;
						nvg__vset(dst, px - dlx*ax + dx*ay, py - dly*ax + dy*ay, lu,1); dst++;
					}
				}
			}

			path->nstroke = (int)(dst - verts);

			verts = dst;
		} else {
			path->stroke = 0;
			path->nstroke = 0;
		}
	}

	return 1;
}


// Draw
void nvgBeginPath(struct NVGcontext* ctx)
{
	ctx->ncommands = 0;
	nvg__clearPathCache(ctx);
}

void nvgMoveTo(struct NVGcontext* ctx, float x, float y)
{
	float vals[] = { NVG_MOVETO, x, y };
	nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

void nvgLineTo(struct NVGcontext* ctx, float x, float y)
{
	float vals[] = { NVG_LINETO, x, y };
	nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

void nvgBezierTo(struct NVGcontext* ctx, float c1x, float c1y, float c2x, float c2y, float x, float y)
{
	float vals[] = { NVG_BEZIERTO, c1x, c1y, c2x, c2y, x, y };
	nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

void nvgArcTo(struct NVGcontext* ctx, float x1, float y1, float x2, float y2, float radius)
{
	float x0 = ctx->commandx;
	float y0 = ctx->commandy;
	float dx0,dy0, dx1,dy1, a, d, cx,cy, a0,a1;
	int dir;

	if (ctx->ncommands == 0) {
		return;
	}

	// Handle degenerate cases.
	if (nvg__ptEquals(x0,y0, x1,y1, ctx->distTol) ||
		nvg__ptEquals(x1,y1, x2,y2, ctx->distTol) ||
		nvg__distPtSeg(x1,y1, x0,y0, x2,y2) < ctx->distTol*ctx->distTol ||
		radius < ctx->distTol) {
		nvgLineTo(ctx, x1,y1);
		return;
	}

	// Calculate tangential circle to lines (x0,y0)-(x1,y1) and (x1,y1)-(x2,y2).
	dx0 = x0-x1;
	dy0 = y0-y1;
	dx1 = x2-x1;
	dy1 = y2-y1;
	nvg__normalize(&dx0,&dy0);
	nvg__normalize(&dx1,&dy1);
	a = nvg__acosf(dx0*dx1 + dy0*dy1);
	d = radius / nvg__tanf(a/2.0f);

//	printf("a=%f° d=%f\n", a/NVG_PI*180.0f, d);

	if (d > 10000.0f) {
		nvgLineTo(ctx, x1,y1);
		return;
	}

	if (nvg__cross(dx0,dy0, dx1,dy1) > 0.0f) {
		cx = x1 + dx0*d + dy0*radius;
		cy = y1 + dy0*d + -dx0*radius;
		a0 = nvg__atan2f(dx0, -dy0);
		a1 = nvg__atan2f(-dx1, dy1);
		dir = NVG_CW;
//		printf("CW c=(%f, %f) a0=%f° a1=%f°\n", cx, cy, a0/NVG_PI*180.0f, a1/NVG_PI*180.0f);
	} else {
		cx = x1 + dx0*d + -dy0*radius;
		cy = y1 + dy0*d + dx0*radius;
		a0 = nvg__atan2f(-dx0, dy0);
		a1 = nvg__atan2f(dx1, -dy1);
		dir = NVG_CCW;
//		printf("CCW c=(%f, %f) a0=%f° a1=%f°\n", cx, cy, a0/NVG_PI*180.0f, a1/NVG_PI*180.0f);
	}

	nvgArc(ctx, cx, cy, radius, a0, a1, dir);
}

void nvgClosePath(struct NVGcontext* ctx)
{
	float vals[] = { NVG_CLOSE };
	nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

void nvgPathWinding(struct NVGcontext* ctx, int dir)
{
	float vals[] = { NVG_WINDING, (float)dir };
	nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

void nvgArc(struct NVGcontext* ctx, float cx, float cy, float r, float a0, float a1, int dir)
{
	float a = 0, da = 0, hda = 0, kappa = 0;
	float dx = 0, dy = 0, x = 0, y = 0, tanx = 0, tany = 0;
	float px = 0, py = 0, ptanx = 0, ptany = 0;
	float vals[3 + 5*7 + 100];
	int i, ndivs, nvals;
	int move = ctx->ncommands > 0 ? NVG_LINETO : NVG_MOVETO; 

	// Clamp angles
	da = a1 - a0;
	if (dir == NVG_CW) {
		if (nvg__absf(da) >= NVG_PI*2) {
			da = NVG_PI*2;
		} else {
			while (da < 0.0f) da += NVG_PI*2;
		}
	} else {
		if (nvg__absf(da) >= NVG_PI*2) {
			da = -NVG_PI*2;
		} else {
			while (da > 0.0f) da -= NVG_PI*2;
		}
	}

	// Split arc into max 90 degree segments.
	ndivs = nvg__maxi(1, nvg__mini((int)(nvg__absf(da) / (NVG_PI*0.5f) + 0.5f), 5));
	hda = (da / (float)ndivs) / 2.0f;
	kappa = nvg__absf(4.0f / 3.0f * (1.0f - nvg__cosf(hda)) / nvg__sinf(hda));

	if (dir == NVG_CCW)
		kappa = -kappa;

	nvals = 0;
	for (i = 0; i <= ndivs; i++) {
		a = a0 + da * (i/(float)ndivs);
		dx = nvg__cosf(a);
		dy = nvg__sinf(a);
		x = cx + dx*r;
		y = cy + dy*r;
		tanx = -dy*r*kappa;
		tany = dx*r*kappa;

		if (i == 0) {
			vals[nvals++] = (float)move;
			vals[nvals++] = x;
			vals[nvals++] = y;
		} else {
			vals[nvals++] = NVG_BEZIERTO;
			vals[nvals++] = px+ptanx;
			vals[nvals++] = py+ptany;
			vals[nvals++] = x-tanx;
			vals[nvals++] = y-tany;
			vals[nvals++] = x;
			vals[nvals++] = y;
		}
		px = x;
		py = y;
		ptanx = tanx;
		ptany = tany;
	}

	nvg__appendCommands(ctx, vals, nvals);
}

void nvgRect(struct NVGcontext* ctx, float x, float y, float w, float h)
{
	float vals[] = {
		NVG_MOVETO, x,y,
		NVG_LINETO, x+w,y,
		NVG_LINETO, x+w,y+h,
		NVG_LINETO, x,y+h,
		NVG_CLOSE
	};
	nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

void nvgRoundedRect(struct NVGcontext* ctx, float x, float y, float w, float h, float r)
{
	if (r < 0.1f) {
		nvgRect(ctx, x,y,w,h);
		return;
	}
	else {
		float vals[] = {
			NVG_MOVETO, x+r, y,
			NVG_LINETO, x+w-r, y,
			NVG_BEZIERTO, x+w-r*(1-NVG_KAPPA90), y, x+w, y+r*(1-NVG_KAPPA90), x+w, y+r,
			NVG_LINETO, x+w, y+h-r,
			NVG_BEZIERTO, x+w, y+h-r*(1-NVG_KAPPA90), x+w-r*(1-NVG_KAPPA90), y+h, x+w-r, y+h,
			NVG_LINETO, x+r, y+h,
			NVG_BEZIERTO, x+r*(1-NVG_KAPPA90), y+h, x, y+h-r*(1-NVG_KAPPA90), x, y+h-r,
			NVG_LINETO, x, y+r,
			NVG_BEZIERTO, x, y+r*(1-NVG_KAPPA90), x+r*(1-NVG_KAPPA90), y, x+r, y,
			NVG_CLOSE
		};
		nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
	}
}

void nvgEllipse(struct NVGcontext* ctx, float cx, float cy, float rx, float ry)
{
	float vals[] = {
		NVG_MOVETO, cx+rx, cy,
		NVG_BEZIERTO, cx+rx, cy+ry*NVG_KAPPA90, cx+rx*NVG_KAPPA90, cy+ry, cx, cy+ry,
		NVG_BEZIERTO, cx-rx*NVG_KAPPA90, cy+ry, cx-rx, cy+ry*NVG_KAPPA90, cx-rx, cy,
		NVG_BEZIERTO, cx-rx, cy-ry*NVG_KAPPA90, cx-rx*NVG_KAPPA90, cy-ry, cx, cy-ry,
		NVG_BEZIERTO, cx+rx*NVG_KAPPA90, cy-ry, cx+rx, cy-ry*NVG_KAPPA90, cx+rx, cy,
		NVG_CLOSE
	};
	nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

void nvgCircle(struct NVGcontext* ctx, float cx, float cy, float r)
{
	nvgEllipse(ctx, cx,cy, r,r);
}

void nvgDebugDumpPathCache(struct NVGcontext* ctx)
{
	const struct NVGpath* path;
	int i, j;

	printf("Dumping %d cached paths\n", ctx->cache->npaths);
	for (i = 0; i < ctx->cache->npaths; i++) {
		path = &ctx->cache->paths[i];
		printf(" - Path %d\n", i);
		if (path->nfill) {
			printf("   - fill: %d\n", path->nfill);
			for (j = 0; j < path->nfill; j++)
				printf("%f\t%f\n", path->fill[j].x, path->fill[j].y);
		}
		if (path->nstroke) {
			printf("   - stroke: %d\n", path->nstroke);
			for (j = 0; j < path->nstroke; j++)
				printf("%f\t%f\n", path->stroke[j].x, path->stroke[j].y);
		}
	}
}

void nvgFill(struct NVGcontext* ctx)
{
	struct NVGstate* state = nvg__getState(ctx);
	const struct NVGpath* path;
	int i;

	nvg__flattenPaths(ctx);
	if (ctx->params.edgeAntiAlias)
		nvg__expandStrokeAndFill(ctx, NVG_FILL|NVG_STROKE, ctx->fringeWidth, NVG_BUTT, NVG_MITER, 3.6f);
	else
		nvg__expandStrokeAndFill(ctx, NVG_FILL, 0.0f, NVG_BUTT, NVG_MITER, 1.2f);

	ctx->params.renderFill(ctx->params.userPtr, &state->fill, &state->scissor, ctx->fringeWidth,
						   ctx->cache->bounds, ctx->cache->paths, ctx->cache->npaths);

	// Count triangles
	for (i = 0; i < ctx->cache->npaths; i++) {
		path = &ctx->cache->paths[i];
		ctx->fillTriCount += path->nfill-2;
		ctx->fillTriCount += path->nstroke-2;
		ctx->drawCallCount += 2;
	}
}

void nvgStroke(struct NVGcontext* ctx)
{
	struct NVGstate* state = nvg__getState(ctx);
	float scale = nvg__getAverageScale(state->xform);
	float strokeWidth = nvg__clampf(state->strokeWidth * scale, 0.0f, 20.0f);
	struct NVGpaint strokePaint = state->stroke;
	const struct NVGpath* path;
	int i;

	if (strokeWidth < ctx->fringeWidth) {
		// If the stroke width is less than pixel size, use alpha to emulate coverate.
		// Since coverage is area, scale by alpha*alpha.
		float alpha = nvg__clampf(strokeWidth / ctx->fringeWidth, 0.0f, 1.0f);
		strokePaint.innerColor.a *= alpha*alpha;
		strokePaint.outerColor.a *= alpha*alpha;
		strokeWidth = ctx->fringeWidth;
	}

	nvg__flattenPaths(ctx);
	if (ctx->params.edgeAntiAlias)
		nvg__expandStrokeAndFill(ctx, NVG_STROKE|NVG_CAPS, strokeWidth*0.5f + ctx->fringeWidth*0.5f, state->lineCap, state->lineJoin, state->miterLimit);
	else
		nvg__expandStrokeAndFill(ctx, NVG_STROKE|NVG_CAPS, strokeWidth*0.5f, state->lineCap, state->lineJoin, state->miterLimit);

	ctx->params.renderStroke(ctx->params.userPtr, &strokePaint, &state->scissor, ctx->fringeWidth,
							 strokeWidth, ctx->cache->paths, ctx->cache->npaths);

	// Count triangles
	for (i = 0; i < ctx->cache->npaths; i++) {
		path = &ctx->cache->paths[i];
		ctx->strokeTriCount += path->nstroke-2;
		ctx->drawCallCount++;
	}
}

// Add fonts
int nvgCreateFont(struct NVGcontext* ctx, const char* name, const char* path)
{
	return fonsAddFont(ctx->fs, name, path);
}

int nvgCreateFontMem(struct NVGcontext* ctx, const char* name, unsigned char* data, int ndata, int freeData)
{
	return fonsAddFontMem(ctx->fs, name, data, ndata, freeData);
}

int nvgFindFont(struct NVGcontext* ctx, const char* name)
{
	if (name == NULL) return -1;
	return fonsGetFontByName(ctx->fs, name);
}

// State setting
void nvgFontSize(struct NVGcontext* ctx, float size)
{
	struct NVGstate* state = nvg__getState(ctx);
	state->fontSize = size;
}

void nvgFontBlur(struct NVGcontext* ctx, float blur)
{
	struct NVGstate* state = nvg__getState(ctx);
	state->fontBlur = blur;
}

void nvgTextLetterSpacing(struct NVGcontext* ctx, float spacing)
{
	struct NVGstate* state = nvg__getState(ctx);
	state->letterSpacing = spacing;
}

void nvgTextLineHeight(struct NVGcontext* ctx, float lineHeight)
{
	struct NVGstate* state = nvg__getState(ctx);
	state->lineHeight = lineHeight;
}

void nvgTextAlign(struct NVGcontext* ctx, int align)
{
	struct NVGstate* state = nvg__getState(ctx);
	state->textAlign = align;
}

void nvgFontFaceId(struct NVGcontext* ctx, int font)
{
	struct NVGstate* state = nvg__getState(ctx);
	state->fontId = font;
}

void nvgFontFace(struct NVGcontext* ctx, const char* font)
{
	struct NVGstate* state = nvg__getState(ctx);
	state->fontId = fonsGetFontByName(ctx->fs, font);
}

static float nvg__quantize(float a, float d)
{
	return ((int)(a / d + 0.5f)) * d;
}

static float nvg__getFontScale(struct NVGstate* state)
{
	return nvg__minf(nvg__quantize(nvg__getAverageScale(state->xform), 0.01f), 4.0f);
}

float nvgText(struct NVGcontext* ctx, float x, float y, const char* string, const char* end)
{
	struct NVGstate* state = nvg__getState(ctx);
	struct NVGpaint paint;
	struct FONStextIter iter;
	struct FONSquad q;
	struct NVGvertex* verts;
	float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
	float invscale = 1.0f / scale;
	int dirty[4];
	int cverts = 0;
	int nverts = 0;

	if (end == NULL)
		end = string + strlen(string);

	if (state->fontId == FONS_INVALID) return x;

	fonsSetSize(ctx->fs, state->fontSize*scale);
	fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
	fonsSetBlur(ctx->fs, state->fontBlur*scale);
	fonsSetAlign(ctx->fs, state->textAlign);
	fonsSetFont(ctx->fs, state->fontId);

	cverts = nvg__maxi(2, (int)(end - string)) * 6; // conservative estimate.
	verts = nvg__allocTempVerts(ctx, cverts);
	if (verts == NULL) return x;

	fonsTextIterInit(ctx->fs, &iter, x*scale, y*scale, string, end);
	while (fonsTextIterNext(ctx->fs, &iter, &q)) {
		// Trasnform corners.
		float c[4*2];
		nvg__xformPt(&c[0],&c[1], q.x0*invscale, q.y0*invscale, state->xform);
		nvg__xformPt(&c[2],&c[3], q.x1*invscale, q.y0*invscale, state->xform);
		nvg__xformPt(&c[4],&c[5], q.x1*invscale, q.y1*invscale, state->xform);
		nvg__xformPt(&c[6],&c[7], q.x0*invscale, q.y1*invscale, state->xform);
		// Create triangles
		if (nverts+6 <= cverts) {
			nvg__vset(&verts[nverts], c[0], c[1], q.s0, q.t0); nverts++;
			nvg__vset(&verts[nverts], c[4], c[5], q.s1, q.t1); nverts++;
			nvg__vset(&verts[nverts], c[2], c[3], q.s1, q.t0); nverts++;
			nvg__vset(&verts[nverts], c[0], c[1], q.s0, q.t0); nverts++;
			nvg__vset(&verts[nverts], c[6], c[7], q.s0, q.t1); nverts++;
			nvg__vset(&verts[nverts], c[4], c[5], q.s1, q.t1); nverts++;
		}
	}

	if (fonsValidateTexture(ctx->fs, dirty)) {
		// Update texture
		if (ctx->fontImage != 0) {
			int iw, ih;
			const unsigned char* data = fonsGetTextureData(ctx->fs, &iw, &ih);
			int x = dirty[0];
			int y = dirty[1];
			int w = dirty[2] - dirty[0];
			int h = dirty[3] - dirty[1];
			ctx->params.renderUpdateTexture(ctx->params.userPtr, ctx->fontImage, x,y, w,h, data);
		}
	}

	// Render triangles.
	paint = state->fill;
	paint.image = ctx->fontImage;
	ctx->params.renderTriangles(ctx->params.userPtr, &paint, &state->scissor, verts, nverts);

	ctx->drawCallCount++;
	ctx->textTriCount += nverts/3;

	return iter.x;
}

void nvgTextBox(struct NVGcontext* ctx, float x, float y, float breakRowWidth, const char* string, const char* end)
{
	struct NVGstate* state = nvg__getState(ctx);
	struct NVGtextRow rows[2];
	int nrows = 0, i;
	int oldAlign = state->textAlign;
	int haling = state->textAlign & (NVG_ALIGN_LEFT | NVG_ALIGN_CENTER | NVG_ALIGN_RIGHT);
	int valign = state->textAlign & (NVG_ALIGN_TOP | NVG_ALIGN_MIDDLE | NVG_ALIGN_BOTTOM | NVG_ALIGN_BASELINE);
	float lineh = 0;

	if (state->fontId == FONS_INVALID) return;

	nvgTextMetrics(ctx, NULL, NULL, &lineh);

	state->textAlign = NVG_ALIGN_LEFT | valign;

	while ((nrows = nvgTextBreakLines(ctx, string, end, breakRowWidth, rows, 2))) {
		for (i = 0; i < nrows; i++) {
			struct NVGtextRow* row = &rows[i];
			if (haling & NVG_ALIGN_LEFT)
				nvgText(ctx, x, y, row->start, row->end);
			else if (haling & NVG_ALIGN_CENTER)
				nvgText(ctx, x + breakRowWidth*0.5f - row->width*0.5f, y, row->start, row->end);
			else if (haling & NVG_ALIGN_RIGHT)
				nvgText(ctx, x + breakRowWidth - row->width, y, row->start, row->end);
			y += lineh * state->lineHeight;
		}
		string = rows[nrows-1].next;
	}

	state->textAlign = oldAlign;
}

int nvgTextGlyphPositions(struct NVGcontext* ctx, float x, float y, const char* string, const char* end, struct NVGglyphPosition* positions, int maxPositions)
{
	struct NVGstate* state = nvg__getState(ctx);
	float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
	float invscale = 1.0f / scale;
	struct FONStextIter iter;
	struct FONSquad q;
	int npos = 0;
	float px;

	if (state->fontId == FONS_INVALID) return 0;

	if (end == NULL)
		end = string + strlen(string);

	if (string == end)
		return 0;

	fonsSetSize(ctx->fs, state->fontSize*scale);
	fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
	fonsSetBlur(ctx->fs, state->fontBlur*scale);
	fonsSetAlign(ctx->fs, state->textAlign);
	fonsSetFont(ctx->fs, state->fontId);

	px = x*scale;
	fonsTextIterInit(ctx->fs, &iter, x*scale, y*scale, string, end);
	while (fonsTextIterNext(ctx->fs, &iter, &q)) {
		positions[npos].str = iter.str;
		positions[npos].x = px * invscale;
		px = iter.x;
		npos++;
		if (npos >= maxPositions)
			break;
	}

	return npos;
}

enum NVGcodepointType {
	NVG_SPACE,
	NVG_NEWLINE,
	NVG_CHAR,
};

int nvgTextBreakLines(struct NVGcontext* ctx, const char* string, const char* end, float breakRowWidth, struct NVGtextRow* rows, int maxRows)
{
	struct NVGstate* state = nvg__getState(ctx);
	float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
	float invscale = 1.0f / scale;
	struct FONStextIter iter;
	struct FONSquad q;
	int nrows = 0;
	float rowStartX = 0;
	float rowWidth = 0;
	float rowMinX = 0;
	float rowMaxX = 0;
	const char* rowStart = NULL;
	const char* rowEnd = NULL;
	const char* wordStart = NULL;
	float wordStartX = 0;
	float wordMinX = 0;
	const char* breakEnd = NULL;
	float breakWidth = 0;
	float breakMaxX = 0;
	int type = NVG_SPACE, ptype = NVG_SPACE;
	unsigned int pcodepoint = 0;

	if (maxRows == 0) return 0;
	if (state->fontId == FONS_INVALID) return 0;

	if (end == NULL)
		end = string + strlen(string);

	if (string == end) return 0;

	fonsSetSize(ctx->fs, state->fontSize*scale);
	fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
	fonsSetBlur(ctx->fs, state->fontBlur*scale);
	fonsSetAlign(ctx->fs, state->textAlign);
	fonsSetFont(ctx->fs, state->fontId);

	breakRowWidth *= scale;

	fonsTextIterInit(ctx->fs, &iter, 0, 0, string, end);
	while (fonsTextIterNext(ctx->fs, &iter, &q)) {
		switch (iter.codepoint) {
			case 9:			// \t
			case 11:		// \v
			case 12:		// \f
			case 32:		// space
			case 0x00a0:	// NBSP
				type = NVG_SPACE;
				break;
			case 10:		// \n
				type = pcodepoint == 13 ? NVG_SPACE : NVG_NEWLINE;
				break;
			case 13:		// \r
				type = pcodepoint == 10 ? NVG_SPACE : NVG_NEWLINE;
				break;
			case 0x0085:	// NEL
				type = NVG_NEWLINE;
				break;
			default:
				type = NVG_CHAR;
				break;
		}

		if (type == NVG_NEWLINE) {
			// Always handle new lines.
			rows[nrows].start = rowStart != NULL ? rowStart : iter.str;
			rows[nrows].end = rowEnd != NULL ? rowEnd : iter.str;
			rows[nrows].width = rowWidth * invscale;
			rows[nrows].minx = rowMinX * invscale;
			rows[nrows].maxx = rowMaxX * invscale;
			rows[nrows].next = iter.next;
			nrows++;
			if (nrows >= maxRows)
				return nrows;
			// Set null break point
			breakEnd = rowStart;
			breakWidth = 0.0;
			breakMaxX = 0.0;
			// Indicate to skip the white space at the beginning of the row.
			rowStart = NULL;
			rowEnd = NULL;
			rowWidth = 0;
			rowMinX = rowMaxX = 0;
		} else {
			if (rowStart == NULL) {
				// Skip white space until the beginning of the line
				if (type == NVG_CHAR) {
					// The current char is the row so far
					rowStartX = iter.x;
					rowStart = iter.str;
					rowEnd = iter.next;
					rowWidth = iter.nextx - rowStartX; // q.x1 - rowStartX;
					rowMinX = q.x0 - rowStartX;
					rowMaxX = q.x1 - rowStartX;
					wordStart = iter.str;
					wordStartX = iter.x;
					wordMinX = q.x0 - rowStartX;
					// Set null break point
					breakEnd = rowStart;
					breakWidth = 0.0;
					breakMaxX = 0.0;
				}
			} else {
				float nextWidth = iter.nextx - rowStartX; //q.x1 - rowStartX;

				if (nextWidth > breakRowWidth) {
					// The run length is too long, need to break to new line.
					if (breakEnd == rowStart) {
						// The current word is longer than the row length, just break it from here.
						rows[nrows].start = rowStart;
						rows[nrows].end = iter.str;
						rows[nrows].width = rowWidth * invscale;
						rows[nrows].minx = rowMinX * invscale;
						rows[nrows].maxx = rowMaxX * invscale;
						rows[nrows].next = iter.str;
						nrows++;
						if (nrows >= maxRows)
							return nrows;
						rowStartX = iter.x;
						rowStart = iter.str;
						rowEnd = iter.next;
						rowWidth = iter.nextx - rowStartX;
						rowMinX = q.x0 - rowStartX;
						rowMaxX = q.x1 - rowStartX;
						wordStart = iter.str;
						wordStartX = iter.x;
						wordMinX = q.x0 - rowStartX;
					} else {
						// Break the line from the end of the last word, and start new line from the begining of the new.
						rows[nrows].start = rowStart;
						rows[nrows].end = breakEnd;
						rows[nrows].width = breakWidth * invscale;
						rows[nrows].minx = rowMinX * invscale;
						rows[nrows].maxx = breakMaxX * invscale;
						rows[nrows].next = wordStart;
						nrows++;
						if (nrows >= maxRows)
							return nrows;
						rowStartX = wordStartX;
						rowStart = wordStart;
						rowEnd = iter.next;
						rowWidth = iter.nextx - rowStartX; // q.x1 - rowStartX;
						rowMinX = wordMinX;
						rowMaxX = q.x1 - rowStartX;
						// No change to the word start
					}
					// Set null break point
					breakEnd = rowStart;
					breakWidth = 0.0;
					breakMaxX = 0.0;
				}

				// track last non-white space character
				if (type == NVG_CHAR) {
					rowEnd = iter.next;
					rowWidth = iter.nextx - rowStartX; // q.x1 - rowStartX;
					rowMaxX = q.x1 - rowStartX;
				}
				// track last end of a word
				if (ptype == NVG_CHAR && (type == NVG_SPACE || type == NVG_SPACE)) {
					breakEnd = iter.str;
					breakWidth = rowWidth;
					breakMaxX = rowMaxX;
				}
				// track last beginning of a word
				if ((ptype == NVG_SPACE || ptype == NVG_SPACE) && type == NVG_CHAR) {
					wordStart = iter.str;
					wordStartX = iter.x;
					wordMinX = q.x0 - rowStartX;
				}
			}
		}

		pcodepoint = iter.codepoint;
		ptype = type;
	}

	// Break the line from the end of the last word, and start new line from the begining of the new.
	if (rowStart != NULL) {
		rows[nrows].start = rowStart;
		rows[nrows].end = rowEnd;
		rows[nrows].width = rowWidth * invscale;
		rows[nrows].minx = rowMinX * invscale;
		rows[nrows].maxx = rowMaxX * invscale;
		rows[nrows].next = end;
		nrows++;
	}

	return nrows;
}

float nvgTextBounds(struct NVGcontext* ctx, float x, float y, const char* string, const char* end, float* bounds)
{
	struct NVGstate* state = nvg__getState(ctx);
	float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
	float invscale = 1.0f / scale;
	float width;

	if (state->fontId == FONS_INVALID) return 0;

	fonsSetSize(ctx->fs, state->fontSize*scale);
	fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
	fonsSetBlur(ctx->fs, state->fontBlur*scale);
	fonsSetAlign(ctx->fs, state->textAlign);
	fonsSetFont(ctx->fs, state->fontId);

	width = fonsTextBounds(ctx->fs, x, y, string, end, bounds);
	if (bounds != NULL) {
		bounds[0] *= invscale;
		bounds[1] *= invscale;
		bounds[2] *= invscale;
		bounds[3] *= invscale;
	}
	return width * invscale;
}

void nvgTextBoxBounds(struct NVGcontext* ctx, float x, float y, float breakRowWidth, const char* string, const char* end, float* bounds)
{
	struct NVGstate* state = nvg__getState(ctx);
	struct NVGtextRow rows[2];
	float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
	float invscale = 1.0f / scale;
	int nrows = 0, i;
	int oldAlign = state->textAlign;
	int haling = state->textAlign & (NVG_ALIGN_LEFT | NVG_ALIGN_CENTER | NVG_ALIGN_RIGHT);
	int valign = state->textAlign & (NVG_ALIGN_TOP | NVG_ALIGN_MIDDLE | NVG_ALIGN_BOTTOM | NVG_ALIGN_BASELINE);
	float lineh = 0, rminy = 0, rmaxy = 0;
	float minx, miny, maxx, maxy;

	if (state->fontId == FONS_INVALID) {
		if (bounds != NULL)
			bounds[0] = bounds[1] = bounds[2] = bounds[3] = 0.0f;
		return;
	}

	nvgTextMetrics(ctx, NULL, NULL, &lineh);

	nvgTextMetrics(ctx, NULL, NULL, &lineh);

	state->textAlign = NVG_ALIGN_LEFT | valign;

	minx = maxx = x;
	miny = maxy = y;

	fonsSetSize(ctx->fs, state->fontSize*scale);
	fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
	fonsSetBlur(ctx->fs, state->fontBlur*scale);
	fonsSetAlign(ctx->fs, state->textAlign);
	fonsSetFont(ctx->fs, state->fontId);
	fonsLineBounds(ctx->fs, 0, &rminy, &rmaxy);
	rminy *= invscale;
	rmaxy *= invscale;

	while ((nrows = nvgTextBreakLines(ctx, string, end, breakRowWidth, rows, 2))) {
		for (i = 0; i < nrows; i++) {
			struct NVGtextRow* row = &rows[i];
			float rminx, rmaxx, dx = 0;
			// Horizontal bounds
			if (haling & NVG_ALIGN_LEFT)
				dx = 0;
			else if (haling & NVG_ALIGN_CENTER)
				dx = breakRowWidth*0.5f - row->width*0.5f;
			else if (haling & NVG_ALIGN_RIGHT)
				dx = breakRowWidth - row->width;
			rminx = x + row->minx + dx;
			rmaxx = x + row->maxx + dx;
			minx = nvg__minf(minx, rminx);
			maxx = nvg__maxf(maxx, rmaxx);
			// Vertical bounds.
			miny = nvg__minf(miny, y + rminy);
			maxy = nvg__maxf(maxy, y + rmaxy);

			y += lineh * state->lineHeight;
		}
		string = rows[nrows-1].next;
	}

	state->textAlign = oldAlign;

	if (bounds != NULL) {
		bounds[0] = minx;
		bounds[1] = miny;
		bounds[2] = maxx;
		bounds[3] = maxy;
	}
}

void nvgTextMetrics(struct NVGcontext* ctx, float* ascender, float* descender, float* lineh)
{
	struct NVGstate* state = nvg__getState(ctx);
	float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
	float invscale = 1.0f / scale;

	if (state->fontId == FONS_INVALID) return;

	fonsSetSize(ctx->fs, state->fontSize*scale);
	fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
	fonsSetBlur(ctx->fs, state->fontBlur*scale);
	fonsSetAlign(ctx->fs, state->textAlign);
	fonsSetFont(ctx->fs, state->fontId);

	fonsVertMetrics(ctx->fs, ascender, descender, lineh);
	if (ascender != NULL)
		*ascender *= invscale;
	if (descender != NULL)
		*descender *= invscale;
	if (lineh != NULL)
		*lineh *= invscale;
}
