#!/bin/bash

CURRENT_PATH=`pwd`
TOOLCHAIN_PATH=${CURRENT_PATH}/toolchain/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux

echo "========= Current path is"   ${CURRENT_PATH}
echo "========= Toolchain path is" ${TOOLCHAIN_PATH}

if [ ! -d "$TOOLCHAIN_PATH" ]; then
    echo " ERROR: Toolchain not exist. please download and unzip toolchain pack in correct path"
    exit 1
fi

cd ${CURRENT_PATH}/Sample
rm -rf build 
mkdir build
cd build

#for code which using opencv
if [[ $1 == "opencv" ]]; then
    OPENCV_PATH=$CURRENT_PATH/ThirdPartyLib/Opencv-3.4/share/OpenCV
    if [ ! -d "${OPENCV_PATH}" ];  then
        echo "ERROR:Opencv3.4 path not exists : ${OPENCV_PATH} ,\n Please download or compiling from source code."
        exit 1
    fi
    cmake -DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_PATH}/toolchain.cmake \
        -DOPENCV_USED=true  -DOpenCV_DIR=${OPENCV_PATH} \
        -DOpenCV_CONFIG_PATH=${OPENCV_PATH} ..
fi

cmake -DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_PATH}/toolchain.cmake ..

make

