cmake_minimum_required(VERSION 3.16.0)
set(EXPORT_COMPILE_COMMANDS ON)
project(Make_Code_Easier VERSION 1.0.0 DESCRIPTION "make life happy Jimn&Jhn!!!")

# -------------------------- 🚀 全局基础配置 --------------------------
# C++ STANDARD
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译模式(自用默认Debug，方便调试；发布时改Release)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    message(WARNING "build type: ${CMAKE_BUILD_TYPE}") # "" 字符串插值(变量展开)特性(自动解析${}占位符中内容) ''原生字符串
endif()

# 统一输出路径(所有库放在build/lib，可执行文件放build/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # 可执行文件
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # 静态库
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # 动态库

message(STATUS "🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀")
# the main file for all projects，global header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# find 3rd libraries
find_package(OpenCV)

# -------------------------- 🚀 编译核心模块 + 测试 --------------------------
add_subdirectory(src)
add_subdirectory(test)
message(STATUS "🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀")
