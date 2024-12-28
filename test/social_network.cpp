#include <cassert>

// uncomment if you have graphviz libraries and added
// parameters to CMake
//#define TEST_VISUALIZATION

#include "data/User.h"
#include "graph/SocialNetwork.h"

#ifdef TEST_VISUALIZATION
    #include "graph/FileExportGraphVisualization.h"
#endif

using namespace std;

int main()
{
    // Create users like this.
    User user_said = User(1, "Said");
    User user_fares = User(2, "Fares");
    User user_hussein = User(3, "Hussein");
    User user_shams = User(4, "Shams");
    User user_abdo = User(5, "Abdo");
    User user_kareem = User(6, "Kareem");
    User user_omar = User(7, "Omar");
    User user_youssef = User(8, "Youssef");

    SocialNetwork social_network = SocialNetwork();

    social_network.add_user(&user_said);
    social_network.add_user(&user_fares);
    social_network.add_user(&user_hussein);
    social_network.add_user(&user_shams);
    social_network.add_user(&user_abdo);
    social_network.add_user(&user_kareem);
    social_network.add_user(&user_omar);
    social_network.add_user(&user_youssef);

    social_network.add_follower(&user_said, &user_fares);
    social_network.add_follower(&user_fares, &user_shams);
    social_network.add_follower(&user_said, &user_shams);
    social_network.add_follower(&user_fares, &user_kareem);
    social_network.add_follower(&user_shams, &user_fares);
    social_network.add_follower(&user_hussein, &user_fares);
    social_network.add_follower(&user_abdo, &user_fares);
    social_network.add_follower(&user_kareem, &user_abdo);
    social_network.add_follower(&user_kareem, &user_youssef);
    social_network.add_follower(&user_youssef, &user_kareem);
    social_network.add_follower(&user_youssef, &user_shams);
    social_network.add_follower(&user_shams, &user_omar);
    social_network.add_follower(&user_omar, &user_youssef);
    social_network.add_follower(&user_kareem, &user_hussein);

    vector<User> fares_followers = social_network.get_followers(user_fares.getId());
    cout<< "Fares's followers:" << endl;
    for (int i = 0; i < fares_followers.size(); i++)
    {
        cout<< fares_followers[i].getName() << endl;
    }

    vector<User> kareem_following = social_network.get_following(user_kareem.getId());
    cout<< endl << "Kareem's following:" << endl;
    for (int i = 0; i < kareem_following.size(); i++)
    {
        cout<< kareem_following[i].getName() << endl;
    }

    const User* mostactive=social_network.get_most_active_user();
    cout<<"most active     "<<mostactive->getId()<<endl<<mostactive->getName()<<endl;
    assert(mostactive == &user_kareem);

    const User* mostinfluincer=social_network.get_most_influencer_user();
    cout<<"most influencer     "<<mostinfluincer->getId()<<endl<<mostinfluincer->getName()<<endl;
    assert(mostinfluincer == &user_fares);

    std::vector<User> my_users;
    my_users.push_back(user_abdo);
    my_users.push_back(user_said);
    my_users.push_back(user_hussein);

    std::vector<int> my_users_ids = {6, 7};

    vector<User *> common=social_network.who_does_n_users_follow(my_users_ids);
    for (int i = 0; i < common.size(); i++)
    {
        cout<< "common with omar kareem follwers    "<<common[i]->getName() << endl;
    }
    assert(common[0] == &user_fares);

    // Test suggest_users_to_follow for Said

    std::vector<User*> suggestions = social_network.suggest_users_to_follow(&user_said);

    // Print the suggestions
    cout<<"Suggested users for " << user_said.getName() << " to follow: ";
    assert(suggestions[1] == &user_omar);
    
    for (User* user : suggestions)
    {
        std::cout << user->getName() << " ";
    }
    cout<<endl;

#ifdef TEST_VISUALIZATION
    auto visitor = new FileExportGraphVisualization("here.png");
    social_network.accept(visitor);
#endif

return 0;
}