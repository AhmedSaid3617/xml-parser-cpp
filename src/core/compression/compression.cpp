#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <regex>
#include <cassert>
#include<stack>

#define pairSize 2
using namespace std;
struct CompressionResult {
    string compressedText;
    unordered_map<string, string> mapping;
    stack<string> tokens;
};


// Helper function to read a file into a string
string readFile(const string &filename) {
    ifstream file(filename);
    stringstream buffer;
    if (file.is_open()) {
        buffer << file.rdbuf();
        file.close();
    } else {
        throw runtime_error("Failed to open the file!");
    }
    return buffer.str();
}

// Helper function to remove spaces and newlines (Minification)
string minifyXML(const string &xmlContent) {
    string minified;
    for (char c : xmlContent) {
        if (!isspace(c)) {
            minified += c;
        }
    }
    return minified;
}

// Function to calculate frequencies of byte pairs
unordered_map<string, int> calculateFrequencies(const string &text) {

    unordered_map<string, int> frequencies;
    for (size_t i = 0; i < text.size() - pairSize +1; ++i) {
        string pair = text.substr(i, pairSize);
        frequencies[pair]++;
    }
    return frequencies;
}

// Function to replace frequent pairs with a new token
string replaceFrequentPairs(const string &text, const string &pair, const string &token) {

    int i=0;
    string replacedText = "";
    while (i<text.size()){
        if (!pair.compare(text.substr(i,token.size()+1))){
            replacedText+=token;
            i+=token.size();
        }else{
            replacedText+=text[i];
        }
        i++;

    }

    return replacedText;

}


// Function to compress the data using BPE
CompressionResult compress(const string &text) {
    unordered_map<string, string> mapping;
    stack<string> tokens;
    string compressedText = text;

    int tokenCounter = 128;
    int counter = 0;

    while (true) {
        auto frequencies = calculateFrequencies(compressedText);

        if (frequencies.empty()) break;

        auto mostFrequentPair = max_element(
            frequencies.begin(), frequencies.end(),
            [](const auto &a, const auto &b) { return a.second < b.second; });

        if (mostFrequentPair->second < 2) break;

        string pair = mostFrequentPair->first;
        tokenCounter++;
        string token = "";
        token += (tokenCounter);

        mapping[token] = pair;
        tokens.push(token);
        compressedText = replaceFrequentPairs(compressedText, pair, token);

        if (counter == 150 || tokenCounter == 255) {

            break;
        }
        counter++;
    }

    return {compressedText, mapping, tokens};
}

string tokenExisit(const string &compressedText, const unordered_map<string, string> &mapping){  // O(n^2) could be replaced use stack while stack increase size of file

    for (const auto & entry: mapping){
            int sizet=entry.first.size();
            for (int i=0;i<compressedText.size()-sizet+1;i++){
                if (compressedText.substr(i,sizet)==entry.first){
                    return entry.first;
                }
            }

    }
    return "";
}

string replaceToken(const string &compressedText, const unordered_map<string, string> &mapping,string _token){
    string token=_token;
    int sizet=token.size();
    string decompressedTest="";
    for (int i=0;i<compressedText.size();){
        if (!token.compare(compressedText.substr(i,sizet))){
            decompressedTest+=mapping.at(token);
            i+=sizet;
        }else{
            decompressedTest+=compressedText.at(i);
            i++;
        }
        //cout<<decompressedTest<<"\n";
    }
    return decompressedTest;


}
string decompressing(const string &compressedText, const unordered_map<string, string> &mapping,stack<string>& tokens){

    string decompressedText=compressedText;


    while(!tokens.empty()){

        string token=tokens.top();
        tokens.pop();
        decompressedText=replaceToken(decompressedText,mapping,token);
       // cout<<decompressedText<<"\n\n";

    }

    return decompressedText;

}




void displayHashTable(unordered_map<string,auto> freq){
    cout<<"{";
    for (const auto& pair : freq) {
        cout <<"("<< pair.first << ": " << pair.second <<"), ";
    }
    cout<<"}\n";
}

// Function to create a file with a string, unordered_map, and stack
void createFile(const string& filename, const string& text, const unordered_map<string, string>& data, stack<string>& stackData) {
    // Open the file in write mode
    ofstream file(filename, ios::out);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    // Write the string
    file << text << "\n";

    // Write the unordered_map

    for (const auto& pair : data) {
        file << pair.first<< pair.second;
    }

    // Write the stack
    file << "\n";
    stack<string> tempStack; // Temporary stack to preserve original stack order
    while (!stackData.empty()) {
        tempStack.push(stackData.top());
        stackData.pop();
    }
    while (!tempStack.empty()) {
        file << tempStack.top();
        stackData.push(tempStack.top());
        tempStack.pop();
    }
    file << "\n";
    file.close(); // Close the file
    cout << "Data saved successfully to " << filename << endl;
}CompressionResult loadFile(const string& filename) {
    string loadedData=readFile(filename);
    CompressionResult result;
    int index=0;
    while(loadedData[index]!='\n'){
        result.compressedText+=loadedData[index];
        index++;
    }
    index++;
    while(loadedData[index]!='\n'){
        result.mapping[loadedData.substr(index,1)]=loadedData.substr(index+1,2);
        index+=3;
    }
    index++;
    while(loadedData[index]!='\n'){
        result.tokens.push(loadedData.substr(index++,1));

    }




    return result;
}

void writeStringToFile(const string& filename, const string& text) {
    // Open the file in write mode
    ofstream file(filename, std::ios::out);

    // Check if the file opened successfully
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    // Write the string to the file
    file << text;

    // Close the file
    file.close();

    cout << "String successfully written to " << filename << "\n";
}
int main() {
    try {
        // Load the XML file
        string filename = "C:\\Users\\20111\\Desktop\\DSA project\\sample.xml";
        string xmlContent = readFile(filename);

        // Minify the XML content
        string minifiedXML = minifyXML(xmlContent);

        cout << "Minified XML:\n" << minifiedXML << "\n";
        string text ="aaabdaaabac"; // used for test
        //minifiedXML=text;
        unordered_map<string,int> freq=calculateFrequencies(text);



            // Compress the XML content
        auto [compressedXML, mapping,tokens] = compress(minifiedXML);
        cout << "\nCompressed XML:\n" << compressedXML << "\n";


        cout << "\nMapping (for decompression):\n";

        auto[compressedXML4LoadedFile, mappings4LoadedFile,tokens4LoadedFile]=loadFile("output.txt");

        for (const auto &entry : mapping) {
            cout << entry.first << " -> " << entry.second << "\n";
        }
        writeStringToFile("testing the size of minifiedXML.txt" ,minifiedXML);
        createFile("output.txt", compressedXML, mapping,tokens);
        cout<<"\ntesting the loaded file\n";

        if (!compressedXML4LoadedFile.compare(compressedXML)){
            cout<<"the compressed text equal\n";
        }else{
            cout<<"not equal compressed text\n";
        }
        stack<string> tempStack;
        bool EqualStack=true;
        if (tokens.size()!=tokens4LoadedFile.size()){
            cout << "The tokens stack are not equal in size.\n";
        }else{
            while(!tokens.empty()){
                if (tokens.top()!=tokens4LoadedFile.top()){
                    cout<<"not equal stacks\n";
                    EqualStack=false;
                    break;
                }
                tempStack.push(tokens.top());
                tokens.pop();
                tokens4LoadedFile.pop();

            }
            if(EqualStack){
                cout<<"they are equal stacks\n";
            }
            while(!tempStack.empty()){

                tokens.push(tempStack.top());
                tokens4LoadedFile.push(tempStack.top());
                tempStack.pop();


            }
        }

        // Ensure the maps are of the same size
        if (mapping.size() != mappings4LoadedFile.size()) {
            cout << "The mappings are not equal in size.\n";
        } else {
            bool EqualsMap=true;
            for (const auto &entry : mapping) {
                if(mappings4LoadedFile[entry.first]!=entry.second){
                    cout<<"not equal maps\n";
                    EqualsMap=false;
                    break;
                }
            }
            if (EqualsMap){
                cout<<"they are equal maps\n";
            }}



        // Decompress the XML content
        string decompressedXML = decompressing(compressedXML4LoadedFile, mappings4LoadedFile,tokens4LoadedFile);
        cout << "\nDecompressed XML:\n" << decompressedXML << "\n";
        cout<<"mapping "<<mapping.size()<<"\n";
        // Verify correctness
        assert(decompressedXML == minifiedXML && "Decompression failed!");
        cout << "\nDecompression successful!\n";
        cout<<"decompressedXML "<<minifiedXML.length()<<" compressedXML "<<compressedXML.length()<<"\n";



    } catch (const exception &e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
