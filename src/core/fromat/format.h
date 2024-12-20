#ifndef FORMAT_H
#define FORMAT_H

#include <string>
#include <vector>

std::string generateIndentation(const std::string& space, int level);
std::vector<std::string> tokenizeXML(const std::string& xmlContent);
std::string formatXML(const std::string& xmlContent);

#endif