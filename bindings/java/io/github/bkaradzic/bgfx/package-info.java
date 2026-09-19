// Copyright 2011-2026 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE

/**
 * Java Foreign Function and Memory API bindings for the bgfx C99 API.
 * <p>
 * Native entry points are exposed through {@link io.github.bkaradzic.bgfx.Bgfx}
 * and instance methods on native wrappers such as
 * {@link io.github.bkaradzic.bgfx.Encoder}. Load a compatible bgfx native library
 * before invoking native methods; symbols are resolved lazily on first use.
 * <p>
 * Native structures can be allocated with
 * constructors accepting a {@link java.lang.foreign.SegmentAllocator}. Their
 * backing memory must remain alive for as long as native code uses it. Wrapping
 * an existing {@link java.lang.foreign.MemorySegment} does not transfer ownership
 * or extend its lifetime. Handles are immutable Java records; their native
 * resources have separate lifetimes managed through the bgfx API.
 * <p>
 * A native null pointer represented by
 * {@link java.lang.foreign.MemorySegment#NULL} is a non-null Java value.
 * Whether a native argument permits a null pointer is determined by the bgfx
 * API contract. The IDL does not provide complete nullability metadata, so Java
 * nullability annotations alone do not establish native pointer requirements.
 */
@NullUnmarked
package io.github.bkaradzic.bgfx;

import org.jspecify.annotations.NullMarked;
import org.jspecify.annotations.NullUnmarked;
