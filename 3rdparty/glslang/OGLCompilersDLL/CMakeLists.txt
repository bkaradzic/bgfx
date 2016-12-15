set(SOURCES InitializeDll.cpp InitializeDll.h)

add_library(OGLCompiler STATIC ${SOURCES})
set_property(TARGET OGLCompiler PROPERTY FOLDER glslang)

if(WIN32)
    source_group("Source" FILES ${SOURCES})
endif(WIN32)

install(TARGETS OGLCompiler 
        ARCHIVE DESTINATION lib)
