//
// Created by shams on 11/25/24.
//

#ifndef XML_PARSER_XML_TO_TREE2_H
#define XML_PARSER_XML_TO_TREE2_H

#include "tree/tree.h"
#include <string>
#include <vector>

class XML_To_Tree2 {
private:
    std::string& xml;

public:
    XML_To_Tree2(std::string& xml): xml(xml)
    {
    }

    TreeNode * convert()
    {
        auto root = new TreeNode();
        std::vector<TreeNode *> stack;
        stack.emplace_back(root);

        std::string tag_name;
        const char * ptr = xml.c_str();
        bool next = true;
        bool is_closing;

        while (next) {
            auto parent = stack.back();
            ptr = traverse_xml(ptr, tag_name, is_closing);

            if (is_closing) {
                stack.pop_back();
                next = stack.back() != root;
                continue;
            }

            auto tag_node = new TreeNode();
            tag_node->tag_name = tag_name;

            parent->add_child(tag_node);

            stack.push_back(tag_node);
        }

        return root;
    }

    static const char * traverse_xml(const char * ptr, std::string& tag_name, bool& is_closing) {
        while (*ptr != '<')
            ptr++;

        // found a tag
        ptr += 1;

        // closing tag
        if (*ptr == '/') {
            is_closing = true;
            ptr += 1;
        } else {
            is_closing = false;
        }

        auto start = ptr;

        while (*ptr != '>')
            ptr++;

        // tag ended
        std::string substring(start, ptr);
        tag_name = substring;

        return ptr;
    }
};


#endif //XML_PARSER_XML_TO_TREE2_H
