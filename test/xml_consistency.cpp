#include <cassert>
#include <string>
#include <vector>
#include <iostream>

#include "consistancy/consistency.h"

using namespace std;

int main() {
    // Remove the following line, test your code features using assert(SOME BOOLEAN EXPRESSION)
    // e.g. `assert(myAdder(1, 2) == (1 + 2));`
    assert(false);

    string xml = "<t1>\n<t2>\nhi\n</t2>\n</t1>\n";
    vector<string> linedXML{100};

    stringToLines(xml, linedXML);

    // use assert to check output

    for(int i=0;i<linedXML.size();i++)
        cout<< linedXML[i]<<endl;


    return 0;
}