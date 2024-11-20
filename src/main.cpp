#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <unordered_map>

using namespace std;
// Helper to find the next occurrence of a character
int find(int indx, char c, const string& line) {
    for (int i = indx; i < line.size(); i++) {
        if (line[i] == c) return i;
    }
    return -1;
}

// Extract the attribute (tag name) at the current position
string get_attribute(int *indx, const string& line) {
    int start = find(*indx, '<', line) + 1;
    int end = find(start, '>', line);
    *indx = end + 1;
    return line.substr(start, end - start);
}

// Extract content of a tag
string get_content(int& indx, const string& line) {
    int start = indx;
    int end = find(indx, '<', line);
    indx = end;
    return line.substr(start, end - start);
}
//creating a stack of attributes
vector<string> attributes_stack(string line){
    int k=0;
    vector<string> attrib_stack;
    while(k<line.size()){
        string s=get_attribute(&k,line);
        if(attrib_stack.empty() || attrib_stack.back()!=s.substr(1))
            attrib_stack.push_back(s);
        else {
        attrib_stack.pop_back();
        attrib_stack.push_back("..");
        }
        
    }
    return attrib_stack;
}

vector<string> findDuplicates(const vector<string>& vec) {
    unordered_map<string, int> countMap;  // To store the count of each string
    vector<string> duplicates;  // To store the duplicates

    // Count occurrences of each string
    for (const string& str : vec) {
        countMap[str]++;
    }

    // Collect strings that appear more than once
    for (const auto& pair : countMap) {
        if (pair.second > 1) {
            duplicates.push_back(pair.first);
        }
    }

    return duplicates;
}

// Convert XML to JSON
string xml_to_json(const string& line) {
    string output;
    stack<string> tags;
    int counter = 0;

    while (counter < line.size()) {
        if (line[counter] == '<' && line[counter + 1] != '/') {
            // Opening tag
            string tag = get_attribute(&counter, line);
            tags.push(tag);

            // Check if the next character is a closing tag or content
            if (line[counter] == '<') {
                output += "\"" + tag + "\": {\n";
            } else {
                //found data
                string content = get_content(counter, line);
                output += "\"" + tag + "\": \"" + content + "\",\n";
                if (line[counter] == '<' && line[counter + 1] == '/') {
                    tags.pop();
                    counter = find(counter, '>', line) + 1;
                }
            }
        } else if (line[counter] == '<' && line[counter + 1] == '/') {
            // Closing tag
            counter = find(counter, '>', line) + 1;
            if (!tags.empty()) {
                tags.pop();
            }
        }
    }

    return "{\n" + output + "\n}";
}

int main() {
string xml = "<users><user><id>1</id><name>Ahmed Ali</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>economy</topic><topic>finance</topic></topics></post><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>solar_energy</topic></topics></post></posts><followers><follower><id>2</id></follower><follower><id>3</id></follower></followers></user><user><id>2</id><name>Yasser Ahmed</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>education</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user><user><id>3</id><name>Mohamed Sherif</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>sports</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user></users>";
    string json = xml_to_json(xml);
    cout << json << endl;
    vector<string> i;
    vector<string> k;
    k=attributes_stack(xml);
    i=findDuplicates(k);
    return 0;
}
