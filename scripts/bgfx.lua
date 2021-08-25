--
-- Copyright 2010-2021 Branimir Karadzic. All rights reserved.
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
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
	}

	defines (_defines)

	links {
		"bx",
	}

	if _OPTIONS["with-glfw"] then
		defines {
			"BGFX_CONFIG_MULTITHREADED=0",
		}
	end

	configuration { "Debug" }
		defines {
			"BGFX_CONFIG_DEBUG=1",
		}

	configuration { "vs* or mingw*", "not durango" }
		includedirs {
			path.join(BGFX_DIR, "3rdparty/dxsdk/include"),
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
			"-framework QuartzCore",
			"-framework OpenGL",
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

	if _OPTIONS["with-webgpu"] then
		defines {
			"BGFX_CONFIG_RENDERER_WEBGPU=1",
			"BGFX_CONFIG_DEBUG_ANNOTATION=0", -- does not work
		}

		local generator = "out/Cmake"

		configuration { "wasm*" }
			defines {
				"BGFX_CONFIG_RENDERER_OPENGL=0",
				"BGFX_CONFIG_RENDERER_OPENGLES=0",
			}

		configuration { "not wasm*" }
			includedirs {
				path.join(DAWN_DIR, "src/include"),
				path.join(DAWN_DIR, "third_party/vulkan-deps/vulkan-headers/src/include"),
				path.join(DAWN_DIR, generator, "gen/src/include"),
			}

			files {
				path.join(DAWN_DIR, generator, "gen/src/dawn/webgpu_cpp.cpp"),
			}
		configuration { "vs*" }
			defines {
				"NTDDI_VERSION=NTDDI_WIN10_RS2",

				-- We can't say `=_WIN32_WINNT_WIN10` here because some files do
				-- `#if WINVER < 0x0600` without including windows.h before,
				-- and then _WIN32_WINNT_WIN10 isn't yet known to be 0x0A00.
				"_WIN32_WINNT=0x0A00",
				"WINVER=0x0A00",
			}

		configuration {}
    end

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
				path.join(BGFX_DIR, "src/glcontext_**.mm"),
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
				path.join(BGFX_DIR, "src/glcontext_**.mm"),
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

if _OPTIONS["with-webgpu"] then
	function usesWebGPU()
		configuration { "wasm*" }
			linkoptions {
				"-s USE_WEBGPU=1",
			}

		configuration { "not wasm*" }
			local generator = "out/Cmake"

			includedirs {
				path.join(DAWN_DIR, "src/include"),
				path.join(DAWN_DIR, generator, "gen/src/include"),
			}

			libdirs {
				path.join(DAWN_DIR, generator),
				path.join(DAWN_DIR, generator, "src/common/Debug"),
				path.join(DAWN_DIR, generator, "src/dawn/Debug"),
				path.join(DAWN_DIR, generator, "src/dawn_native/Debug"),
				path.join(DAWN_DIR, generator, "src/dawn_platform/Debug"),
				path.join(DAWN_DIR, generator, "third_party/tint/src/Debug"),
				path.join(DAWN_DIR, generator, "third_party/vulkan-deps/spirv-tools/src/source/Debug"),
				path.join(DAWN_DIR, generator, "third_party/vulkan-deps/spirv-tools/src/source/opt/Debug"),
				path.join(DAWN_DIR, generator, "third_party/vulkan-deps/spirv-cross/src/Debug"),
			}

			links {
				-- shared
				--"dawn_proc_shared",
				--"dawn_native_shared",
				--"shaderc_spvc_shared",
				-- static
				"dawn_common",
				"dawn_proc",
				"dawn_native",
				"dawn_platform",
				----"shaderc",
				"tint",
				"SPIRV-Tools",
				"SPIRV-Tools-opt",
				"spirv-cross-cored",
				"spirv-cross-hlsld",
				"spirv-cross-glsld",
				"spirv-cross-msld",
				--"spirv-cross-reflectd",
			}

			removeflags {
				"FatalWarnings",
			}

		configuration {}
	end
end
