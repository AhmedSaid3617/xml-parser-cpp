#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <vector>

#include "data/User.h"
#include "graph/SocialNetwork.h"

User* get_most_influential(SocialNetwork &social_network);
User* get_most_active(SocialNetwork &social_network);

#endif