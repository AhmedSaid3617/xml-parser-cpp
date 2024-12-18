#ifndef DATA_POST_H
#define DATA_POST_H

#include <vector>
#include <string>

class Post {

private:
    std::string body;
    std::vector<std::string> topics;

public:
    Post();
    // Getters
    std::string getBody() const;
    const std::vector<std::string>& getTopics() const;

    ~Post();
    friend class User;
    friend class SocialNetwork;
};

#endif // DATA_POST_H
