#!/bin/bash

CURRENT_PATH=`pwd`
#TOOLCHAIN_PATH=/home/vincent/Downloads/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux.bak
TOOLCHAIN_PATH=${CURRENT_PATH}/toolchain/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux

echo "========= Current path is"   ${CURRENT_PATH}
echo "========= Toolchain path is" ${TOOLCHAIN_PATH}

cd ${CURRENT_PATH}/Sample
rm -rf build 
mkdir build
cd build

#for code which using opencv
if [[ $1 == "opencv" ]]; then
cmake -DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_PATH}/toolchain.cmake -DOPENCV_USED=true -DOpenCV_DIR=${TOOLCHAIN_PATH}/../../ThirdPartyLib/Opencv-3.4/share/OpenCV -DOpenCV_CONFIG_PATH=${TOOLCHAIN_PATH}/../../ThirdPartyLib/Opencv-3.4/share/OpenCV ..
fi

cmake -DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_PATH}/toolchain.cmake ..

make

