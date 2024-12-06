#ifndef XML_PARSER_CONSISTENCY_H
#define XML_PARSER_CONSISTENCY_H

#include <string>
#include <vector>

void tokenizeXML (std::string &XML_data,std::vector<std::string> &TokenizedXML);
int validateXML(std::vector<std::string> &tags);
int report_errors(std::vector <std::string> &lines, std::vector <std::string> &tags, int error_index);
void stringToLines (std::string &XML, std::vector <std::string> &LinedXml);
int check_errors(std::string xml_file);
int find_errors(std::vector <std::string> &lines, std::vector <std::string> &tags, int error_index);
int fix_errors(std::string xml_file);

#endif //XML_PARSER_CONSISTENCY_H
