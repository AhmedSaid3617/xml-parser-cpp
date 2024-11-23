#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string generateIndentation(const string& space, int level) { //repeat each space by number of levels

    string result;

    for (int i = 0; i < level; ++i) {
        result += space;
    }

    return result;
}


string processXML(const string& xmlContent, const string& outputFilePath) {

    vector<string> Output_XML;
    int depth = 0;
    const string space = "    ";  // 4 spaces for indentation

    // Tokenize the XML content
    istringstream xmlStream(xmlContent);
    string fragment, line;
    vector<string> tokens; //getting each token seperated

    // Splitting XML
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


    for (size_t idx = 0; idx < tokens.size(); ++idx) {

        string currentTag = tokens[idx];
        currentTag.erase(remove(currentTag.begin(), currentTag.end(), '\n'), currentTag.end());
        currentTag.erase(remove(currentTag.begin(), currentTag.end(), '\r'), currentTag.end());

        if (currentTag.empty()) continue;

        if (currentTag.find("</") == 0) {  //closing Tag
            --depth;
            Output_XML.push_back(generateIndentation(space, depth) + currentTag);

        } else if (currentTag.find("<") == 0 && currentTag.find("</") == string::npos) { //opening tag

                Output_XML.push_back(generateIndentation(space, depth) + currentTag);
                ++depth;
            }
        else { //content
            Output_XML.push_back(generateIndentation(space, depth) + currentTag);
        }
    }

    // joining the final vector
    ostringstream formattedStream;
    for (const auto& line : Output_XML) {
        formattedStream << line << "\n";
    }

    string formattedXMLString = formattedStream.str();


    ofstream fileStream(outputFilePath);
    fileStream << formattedXMLString;
    fileStream.close();


    return formattedXMLString;
}

int main() {

    string xml_string =
        "<users>"
        "<user>"
        "<id>1</id>"
        "<name>user1</name>"
        "<posts>"
        "<post>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</post>"
        "<post>Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris.</post>"
        "</posts>"
        "<followers>"
        "<follower>"
        "<id>2</id>"
        "</follower>"
        "<follower>"
        "<id>4</id>"
        "</follower>"
        "</followers>"
        "</user>"
        "</users>";

    string OUTXML = "Project.xml";

    // Prettify the XML content and save it
    string formattedXML = processXML(xml_string, OUTXML);

    cout<<"Did IT";

    return 0;
}
