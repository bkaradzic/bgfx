--
-- Copyright 2010-2015 Branimir Karadzic. All rights reserved.
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

			configuration { "vs20* or mingw*" }
				links {
					"gdi32",
					"psapi",
				}

			configuration { "mingw*" }
				linkoptions {
					"-shared",
				}

			configuration { "linux-*" }
				buildoptions {
					"-fPIC",
				}

			configuration {}
		end

		includedirs {
			path.join(BGFX_DIR, "3rdparty"),
			path.join(BGFX_DIR, "3rdparty/dxsdk/include"),
			path.join(BGFX_DIR, "../bx/include"),
		}

		defines {
			_defines,
		}

		if _OPTIONS["with-glfw"] then
			defines {
				"BGFX_CONFIG_MULTITHREADED=0",
			}
		end

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

		configuration { "winphone8* or winstore8*" }
			linkoptions {
				"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
			}

		configuration { "*clang*" }
			buildoptions {
				"-Wno-microsoft-enum-value", -- enumerator value is not representable in the underlying type 'int'
				"-Wno-microsoft-const-init", -- default initialization of an object of const type '' without a user-provided default constructor is a Microsoft extension
			}

		configuration { "osx" }
			links {
				"Cocoa.framework",
			}

		configuration { "not nacl" }
			includedirs {
				--nacl has GLES2 headers modified...
				path.join(BGFX_DIR, "3rdparty/khronos"),
			}

		configuration {}

		includedirs {
			path.join(BGFX_DIR, "include"),
		}

		files {
			path.join(BGFX_DIR, "include/**.h"),
			path.join(BGFX_DIR, "src/**.cpp"),
			path.join(BGFX_DIR, "src/**.h"),
		}

		removefiles {
			path.join(BGFX_DIR, "src/**.bin.h"),
		}

		if _OPTIONS["with-amalgamated"] then
			excludes {
				path.join(BGFX_DIR, "src/bgfx.cpp"),
				path.join(BGFX_DIR, "src/glcontext_egl.cpp"),
				path.join(BGFX_DIR, "src/glcontext_glx.cpp"),
				path.join(BGFX_DIR, "src/glcontext_ppapi.cpp"),
				path.join(BGFX_DIR, "src/glcontext_wgl.cpp"),
				path.join(BGFX_DIR, "src/image.cpp"),
				path.join(BGFX_DIR, "src/ovr.cpp"),
				path.join(BGFX_DIR, "src/renderdoc.cpp"),
				path.join(BGFX_DIR, "src/renderer_d3d9.cpp"),
				path.join(BGFX_DIR, "src/renderer_d3d11.cpp"),
				path.join(BGFX_DIR, "src/renderer_d3d12.cpp"),
				path.join(BGFX_DIR, "src/renderer_null.cpp"),
				path.join(BGFX_DIR, "src/renderer_gl.cpp"),
				path.join(BGFX_DIR, "src/renderer_vk.cpp"),
				path.join(BGFX_DIR, "src/shader_dx9bc.cpp"),
				path.join(BGFX_DIR, "src/shader_dxbc.cpp"),
				path.join(BGFX_DIR, "src/shader_spirv.cpp"),
				path.join(BGFX_DIR, "src/vertexdecl.cpp"),
			}

			configuration { "xcode4 or osx or ios*" }
				files {
					path.join(BGFX_DIR, "src/amalgamated.mm"),
				}

				excludes {
					path.join(BGFX_DIR, "src/glcontext_eagl.mm"),
					path.join(BGFX_DIR, "src/glcontext_nsgl.mm"),
					path.join(BGFX_DIR, "src/renderer_mtl.mm"),
					path.join(BGFX_DIR, "src/amalgamated.cpp"),
				}

			configuration {}

		else
			configuration { "xcode4 or osx or ios*" }
				files {
					path.join(BGFX_DIR, "src/glcontext_eagl.mm"),
					path.join(BGFX_DIR, "src/glcontext_nsgl.mm"),
					path.join(BGFX_DIR, "src/renderer_mtl.mm"),
				}

			configuration {}

			excludes {
				path.join(BGFX_DIR, "src/amalgamated.**"),
			}
		end

		configuration {}

		copyLib()
end
