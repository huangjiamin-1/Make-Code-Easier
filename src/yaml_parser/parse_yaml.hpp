/*
 * @Author: Jimn
 * @Date: 2025-12-23 20:12:52
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-12-26 09:56:49
 * @FilePath: /Make-Code-Easier/files/C++解析Yaml文件/src/parse_yaml.hpp
 * @Description: 解析yaml文件
 */
#pragma once
#include "common/common.hpp"
#include "common/error_code.hpp"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

namespace Jimn_Jhn{  
    namespace Process_Yaml{
        enum class FileNodeTYPE{
            INT = 0,
            FLOAT,
            STR,
            MAT,
            MAP,
        };

        /// @brief cv::FileNode结构转为map结构的结构体
        struct FileNode2Map
        {
            JString _node_name = "";
            FileNodeTYPE _type;
            float _fdata;
            JString _sdata;
            int _idata;
            cv::Mat _mat;
            std::vector<FileNode2Map> _map;
        };

        /// @brief 判断是否是Opencv特有的结构，cv::Mat的结构是特殊的FileNode::Map
        /// @param node 节点
        /// @return 1 是cv::Mat 0 不是cv::Mat,只是Map
        OUT bool is_opencv_mat(IN const cv::FileNode node);

        /// @brief 拷贝Yaml文件 推荐使用write_FileNode2Map_to_YamlFile函数
        /// @param file_name 要拷贝的文件名
        /// @param out_file 输出的文件名
        /// @return 0 SUCCESS Other Faliure ErrorCode
        OUT ErrorCode copy_yaml(IN const JString& file_name, OUT const JString& out_file);
        
        /// @brief 递归解析 cv::FileNode 到 FileNode2Map
        /// @param node 输入的 OpenCV 文件节点
        /// @param node_name 节点名称
        /// @param out_map 输出的自定义 FileNode2Map 结构体
        /// @return 
        OUT void parse_FileNode_to_FileNode2Map(IN const cv::FileNode& node, IN const JString& node_name, OUT FileNode2Map& out_map);

        /// @brief 对外封装的接口，用户可以将yaml文件传入产生对应的FileNode2Map结构数据
        /// @param yaml_path 文件路径
        /// @return 封装的Map结构体
        OUT FileNode2Map parse_Yaml_to_FileNode2Map(IN const JString& yaml_path);

        /// @brief 通过递归实现文件的写出，类似copy_yaml使用队列实现了文件的copy
        /// @param in_map 处理封装的数据结构
        /// @param fs Yaml数据处理流
        /// @return void
        OUT void write_FileNode2Map_to_Yaml(IN const FileNode2Map& in_map, IN cv::FileStorage& fs);

        /// @brief 对外封装的接口，用户可以通过该接口将原结构数据或者修改后的数据写入到指定Yaml文件
        /// @param in_map 源文件或修改后的文件
        /// @param yaml_path 输出文件路径
        /// @return 1 SUCCESS 0 FAILEID
        OUT ErrorCode write_FileNode2Map_to_YamlFile(IN const FileNode2Map& in_map, IN const std::string& yaml_path);
 
        /// @brief 查找修改的节点，然后传出该节点，进行数据修改
        /// @param in_map 由parse_Yaml_to_FileNode2Map函数解析产生的数据结构
        /// @param keys 对应key的字符串节点，支持单节点递归查找
        /// @param level 当前递归深度
        /// @return 查找到的节点，没有找到会抛出异常
        OUT FileNode2Map& find_and_rewrite_kv(IN FileNode2Map& in_map, IN const std::vector<JString>& keys, IN int level=0);
    };
};