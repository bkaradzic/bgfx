cmake_minimum_required(VERSION 2.8.11)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(ENABLE_AMD_EXTENSIONS "Enables support of AMD-specific extensions" ON)
option(ENABLE_GLSLANG_BINARIES "Builds glslangValidator and spirv-remap" ON)

option(ENABLE_NV_EXTENSIONS "Enables support of Nvidia-specific extensions" ON)

option(ENABLE_HLSL "Enables HLSL input support" ON)

enable_testing()

set(CMAKE_INSTALL_PREFIX "install" CACHE STRING "prefix")

project(glslang)

if(ENABLE_AMD_EXTENSIONS)
    add_definitions(-DAMD_EXTENSIONS)
endif(ENABLE_AMD_EXTENSIONS)

if(ENABLE_NV_EXTENSIONS)
    add_definitions(-DNV_EXTENSIONS)
endif(ENABLE_NV_EXTENSIONS)

if(ENABLE_HLSL)
    add_definitions(-DENABLE_HLSL)
endif(ENABLE_HLSL)

if(WIN32)
    set(CMAKE_DEBUG_POSTFIX "d")
    if(MSVC)
        include(ChooseMSVCCRT.cmake)
    endif(MSVC)
    add_definitions(-DGLSLANG_OSINCLUDE_WIN32)
elseif(UNIX)
    add_definitions(-fPIC)
    add_definitions(-DGLSLANG_OSINCLUDE_UNIX)
else(WIN32)
    message("unknown platform")
endif(WIN32)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -Wmaybe-uninitialized -Wuninitialized -Wunused -Wunused-local-typedefs
      -Wunused-parameter -Wunused-value  -Wunused-variable -Wunused-but-set-parameter -Wunused-but-set-variable)
    add_definitions(-Wno-reorder)  # disable this from -Wall, since it happens all over.
    add_definitions(-std=c++11)
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
    add_definitions(-Wall -Wuninitialized -Wunused -Wunused-local-typedefs
      -Wunused-parameter -Wunused-value  -Wunused-variable)
    add_definitions(-Wno-reorder)  # disable this from -Wall, since it happens all over.
    add_definitions(-std=c++11)
endif()

function(glslang_set_link_args TARGET)
    # For MinGW compiles, statically link against the GCC and C++ runtimes.
    # This avoids the need to ship those runtimes as DLLs.
    if(WIN32)
	if(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
	    set_target_properties(${TARGET} PROPERTIES
		    LINK_FLAGS "-static -static-libgcc -static-libstdc++")
        endif()
    endif(WIN32)
endfunction(glslang_set_link_args)

# We depend on these for later projects, so they should come first.
add_subdirectory(External)

add_subdirectory(glslang)
add_subdirectory(OGLCompilersDLL)
if(ENABLE_GLSLANG_BINARIES)
	add_subdirectory(StandAlone)
endif()
add_subdirectory(SPIRV)
if(ENABLE_HLSL)
    add_subdirectory(hlsl)
endif(ENABLE_HLSL)
add_subdirectory(gtests)
