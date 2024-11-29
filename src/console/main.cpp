#include <string>
#include <iostream>
#include "fromat/format.h"

int main() {
    std::string my_string = "<id><x></x></id>";
    std::cout << processXML(my_string, "out.txt");

    return 0;
}