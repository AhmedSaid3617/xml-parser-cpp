#include "main.h"
string convert_json(TreeNode* node, int level) {
        string json = "";
        if (node->children.size() > 1) json += "\n" + insert_taps(level) + "\"" + node->tag_name + "\":[\n" + insert_taps(level) + "{";
        else if (node->children.size() == 1) json += "\n" + insert_taps(level) + "\"" + node->tag_name + "\":{";
        else if (node->children.size() == 0)
            json += "\n" + insert_taps(level) + "\"" + node->tag_name + "\":\"" + format_newLine(erase_unwanted_chars(node->tag_value,false), level,50)  + "\"";
        for (int i = 0; i < node->children.size(); i++) {
            json += convert_json(node->children[i], level + 1);
        }
        if (node->children.size() > 0) json += "\n" + insert_taps(level) + "}";
        return json;
    }