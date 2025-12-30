/*
 * @Author: Jimn
 * @Date: 2025-12-23 20:15:41
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-12-30 15:33:41
 * @FilePath: /Make-Code-Easier/files/C++解析Yaml文件/src/parse_yaml.cpp
 * @Description: 解析yaml文件 源代码
 */
#include "parse_yaml.hpp"

namespace Jimn_Jhn{
    namespace Process_Yaml{
        OUT bool is_opencv_mat(IN const cv::FileNode node)
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

        /// @brief 检查该节点是否是叶子节点，如果是则直接写入到Yaml文件中[目前支持的类型有str,int,float,cv::Mat]
        /// @param node 节点 cv::FileNode
        /// @param out 输出文档
        /// @return 1 SUCCESS 0 FAILURE
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
            }else if(is_opencv_mat(node)){
                cv::Mat data;
                node >> data;
                out << node_name << data;
            }else
                return false;
            return true;
        }

        OUT ErrorCode copy_yaml(IN const JString & file_name, OUT const JString& out_file)
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
                                out.startWriteStruct(first_node.name(), cv::FileNode::MAP, ""); // 这个结构可以由 {}替换，{}在opencv中表示Map []表示int，str等 fs << node_name << { ... fs << }
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

        OUT void parse_FileNode_to_FileNode2Map(IN const cv::FileNode & node, IN const JString & node_name, OUT FileNode2Map & out_map)
        {
            // 初始化节点名称
            out_map.node_name_ = node_name;

            // 处理Map类型: 使用递归的写法
            if (!is_opencv_mat(node) && node.isMap())
            {
                out_map.type_ = FileNodeTYPE::MAP;
                for (const auto& it: node)
                {
                    JString key = it.name(); // 获取当前节点名称
                    FileNode2Map child_node; // 子节点对象
                    // 递归
                    parse_FileNode_to_FileNode2Map(it, key, child_node);
                    // 将子节点存入当前节点的_map中
                    out_map.map_.push_back(child_node);
                }
            }else if (node.isInt())
            {
                out_map.type_ = FileNodeTYPE::INT;
                node >> out_map.idata_;
            }else if (node.isReal())
            {
                out_map.type_ = FileNodeTYPE::FLOAT;
                node >> out_map.fdata_;
            }else if (node.isString())
            {
                out_map.type_ = FileNodeTYPE::STR;
                node >> out_map.sdata_;
            }else {
                out_map.type_ = FileNodeTYPE::MAT;
                node >> out_map.mat_;
            }    
            return;
        }

        OUT FileNode2Map parse_Yaml_to_FileNode2Map(IN const JString& yaml_path)
        {
            cv::FileStorage fs(yaml_path, cv::FileStorage::READ);
            if (!fs.isOpened())
            {
                throw std::runtime_error("Failed to create yaml file: " + yaml_path);
            }

            FileNode2Map root_node;
            // 读取根节点
            cv::FileNode root_fn = fs.root(); // 根节点的name会报错
            parse_FileNode_to_FileNode2Map(root_fn, "", root_node);

            fs.release();
            return root_node;
        }
    
        OUT void write_FileNode2Map_to_Yaml(IN const FileNode2Map& in_map, IN cv::FileStorage& fs)
        {
            // 1. 处理 映射类型（MAP）：以字典形式写入，递归写入子节点
            if (in_map.type_ == FileNodeTYPE::MAP)
            {
                // 开始写入字典 处理根节点，opencv提供的root.name有问题
                if (in_map.node_name_ == "")
                {
                    for (const auto& pair : in_map.map_)
                    {
                        write_FileNode2Map_to_Yaml(pair, fs);
                    }
                }else{
                    fs << in_map.node_name_ << "{";
                    // 遍历子节点，递归写入
                    for (const auto& pair : in_map.map_)
                    {
                        write_FileNode2Map_to_Yaml(pair, fs);
                    }
                    // 结束字典写入
                    fs << "}";
                }
                
            }
            // 2. 处理 标量类型 & 矩阵类型：直接写入键值对
            else
            {
                // 根据数据类型写入对应值
                if (in_map.type_ == FileNodeTYPE::INT)
                {
                    fs << in_map.node_name_ << in_map.idata_;
                }
                else if (in_map.type_ == FileNodeTYPE::FLOAT)
                {
                    fs << in_map.node_name_ << in_map.fdata_;
                }
                else if (in_map.type_ == FileNodeTYPE::STR)
                {
                    fs << in_map.node_name_ << std::string(in_map.sdata_); // 转换为 std::string 写入
                }
                else
                {
                    fs << in_map.node_name_ << in_map.mat_; // 直接写入 cv::Mat
                }
            }
        }
        
        OUT ErrorCode write_FileNode2Map_to_YamlFile(IN const FileNode2Map& in_map, IN const std::string& yaml_path)
        {
            cv::FileStorage fs(yaml_path, cv::FileStorage::WRITE | cv::FileStorage::FORMAT_YAML);
            if (!fs.isOpened())
            {
                PRINT_ERROR("File Open Failed!!! %d", __LINE__);
                return ErrorCode::FILEOPENFAILED;
            }

            // 递归写入根节点
            write_FileNode2Map_to_Yaml(in_map, fs);

            fs.release();
            return ErrorCode::SUCCESS;
        }
        
        OUT FileNode2Map& find_and_rewrite_kv(IN FileNode2Map & in_map, IN const std::vector<JString>& keys,  IN int level)
        {
            if (level == keys.size())
            {
                return in_map;
            }

            for (size_t i = 0; i < in_map.map_.size(); i++)
            {
                if (in_map.map_[i].node_name_ == keys[level])
                {
                    return find_and_rewrite_kv(in_map.map_[i], keys, ++level);   
                }
            }

            // 注意：此处返回in_map引用，确保返回值类型一致
            // PRINT_WARN("cant find index %d key %s, return ori map", level, keys[level]);
            // 这边可以实现自己的异常类型，将level传出去进行使用
            throw std::runtime_error("cant find index " + std::to_string(level) + " key: " + keys[level] + " you can add it in this level");
        }
    };
};













