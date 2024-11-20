#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;
string get_content(int start,string line){
    string output;
    for (int i=start;line[i]!='<';i++){
        output+=line[i];
    }
}
bool is_duplicate(string attribute,string line){
    for (int i=0;i<line.size();i++){
            if(line.substr(0,attribute.size()-1)==attribute) return true;
    }
    return false;
}
int find(int indx,char c,string line){
    char k;
    for (int i=indx;i<line.size();i++){
        k=line[i];
        if(line[i]==c) return i;
    }
    return -1;
} 
string get_attribute(int *indx , string line){
    int start=find(*indx,'<',line)+1;
    int end=find(start,'>',line);
    *indx=end+1;
    return line.substr(start,end-start);
}
// Function to manually parse XML and convert it to JSON format
string xml_to_json(string line){
int counter=0;
string output;
while(counter<line.size()){
string check=get_attribute(&counter, line);
if(!is_duplicate('<'+check+'>',line)){
output.append("{ \""+ check + "\" :\n");
}
else{
    output.append("\t{\n" + std::string("\t\"") + check + "\" : [\n");
    while(line.substr(counter,check.size()+2) != ("</"+check+'>') ){
        output.append("{\n\t\"" + get_attribute(&counter,line) + "\": ");
        
        output.append("\"" + get_content(counter,line) + "\",\n\t");
    }
}
}
return output;
}
int main() {
    // XML string (can be read from a file, for simplicity it's hardcoded here)
    string xml = "<person><name>John Doe</name><age>30</age><address><street>Main St</street><city>Somewhere</city></address></person>";
    xml=xml_to_json(xml);
    cout << xml << endl;
    return 0;
}
