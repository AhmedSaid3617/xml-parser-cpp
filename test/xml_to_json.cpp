#include <string>
#include <iostream>
#include <cassert>
#include "tree/tree.h"
#include "convert/tree_to_json.h"
#include "convert/XML_To_Tree2.h"

using namespace std;

int main(){
    string xml = "<html><head><title>abood</title><meta>koko</meta></head></html>";

    auto * converter = new XML_To_Tree2(xml);
    TreeNode * root  = converter->convert();


    return 0;
}