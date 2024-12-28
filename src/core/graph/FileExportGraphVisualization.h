//
// Created by Shams El-Din Abdel-Monem on 28/12/2024.
//

#ifndef XML_PARSER_FILEEXPORTGRAPHVISUALIZATION_H
#define XML_PARSER_FILEEXPORTGRAPHVISUALIZATION_H

#include <gvc.h>
#include <string>
#include "graph/GraphVisualizationSocialNetworkVisitor.h"
#include "graph/SocialNetwork.h"

class FileExportGraphVisualization : public GraphVisualizationSocialNetworkVisitor {
private:
    std::string filename;

    // export the social network into file specified
    std::any visit(SocialNetwork * network) final {
        // Set up a Graphviz context
        GVC_t *gvc = gvContext();

        // Create a simple directed graph
        Agraph_t *g = agopen("Social Network", Agdirected, nullptr);

        // convert the social network into gvc graph
        // first add all users
        for (auto user:network->get_users()) {
            add_node(g, user);
        }

        // add all relations
        for (auto user:network->get_users()) {
            for (auto followee:network->get_following(user->getId())) {
                add_edge(g, user, &followee);
            }
        }

        // Set a node attribute
        //agsafeset(n, "color", "red", "");

        // Compute a layout using the default layout engine (e.g., "dot")
        gvLayout(gvc, g, "dot");

        // Render the graph to a memory buffer in PNG format
        char *imageData = nullptr;
        unsigned int imageSize = 0;

        if (gvRenderFilename(gvc, g, "png", filename.c_str()) != 0) {
        }

        // Free the memory buffer
        gvFreeRenderData(imageData);

        // Clean up Graphviz resources
        gvFreeLayout(gvc, g);
        agclose(g);
        gvFreeContext(gvc);

        return nullptr;
    }

public:
    explicit FileExportGraphVisualization(std::string filename): filename(filename) {
    }
};

#endif //XML_PARSER_FILEEXPORTGRAPHVISUALIZATION_H
