--
-- Copyright 2010-2018 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--

function filesexist(_srcPath, _dstPath, _files)
	for _, file in ipairs(_files) do
		file = path.getrelative(_srcPath, file)
		local filePath = path.join(_dstPath, file)
		if not os.isfile(filePath) then return false end
	end

	return true
end

function overridefiles(_srcPath, _dstPath, _files)

	local remove = {}
	local add = {}
	for _, file in ipairs(_files) do
		file = path.getrelative(_srcPath, file)
		local filePath = path.join(_dstPath, file)
		if not os.isfile(filePath) then return end

		table.insert(remove, path.join(_srcPath, file))
		table.insert(add, filePath)
	end

	removefiles {
		remove,
	}

	files {
		add,
	}
end

function bgfxProject(_name, _kind, _defines)
	project ("bgfx" .. _name)
		uuid (os.uuid("bgfx" .. _name))
		bgfxProjectBase(_kind, _defines)
		copyLib()
end

function bgfxProjectBase(_kind, _defines)
		kind (_kind)

		if _kind == "SharedLib" then
			defines {
				"BGFX_SHARED_LIB_BUILD=1",
			}

			links {
				"bimg",
				"bx",
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
			path.join(BX_DIR,   "include"),
			path.join(BIMG_DIR, "include"),
		}

		defines {
			_defines,
		}

		links {
			"bx",
		}

		if _OPTIONS["with-glfw"] then
			defines {
				"BGFX_CONFIG_MULTITHREADED=0",
			}
		end

		if _OPTIONS["with-ovr"] then
			defines {
--				"BGFX_CONFIG_MULTITHREADED=0",
				"BGFX_CONFIG_USE_OVR=1",
			}
			includedirs {
				"$(OVR_DIR)/LibOVR/Include",
			}

			configuration { "x32" }
				libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/Windows/Win32/Release", _ACTION) }

			configuration { "x64" }
				libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/Windows/x64/Release", _ACTION) }

			configuration { "x32 or x64" }
				links { "libovr" }

			configuration {}
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

		configuration { "winstore*" }
			linkoptions {
				"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
			}

		configuration { "*clang*" }
			buildoptions {
				"-Wno-microsoft-enum-value", -- enumerator value is not representable in the underlying type 'int'
				"-Wno-microsoft-const-init", -- default initialization of an object of const type '' without a user-provided default constructor is a Microsoft extension
			}

		configuration { "osx" }
			linkoptions {
				"-framework Cocoa",
				"-framework QuartzCore",
				"-framework OpenGL",
				"-weak_framework Metal",
				"-weak_framework MetalKit",
			}

		configuration { "not linux-steamlink", "not NX32", "not NX64" }
			includedirs {
				-- steamlink has EGL headers modified...
				-- NX has EGL headers modified...
				path.join(BGFX_DIR, "3rdparty/khronos"),
			}

		configuration { "linux-steamlink" }
			defines {
				"EGL_API_FB",
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

		overridefiles(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-ext"), {
			path.join(BGFX_DIR, "src/renderer_gnm.cpp"),
			path.join(BGFX_DIR, "src/renderer_gnm.h"),
		})

		if _OPTIONS["with-amalgamated"] then
			excludes {
				path.join(BGFX_DIR, "src/bgfx.cpp"),
				path.join(BGFX_DIR, "src/debug_**.cpp"),
				path.join(BGFX_DIR, "src/glcontext_**.cpp"),
				path.join(BGFX_DIR, "src/image.cpp"),
				path.join(BGFX_DIR, "src/hmd**.cpp"),
				path.join(BGFX_DIR, "src/renderer_**.cpp"),
				path.join(BGFX_DIR, "src/shader**.cpp"),
				path.join(BGFX_DIR, "src/topology.cpp"),
				path.join(BGFX_DIR, "src/vertexdecl.cpp"),
			}

			configuration { "xcode* or osx or ios*" }
				files {
					path.join(BGFX_DIR, "src/amalgamated.mm"),
				}

				excludes {
					path.join(BGFX_DIR, "src/glcontext_**.mm"),
					path.join(BGFX_DIR, "src/renderer_**.mm"),
					path.join(BGFX_DIR, "src/amalgamated.cpp"),
				}

			configuration { "not (xcode* or osx or ios*)" }
				excludes {
					path.join(BGFX_DIR, "src/**.mm"),
				}

			configuration {}

		else
			configuration { "xcode* or osx or ios*" }
				files {
					path.join(BGFX_DIR, "src/glcontext_**.mm"),
					path.join(BGFX_DIR, "src/renderer_**.mm"),
				}

			configuration {}

			excludes {
				path.join(BGFX_DIR, "src/amalgamated.**"),
			}
		end

		configuration {}
end
