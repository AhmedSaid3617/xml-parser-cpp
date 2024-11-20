#include "../inc/functions.h"

vector<string> tokenizeXML (string XML_data){
    vector <string> TokenizedXML;
    string tag = 0;

    for(int i = 0 ; i<XML_data.size();i++){

        if(XML_data[i] == '<'){
            tag.push_back(XML_data[i]);
            int j =i+1;
            while (XML_data[j]!='>')
            {
                tag.push_back(XML_data[j]);
            }
            if(XML_data[j] == '>'){
                tag.push_back(XML_data[j]);
            }
           i = j;
           TokenizedXML.push_back(tag);
           tag.clear();  
        }
    }
    return TokenizedXML;
}