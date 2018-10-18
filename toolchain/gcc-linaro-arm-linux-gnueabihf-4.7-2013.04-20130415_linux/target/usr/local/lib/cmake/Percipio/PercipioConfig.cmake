# outputs:
#   Percipio_FOUND
#        

if (CMAKE_VERSION VERSION_LESS 2.8.9)
    message(FATAL_ERROR "Percipio requires at least CMake version 2.8.9")
endif()

if (NOT Percipio_FIND_COMPONENTS)
    message(FATAL_ERROR "The Percipio package requires at least one component")
    # set(Percipio_NOT_FOUND_MESSAGE "The Percipio package requires at least one component")
    set(Percipio_FOUND False)
    return()
endif()
# set(Percipio_FIND_QUIETLY TRUE)
# set(Percipio_FIND_COMPONENTS Foundation XML JSON Util Net Crypto NetSSL Data DataSQLite DataMySQL Zip MongoDB DepthProc 3rd)

set(_Percipio_FIND_PARTS_REQUIRED)
if (Percipio_FIND_REQUIRED)
    set(_Percipio_FIND_PARTS_REQUIRED REQUIRED)
endif()
set(_Percipio_FIND_PARTS_QUIET)
if (Percipio_FIND_QUIETLY)
    set(_Percipio_FIND_PARTS_QUIET QUIET)
endif()

get_filename_component(_Percipio_install_prefix "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)

set(_Percipio_NOTFOUND_MESSAGE)

# Let components find each other, but don't overwrite CMAKE_PREFIX_PATH
set(_Percipio_CMAKE_PREFIX_PATH_old ${CMAKE_PREFIX_PATH})
set(CMAKE_PREFIX_PATH ${_Percipio_install_prefix})

foreach(module ${Percipio_FIND_COMPONENTS})
    find_package(Percipio${module}
        ${_Percipio_FIND_PARTS_QUIET}
        ${_Percipio_FIND_PARTS_REQUIRED}
        PATHS "${_Percipio_install_prefix}" NO_DEFAULT_PATH
    )
    if (NOT Percipio${module}_FOUND)
        if (Percipio_FIND_REQUIRED_${module})
            set(_Percipio_NOTFOUND_MESSAGE "${_Percipio_NOTFOUND_MESSAGE}Failed to find Percipio component \"${module}\" config file at \"${_Percipio_install_prefix}/Percipio${module}/Percipio${module}Config.cmake\"\n")
        elseif(NOT Percipio_FIND_QUIETLY)
            message(WARNING "Failed to find Percipio component \"${module}\" config file at \"${_Percipio_install_prefix}/Percipio${module}/Percipio${module}Config.cmake\"")
        endif()
    else()
        # For backward compatibility set the LIBRARIES variable
        list(APPEND Percipio_LIBRARIES "Percipio::${module}")
    endif()
endforeach()

# Restore the original CMAKE_PREFIX_PATH value
set(CMAKE_PREFIX_PATH ${_Percipio_CMAKE_PREFIX_PATH_old})

if (_Percipio_NOTFOUND_MESSAGE)
    set(Percipio_NOT_FOUND_MESSAGE "${_Percipio_NOTFOUND_MESSAGE}")
    set(Percipio_FOUND False)
endif()

