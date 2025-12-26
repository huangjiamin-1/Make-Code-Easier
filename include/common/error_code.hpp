/*
 * @Author: Jimn
 * @Date: 2025-12-25 19:59:14
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-12-25 20:16:35
 * @FilePath: /Make-Code-Easier/include/common/error_code.hpp
 * @Description: 错误编码
 */
#pragma once

enum class ErrorCode{
    FILEOPENFAILED = -1,
    SUCCESS = 0,

    FILEFORMATERROR = 100, // File format error
};