#include "compression.h"

#define pairSize 2
using namespace std;


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
    int i=0;
    while(i<xmlContent.size()) {

        if (xmlContent[i]!='\n' && xmlContent[i]!='\t') {
            minified += xmlContent[i];
        }
        i++;
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
string CompresedTosring(const string& text, const unordered_map<string, string>& data, stack<string>& stackData) {
    string Compressed="";

    // Write the string
    Compressed+=text + "\n";

    // Write the unordered_map

    for (const auto& pair : data) {
        Compressed+= pair.first+ pair.second;
    }

    // Write the stack
    Compressed+= "\n";
    stack<string> tempStack; // Temporary stack to preserve original stack order
    while (!stackData.empty()) {
        tempStack.push(stackData.top());
        stackData.pop();
    }
    while (!tempStack.empty()) {
        Compressed+=tempStack.top();
        stackData.push(tempStack.top());
        tempStack.pop();
    }
    Compressed+="\n";

   return Compressed;
}
CompressionResult loadFile(const string& filename) {
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
CompressionResult loadData(string loadedData) {

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
string Compress(string text){
    auto [compressedXML, mapping,tokens] = compress(text);
    return CompresedTosring(compressedXML, mapping,tokens);
}
string Decompress(string text){
    auto[compressedXML4LoadedFile, mappings4LoadedFile,tokens4LoadedFile]=loadData(text);
    return decompressing(compressedXML4LoadedFile, mappings4LoadedFile,tokens4LoadedFile);

}
