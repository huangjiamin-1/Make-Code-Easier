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
    /// @brief 解析yaml文件，生成修改其中的值
    /// @param yaml_file 文件路径
    /// @return 是否成功
    OUT ErrorCode parse_yaml(IN const JString& yaml_file, IN const JString& out_file, IN const std::vector<JString>& keys);

    OUT ErrorCode generate_yaml(IN const cv::FileNode& root, IN const JString& out_file, IN const std::vector<JString>& keys);

    OUT ErrorCode copy_yaml(IN const JString& file_name, OUT const JString& out_file);

    OUT bool is_opencv_mat(IN const cv::FileNode node);
};