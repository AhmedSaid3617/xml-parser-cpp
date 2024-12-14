#include "Post.h"

// Getter for body
std::string Post::getBody() const {
    return body;
}

// Getter for topics
const std::vector<std::string>& Post::getTopics() const {
    return topics;
}
