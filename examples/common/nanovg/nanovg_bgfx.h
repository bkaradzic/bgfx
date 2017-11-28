/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef NANOVG_BGFX_H_HEADER_GUARD
#define NANOVG_BGFX_H_HEADER_GUARD

#include "bgfx/bgfx.h"

namespace bx { struct AllocatorI; }

struct NVGcontext;

struct NVGLUframebuffer {
  NVGcontext* ctx;
  bgfx::FrameBufferHandle handle;
  int image;
  uint8_t viewId;
};

typedef struct NVGLUframebuffer NVGLUframebuffer;

///
NVGcontext* nvgCreate(int32_t edgeaa, uint16_t _viewId, bx::AllocatorI* _allocator);

///
NVGcontext* nvgCreate(int32_t edgeaa, uint16_t _viewId);

///
void nvgDelete(struct NVGcontext* ctx);

///
void nvgSetViewId(struct NVGcontext* ctx, uint16_t _viewId);

///
uint16_t nvgGetViewId(struct NVGcontext* ctx);

// Helper functions to create bgfx framebuffer to render to.
// Example:
//		float scale = 2;
//		NVGLUframebuffer* fb = nvgluCreateFramebuffer(ctx, 100 * scale, 100 * scale, 0);
//		nvgluSetViewFramebuffer(VIEW_ID, fb);
//		nvgluBindFramebuffer(fb);
//		nvgBeginFrame(ctx, 100, 100, scale);
//		// renders anything offscreen
//		nvgEndFrame(ctx);
//		nvgluBindFramebuffer(NULL);
//
//		// Pastes the framebuffer rendering.
//		nvgBeginFrame(ctx, 1024, 768, scale);
//		NVGpaint paint = nvgImagePattern(ctx, 0, 0, 100, 100, 0, fb->image, 1);
//		nvgBeginPath(ctx);
//		nvgRect(ctx, 0, 0, 100, 100);
//		nvgFillPaint(ctx, paint);
//		nvgFill(ctx);
//		nvgEndFrame(ctx);

///
NVGLUframebuffer* nvgluCreateFramebuffer(NVGcontext* ctx, int width, int height, int imageFlags, uint16_t viewId);

///
NVGLUframebuffer* nvgluCreateFramebuffer(NVGcontext* ctx, int width, int height, int imageFlags);

///
void nvgluBindFramebuffer(NVGLUframebuffer* framebuffer);

///
void nvgluDeleteFramebuffer(NVGLUframebuffer* framebuffer);

///
void nvgluSetViewFramebuffer(uint16_t viewId, NVGLUframebuffer* framebuffer);

#endif // NANOVG_BGFX_H_HEADER_GUARD
