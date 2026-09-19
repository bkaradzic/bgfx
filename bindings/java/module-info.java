// Copyright 2011-2026 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE

/**
 * Java Foreign Function and Memory API bindings for the bgfx C99 API.
 *
 * <p>The {@link io.github.bkaradzic.bgfx} package provides native entry points,
 * structures, handles, enums, and flags. The
 * {@link io.github.bkaradzic.bgfx.caps} and {@link io.github.bkaradzic.bgfx.init}
 * packages contain supporting capability and initialization structures.
 *
 * <p>Load a compatible bgfx native library before invoking native entry points.
 * Symbols are resolved lazily on first invocation. When running on the module
 * path, enable native access with
 * {@code --enable-native-access=io.github.bkaradzic.bgfx}.
 */
module io.github.bkaradzic.bgfx {
	requires static transitive org.jspecify;

    exports io.github.bkaradzic.bgfx;
	exports io.github.bkaradzic.bgfx.caps;
	exports io.github.bkaradzic.bgfx.init;
	exports io.github.bkaradzic.bgfx.util;
}
