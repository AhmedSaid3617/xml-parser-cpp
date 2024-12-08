#include <stack>
#include <iostream>

#include "consistency.h"

using namespace std;

void tokenizeXML (string &XML_data,vector<string> &TokenizedXML){
    string tag = "";

    for(int i = 0 ; i<XML_data.size();i++){

        if(XML_data[i] == '<'){
            tag.push_back(XML_data[i]);
            int j =i+1;
            while (XML_data[j]!='>')
            {
                tag.push_back(XML_data[j]);
                j++;
            }
            if(XML_data[j] == '>'){
                tag.push_back(XML_data[j]);
            }
           i = j;
           TokenizedXML.push_back(tag);
           tag.clear();  
        }
    }
}

// to make sure every tag has opening and closing
int validateXML(vector<string> &tags) {
    stack<string> s;
    stack<int> index;
    string close = tags[0];
    if (close.at(1) == '/') return 0; // if the first tag in the array is closing return 0
    s.push(tags[0]);
    index.push(0);
    for(int i = 1; i < tags.size(); i++) { // looping over the array and pushing the tags into a stack until we find its closing
        if (!s.empty()) {
            close = s.top();
            close.insert(close.begin()+1, '/');
        }
        else {
            close = "";
        }
        if(close == tags[i] && !s.empty()) {
            s.pop();
            index.pop();
        }
        else {
            if (tags[i].at(1) == '/') {
                if(index.empty()) return i;
                if(tags[i] == tags[i+1]) return i;
                return index.top();
            }
            s.push(tags[i]);
            index.push(i);
        }
    }
    if(s.empty()) return -1;
    else return index.top();
}

int report_errors(vector <string> &lines, vector <string> &tags, int error_index) {
    int j, occur = 0;
    string tag;
    string error = tags[error_index];
    for (int s = 0; s < error_index; s++) {
        if (tags[s] == error) occur++;
    }
    for (int i = 0; i < lines.size(); i++) {
        j = 0;
        while (lines[i][j] == ' ') {
            j++;
        }
        if (lines[i][j] != '<') continue;
        while (lines[i][j] != '>') {
            tag.push_back(lines[i][j]);
            j++;
        }
        tag.push_back('>');
        if (tag == error && occur == 0) return i+1;
        if (tag == error) occur--;
        tag.clear();
        if(j != lines[i].size() - 1) {
            while (lines[i][j] != '<') {
                j++;
            }
            while (lines[i][j] != '>') {
                tag.push_back(lines[i][j]);
                j++;
            }
            tag.push_back('>');
            if (tag == error && occur == 0) return i+1;
            if (tag == error) occur--;
            tag.clear();
        }
    }
    return -1;
}

void stringToLines (string &XML, vector <string> &LinedXml){
    int line_number = 0;
    LinedXml = {""};
    for (int i =0;i<XML.size();i++){
        if(XML[i]!= '\n'){
            LinedXml[line_number].push_back(XML[i]);
        }
        else if(XML[i] == '\n') {
            line_number++;
            LinedXml.push_back("");
        }
    }
}

int find_errors(vector <string> &lines, vector <string> &tags, int error_index) {
    int j, occur = 0;
    string tag;
    int starting = 0;
    bool duplicate = false;
    if(error_index == -1) return -1;
    string error = tags[error_index];
    if(tags[error_index] == tags[error_index+1] || tags[error_index] == tags[error_index - 1]) duplicate = true;
    for (int s = 0; s < error_index; s++) {
        if (tags[s] == error) occur++;
    }
    for (int i = 0; i < lines.size(); i++) {
        j = 0;
        while (lines[i][j] == ' ') {
            j++;
        }
        if (lines[i][j] != '<') continue;
        starting = j;
        while (lines[i][j] != '>') {
            tag.push_back(lines[i][j]);
            j++;
        }
        tag.push_back('>');
        if (tag == error && occur == 0 && duplicate) {
            if(error.at(1) == '/') {
                lines[i].erase(lines[i].begin()+starting +1);
            }
            else if(error.at(1) != '/') {
                lines[i].insert(lines[i].begin()+starting +1, '/');
            }
            return i+1;
        }
        if (tag == error && occur == 0) {
            if(error.at(1) == '/') {
                error.erase(error.begin()+1);
                lines.insert(lines.begin()+ i, error);
            }
            else if(error.at(1) != '/') {
                error.insert(error.begin()+1,'/');
                // cout<<error<<endl;
                lines.insert(lines.begin()+ i+1, error);
            }
            return i+1;
        }
        if (tag == error) occur--;
        tag.clear();
        if(j != lines[i].size() - 1) {
            while (lines[i][j] != '<') {
                j++;
            }
            starting = j;
            while (lines[i][j] != '>') {
                tag.push_back(lines[i][j]);
                j++;
            }
            tag.push_back('>');
            if (tag == error && occur == 0 && duplicate) {
                if(error.at(1) == '/') {
                    lines[i].erase(lines[i].begin()+starting +1);
                }
                else if(error.at(1) != '/') {
                    lines[i].insert(lines[i].begin()+starting +1, '/');
                }
                return i+1;
            }
            if (tag == error && occur == 0) {
                if(error.at(1) == '/') {
                    error.erase(error.begin()+1);
                    lines.insert(lines.begin()+ i, error);
                }
                else if(error.at(1) != '/') {
                    error.insert(error.begin()+1,'/');
                    error.erase(error.begin()+1);
                    lines.insert(lines.begin()+ i+1, error);
                }
                return i+1;
            }
            if (tag == error) occur--;
            tag.clear();
        }
    }
    return -1;
}

int check_errors(string xml_data) {
    int tag_index = 0;
    vector <string> lines;
    vector <string> tags;

    tokenizeXML(xml_data, tags);
    stringToLines(xml_data, lines);
    tag_index = validateXML(tags);

    if(tag_index == -1) return -1;

    else return report_errors(lines, tags, tag_index);
}

string fix_errors(string xml_data) {
    int tag_index = 0;
    int error_index = 0;
    string data = "";
    vector <string> lines;
    vector <string> tags;

    tokenizeXML(xml_data, tags);
    stringToLines(xml_data, lines);
    tag_index = validateXML(tags);
    error_index = find_errors(lines, tags, tag_index);
    if(error_index == -1) {
        return xml_data;
    }
    else {
        data+=lines[0];
        for(int i = 1; i < lines.size(); i++) {
            data+= '\n';
            data += lines[i];
        }
        return fix_errors(data);
    }
}
