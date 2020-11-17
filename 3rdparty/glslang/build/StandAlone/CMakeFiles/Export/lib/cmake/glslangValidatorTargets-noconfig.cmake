#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "glslangValidator" for configuration ""
set_property(TARGET glslangValidator APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(glslangValidator PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/glslangValidator"
  )

list(APPEND _IMPORT_CHECK_TARGETS glslangValidator )
list(APPEND _IMPORT_CHECK_FILES_FOR_glslangValidator "${_IMPORT_PREFIX}/bin/glslangValidator" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
