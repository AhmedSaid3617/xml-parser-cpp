#include "../inc/functions.h"

void stringToLines (string &XML, vector <string> &LinedXml);


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
    string close = tags[0];
    if (close.at(1) == '/') return 0; // if the first tag in the array is closing return 0
    s.push(tags[0]);
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
        }
        else {
            if (tags[i].at(1) == '/') {
                return i;
            }
            s.push(tags[i]);
        }
    }
    if(s.empty()) return -1;
    else return 0;
}



void stringToLines (string &XML, vector <string> &LinedXml){

    int line_number = 0;
    for (int i =0;i<XML.size();i++){

        if(XML[i]!= '\n'){
            LinedXml[line_number].push_back(XML[i]);
        }
        else if(XML[i] == '\n') {
            line_number++;
        }
    }

}