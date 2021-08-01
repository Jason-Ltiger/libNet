cmake_minimum_required(VERSION 2.5)
project(libNet)

#编译成动态库so，设置输出动态库的路径，放在根目录lib文件夹下
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
#设置调试信息，启动C++11语言标准
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -std=c++11")


aux_source_directory(. SRC_LIST)
#生成动态库
add_library(libNet SHARED ${SRC_LIST})