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
			BGFX_DIR .. "3rdparty",
			BGFX_DIR .. "../bx/include",
		}

		defines {
			_defines,
		}

		if _OPTIONS["with-ovr"] then
			defines {
				"BGFX_CONFIG_USE_OVR=1",
			}
			includedirs {
				"$(OVR_DIR)/LibOVR/Include",
			}
		end

		configuration { "Debug" }
			defines {
				"BGFX_CONFIG_DEBUG=1",
			}

		configuration { "android*" }
			links {
				"EGL",
				"GLESv2",
			}

		configuration { "mingw* or vs2008" }
			includedirs {
				"$(DXSDK_DIR)/include",
			}

		configuration { "xcode4 or osx or ios*" }
			files {
				BGFX_DIR .. "src/**.mm",
			}

		configuration { "osx" }
			links {
				"Cocoa.framework",
			}

		configuration { "not nacl" }
			includedirs {
				--nacl has GLES2 headers modified...
				BGFX_DIR .. "3rdparty/khronos",
			}

		configuration { "x64", "vs* or mingw*" }
			defines {
				"_WIN32_WINNT=0x601",
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
