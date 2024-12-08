#include <cassert>
#include <string>
#include <vector>
#include <iostream>

#include "consistency/consistency.h"

using namespace std;

int main() {
    // Remove the following line, test your code features using assert(SOME BOOLEAN EXPRESSION)
    string XMLFile ="<note>\n<to>Tove</to>\n<from>Jani</from>\n<heading>Reminder</heading>\n<body>Don't forget me this weekend!</body>\n</note>";
    string XMLFile1 ="<note>\n<to>Tove<to>\n<from>Jani</from>\n<heading>Reminder</heading>\n<body>Don't forget me this weekend!</body>\n</note>";
    string XMLFile2 ="<note>\n</to>Tove</to>\n<from>Jani</from>\n<heading>Reminder</heading>\n<body>Don't forget me this weekend!</body>\n</note>";
    string XMLFile3 ="<note>\n<to>Tove</to>\n<from>Jani</from>\n<heading>Reminder</heading>\n<heading>loop<heading>\n<body>Don't forget me this weekend!</body>\n</note>";
    string XMLFile4 ="<note>\n<to>Tove</to>\n<from>Jani</from>\n<heading>Reminder</heading>\n<heading>loop</heading>\n<body>Don't forget me this weekend!</body>\n</note>\n</full>";

    assert(check_errors(XMLFile) == -1);
    assert(check_errors(XMLFile1) == 2);
    assert(check_errors(XMLFile2) == 2);
    assert(check_errors(XMLFile3) == 5);
    assert(check_errors(XMLFile4) == 8);

    assert(check_errors(fix_errors(XMLFile)) == -1);
    assert(check_errors(fix_errors(XMLFile1)) ==-1);
    assert(check_errors(fix_errors(XMLFile2)) ==-1);
    assert(check_errors(fix_errors(XMLFile3)) ==-1);
    assert(check_errors(fix_errors(XMLFile4)) ==-1);
    return 0;
}
