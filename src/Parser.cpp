#include "main.h"
string convert_json(TreeNode* node, int level) {
    string json = "";
    // Opening square bracket or curly brace depending on the number of children
    if (node->siblings_same_type()) {
        json += "\n" + insert_taps(level) + "\"" + node->tag_name + "\":[\n";
        for (int i = 0; i < node->children.size(); i++) {
            json += insert_taps(level + 1);
            json += convert_json(node->children[i], level + 1);
            json += "\n" + insert_taps(level + 1);
            if (i < node->children.size() - 1) {
                json += ",";  // Add comma if not the last child
            }
            json += "\n";
        }
        json += insert_taps(level) + "]";  // Closing the square brackets for an array
    } 
    else if (node->children.size() >= 1) {
         for (int i = 0; i < node->children.size(); i++) {
        json += "\n" + insert_taps(level) + "\"" + node->tag_name + "\":{";
        json += convert_json(node->children[i], level + 1);  // Handle the single child
        json += "\n" + insert_taps(level) + "}";
    }
    }
    else if (node->children.size() == 0) {
        // For nodes with no children, treat it as a leaf node and add its value
        json += "\n" + insert_taps(level) + "\"" + node->tag_name + "\":\"" + format_newLine(erase_unwanted_chars(node->tag_value, false), level, 50) + "\"";
    }

    return json;
}