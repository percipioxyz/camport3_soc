#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Percipio::Net" for configuration "Release"
set_property(TARGET Percipio::Net APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Percipio::Net PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/slib/libPercipioNet.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Percipio::Net )
list(APPEND _IMPORT_CHECK_FILES_FOR_Percipio::Net "${_IMPORT_PREFIX}/slib/libPercipioNet.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
