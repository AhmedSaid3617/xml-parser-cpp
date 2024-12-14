#ifndef DATA_USER_H
#define DATA_USER_H

#include <vector>
#include <string>

#include "Post.h"

class User {

private:
    int id;
    std::string name;
    std::vector<Post> post_list;
    std::vector<int> followers;

    // Private setters
    // TODO: might remove the setters.
    void setId(int newId);
    void setName(const std::string& newName);
    void setPostList(const std::vector<Post>& newPostList);
    void setFollowers(const std::vector<int>& newFollowers);

public:
    // Empty constructor
    User();

    User(int id, std::string name, const std::vector<int> &followers);;

    // Getter for id
    int getId() const;

    // Getter for name
    std::string getName() const;

    // Getter for post_list
    const std::vector<Post>& getPostList() const;

    // Getter for followers
    const std::vector<int>& getFollowers() const;

    void testInitUser();
};

#endif