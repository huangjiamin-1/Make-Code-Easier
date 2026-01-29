/*
 * @Author: Jimn
 * @Date: 2025-12-23 19:05:58
 * @LastEditors: Jimn
 * @LastEditTime: 2026-01-29 19:28:49
 * @FilePath: /Make-Code-Easier/include/common/common.hpp
 * @Description: 🚀通用文件
 */
#pragma once
/**************************🚀STL!!!!!!!🚀**************************/
#include <iostream>
#include <string>

/**************************🚀MARCO!!!!!!🚀**************************/

/*NULL MACRO DESCRIBE INPUT*/
#define IN
/*NULL MACRO DESCRIBE OUTPUT*/
#define OUT

#define TEST_OPEN_PRINT (true)

#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RESET   "\033[0m"

using INT32 = int;
using JString = std::string;


/**************************🚀FUN!!!!!!!!🚀**************************/

/*添加换行的打印，原理:[C标准规定]相邻的字符串字面量会被编译器自动拼接成一个完整的字符串*/
#if(TEST_OPEN_PRINT)
    #define PRINT_INFO(fmt, ...)  do{ \
        printf(COLOR_GREEN "[INFO][%s] " fmt COLOR_RESET "\n", \
              __func__, ##__VA_ARGS__); \
    }while(0)
    #define PRINT_WARN(fmt, ...)  do{ \
        printf(COLOR_YELLOW "[WARN][%s] " fmt COLOR_RESET "\n", \
               __func__, ##__VA_ARGS__); \
    }while(0)
#else 
    #define PRINT_INFO(fmt, ...)  do{}while(0) 
    #define PRINT_WARN(fmt, ...)  do{}while(0)
#endif 
#define PRINT_ERROR(fmt,...)  do{ \
    printf(COLOR_RED "[ERROR][%s] " fmt COLOR_RESET "\n", \
            __func__, ##__VA_ARGS__); \
}while(0)