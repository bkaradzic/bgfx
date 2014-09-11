--
-- Copyright 2010-2014 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

function bgfxProject(_name, _kind, _defines)

	project ("bgfx" .. _name)
		uuid (os.uuid("bgfx" .. _name))
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
			_defines,
		}

		configuration { "Debug" }
			defines {
				"BGFX_CONFIG_DEBUG=1",
			}

		configuration { "android*" }
			links {
				"EGL",
				"GLESv2",
			}

		configuration { "windows", "not vs201*" }
			includedirs {
				"$(DXSDK_DIR)/include",
			}

		configuration { "windows" }
			links {
				"gdi32",
			}

		configuration { "xcode4 or osx or ios*" }
			files {
				BGFX_DIR .. "src/**.mm",
			}

		configuration { "osx" }
			links {
				"Cocoa.framework",
			}

		configuration { "vs* or linux or mingw or xcode4 or osx or ios* or rpi" }
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
