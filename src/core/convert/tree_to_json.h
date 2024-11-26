#ifndef XML_PARSER_TREE_TO_JSON_H
#define XML_PARSER_TREE_TO_JSON_H
#include <string>
#include "tree\tree.h"
std::string convert_json(TreeNode* node, int level);
std::string insert_taps(int level);
std::string xml_to_json(std::string xml);
#endif //XML_PARSER_TREE_TO_JSON_H
