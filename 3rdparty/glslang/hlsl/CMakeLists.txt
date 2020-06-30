
# The HLSL source is directly embedded into the glslang target when ENABLE_HLSL
# is set.
# This source now lives at: glslang/HLSL/
# The HLSL target is now just a stub that exists for backwards compatibility for
# projects that referenced this target.

add_library(HLSL ${LIB_TYPE} "stub.cpp")
set_property(TARGET HLSL PROPERTY FOLDER hlsl)
set_property(TARGET HLSL PROPERTY POSITION_INDEPENDENT_CODE ON)

if(WIN32 AND BUILD_SHARED_LIBS)
    set_target_properties(HLSL PROPERTIES PREFIX "")
endif()

if(ENABLE_GLSLANG_INSTALL)
    if(BUILD_SHARED_LIBS)
        install(TARGETS HLSL EXPORT HLSLTargets
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
    else()
        install(TARGETS HLSL EXPORT HLSLTargets
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
    endif()
	install(EXPORT HLSLTargets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)
endif(ENABLE_GLSLANG_INSTALL)
