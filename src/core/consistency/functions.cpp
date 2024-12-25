#include <iostream>

#include "consistency.h"

using namespace std;

//extracting the tags from the string for validation
void tokenizeXML (string &XML_data,vector<Tag> &TokenizedXML){
    string name = "";
    int line = 1;
    int index = 0;
    TokenizedXML.clear();

    for(int i = 0 ; i<XML_data.size();i++){
        if(XML_data[i] == '\n') line++;

        if(XML_data[i] == '<'){
            name.push_back(XML_data[i]);
            int j =i+1;
            while (XML_data[j]!='>')
            {
                name.push_back(XML_data[j]);
                j++;
            }
            if(XML_data[j] == '>'){
                name.push_back(XML_data[j]);
            }
           i = j;
           Tag tag(name, line, index);
            index++;
            TokenizedXML.push_back(tag);
           name.clear();
        }
    }
}

// to make sure every tag has opening and closing and if there is an error it sets line_to_be_fixed
int validateXML(vector<Tag> &tags) {
    stack<Tag> tokens;
    bool flag = false;
    int index = -1;
    if(tags[0].opening == false) {
        tags[0].line_to_be_fixed = -3;
        return 0;
    }
    for(int i = 0; i<tags.size();i++) {
        //if the tag is not opening and stack is empty return the tag index
        if(!tags[i].opening && tokens.empty()) {
            tags[i].line_to_be_fixed = -2;
            return tags[i].index;
        }
        //two identical tags are opening or closing -5 for closing and -6 for opening
        else if(tags[i].name == tags[i+1].name && tags[i].opening == tags[i+1].opening) {
            if(tags[i].opening == false) {
                tags[i].line_to_be_fixed = -5;
                return tags[i].index;
            }
            tags[i+1].line_to_be_fixed = -6;
            return tags[i+1].index;
        }

        //push the tag into the stack if opening
        else if(tags[i].opening == true) {
            tokens.push(tags[i]);
        }

        else if(!tokens.empty()) {
            //pop if the closing tag of the tag on top is encountered
            if(tags[i].name == tokens.top().name && tags[i].opening != tokens.top().opening) {
                tokens.pop();
            }

            /*when the closing tag is not for the one on the top search for its closing if available
             *if found then the tags[i] is the one in error if not then the top one is in error
             */
            else if(tags[i].name != tokens.top().name && tags[i].opening == false) {
                for(int j = i;j<tags.size();j++) {
                    if(tokens.top().name == tags[j].name && !tags[j].opening) flag = true;
                }

                if(flag) {
                    tags[i].line_to_be_fixed = tokens.top().line;
                    return tags[i].index;
                }
                index = tokens.top().index;
                tags[index].line_to_be_fixed = tags[i].line;
                return tokens.top().index;
            }
        }
    }
    if(tokens.empty()) return -1;
    index = tokens.top().index;
    tags[index].line_to_be_fixed = -4;           //opening tag without a closing one for the most part added to the end

    return tokens.top().index;
}

//fixes one error based on line_to_be_fixed value
void fix_error(vector<string> &lines, vector<Tag> &tags, int error_index) {
    Tag error = tags[error_index];
    int index = 1;
    int line_in_error = error.line_to_be_fixed;
    if(line_in_error == -3) {
        if(error.name == tags[tags.size() -1].name && error.opening == tags[tags.size() -1].opening) {
            lines[0].erase(lines[0].begin()+ 1);
            return;
        }
        lines.insert(lines.begin(), error.name);
    }

    else if(line_in_error == -5) {
        lines[error.line - 1].erase(lines[error.line - 1].begin()+ 1);
    }

    else if(line_in_error == -6) {
        while(lines[error.line - 1][index] != '<') {
            index++;
        }
        lines[error.line -1].insert(lines[error.line -1].begin() +index +1, '/');
    }

    else if(line_in_error == -4) {
        if(error.name == tags[0].name && error.opening == tags[0].opening) {
            lines[error.line - 1].insert(lines[error.line -1].begin() +1, '/');
            return;
        }
        lines.push_back(error.closing);
    }

    else if(line_in_error == -2) {
        if(error.index == tags.size()-1) {
            lines.insert(lines.begin(), error.name);
            return;
        }
        lines.insert(lines.begin()+ error.line -1, error.name);
    }

    else if(line_in_error > 0) {
        if(error.opening) {
            lines.insert(lines.begin() +line_in_error -1, error.closing);
            return;
        }
        lines.insert(lines.begin() +line_in_error + 1, error.name);
    }
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

int verify(string &XML) {
    vector<Tag> tokens;
    string data = "";
    int index;
    tokenizeXML(XML, tokens);
    index = validateXML(tokens);
    if(index == -1) return -1;
    return tokens[index].line;
}

//fixes all errors by calling itself
string fix_file(string &XML) {
    vector <string> lines;
    vector<Tag> tokens;
    string data = "";
    int index;
    tokenizeXML(XML, tokens);
    stringToLines(XML, lines);
    index = validateXML(tokens);
    if(index == -1) return XML;

    fix_error(lines, tokens, index);
    data += lines[0];
    for(int i = 1; i<lines.size();i++) {
        data += '\n';
        data += lines[i];
    }
    return fix_file(data);
}
