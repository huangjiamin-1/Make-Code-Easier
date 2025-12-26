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
    using namespace std;
    // JString file_path = "/media/mj/44367E9F88E0AE11/Jimn/Make-Code-Easier/config/cam0_pinhole.yaml";
    JString file_path = "D:/Jimn_Jhn/Files_in_Dahua/Make-Code-Easier/config/out.yaml";
    // 1. 读取包含该矩阵的 YAML 文件
    cv::FileStorage fs(file_path, cv::FileStorage::READ);
    if (!fs.isOpened()) {
        PRINT_INFO("文件打开失败！");
        return -1;
    }
    JString out_path = "D:/Jimn_Jhn/Files_in_Dahua/Make-Code-Easier/config/out.yaml";
    cv::FileStorage ou(out_path, cv::FileStorage::WRITE);
    
    cv::FileNode root = fs.root();
    for(auto iter = root.begin(); root.end() != iter; ++iter){
        if((*iter).isString()) {
            JString str = "";
            (*iter) >> str;
            cout << str << endl;
            ou.write((*iter).name(), str);
        }
    }

    ou.startWriteStruct("data", cv::FileNode::MAP, "opencv-matrix");  // 启动 SEQ 结构
    ou << "rows" << 4;          // 矩阵行数
    ou << "cols" << 4;          // 矩阵列数
    ou << "dt" << "d";          // 数据类型：double
    ou.startWriteStruct("p", cv::FileNode::MAP, "");
    ou << "hello" << 12;
    ou << "hallo" << 13;
    ou << "data" << cv::Matx33d::eye();
    ou.startWriteStruct("t", cv::FileNode::MAP, "");
    ou << "hello" << 12;
    ou << "hallo" << 13;
    ou.startWriteStruct("h", cv::FileNode::MAP, "");
    ou << "hello" << 12;
    ou << "hallo" << 13;
    ou << "data" << cv::Matx33d::eye();
    ou.endWriteStruct();
    ou.endWriteStruct();
    ou.endWriteStruct();
    ou.endWriteStruct();  // 结束 data 的 SEQ 结构
    
    ou.release();
    

    

    fs.release();
    out_path = "D:/Jimn_Jhn/Files_in_Dahua/Make-Code-Easier/config/out1.yaml";

    Jimn_Jhn::copy_yaml(file_path, out_path);
    return 0;
}