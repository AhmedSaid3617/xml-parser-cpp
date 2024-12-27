#ifndef COMRESSION_H
#define COMRESSION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <regex>
#include <cassert>
#include<stack>


using namespace std;

struct CompressionResult {
    string compressedText;
    unordered_map<string, string> mapping;
    stack<string> tokens;
};

std::string readFile(const std::string &filename);
std::string minifyXML(const std::string &xmlContent);
unordered_map<std::string, int> calculateFrequencies(const std::string &text);
std::string replaceFrequentPairs(const std::string &text, const std::string &pair, const std::string &token);
CompressionResult compress(const string &text);
string tokenExisit(const string &compressedText, const unordered_map<string, string> &mapping);
string replaceToken(const string &compressedText, const unordered_map<string, string> &mapping,string _token);
string decompressing(const string &compressedText, const unordered_map<string, string> &mapping,stack<string>& tokens);
void displayHashTable(unordered_map<string,auto> freq);void createFile(const string& filename, const string& text, const unordered_map<string, string>& data, stack<string>& stackData);
CompressionResult loadFile(const string& filename);
void writeStringToFile(const std::string& filename, const std::string& text);
CompressionResult loadFile(const string& filename) ;
string Decompress(string text);
string Compress(string text);

#endif
