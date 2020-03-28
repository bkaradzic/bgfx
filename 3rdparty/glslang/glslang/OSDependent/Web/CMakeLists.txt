if(ENABLE_GLSLANG_JS)
    add_executable(glslang.js "glslang.js.cpp")
    glslang_set_link_args(glslang.js)
    target_link_libraries(glslang.js glslang SPIRV)

    # Link library names that start with "-" are treated as link flags.
    # "-Os" should be OK in MSVC; don't use /Os because CMake won't
    # treat it as a link flag.
    target_link_libraries(glslang.js "-Os")

    if(EMSCRIPTEN)
        set_target_properties(glslang.js PROPERTIES
            OUTPUT_NAME "glslang"
            SUFFIX ".js")
        em_link_pre_js(glslang.js "${CMAKE_CURRENT_SOURCE_DIR}/glslang.pre.js")

        target_link_libraries(glslang.js "--llvm-lto 1")
        target_link_libraries(glslang.js "--closure 1")
        target_link_libraries(glslang.js "-s MODULARIZE=1")
        target_link_libraries(glslang.js "-s ALLOW_MEMORY_GROWTH=1")
        target_link_libraries(glslang.js "-s FILESYSTEM=0")

        if(ENABLE_EMSCRIPTEN_SINGLE_FILE)
            target_link_libraries(glslang.js "-s SINGLE_FILE=1")
        endif(ENABLE_EMSCRIPTEN_SINGLE_FILE)

        if(ENABLE_EMSCRIPTEN_ENVIRONMENT_NODE)
            target_link_libraries(glslang.js "-s ENVIRONMENT=node -s BINARYEN_ASYNC_COMPILATION=0")
        else()
            target_link_libraries(glslang.js "-s ENVIRONMENT=web,worker")
        endif()

        if(NOT ENABLE_EMSCRIPTEN_ENVIRONMENT_NODE)
            add_custom_command(TARGET glslang.js POST_BUILD
                COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/glslang.after.js >> ${CMAKE_CURRENT_BINARY_DIR}/glslang.js)
        endif()
    endif(EMSCRIPTEN)
endif(ENABLE_GLSLANG_JS)
