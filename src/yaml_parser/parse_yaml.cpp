/*
 * @Author: Jimn
 * @Date: 2025-12-23 20:15:41
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-12-26 10:01:18
 * @FilePath: /Make-Code-Easier/files/C++解析Yaml文件/src/parse_yaml.cpp
 * @Description: 解析yaml文件 源代码
 */
#include "parse_yaml.hpp"

OUT ErrorCode Jimn_Jhn::parse_yaml(IN const JString& yaml_file, IN const JString& out_file, IN const std::vector<JString>& keys) {
    cv::FileStorage fs(yaml_file, cv::FileStorage::READ);
    if (!fs.isOpened())
    {
        PRINT_ERROR("File Open Fail!!!, %d", __LINE__);
        return ErrorCode::FILEOPENFAILED;
    }else{
        if (fs.getFormat() == cv::FileStorage::FORMAT_YAML){
            // 获取Yaml的根节点
            const cv::FileNode& root = fs.root();
            
            fs.release();
            return ErrorCode::SUCCESS;
        }else{
            PRINT_ERROR("Open File Format is not Yaml!!!, %d", __LINE__);
            fs.release();
            return ErrorCode::FILEFORMATERROR;
        }
    }
}



OUT ErrorCode Jimn_Jhn::generate_yaml(IN const cv::FileNode& root, IN const JString& out_file, IN const std::vector<JString>& keys) {
    cv::FileStorage fs(out_file, cv::FileStorage::WRITE);
    if (!fs.isOpened())
    {
        PRINT_ERROR("File Open Fail!!!, %d", __LINE__);
        return ErrorCode::FILEOPENFAILED;
    }
    // 写信息到输出文件
    // for (const auto &node : root){
    //     cv::FileNode cur_node = node;
    //     while (cur_node.isMap())
    //     {
    //         JString name = cur_node.name();
            
    //     }
    // }
    for (const auto &node : root)
    {
        PRINT_INFO("node name: %s", node.name().c_str());
        PRINT_INFO("is string %d", node.isString());
        PRINT_INFO("is Map %d", node.isMap());
        if (node.isString())
        {
            JString val;
            node >> val;
            fs.write(node.name(), val);
        }
        
    }

    return ErrorCode::SUCCESS;
    
}

OUT static bool is_levaf_node(IN const cv::FileNode& node, IN cv::FileStorage& out){
    JString node_name = node.name();
    if (node.isInt())
    {
        INT32 data = 0;
        node >> data; // 读取原始数据
        out << node_name << data;
    }else if (node.isString())
    {
        JString str = "";
        node >> str;
        out << node_name << str;
    }else if (node.isReal()){
        double data = 0.0;
        node >> data;
        out << node_name << data;
    }else if(Jimn_Jhn::is_opencv_mat(node)){
        cv::Mat data;
        node >> data;
        out << node_name << data;
    }else
        return false;
    return true;
}

OUT ErrorCode Jimn_Jhn::copy_yaml(IN const JString & file_name, OUT const JString& out_file)
{
    cv::FileStorage fs(file_name, cv::FileStorage::READ);
    if (!fs.isOpened())
    {
        PRINT_ERROR("File Open Fail!!!, %d", __LINE__);
        return ErrorCode::FILEOPENFAILED;
    }
    cv::FileStorage out(out_file, cv::FileStorage::WRITE);
    if (!out.isOpened())
    {
        PRINT_ERROR("File Open Fail!!!, %d", __LINE__);
        return ErrorCode::FILEOPENFAILED;
    }
    
    const cv::FileNode& root = fs.root();
    for (const auto& node: root)
    {
        JString node_name = node.name();
        if (is_levaf_node(node, out))
        {   
            ;
        }else{
            // 深度递归
            if (node.isMap())
            {
                out.startWriteStruct(node_name, cv::FileNode::MAP, "");
                std::deque<cv::FileNode> node_queue;
                std::deque<int> group_queue;
                int num = 0; // 记录属于哪个map, total自增
                for(const auto& name: node.keys()){
                    node_queue.push_back(node[name]);
                    group_queue.push_back(num);
                }
                num++;
                while (!node_queue.empty()) // 所有的key value
                {
                    cv::FileNode& first_node = node_queue.front();
                    node_queue.pop_front();
                    int node_id = group_queue.front(); // 当前的id
                    group_queue.pop_front();
                    if (!is_opencv_mat(first_node) && first_node.isMap()){
                        out.startWriteStruct(first_node.name(), cv::FileNode::MAP, "");
                        auto local_node_vector = first_node.keys();
                        for(int i = local_node_vector.size() - 1; i >= 0; i--){
                            node_queue.push_front(first_node[local_node_vector[i]]);
                            group_queue.push_back(num);
                        }
                        num++;
                    }else if (is_levaf_node(first_node, out))
                    {
                        if (!group_queue.empty() && node_id != group_queue.front())
                        {
                            out.endWriteStruct();
                        }
                    }
                }

                out.endWriteStruct();
            }
            
        }
    }
    out.release();
    fs.release();
    return OUT ErrorCode::SUCCESS;
}

/// @brief 用于判断是否是!!opencv-matrix格式
/// @param node 节点
/// @return 1 SUCCESS 0 FAILURE
OUT bool Jimn_Jhn::is_opencv_mat(IN const cv::FileNode node)
{
    if (node.isMap())
    {
        const auto& node_keys = node.keys();        
        if (node_keys.size() != 4) // cv::Mat矩阵形式是有4个键 rows, cols, dt, data
        {
            return false;
        }else{
            if (node_keys[0] == "rows" && node_keys[1] == "cols" &&\
                node_keys[2] == "dt" && node_keys[3] == "data")
            {
                return true;
            }else
                return false;
        }
    }
    return false;
}
