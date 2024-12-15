#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <vector>

#include "data/User.h"
#include "graph/SocialNetwork.h"

std::vector<User> get_mutual(SocialNetwork &social_network, std::vector<User> &users);
std::vector<User> get_suggested(SocialNetwork &social_network, User &user);

#endif