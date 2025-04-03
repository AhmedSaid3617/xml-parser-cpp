#include "main.h"
#include "fromat/format.h"
#include "consistency/consistency.h"
#include "compression/compression.h"
#include "convert/tree_to_json.h"
#include "graph/SocialNetwork.h"
#include "data/User.h"
#ifdef GRAPH_VIZ
#include "graph/FileExportGraphVisualization.h"
#endif
using namespace std;

int main(int argc, char *argv[]) {

    if(!validCommand(argc,argv)) {
        printUsage();
        return 0;
    }

    string operation = getOption(argc,argv);

    if(operation == "-help") {
        print_all_commands();
        return 0;
    }

    string file_path = get_input_path(argc,argv);
    string XML_file = File_to_string(file_path);

    if(XML_file.empty()) {
        printWrongArgument();
        return 0;
    }

    if(operation == "verify") {

        if(string(argv[4]) == "-f") {
            string fixed_file = fix_file(XML_file);
            string output_file_path = argv[6];
            write_to_output_file(output_file_path,fixed_file);
            return 0;
        }

        int index =verify(XML_file);
        if (index == -1) cout<<"The Xml file is valid";
        else cout<<"There is an error in line "<<index;

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

    if(operation == "mini") {
        string minified_XML = minifyXML(XML_file);
        string output_file_path = argv[5];
        write_to_output_file(output_file_path,minified_XML);
        return 0;
    }

    if(operation == "compress") {
        string minified_XML = minifyXML(XML_file);
        string compressed_XML = Compress(minified_XML);
        string output_file_path = argv[5];
        write_to_output_file(output_file_path,compressed_XML);
        return 0;
    }

    if(operation == "decompress") {
        string decompressed_XML = Decompress(XML_file);
        string output_file_path = argv[5];
        string formated_file = formatXML(decompressed_XML);
        write_to_output_file(output_file_path,formated_file);
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

            int user_id = id - '0';
            ids.push_back(user_id);
        }
        vector<User*> mutual_users = social_network->who_does_n_users_follow(ids);

        for(int i = 0; i < mutual_users.size(); i++) cout<<"Name:"<<mutual_users[i]->getName()<<endl;

        return 0;
    }

    if(operation == "suggest") {
        int user_id = atoi(argv[5]);
        User* user_to_the_passed_id = social_network->get_user(user_id);
        vector<User*> suggested_users = social_network->suggest_users_to_follow(user_to_the_passed_id);

        if(suggested_users.empty()) {
            cout<<"There is no suggested user to follow"<<endl;
            return 0;
        }

        for(int i = 0; i < suggested_users.size(); i++)
            cout<<"Name:"<<suggested_users[i]->getName()<<" id:"<<suggested_users[i]->getId()<<endl;
        
        return 0;
    }

    if(operation == "search") {
        string argument = argv[2];
        if(argument == "-w") {
            string wanted_word = argv[3];
            vector<Post*> posts_containing_word = social_network->search_posts(wanted_word);

            if(posts_containing_word.empty()) {
                cout<<"There are no posts containing "<<wanted_word<<endl;
                return 0;
            }

            for(int i = 0; i < posts_containing_word.size(); i++)
                cout<<posts_containing_word[i]->getBody();
            return 0;
        }
        if(argument == "-t") {
            string wanted_topic = argv[3];
            vector<Post*> posts_with_the_topic = social_network->search_topics(wanted_topic);

            if(posts_with_the_topic.empty()) {
                cout<<"There are no posts on "<<wanted_topic<<" topic"<<endl;
                return 0;
            }
            
            for(int i = 0; i < posts_with_the_topic.size(); i++)
                cout<<posts_with_the_topic[i]->getBody();
            return 0;
        }
        cout<<"Invalid Arguments";
        return 0;
    }

    if(operation == "most_active") {
        auto* most_active_user = social_network->get_most_active_user();
        cout<<"Name:"<<most_active_user->getName()<<" id:"<<most_active_user->getId();
        return 0;
    }

    if(operation == "most_influencer") {
        auto* most_influencer_user = social_network->get_most_influencer_user();
        cout<<"Name:"<<most_influencer_user->getName()<<" id:"<<most_influencer_user->getId();
        return 0;
    }

#ifdef GRAPH_VIZ
    if(operation == "draw"){
        string output_file_path = argv[5];
        auto visitor = new FileExportGraphVisualization(output_file_path);
        social_network->accept(visitor);
        return 0;
    }
#endif
    return 0;
}
