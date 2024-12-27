#include "compression/compression.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{

    string xml1 = "<html>\t"
                  "\n"
                  "\n"
                  ""
                  "<pot>test test test</pot></html>";

    string compressed = Compress(minifyXML(xml1));
    string decompressed = Decompress(compressed);
    assert(decompressed == minifyXML(xml1));

    // Read from file.
    std::ifstream file("test/sample.txt");
    std::ostringstream buffer;
    buffer << file.rdbuf();
    file.close();

    // Compress into out.txt
    string xml2 = buffer.str();
    std::ofstream file_out("out.txt");
    file_out << Compress(minifyXML(xml2));
    file_out.close();

    // Decompress from out.txt
    std::ifstream file_in("out.txt");
    buffer << file_in.rdbuf();
    file_in.close();

    decompressed = Decompress(buffer.str());
    cout << xml2 << endl;
    cout << decompressed;
    assert(decompressed == minifyXML(xml2));

    return 0;
}
