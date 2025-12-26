/*
 * @Author: Jimn
 * @Date: 2025-12-23 19:05:58
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-12-25 19:50:21
 * @FilePath: /Make-Code-Easier/common/common.hpp
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

using INT32 = int;
using JString = std::string;

/**************************🚀FUN!!!!!!!!🚀**************************/

/*添加换行的打印，原理:[C标准规定]相邻的字符串字面量会被编译器自动拼接成一个完整的字符串*/
#define PRINT_INFO(fmt, ...) printf(fmt "\n", ##__VA_ARGS__)