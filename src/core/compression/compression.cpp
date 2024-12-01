#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <regex>
#include <cassert>

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
        //string pair ="" + text[i]+text[i+1];
        frequencies[pair]++;
    }
    return frequencies;
}

// Function to replace frequent pairs with a new token
string replaceFrequentPairs(const string &text, const string &pair, const string &token) {
    /*
    string replacedText = text;

    size_t pos = 0;
    while ((pos = replacedText.find(pair, pos)) != string::npos) {
        replacedText.replace(pos, pair.size(), token);
        pos += token.size();
    }
    */
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
pair<string, unordered_map<string, string>> compress(const string &text) {
    unordered_map<string, string> mapping;
    string compressedText = text;

    int tokenCounter = 128;


    int couner=0;
    while (true) {
        // Calculate frequencies of byte pairs
        auto frequencies = calculateFrequencies(compressedText);

        // Find the most frequent pair
        if (frequencies.empty()) break;

        auto mostFrequentPair = max_element(
            frequencies.begin(), frequencies.end(),
            [](const auto &a, const auto &b) { return a.second < b.second; });

        if (mostFrequentPair->second < 2) break; // Stop if no frequent pairs are found

        string pair = mostFrequentPair->first;


        //string token ="";token+= char('X'+tokenCounter++);
        //cout<<token<<"\n";
        tokenCounter++;
        cout<<"tokenCounter   "<<tokenCounter<<"\n";
        string token = "";
        cout<<"token   "<<token<<"\n";
        token+=(tokenCounter);
        cout<<"token   "<<token<<"\n";


        mapping[token] = pair;

        // Replace the most frequent pair with a new token
        compressedText = replaceFrequentPairs(compressedText, pair, token);
        if(couner==150 || tokenCounter==255){
            cout<<" tokenCounter "<<tokenCounter<<"\n";
            break;
        }
        couner++;
        cout<<compressedText<<"\n\n";

    }

    return {compressedText, mapping};
}

string tokenExisit(const string &compressedText, const unordered_map<string, string> &mapping){

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
string replaceToken(const string &compressedText, const unordered_map<string, string> &mapping){
    string token=tokenExisit(compressedText,mapping);
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
string decompressing(const string &compressedText, const unordered_map<string, string> &mapping){
    auto token=tokenExisit(compressedText,mapping);
    string decompressedText=compressedText;
    cout<<decompressedText<<"\n";

    while((token.compare("")!=0)){
        decompressedText=replaceToken(decompressedText,mapping);
       // cout<<decompressedText<<"\n\n";
        token=tokenExisit(decompressedText,mapping);

    }

    return decompressedText;

}


// Function to decompress the data
string decompress(const string &compressedText, const unordered_map<string, string> &mapping) {
    string decompressedText = compressedText;

    vector<pair<string, string>> sortedMapping(mapping.begin(), mapping.end());
    sort(sortedMapping.begin(), sortedMapping.end(),
         [](const auto &a, const auto &b) { return a.first.size() > b.first.size(); });

    for (const auto &entry : sortedMapping) {
        size_t pos = 0;
        while ((pos = decompressedText.find(entry.first, pos)) != string::npos) {
            decompressedText.replace(pos, entry.first.size(), entry.second);
        }
    }

    return decompressedText;
}
void displayHashTable(unordered_map<string,int> freq){
    cout<<"{";
    for (const auto& pair : freq) {
        cout <<"("<< pair.first << ": " << pair.second <<"), ";
    }
    cout<<"}\n";
}

int main() {
    try {
        // Load the XML file
        string filename = "C:\\Users\\20111\\Desktop\\DSA project\\sample.xml";
        string xmlContent = readFile(filename);

        // Minify the XML content
        string minifiedXML = minifyXML(xmlContent);

        cout << "Minified XML:\n" << minifiedXML << "\n";
        string text ="aaabdaaabac";
        //minifiedXML=text;
        unordered_map<string,int> freq=calculateFrequencies(text);



            // Compress the XML content
        auto [compressedXML, mapping] = compress(minifiedXML);
        cout << "\nCompressed XML:\n" << compressedXML << "\n";


        cout << "\nMapping (for decompression):\n";
        for (const auto &entry : mapping) {
            cout << entry.first << " -> " << entry.second << "\n";
        }




        // Decompress the XML content
        string decompressedXML = decompressing(compressedXML, mapping);
        cout << "\nDecompressed XML:\n" << decompressedXML << "\n";
    cout<<"mapping "<<mapping.size()<<"\n";
        // Verify correctness
        assert(decompressedXML == minifiedXML && "Decompression failed!");
        cout << "\nDecompression successful!\n";
        cout<<"decompressedXML "<<minifiedXML.length()<<" compressedXML "<<compressedXML.length()<<"\n";


/*
        // Compress the XML content
        auto [compressedXML, mapping] = compress(minifiedXML);
        cout << "\nCompressed XML:\n" << compressedXML << "\n";

        cout << "\nMapping (for decompression):\n";
        for (const auto &entry : mapping) {
            cout << entry.first << " -> " << entry.second << "\n";
        }

        // Decompress the XML content
        string decompressedXML = decompress(compressedXML, mapping);
        cout << "\nDecompressed XML:\n" << decompressedXML << "\n";

        // Verify correctness
        assert(decompressedXML == minifiedXML && "Decompression failed!");
        cout << "\nDecompression successful!\n";*/
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
