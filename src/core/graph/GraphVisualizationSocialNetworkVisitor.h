#ifndef XML_PARSER_GRAPHVISUALIZATIONSOCIALNETWORKVISITOR_H
#define XML_PARSER_GRAPHVISUALIZATIONSOCIALNETWORKVISITOR_H

#include <gvc.h>
#include "hashtable.h"
#include "SocialNetworkVisitor.h"
#include "SocialNetwork.h"

class GraphVisualizationSocialNetworkVisitor : public SocialNetworkVisitor {
protected:
    void add_node(Agraph_t *g, const User * user) {
        // const_cast is illegal but the only way to interface with old C code
        Agnode_t *n = agnode(g, const_cast<char *>(user->getName().append("(").append(to_string(user->getId())).append(")").c_str()), 1);

        nodes.insert(user->getId(), n);
    }

    void add_edge(Agraph_t *g, const User * a, const User * b) {
        agedge(g, nodes[a->getId()], nodes[b->getId()], nullptr, 1);
    }

private:
    hash_table<Agnode_t*> nodes;
};

#endif //XML_PARSER_GRAPHVISUALIZATIONSOCIALNETWORKVISITOR_H
