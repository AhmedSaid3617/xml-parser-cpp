#include "Post.h"

Post::Post()
{
}

// Getter for body
std::string Post::getBody() const {
    return body;
}

// Getter for topics
const std::vector<std::string>& Post::getTopics() const {
    return topics;
}

Post::~Post()
{
}
