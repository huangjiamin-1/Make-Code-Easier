/*
 * @Author: Jimn
 * @Date: 2025-12-23 18:40:54
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-12-25 21:13:09
 * @FilePath: /C++解析Yaml文件/main.cpp
 * @Description: 使用C++解析Yaml文件
 */
#include <iostream>
#include "common/common.hpp"
#include "parse_yaml.hpp"

int main(IN int argc, IN char *argv[]) 
{
    JString file_path = "/media/mj/44367E9F88E0AE11/Jimn/Make-Code-Easier/config/cam0_pinhole.yaml";
    ErrorCode ret = Jimn_Jhn::parse_yaml(file_path);
    PRINT_INFO("ret value %d", (int)ret);
    return 0;
}