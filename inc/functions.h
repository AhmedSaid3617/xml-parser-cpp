#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <stack>
using namespace std;

string readXMLFile (string xml_file);// omar

void tokenizeXML (string &XML_data,vector<string>& TokenizedXML); //fares


bool IsOpening_closing(vector<string>); // fares


vector<string> extract_tag_name(vector<string>) ;  //Fares


int validateXML(vector<string>); //Omar

void ReportErrors(vector<string>); 

#endif
