#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

#include "format.h"

using namespace std;

string generateIndentation(const string& space, int level) {
    string result;
    for (int i = 0; i < level; ++i) {
        result += space;
    }
    return result;
}

// Function to tokenize XML
vector<string> tokenizeXML(const string& xmlContent) {

    vector<string> tokens;
    istringstream xmlStream(xmlContent);
    string fragment, line;

    while (getline(xmlStream, line, '>')) {

        line += ">";
        size_t pos = 0;

        while ((pos = line.find("<", pos)) != string::npos) {

            if (pos > 0) {
                tokens.push_back(line.substr(0, pos));
            }

            line = line.substr(pos);
            size_t tagEndPos = line.find('>');
            tokens.push_back(line.substr(0, tagEndPos + 1));
            line = line.substr(tagEndPos + 1);
        }

        if (!line.empty()) {
            tokens.push_back(line);
        }

    }
    return tokens;
}

// Function to process XML content and generate formatted XML
string formatXML(const string& xmlContent, const string& outputFilePath) {

    vector<string> Output_XML;
    int depth = 0;
    const string space = "    ";  // 4 spaces for indentation

    vector<string> tokens = tokenizeXML(xmlContent);

    for (size_t idx = 0; idx < tokens.size(); ++idx) {

        string currentTag = tokens[idx];
        currentTag.erase(remove(currentTag.begin(), currentTag.end(), '\n'), currentTag.end());
        currentTag.erase(remove(currentTag.begin(), currentTag.end(), '\r'), currentTag.end());

        if (currentTag.empty()) continue;

        if (currentTag.find("</") == 0) {  // closing Tag
            --depth;
            Output_XML.push_back(generateIndentation(space, depth) + currentTag);
        }

        else if (currentTag.find("<") == 0 && currentTag.find("</") == string::npos) {  // opening tag
            Output_XML.push_back(generateIndentation(space, depth) + currentTag);
            ++depth;
        }

        else {  // content
            Output_XML.push_back(generateIndentation(space, depth) + currentTag);
        }
    }

    // Join the formatted lines into a single string
    ostringstream formattedStream;
    for (const auto& line : Output_XML) {
        formattedStream << line << "\n";
    }

    string formattedXMLString = formattedStream.str();

    // Save the formatted XML to a file
    ofstream fileStream(outputFilePath);
    fileStream << formattedXMLString;
    fileStream.close();

    return formattedXMLString;
}

// Function to read XML content from a file
string readXMLFromFile(const string& filePath) {
    ifstream file(filePath);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to write XML content to a file
void writeXMLToFile(const string& xmlContent, const string& filePath) {
    ofstream file(filePath);
    file << xmlContent;
    file.close();
}