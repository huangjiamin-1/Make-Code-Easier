/*
 * @Author: Jimn
 * @Date: 2025-12-30 13:58:27
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-12-30 14:44:34
 * @FilePath: /Make-Code-Easier/include/common/fargs.hpp
 * @Description: 命令行参数宏实现,这是一个学习命令行拼接令牌·##·模块，非必要不要使用
 */
#pragma once
#include "common.hpp"
#include <vector>

namespace Jimn_Jhn{
    namespace Flags{
        /**************************🚀Core Structure & Global Regist Table !!!!!!!🚀**************************/
        /* 
        * 单个参数的结构体：存储[参数名，参数值，帮助说明] 
        */
        struct JFLagItem
        {
            JString _flag_name; 
            JString* _flag_value;
            JString _help_text;   
        };

        /*
        * 全局参数注册表：所有通过宏定义的参数，都会自动加入这个容器
        */
        static std::vector<JFLagItem> g_flags_registry;

        // ===================== 2. 核心宏定义 =====================
        #define DEFINE_FLAGS_STRING(name, val, txt) \
            /* 定义全局变量 FLAGS_xxx，初始化赋值为默认值val，用户可直接访问/修改 */ \
            JString FLAGS_##name = (val); /* 使用令牌拼接运算符##，预处理器会把两个标识符拼接为一个新的标识符 s_##name[name = log_dir] => s_log_dir */ \
            /* 静态注册器：程序启动时自动将参数信息加入全局注册表 */ \
            static bool g_register_flag_##name = [](){ \
                JFLagItem item; \
                item._flag_name = #name; /* #: 把参数名转为字符串(e.g. Jimn->"Jimn") */ \
                item._flag_value = &FLAGS_##name; /* 绑定全局变量指针 */ \
                item._help_text = (txt);    /* 赋值帮助说明 */ \
                g_flags_registry.push_back(item); \
                return true; \ 
            }(); \
    };
};

using namespace Jimn_Jhn::Flags;

