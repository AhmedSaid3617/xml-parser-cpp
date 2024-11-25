#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <unordered_map>
#include <sstream>
#define SOME_NUMBER 1024
using namespace std;

class Node {
public:
    string name;                   // Tag name
    string content;                // Text content inside the tag
    vector<Node*> children;        // List of child nodes
    int test=55;

    // Constructor
    Node(const string& nodeName) : name(nodeName), content("") {}

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

    string toJSON() {
        if (!root) {
            return "{}";
        }
        stringstream ss;
        convertToJSON(root, ss, 0);
        return ss.str();
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

    void convertToJSON(Node* node, stringstream& ss, int depth) {
        string indent(depth * 2, ' ');

        ss << indent << "\"" << node->name << "\": ";

        if (node->children.empty()) { // Leaf node
            if (!node->content.empty()) {
                ss << "\"" << escapeJSON(node->content) << "\"";
            } else {
                ss << "null";
            }
        } else { // Node with children
            unordered_map<string, int> childCount;
            for (auto& child : node->children) {
                childCount[child->name]++;
            }

            ss << "{\n";
            unordered_map<string, bool> arrayStarted;

            for (size_t i = 0; i < node->children.size(); ++i) {
                Node* child = node->children[i];
                bool isLastChild = (i == node->children.size() - 1);

                // Handle arrays
                if (childCount[child->name] > 1 && !arrayStarted[child->name]) {
                    ss << indent << "  \"" << child->name << "\": [\n";
                    arrayStarted[child->name] = true;
                }

                if (childCount[child->name] > 1) {
                    if (child->children.empty()) { // Simple content in an array
                        ss << indent << "    \"" << escapeJSON(child->content) << "\"";
                    } else { // Nested object in an array
                        ss << indent << "    ";
                        ss << "{\n";
                        for (auto& grandchild : child->children) {
                            convertToJSON(grandchild, ss, depth + 4);
                        }
                        ss << indent << "    }";
                    }

                    if (i + 1 < node->children.size() && node->children[i + 1]->name == child->name) {
                        ss << ",";
                    } else {
                        ss << "\n" << indent << "  ]";
                        arrayStarted[child->name] = false;
                    }
                } else if (!arrayStarted[child->name]) {
                    convertToJSON(child, ss, depth + 1);
                }

                if (!isLastChild && !arrayStarted[child->name]) {
                    ss << ",";
                }

                ss << "\n";
            }
            ss << indent << "}";
        }
    }

    string escapeJSON(const string& str) {
        string escaped;
        for (char c : str) {
            switch (c) {
                case '\"': escaped += "\\\""; break;
                case '\\': escaped += "\\\\"; break;
                case '\b': escaped += "\\b"; break;
                case '\f': escaped += "\\f"; break;
                case '\n': escaped += "\\n"; break;
                case '\r': escaped += "\\r"; break;
                case '\t': escaped += "\\t"; break;
                default: escaped += c; break;
            }
        }
        return escaped;
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

int main() {
    string xml = "<users><user><id>1</id><name>Ahmed Ali</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>economy</topic><topic>finance</topic></topics></post><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>solar_energy</topic></topics></post></posts><followers><follower><id>2</id></follower><follower><id>3</id></follower></followers></user><user><id>2</id><name>Yasser Ahmed</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>education</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user><user><id>3</id><name>Mohamed Sherif</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>sports</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user></users>";

    vector<string> tokens = tokenizeXML(xml);

    Tree tree;
    tree.build(tokens);

    cout << "JSON Representation:" << endl;
    cout << tree.toJSON() << endl;

    return 0;
}
