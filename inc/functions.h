#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <bits/stdc++.h>
using namespace std;

string readXMLFile (string xml_file);// omar



vector<string> tokenizeXML (string); //fares


bool IsOpening_closing(vector<string>); // fares


vector<string> extract_tag_name(vector<string>) ;  //Fares


vector<string> validateXML(vector<string>); //Omar

void ReportErrors(vector<string>); 

#endif