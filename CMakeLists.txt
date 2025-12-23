cmake_minimum_required(VERSION 3.16.0)
project(Make_Code_Easier VERSION 1.0.0 DESCRIPTION "make life happy Jimn&Jhn!!!")

# -------------------------- 🚀 全局基础配置 --------------------------
# C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译模式（自用默认Debug，方便调试；发布时改Release）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    message(WARNING "build type: ${CMAKE_BUILD_TYPE}") # "" 字符串插值(变量展开)特性(自动解析${}占位符中内容) ''原生字符串
endif()

message(STATUS "🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀")
# the main file for all projects
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/common)

add_subdirectory(src)
add_subdirectory(test)
message(STATUS "🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀🚀")
