#include "compression/compression.h"
#include <cassert>
#include <iostream>



int main(){
    auto result = Compress("f\ng");
    std::cout << Decompress(result);
}
