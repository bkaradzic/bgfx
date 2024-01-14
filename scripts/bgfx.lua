--
-- Copyright 2010-2024 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
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

function bgfxProjectBase(_kind, _defines)

	kind (_kind)

	if _kind == "SharedLib" then
		defines {
			"BGFX_SHARED_LIB_BUILD=1",
		}

		links {
			"bimg",
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
			links {
				"X11",
				"GL",
				"pthread",
			}

		configuration { "android*" }
			targetextension ".so"

		configuration { "android*" ,"Debug"}
			linkoptions {
				"-Wl,-soname,libbgfx-shared-libDebug.so",
			}

		configuration { "android*" ,"Release"}
			linkoptions {
				"-Wl,-soname,libbgfx-shared-libRelease.so",
			}

		configuration {}
	else
		configuration { "android*" }
			linkoptions {
				"-Wl,--fix-cortex-a8",
			}

		configuration {}
	end

	includedirs {
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BIMG_DIR, "include"),
	}

	defines (_defines)

	using_bx()

	if _OPTIONS["with-glfw"] then
		defines {
			"BGFX_CONFIG_MULTITHREADED=0",
		}
	end

	configuration { "linux-*" }
		includedirs {
			path.join(BGFX_DIR, "3rdparty/directx-headers/include/directx"),
			path.join(BGFX_DIR, "3rdparty/directx-headers/include"),
			path.join(BGFX_DIR, "3rdparty/directx-headers/include/wsl/stubs"),
		}

	configuration { "vs* or mingw*", "not durango" }
		includedirs {
			path.join(BGFX_DIR, "3rdparty/directx-headers/include/directx"),
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

	configuration { "osx*" }
		buildoptions { "-x objective-c++" }  -- additional build option for osx
		linkoptions {
			"-framework Cocoa",
			"-framework IOKit",
			"-framework OpenGL",
			"-framework QuartzCore",
			"-weak_framework Metal",
			"-weak_framework MetalKit",
		}

	configuration { "not NX32", "not NX64" }
		includedirs {
			-- NX has EGL headers modified...
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
		path.join(BGFX_DIR, "scripts/**.natvis"),
	}

	removefiles {
		path.join(BGFX_DIR, "src/**.bin.h"),
	}

	overridefiles(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-agc"), {
		path.join(BGFX_DIR, "src/renderer_agc.cpp"),
		path.join(BGFX_DIR, "src/renderer_agc.h"),
	})

	overridefiles(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-gnm"), {
		path.join(BGFX_DIR, "src/renderer_gnm.cpp"),
		path.join(BGFX_DIR, "src/renderer_gnm.h"),
	})

	overridefiles(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-nvn"), {
		path.join(BGFX_DIR, "src/renderer_nvn.cpp"),
		path.join(BGFX_DIR, "src/renderer_nvn.h"),
	})

	if _OPTIONS["with-amalgamated"] then
		excludes {
			path.join(BGFX_DIR, "src/bgfx.cpp"),
			path.join(BGFX_DIR, "src/debug_**.cpp"),
			path.join(BGFX_DIR, "src/dxgi.cpp"),
			path.join(BGFX_DIR, "src/glcontext_**.cpp"),
			path.join(BGFX_DIR, "src/hmd**.cpp"),
			path.join(BGFX_DIR, "src/image.cpp"),
			path.join(BGFX_DIR, "src/nvapi.cpp"),
			path.join(BGFX_DIR, "src/renderer_**.cpp"),
			path.join(BGFX_DIR, "src/shader**.cpp"),
			path.join(BGFX_DIR, "src/topology.cpp"),
			path.join(BGFX_DIR, "src/vertexlayout.cpp"),
		}

		configuration { "xcode* or osx* or ios*" }
			files {
				path.join(BGFX_DIR, "src/amalgamated.mm"),
			}

			excludes {
				path.join(BGFX_DIR, "src/renderer_**.mm"),
				path.join(BGFX_DIR, "src/amalgamated.cpp"),
			}

		configuration { "not (xcode* or osx* or ios*)" }
			excludes {
				path.join(BGFX_DIR, "src/**.mm"),
			}

		configuration {}

	else
		configuration { "xcode* or osx* or ios*" }
			files {
				path.join(BGFX_DIR, "src/renderer_**.mm"),
			}

		configuration {}

		excludes {
			path.join(BGFX_DIR, "src/amalgamated.**"),
		}
	end

	if filesexist(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-gnm"), {
		path.join(BGFX_DIR, "scripts/bgfx.lua"), }) then

		dofile(path.join(BGFX_DIR, "../bgfx-gnm/scripts/bgfx.lua") )
	end

	if filesexist(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-nvn"), {
		path.join(BGFX_DIR, "scripts/bgfx.lua"), }) then

		dofile(path.join(BGFX_DIR, "../bgfx-nvn/scripts/bgfx.lua") )
	end

	configuration {}
end

function bgfxProject(_name, _kind, _defines)

	project ("bgfx" .. _name)
		uuid (os.uuid("bgfx" .. _name))

		bgfxProjectBase(_kind, _defines)

		copyLib()
end
