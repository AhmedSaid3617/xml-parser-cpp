/**
 * Template test file, copy and add to CMakeLists as test
 */

#include <cassert>
#include <string>
#include "graph/SocialNetwork.h"

int main() {
    // Remove the following line, test your code features using assert(SOME BOOLEAN EXPRESSION)
    // e.g. `assert(myAdder(1, 2) == (1 + 2));`
    
    SocialNetwork social_network = SocialNetwork();

    std::string xml = R"(<users>
    <user>
        <id>1</id>
        <name>Ahmed Ali</name>
        <posts>
            <post>
                <body>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
                </body>
                <topics>
                    <topic>
                        economy
                    </topic>
                    <topic>
                        finance
                    </topic>
                </topics>
            </post>
            <post>
                <body>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
                </body>
                <topics>
                    <topic>
                        solar_energy
                    </topic>
                </topics>
            </post>
        </posts>
        <followers>
            <follower>
                <id>2</id>
            </follower>
            <follower>
                <id>3</id>
            </follower>
        </followers>
    </user>
    <user>
        <id>2</id>
        <name>Yasser Ahmed</name>
        <posts>
            <post>
                <body>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
                </body>
                <topics>
                    <topic>
                        education
                    </topic>
                </topics>
            </post>
        </posts>
        <followers>
            <follower>
                <id>1</id>
            </follower>
        </followers>
    </user>
    <user>
        <id>3</id>
        <name>Mohamed Sherif</name>
        <posts>
            <post>
                <body>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
                </body>
                <topics>
                    <topic>
                        sports
                    </topic>
                </topics>
            </post>
        </posts>
        <followers>
            <follower>
                <id>1</id>
            </follower>
        </followers>
    </user>
</users>)";

    social_network.extract_data(xml);
    /* for(const User* user: social_network.get_users()){
        std::cout << user->getPostList()[0].getTopics()[0];
    } */
    return 0;
}