/*
 * @Author: Jimn
 * @Date: 2025-12-23 20:15:41
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-12-26 10:01:18
 * @FilePath: /Make-Code-Easier/files/C++解析Yaml文件/src/parse_yaml.cpp
 * @Description: 解析yaml文件 源代码
 */
#include "parse_yaml.hpp"

OUT ErrorCode Jimn_Jhn::parse_yaml(IN const std::string& yaml_file) {
    cv::FileStorage fs(yaml_file, cv::FileStorage::READ);
    if (!fs.isOpened())
    {
        PRINT_INFO("File Open Fail!!!");
        return ErrorCode::FILEOPENFAILED;
    }else{
        if (fs.getFormat() == cv::FileStorage::FORMAT_YAML){
            // 获取Yaml的根节点
            const cv::FileNode& root = fs.root();
            yaml_structure_use_map(root);
            fs.release();
            return ErrorCode::SUCCESS;
        }else{
            PRINT_INFO("Open File Format is not Yaml");
            fs.release();
            return ErrorCode::FILEFORMATERROR;
        }
    }
}

OUT void Jimn_Jhn::yaml_structure_use_map(IN const cv::FileNode& root) {
    std::queue<cv::FileNode> nodes_queue;
    for (const auto &node : root)
    {
        PRINT_INFO("node name: %s", node.name().c_str());
        PRINT_INFO("is string %d", node.isString());
        PRINT_INFO("is Map %d", node.isMap());
        nodes_queue.emplace(node);
    }
    return;
}

OUT ErrorCode Jimn_Jhn::generate_yaml(IN const cv::FileNode& root, IN const JString& out_file, IN const std::vector<JString>& keys) {
    cv::FileStorage fs(out_file, cv::FileStorage::WRITE);
    if (!fs.isOpened())
    {
        PRINT_INFO("out file open failed!!!");
        return ErrorCode::FILEOPENFAILED;
    }
    // 写信息到输出文件
    for (const auto &node : root){
        cv::FileNode cur_node = node;
        while (cur_node.isMap())
        {
            JString name = cur_node.name();
        }
    }
    
}
