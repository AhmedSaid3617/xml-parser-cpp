//
// Created by Shams El-Din Abdel-Monem on 28/12/2024.
//

#ifndef XML_PARSER_SOCIALNETWORKVISITOR_H
#define XML_PARSER_SOCIALNETWORKVISITOR_H

#include <any>

class SocialNetwork;

class SocialNetworkVisitor {
    virtual std::any visit(SocialNetwork * socialNetwork) = 0;

public:
friend SocialNetwork;
};


#endif //XML_PARSER_SOCIALNETWORKVISITOR_H
