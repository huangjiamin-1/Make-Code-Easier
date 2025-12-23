cmake_minimum_required(VERSION 3.16.0)
project(YAML_PARSE VERSION 1.0.0 DESCRIPTION "使用Opencv解析Yaml文件")

set(EXPORT_COMPILE_COMMANDS ON)
PRINT(${PROJECT_DESCRIPTION})

find_package(OpenCV)
PRINT(${OpenCV_INCLUDE_DIRS})
PRINT(${OpenCV_LIBRARIES})

set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
add_library(parse_yaml STATIC ${SRC})
target_include_directories(parse_yaml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

