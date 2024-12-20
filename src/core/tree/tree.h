#ifndef XML_PARSER_TREE_H
#define XML_PARSER_TREE_H

#include <string>
#include <vector>

class TreeNode{
public:
    std::string tag_name;
    std::string tag_value;
    TreeNode *parent;
    std::vector<TreeNode *> children;

    TreeNode();
    TreeNode(std::string name,std::string value,TreeNode *parent);
    TreeNode(std::string name,std::string value,TreeNode *parent,std::vector<TreeNode *> children);
    void set_children(std::vector<TreeNode *> children);
    void add_child(TreeNode * child) {
        children.push_back(child);
    }
    bool siblings_same_type();
    static TreeNode* Parse_XML(const std::string data);
    static void Free_XML(TreeNode* root);
};


#endif //XML_PARSER_TREE_H
