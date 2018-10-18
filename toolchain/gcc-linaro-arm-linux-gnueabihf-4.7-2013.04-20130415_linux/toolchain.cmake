STRING(REGEX REPLACE "(.*)/.*" "\\1" CUR_TOOLCHAIN_ROOT_PATH "${CMAKE_TOOLCHAIN_FILE}")
# message(STATUS ">>>>>>>>>>>>> CUR_TOOLCHAIN_ROOT_PATH = ${CUR_TOOLCHAIN_ROOT_PATH}")
if(NOT CUR_TOOLCHAIN_ROOT_PATH MATCHES "^/")
    set(TOOLCHAIN_ROOT_PATH ${CMAKE_BINARY_DIR}/${CUR_TOOLCHAIN_ROOT_PATH})
else()
    set(TOOLCHAIN_ROOT_PATH ${CUR_TOOLCHAIN_ROOT_PATH})
endif()
message(STATUS ">>>>>>>>>>>>> TOOLCHAIN_ROOT_PATH = ${TOOLCHAIN_ROOT_PATH}")

if(CMAKE_INSTALL_PREFIX)
else()
    set(CMAKE_INSTALL_PREFIX ${TOOLCHAIN_ROOT_PATH}/target/usr/local CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
endif()
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

set(CMAKE_TOOLCHAIN_PREFIX arm-linux-gnueabihf- CACHE PATH "Toolchain prefix in cross compiling." FORCE)

# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   ${TOOLCHAIN_ROOT_PATH}/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_ROOT_PATH}/bin/arm-linux-gnueabihf-g++)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  ${TOOLCHAIN_ROOT_PATH}/target)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
