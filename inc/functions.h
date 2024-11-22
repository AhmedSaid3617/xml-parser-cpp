#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <stack>
using namespace std;

void stringToLines (string &XML, vector <string> &LinedXml);

void tokenizeXML (string &XML_data,vector<string>& TokenizedXML); //fares


bool IsOpening_closing(vector<string>); // fares


vector<string> extract_tag_name(vector<string>) ;  //Fares


int validateXML(vector<string>); //Omar

int report_errors(vector <string> &lines, vector <string> &tags, int error_index); 

#endif
