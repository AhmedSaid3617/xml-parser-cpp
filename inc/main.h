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
#include <stack>
#include <string.h>
using namespace std;

class Node {
public:
    string name;                   // Tag name
    string content;                // Text content inside the tag
    vector<Node*> children;        // List of child nodes

    // Constructor
    Node(const string& nodeName) : name(nodeName), content("") {}

    bool children_same_type() {
        int n = children.size();
        if (n == 0) return false;

        string name;
        if (children[0] != nullptr) {
            name = children[0]->name;
        } else {
            return false;
        }

        for (int i = 1; i < n; i++) {
            if (children[i] == nullptr || children[i]->name != name) {
                return false;
            }
        }

        return true;
    }

    ~Node() { // Destructor to clean up children
        for (Node* child : children) {
            delete child;
        }
    }
};

class Tree {
public:
    Node* root;

    Tree() : root(nullptr) {}

    void build(const vector<string>& tokens) {
        root = parseXMLTree(tokens);
    }


    ~Tree() {
        delete root;
    }

private:
    Node* parseXMLTree(const vector<string>& tokens) {
        Node* root = nullptr;
        stack<Node*> nodeStack;

        for (const auto& token : tokens) {
            if (token[0] == '<' && token[1] != '/') { // Opening tag or self-closing tag
                size_t nameEnd = token.find_first_of(" />", 1);
                string tagName = token.substr(1, nameEnd - 1);

                Node* newNode = new Node(tagName);

                if (!nodeStack.empty()) {
                    nodeStack.top()->children.push_back(newNode);
                } else {
                    root = newNode;
                }

                if (token.back() != '/') { // Not self-closing tag
                    nodeStack.push(newNode);
                }
            } else if (token[0] == '<' && token[1] == '/') { // Closing tag
                nodeStack.pop();
            } else { // Text content
                if (!nodeStack.empty()) {
                    nodeStack.top()->content = token;
                }
            }
        }

        return root;
    }




};
vector<string> tokenizeXML(const string& xml) {
    vector<string> tokens;
    size_t pos = 0;

    while (pos < xml.length()) {
        size_t start = xml.find('<', pos);
        if (start == string::npos) break;

        if (start > pos) { // Text content
            tokens.push_back(xml.substr(pos, start - pos));
        }

        size_t end = xml.find('>', start);
        if (end == string::npos) break;

        tokens.push_back(xml.substr(start, end - start + 1));
        pos = end + 1;
    }

    return tokens;
}
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
    bool siblings_same_type();
    static TreeNode* Parse_XML(const string data);
	static void Free_XML(TreeNode* root);
};
string convert_json(TreeNode* node, int level);
string insert_taps(int level);
string erase_unwanted_chars(string str, bool erase_white_space);
string format_newLine(string str, int level, int maxChar);
#endif