cmake_minimum_required(VERSION 3.16.0)
project(YAML_PARSE VERSION 1.0.0 DESCRIPTION "使用Opencv解析Yaml文件")

set(EXPORT_COMPILE_COMMANDS ON)
PRINT(${PROJECT_DESCRIPTION})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
add_library(parse_yaml STATIC ${SRC})
target_include_directories(parse_yaml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(parse_yaml PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(parse_yaml PUBLIC ${OpenCV_LIBRARIES})
# set_target_properties(parse_yaml PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}) 

