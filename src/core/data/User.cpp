#include "User.h"
#include <iostream>

// Empty constructor
User::User() : id(0), name(""), post_list() {}

// Parameterized constructor
User::User(int id, std::string name) 
    : id(id), name(name) {}

// Getter for id
int User::getId() const {
    return id;
}

// Getter for name
std::string User::getName() const {
    return name;
}

// Getter for post_list
const std::vector<Post>& User::getPostList() const {
    return post_list;
}

//TODO: might remove setters.
// Private setter implementations
void User::setId(int newId) {
    id = newId;
}

void User::setName(const std::string& newName) {
    name = newName;
}

void User::setPostList(const std::vector<Post>& newPostList) {
    post_list = newPostList;
}

// Testing method
void User::testInitUser() {
    std::cout << "Testing User initialization..." << std::endl;
}
