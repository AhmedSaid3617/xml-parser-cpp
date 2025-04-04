#ifndef COMRESSION_H
#define COMRESSION_H

#include <iostream>

using namespace std;

#include <string>
#include <unordered_map>
#include <stack>

struct CompressionResult {
    string compressedText;
    unordered_map<string, string> mapping;
    stack<string> tokens;
};


string readFile(const string &filename);
string minifyXML(const string &xmlContent);
unordered_map<string, int> calculateFrequencies(const string &text);
string replaceFrequentPairs(const string &text, const string &pair, const string &token);
CompressionResult compress(const string &text);
string tokenExisit(const string &compressedText, const unordered_map<string, string> &mapping);
string replaceToken(const string &compressedText, const unordered_map<string, string> &mapping);
string decompressing(const string &compressedText, const unordered_map<string, string> &mapping);
//void displayHashTable(unordered_map<string,auto> freq);
void createFile(const string& filename, const string& text, const unordered_map<string, string>& data, stack<string>& stackData);
CompressionResult loadFile(const string& filename);
void writeStringToFile(const std::string& filename, const std::string& text);
CompressionResult loadFile(const string& filename) ;
string Decompress(string text);
string Compress(string text);
#endif
