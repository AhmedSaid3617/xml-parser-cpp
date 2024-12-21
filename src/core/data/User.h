#ifndef DATA_USER_H
#define DATA_USER_H

#include <vector>
#include <string>

#include "Post.h"
#include "graph/Graph.h"

class User {

private:
    int id;
    std::string name;
    std::vector<Post> post_list;

    // Private setters
    // TODO: might remove the setters.
    void setId(int newId);
    void setName(const std::string& newName);
    void setPostList(const std::vector<Post>& newPostList);

public:
    // Empty constructor
    User();

    User(int id, std::string name);

    // Getter for id
    int getId() const;

    // Getter for name
    std::string getName() const;

    // Getter for post_list
    const std::vector<Post>& getPostList() const;

    void testInitUser();

    friend class SocialNetwork;
};

#endif
