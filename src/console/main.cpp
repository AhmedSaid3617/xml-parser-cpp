#include <string>
#include <iostream>
#include "fromat/format.h"

int main() {
    std::string my_string = "<id><x></x></id>";
    std::cout << formatXML(my_string);

    return 0;
}