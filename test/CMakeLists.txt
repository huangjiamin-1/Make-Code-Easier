PRINT("building test file")

function(create_exe NAME SRC LIBS)
    add_executable(${NAME} ${SRC})
    target_link_libraries(${NAME} PUBLIC ${LIBS})
endfunction()

set(LOCAL_PATH ${CMAKE_CURRENT_SOURCE_DIR})
create_exe(yaml ${LOCAL_PATH}/yaml_parser/main.cpp parse_yaml)