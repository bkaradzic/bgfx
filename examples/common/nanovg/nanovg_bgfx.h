/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef NANOVG_BGFX_H_HEADER_GUARD
#define NANOVG_BGFX_H_HEADER_GUARD

namespace bx { struct AllocatorI; }

struct NVGcontext;

NVGcontext* nvgCreate(int edgeaa, unsigned char _viewId, bx::AllocatorI* _allocator);
NVGcontext* nvgCreate(int edgeaa, unsigned char _viewId);
void nvgViewId(struct NVGcontext* ctx, unsigned char _viewId);
void nvgDelete(struct NVGcontext* ctx);

#endif // NANOVG_BGFX_H_HEADER_GUARD
