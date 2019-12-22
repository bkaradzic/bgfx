cmake_minimum_required(VERSION 3.0)

if (CMAKE_VERSION VERSION_GREATER 3.15 OR CMAKE_VERSION VERSION_EQUAL 3.15)
    cmake_policy(SET CMP0091 NEW) # Enables use of MSVC_RUNTIME_LIBRARY
    cmake_policy(SET CMP0092 NEW) # Enables clean /W4 override for MSVC
endif()

project(meshoptimizer VERSION 0.13 LANGUAGES CXX)

option(MESHOPT_BUILD_DEMO "Build demo" OFF)
option(MESHOPT_BUILD_TOOLS "Build tools" OFF)
option(MESHOPT_BUILD_SHARED_LIBS "Build shared libraries" OFF)
set(MESHOPT_BUILD_TOOLS_GLFW_FOLDER_NAME "" CACHE STRING "Custom folder to look for GLFW")

set(SOURCES
    src/meshoptimizer.h
    src/allocator.cpp
    src/clusterizer.cpp
    src/indexcodec.cpp
    src/indexgenerator.cpp
    src/overdrawanalyzer.cpp
    src/overdrawoptimizer.cpp
    src/simplifier.cpp
    src/spatialorder.cpp
    src/stripifier.cpp
    src/vcacheanalyzer.cpp
    src/vcacheoptimizer.cpp
    src/vertexcodec.cpp
    src/vfetchanalyzer.cpp
    src/vfetchoptimizer.cpp
)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wshadow -Wno-missing-field-initializers -Werror)
endif()

add_library(meshoptimizer ${SOURCES})
target_include_directories(meshoptimizer INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")

if(MESHOPT_BUILD_SHARED_LIBS)
    set_target_properties(meshoptimizer PROPERTIES CXX_VISIBILITY_PRESET hidden)
    set_target_properties(meshoptimizer PROPERTIES VISIBILITY_INLINES_HIDDEN ON)

    if(WIN32)
        target_compile_definitions(meshoptimizer INTERFACE "MESHOPTIMIZER_API=__declspec(dllimport)")
        target_compile_definitions(meshoptimizer PRIVATE "MESHOPTIMIZER_API=__declspec(dllexport)")
    else()
        target_compile_definitions(meshoptimizer PUBLIC "MESHOPTIMIZER_API=__attribute__((visibility(\"default\")))")
    endif()
endif()

set(TARGETS meshoptimizer)

if(MESHOPT_BUILD_DEMO)
    add_executable(demo demo/main.cpp demo/miniz.cpp demo/tests.cpp tools/meshloader.cpp)
    target_link_libraries(demo meshoptimizer)
endif()

if(MESHOPT_BUILD_TOOLS)
    add_executable(gltfpack tools/gltfpack.cpp tools/meshloader.cpp tools/basistoktx.cpp)
    target_link_libraries(gltfpack meshoptimizer)
    list(APPEND TARGETS gltfpack)

    if(MESHOPT_BUILD_SHARED_LIBS)
        string(CONCAT RPATH "$ORIGIN/../" ${CMAKE_INSTALL_LIBDIR})
        set_target_properties(gltfpack PROPERTIES INSTALL_RPATH ${RPATH})
    endif()

    if(NOT (MESHOPT_BUILD_TOOLS_GLFW_FOLDER_NAME STREQUAL ""))
        message(STATUS "Using GLFW3 from: ${MESHOPT_BUILD_TOOLS_GLFW_FOLDER_NAME}")
        set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
        set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
        set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
        set(GLFW_INSTALL OFF CACHE BOOL "")
        add_subdirectory(${MESHOPT_BUILD_TOOLS_GLFW_FOLDER_NAME})
        set(glfw3_FOUND TRUE)
        set(glfw3_LIBRARY glfw)
    else()
        find_package(glfw3 3.3 QUIET)
    endif()

    if (glfw3_FOUND)
        add_executable(lodviewer tools/lodviewer.cpp tools/meshloader.cpp)
        target_link_libraries(lodviewer ${glfw3_LIBRARY} meshoptimizer)
    endif()
endif()

include(GNUInstallDirs)

install(TARGETS ${TARGETS} EXPORT meshoptimizerTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES src/meshoptimizer.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT meshoptimizerTargets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/meshoptimizer NAMESPACE meshoptimizer::)

# TARGET_PDB_FILE is available since 3.1
if(MSVC AND NOT (CMAKE_VERSION VERSION_LESS "3.1"))
    foreach(TARGET ${TARGETS})
        get_target_property(TARGET_TYPE ${TARGET} TYPE)
        if(NOT ${TARGET_TYPE} STREQUAL "STATIC_LIBRARY")
            install(FILES $<TARGET_PDB_FILE:${TARGET}> DESTINATION ${CMAKE_INSTALL_BINDIR} OPTIONAL)
        endif()
    endforeach(TARGET)
endif()

include(CMakePackageConfigHelpers)

configure_package_config_file(config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/meshoptimizerConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/meshoptimizer NO_SET_AND_CHECK_MACRO)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/meshoptimizerConfigVersion.cmake COMPATIBILITY ExactVersion)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/meshoptimizerConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/meshoptimizerConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/meshoptimizer)
