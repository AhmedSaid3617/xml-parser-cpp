
#include <cassert>

#include "data/User.h"
#include "graph/SocialNetwork.h"

using namespace std;

int main() {
    // Create users like this.
    User user_1 = User(1, "User 1");
    User user_2 = User(2, "User 2");

    SocialNetwork my_sn = SocialNetwork();

    my_sn.add_user(&user_1);
    my_sn.add_user(&user_2);

    my_sn.add_follower(&user_1, &user_2);

    return 0;
}