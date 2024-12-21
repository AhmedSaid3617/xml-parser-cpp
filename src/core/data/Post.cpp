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

bool Post::contains(std::string search_str)
{   
    if (this->body.find(search_str) != std::string::npos)
    {
        return true;
    }

    for (std::string topic : topics){
        if (topic.find(search_str) != std::string::npos)
        {
            return true;
        }
    }
    
    return false;
}

Post::~Post()
{
}
