#ifndef COMRESSION_H
#define COMRESSION_H

string readFile(const string &filename);
string minifyXML(const string &xmlContent);
unordered_map<string, int> calculateFrequencies(const string &text);
string replaceFrequentPairs(const string &text, const string &pair, const string &token);
pair<string, unordered_map<string, string>> compress(const string &text);
string tokenExisit(const string &compressedText, const unordered_map<string, string> &mapping);
string replaceToken(const string &compressedText, const unordered_map<string, string> &mapping);
string decompressing(const string &compressedText, const unordered_map<string, string> &mapping);
string decompress(const string &compressedText, const unordered_map<string, string> &mapping);

#endif
