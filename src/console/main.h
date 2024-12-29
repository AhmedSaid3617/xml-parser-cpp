#ifndef MAIN_H
#define MAIN_H
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>



#define MINUMUM_ARGUMENTS_COUNT 2


std::vector<std::string> options = {"format", "compress","verify","json","mutual","most_active",
    "most_influencer", "-help", "draw", "decompress", "mini", "suggest", "search"};

inline void printUsage() {
    std::cout << "Usage: xml_editor <option> -i <input_file> -o <output_file>\n";
}

void printWrongArgument() {
    std::cout << "Invalid argument.\n";
}

bool minArgumentCount(int count) {
    if (count < MINUMUM_ARGUMENTS_COUNT) {
        printWrongArgument();
        return false;
    }
    return true;
}

bool validOption(int argumentCount,char* argument[]) {
    for (int i = 0; i < argumentCount; i++)
    {
        if (std::find(options.begin(), options.end(), argument[i]) != options.end())
        {
            return true;
        }
    }
    printWrongArgument();
    return false;
}

bool validCommand(int argumentCount,char* argument[]) {
    return minArgumentCount(argumentCount) && validOption(argumentCount,argument);
}

std::string getOption(int argumentCount, char* argument[]) {
    for (int i = 0; i < argumentCount; i++)
    {
        if (std::find(options.begin(), options.end(), argument[i]) != options.end())
        {
            return argument[i];
        }
    }
    return "";
}

std::string File_to_string(const std::string &file_path) {
    std::ifstream file;
    std::stringstream buffer;
    file.open(file_path);
    if (file.is_open()) {
        buffer << file.rdbuf();
        file.close();
    }
    else return "";
    file.close();
    return buffer.str();
}

void write_to_output_file(const std::string &file_path, const std::string &output_file) {
    std::ofstream outputFile;
    outputFile.open(file_path);
    if (!outputFile.is_open()) {
        std::cout<<"Invalid file path";
        return;
    }
    outputFile << output_file;
    outputFile.close();
}

std::string get_input_path(int argumentcount, char* argument[]) {
    for(int i = 0; i < argumentcount; i++) {
        if(std::string(argument[i]) == "-i") {
            return argument[i+1];
        }
    }
    return "";
}

void print_all_commands() {
    std::cout<<"xml_editor verify -i input_file.xml -o output_file.xml"<<std::endl;
    std::cout<<"xml_editor verify -i input_file.xml -f -output_file.xml"<<std::endl;
    std::cout<<"xml_editor format -i input_file.xml -o output_file.xml"<<std::endl;
    std::cout<<"xml_editor json -i input_file.xml -o output_file.xml"<<std::endl;
    std::cout<<"xml_editor mutual -i input_file.xml -ids 1,2,3"<<std::endl;
    std::cout<<"xml_editor most_active -i input_file.xml"<<std::endl;
    std::cout<<"xml_editor most_influencer -i input_file.xml"<<std::endl;
}
#endif //MAIN_H
