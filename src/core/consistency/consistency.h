#ifndef XML_PARSER_CONSISTENCY_H
#define XML_PARSER_CONSISTENCY_H

#include <string>
#include <vector>
#include <stack>

class Tag {
public:
    std::string name;               //store the tag name without '/'
    std::string closing;            //store the closing tag for fixing errors
    int line;                  //the line the tag is in
    int index;                 //the index of the tag in the tags vector needed for validate function
    int line_to_be_fixed;      //used to identify the error as each value represents a case
    bool opening;              //stores whether the tag is opening or closing

    //constructor
    Tag(std::string tag, int Line, int i){
        if(tag.at(1) == '/') {
            this->opening = false;
            this->closing = tag;
            tag.erase(tag.begin() + 1);
            this->name = tag;

        }
        else {
            this->opening = true;
            this->name = tag;
            tag.insert(tag.begin()+1, '/');
            closing = tag;
        }
        this->index = i;
        this->line = Line;
        this->line_to_be_fixed = -1;
    };

    //set the error case
    void set_line_to_be_fixed(int Line) {
        this->line_to_be_fixed = Line;
    }

};

void tokenizeXML (std::string &XML_data,std::vector<Tag> &TokenizedXML);
int validateXML(std::vector<Tag> &tags);
int verify(std::string XML);
void fix_error(std::vector<std::string> &lines, std::vector<Tag> &tags, int error_index);
void stringToLines (std::string &XML, std::vector <std::string> &LinedXml);
std::string fix_file(std::string XML);

#endif //XML_PARSER_CONSISTENCY_H
