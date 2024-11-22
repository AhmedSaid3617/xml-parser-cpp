#include <cassert>
#include "consistancy/XMLConsistancy.h"

class XMLConsistencyImpl: public XMLConsistency {
public:
    XMLConsistencyResult check(std::string) override {
        return {};
    }
};

int main() {
    XMLConsistencyImpl impl;
    assert(impl.check("<html></html>").consistent);
}