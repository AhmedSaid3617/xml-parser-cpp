// User.cpp
#include "User.h"

// Empty constructor
User::User()
    : id(0), name(""), post_list(), followers() {}

User::User(int id, std::string name, const std::vector<int> &followers)
{
    this->id = id;
    this->name = name;
    this->followers = followers;
}

// Private setters
// TODO: might remove the setters.
void User::setId(int newId)
{
    id = newId;
}

void User::setName(const std::string &newName)
{
    name = newName;
}

void User::setPostList(const std::vector<Post> &newPostList)
{
    post_list = newPostList;
}

void User::setFollowers(const std::vector<int> &newFollowers)
{
    followers = newFollowers;
}

// Getters
int User::getId() const
{
    return id;
}

std::string User::getName() const
{
    return name;
}

const std::vector<Post> &User::getPostList() const
{
    return post_list;
}

const std::vector<int> &User::getFollowers() const
{
    return followers;
}
