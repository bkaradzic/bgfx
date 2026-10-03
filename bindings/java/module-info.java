// Copyright 2011-2026 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE

/**
 * Java Foreign Function and Memory API bindings for the bgfx C99 API.
 *
 * <p>Native entry points and supporting types are in
 * {@link io.github.bkaradzic.bgfx}. Load a compatible bgfx native library
 * before invoking native methods. When running on the module path, enable
 * native access with {@code --enable-native-access=io.github.bkaradzic.bgfx}.
 */
module io.github.bkaradzic.bgfx {
	requires static transitive org.jspecify;

	exports io.github.bkaradzic.bgfx;
}
