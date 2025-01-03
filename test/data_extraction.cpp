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
    <user>
        <id>4</id>
        <name>Salma Hussein</name>
        <posts>
            <post>
                <body>
                    Salma's 1st post.
                </body>
                <topics>
                    <topic>
                        technology
                    </topic>
                </topics>
            </post>
            <post>
                <body>
                    Salma's 2nd post.
                </body>
                <topics>
                    <topic>
                        salma_topic.
                    </topic>
                </topics>
            </post>
        </posts>
        <followers>
            <follower>
                <id>1</id>
            </follower>
            <follower>
                <id>3</id>
            </follower>
        </followers>
    </user>
    <user>
        <id>5</id>
        <name>Omar Khaled</name>
        <posts>
            <post>
                <body>
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
                </body>
                <topics>
                    <topic>
                        travel
                    </topic>
                    <topic>
                        photography
                    </topic>
                </topics>
            </post>
        </posts>
        <followers>
            <follower>
                <id>4</id>
            </follower>
        </followers>
    </user>
</users>)";

    social_network.extract_data(xml);
    
    // Followers of Ahmed Ali.
    std::vector<User> user_1_followers = social_network.get_followers(1);
    assert(user_1_followers[0].getName() == "Yasser Ahmed");
    assert(user_1_followers[1].getName() == "Mohamed Sherif");

    // Following of Salma Hussein.
    std::vector<User> user_4_following = social_network.get_following(4);
    assert(user_4_following[0].getName() == "Omar Khaled");

    // Search in one post.
    std::vector<Post*> posts = social_network.get_posts();

    // Search in all posts.
    std::vector<Post*> salma_posts = social_network.search_posts("Salma");
    assert(salma_posts[0]->contains("Salma"));

    std::vector<Post*> economy_posts = social_network.search_topics("economy");
    cout << economy_posts[0]->getTopics()[0] << endl;

    std::vector<int> my_users_ids = {2, 3};
    vector<User*> mutuals = social_network.who_does_n_users_follow(my_users_ids);
    for(User* user : mutuals){
        cout << user->getId() << endl;
    }
    mutuals = social_network.who_does_n_users_follow(my_users_ids);
    for(User* user : mutuals){
        cout << user->getId() << endl;
    }

    return 0;
}