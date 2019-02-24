#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MinGfx::MinGfx" for configuration "Debug"
set_property(TARGET MinGfx::MinGfx APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MinGfx::MinGfx PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/MinGfx-1.0/libMinGfxd.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MinGfx::MinGfx )
list(APPEND _IMPORT_CHECK_FILES_FOR_MinGfx::MinGfx "${_IMPORT_PREFIX}/lib/MinGfx-1.0/libMinGfxd.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
