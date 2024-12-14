#include <cassert>
#include "graph/SocialNetwork.h"
#include <iostream>

int main() {
    SocialNetwork network;

    User shams = User(1, "Ahmed Said");
    User saeed = User(2, "Shams");
    User karim = User(3, "Kareem");
    User fares = User(4, "Farse");

    network.add_user(&shams);
    network.add_user(&saeed);
    network.add_user(&karim);
    network.add_user(&fares);

    network.add_follower(&shams, &saeed);
    network.add_follower(&karim, &saeed);
    network.add_follower(&fares, &saeed);
    network.add_follower(&saeed, &shams);

    network.print_followers(std::cout, 2); // Print saeed followers {1, 3, 4}
    std::cout << std::endl;
    network.print_following(std::cout, 2); // Print saeed following whom {1}


    return 0;
}