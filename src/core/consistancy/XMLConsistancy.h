#ifndef QT_TEST_XML_CONSISTENCY_H
#define QT_TEST_XML_CONSISTENCY_H

#include <string>

class XMLConsistencyResult {
public:
    bool consistent = false;
    char * failed_around = nullptr;

public:
    XMLConsistencyResult(): consistent(), failed_around() {}
};

class XMLConsistency {
public:
    virtual XMLConsistencyResult check(std::string) = 0;
};


#endif //QT_TEST_XML_CONSISTENCY_H
