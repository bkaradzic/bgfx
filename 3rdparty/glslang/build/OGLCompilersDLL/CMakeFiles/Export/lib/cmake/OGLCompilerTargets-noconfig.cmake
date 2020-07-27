#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "OGLCompiler" for configuration ""
set_property(TARGET OGLCompiler APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(OGLCompiler PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libOGLCompiler.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS OGLCompiler )
list(APPEND _IMPORT_CHECK_FILES_FOR_OGLCompiler "${_IMPORT_PREFIX}/lib/libOGLCompiler.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
