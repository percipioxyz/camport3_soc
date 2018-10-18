#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Percipio::Foundation" for configuration "Release"
set_property(TARGET Percipio::Foundation APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Percipio::Foundation PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/slib/libPercipioFoundation.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Percipio::Foundation )
list(APPEND _IMPORT_CHECK_FILES_FOR_Percipio::Foundation "${_IMPORT_PREFIX}/slib/libPercipioFoundation.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
