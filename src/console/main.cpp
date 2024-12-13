#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "fromat/format.h"

using namespace std;

vector<string> options = {"format", "compress"};


void printUsage() {
    std::cout << "Usage: xml_editor <option> -i <input_file> -o <output_file>\n";
}

int main(int argc, char *argv[]) {
    
    if (argc < 5)
    {
        printUsage();
        return 1;
    }

    for (int i = 0; i < argc; i++)
    {
        if (std::find(options.begin(), options.end(), argv[i]) != options.end())
        {
            
        }
    }

    return 0;
}