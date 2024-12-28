#include "compression/compression.h"
#include <cassert>
#include <iostream>



int main(){
    auto result = Compress(minifyXML("<html>\t"
                                     ""
                                     ""
                                     ""
                                     "<pot>test test test</pot></html>"));
    std::cout << Decompress(result);
}
