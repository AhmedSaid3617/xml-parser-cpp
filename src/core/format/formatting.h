#ifndef XML_PARSER_FORMATTING_H
#define XML_PARSER_FORMATTING_H

#include <string>
#include <vector>


std::string erase_unwanted_chars(std::string str, bool erase_white_space);
std::string format_newLine(std::string str, int level, int maxChar);

#endif //XML_PARSER_FORMATTING_H
