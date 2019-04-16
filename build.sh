#!/bin/bash

CURRENT_PATH=`pwd`
#TOOLCHAIN_PATH=/home/vincent/Downloads/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux.bak
TOOLCHAIN_PATH=${CURRENT_PATH}/toolchain/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux

echo "========= Current path is"   ${CURRENT_PATH}
echo "========= Toolchain path is" ${TOOLCHAIN_PATH}

cd ${CURRENT_PATH}/sample
rm -rf build 
mkdir build
cd build

#for code which using opencv
#cmake -DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_PATH}/toolchain.cmake -DOpenCV_DIR=${TOOLCHAIN_PATH}/arm-linux-gnueabihf/share/OpenCV -DOpenCV_CONFIG_PATH=${TOOLCHAIN_PATH}/arm-linux-gnueabihf/share/OpenCV ..

cmake -DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_PATH}/toolchain.cmake ..

make

