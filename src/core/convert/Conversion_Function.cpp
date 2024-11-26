#include "../tree/tree.h"
#include "tree_to_json.h"
#include "XML_To_Tree2.h"
using namespace std;
string xml_to_json(string xml)
{
    auto * converter = new XML_To_Tree2(xml);
    TreeNode * root  = converter->convert();
    string output= XML_To_Tree2::convert_json(root->children[0]);
    return output;
}

