// Copyright 2011-2026 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE

/**
 * Java Foreign Function and Memory API bindings for bgfx.
 */
module io.github.bkaradzic.bgfx {
	requires static transitive org.jspecify;
    requires jdk.jdi;

    exports io.github.bkaradzic.bgfx;
	exports io.github.bkaradzic.bgfx.caps;
	exports io.github.bkaradzic.bgfx.init;
	exports io.github.bkaradzic.bgfx.util;
}
