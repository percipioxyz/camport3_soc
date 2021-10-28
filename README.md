# 目录结构

sample_raw/RawFetchFrame: 示例代码
sample_raw/include:       依赖的头文件
sample_raw/lib:           依赖的动态库 
toolchain:                交叉编译工具链 （单独下载)
ThirdPartyLib             第三方库依赖,opencv等




# 编译步骤

运行 ` ./build.sh `
sample_raw/RawFetchFrame/build/bin/中产生bin文件

编译依赖opencv的程序:
运行 ` ./build.sh opencv`

