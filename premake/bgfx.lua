--
-- Copyright 2010-2014 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

function bgfxProject(_name, _uuid, _kind, _defines)

	project ("bgfx" .. _name)
		uuid (_uuid)
		kind (_kind)

		if _kind == "SharedLib" then
			defines {
				"BGFX_SHARED_LIB_BUILD=1",
			}
		end

		includedirs {
			BGFX_DIR .. "../bx/include",
		}

		defines {
	--		"BGFX_CONFIG_RENDERER_OPENGL=1",
		}

		configuration { "Debug" }
			defines {
				"BGFX_CONFIG_DEBUG=1",
				_defines,
			}

		configuration { "android*" }
			links {
				"EGL",
				"GLESv2",
			}

		configuration { "windows" }
			includedirs {
				"$(DXSDK_DIR)/include",
			}
			links {
				"gdi32",
			}

		configuration { "osx or ios*" }
			files {
				BGFX_DIR .. "src/**.mm",
			}

		configuration { "osx" }
			links {
				"Cocoa.framework",
			}

		configuration { "vs* or linux or mingw or osx or ios*" }
			includedirs {
				--nacl has GLES2 headers modified...
				BGFX_DIR .. "3rdparty/khronos",
			}

		configuration {}

		includedirs {
			BGFX_DIR .. "include",
		}

		files {
			BGFX_DIR .. "include/**.h",
			BGFX_DIR .. "src/**.cpp",
			BGFX_DIR .. "src/**.h",
		}

		excludes {
			BGFX_DIR .. "src/**.bin.h",
		}

		configuration {}

		copyLib()
end
