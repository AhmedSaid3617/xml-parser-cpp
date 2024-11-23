#ifndef MAIN_H
#define MAIN_H
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
class TreeNode{
    public:
    string tag_name;
    string tag_value;
    TreeNode *parent;
    vector<TreeNode *> children;

    TreeNode();
    TreeNode(string name,string value,TreeNode *parent);
    TreeNode(string name,string value,TreeNode *parent,vector<TreeNode *> children);
    void set_children(vector<TreeNode *> children);
    bool children_same_type();
    static TreeNode* Parse_XML(const string data);
	static void Free_XML(TreeNode* root);
};
string convert_json(TreeNode* node, int level);
string insert_taps(int level);
string erase_unwanted_chars(string str, bool erase_white_space);
string format_newLine(string str, int level, int maxChar);
#endif