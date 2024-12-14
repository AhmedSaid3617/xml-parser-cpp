#ifndef DATA_POST_H
#define DATA_POST_H

#include <vector>
#include <string>
#include "User.h"

class Post {

private:
    std::string body;
    std::vector<std::string> topics;

public:
    // Getters
    std::string getBody() const;
    const std::vector<std::string>& getTopics() const;

    friend class User;
};

#endif // DATA_POST_H
