#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include "fromat/format.h"
#include "consistency/consistency.h"
#include "convert/tree_to_json.h"
#include "graph/SocialNetwork.h"
#include "data/User.h"


#define MINUMUM_ARGUMENTS_COUNT 5

using namespace std;

vector<string> options = {"format", "compress","verify","json","mutual","most_active","most_influencer", "-help"};

void printUsage() {
    std::cout << "Usage: xml_editor <option> -i <input_file> -o <output_file>\n";
}

void printWrongArgument() {
    cout << "Invalid argument.\n";
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

string getOption(int argumentCount, char* argument[]) {
    for (int i = 0; i < argumentCount; i++)
    {
        if (std::find(options.begin(), options.end(), argument[i]) != options.end())
        {
            return argument[i];
        }
    }
    return "";
}

string File_to_string(const string &file_path) {
    ifstream file;
    stringstream buffer;
    file.open(file_path);
    if (file.is_open()) {
        buffer << file.rdbuf();
        file.close();
    }
    else return "";
    file.close();
    return buffer.str();
}

void write_to_output_file(const string &file_path, const string &output_file) {
    ofstream outputFile;
    outputFile.open(file_path);
    if (!outputFile.is_open()) {
        cout<<"Invalid file path";
        return;
    }
    outputFile << output_file;
    outputFile.close();
}

void print_all_commands() {
    cout<<"xml_editor verify -i input_file.xml -o output_file.xml"<<endl;
    cout<<"xml_editor verify -i input_file.xml -f -output_file.xml"<<endl;
    cout<<"xml_editor format -i input_file.xml -o output_file.xml"<<endl;
    cout<<"xml_editor json -i input_file.xml -o output_file.xml"<<endl;
    cout<<"xml_editor mutual -i input_file.xml -ids 1,2,3"<<endl;
    cout<<"xml_editor most_active -i input_file.xml"<<endl;
    cout<<"xml_editor most_influencer -i input_file.xml"<<endl;
}

int main(int argc, char *argv[]) {

    if(!validCommand(argc,argv)) return 0;

    string operation = getOption(argc,argv);
    string file_path = argv[3];
    string XML_file = File_to_string(file_path);
    if(XML_file.empty()) {
        printWrongArgument();
        return 1;
    }

    if(operation == "-help") {
        print_all_commands();
        return 0;
    }

    if(operation == "verify") {
        string fixed_file;

        if(argv[4] == "-f") {
            fixed_file = fix_file(XML_file);
            string output_file_path = argv[6];
            write_to_output_file(output_file_path,fixed_file);
            return 0;
        }

        int index =verify(XML_file);
        if (index == -1) cout<<"The Xml file is valid";
        else cout<<"There is an error in line"<<index;

        return 0;
    }

    if(operation == "format"){
        string formated_file = formatXML(XML_file);
        string output_file_path = argv[5];
        write_to_output_file(output_file_path,formated_file);
        return 0;
    }

    if(operation == "json") {
        string json_file = xml_to_json(XML_file);
        string output_file_path = argv[5];
        write_to_output_file(output_file_path,json_file);
        return 0;
    }

    auto* social_network = new SocialNetwork();
    social_network->extract_data(XML_file);

    if(operation == "mutual") {
        string user_ids_mutual_wanted = argv[5];
        char id;
        vector<int> ids;
        for(int i = 0; i < user_ids_mutual_wanted.size(); i = i+2) {
            id = user_ids_mutual_wanted[i];

            if(!std::isdigit(id)) {
                printWrongArgument();
                return 0;
            }

            ids.push_back(id);
        }
        vector<User*> mutual_users = social_network->who_does_n_users_follow(ids);

        for(int i = 0; i < mutual_users.size(); i++) cout<<mutual_users[i]->getName()<<endl;

        return 0;
    }

    if(operation == "most_active") {
        auto* most_active_user = social_network->get_most_active_user();
        cout<<most_active_user->getName()<<" "<<most_active_user->getId();
        return 0;
    }

    if(operation == "most_influencer") {
        auto* most_influencer_user = social_network->get_most_influencer_user();
        cout<<most_influencer_user->getName()<<" "<<most_influencer_user->getId();
        return 0;
    }
    return 0;
}
