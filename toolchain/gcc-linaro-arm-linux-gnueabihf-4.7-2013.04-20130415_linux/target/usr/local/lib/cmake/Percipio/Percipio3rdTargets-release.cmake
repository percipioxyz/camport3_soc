#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Percipio::3rd" for configuration "Release"
set_property(TARGET Percipio::3rd APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Percipio::3rd PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/slib/libPercipio3rd.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Percipio::3rd )
list(APPEND _IMPORT_CHECK_FILES_FOR_Percipio::3rd "${_IMPORT_PREFIX}/slib/libPercipio3rd.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
