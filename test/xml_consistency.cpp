#include <cassert>
#include <string>
#include <vector>
#include <iostream>

#include "consistency/consistency.h"

using namespace std;

int main() {
    // Remove the following line, test your code features using assert(SOME BOOLEAN EXPRESSION)
    string XMLFile ="<note>\n<body>\n<to>Tove<to>\n</from>Jani</from>\n</heading>Reminder</heading>\nDon't forget me this weekend!\n<testttttt>\n</lol>\n</body>\n</note>\n</root>";

    cout << fix_file(XMLFile);
    return 0;
}
