#ifndef XML_PARSER_SOCIALNETWORK_H
#define XML_PARSER_SOCIALNETWORK_H

#include <vector>
#include "Graph.h"
#include "data/User.h"
#include "hashtable.h"
#include <iostream>

struct user_id_graph_key_t {
    uint32_t id;
    graph_key_t key;

    user_id_graph_key_t(uint32_t id, graph_key_t key): id(id), key(key) {
    }
};

/**
 * @note Edge convention is that a follows b. (a is the follower, b is being followed).
*/
class SocialNetwork: public Graph<User>{
    DynamicArray<user_id_graph_key_t> users;

private:
    using Graph<User>::get_vertex;
    using Graph<User>::get_vertices_count;
    using Graph<User>::add_vertex;
    using Graph<User>::add_edge;

    Vertex<User> * get_user(uint32_t id) {
        return this->get_vertex(get_key(id));
    }

    Vertex<User> * get_user(graph_key_t key) {
        return this->get_vertex(key);
    }

    graph_key_t get_key(User * user) {
        return get_key(user->getId());
    }

    graph_key_t get_key(uint32_t id) {
        for (graph_key_t i = { 0 }; i.index < get_users_count(); ++i.index) {
            if (get_user(i)->get_data()->getId() == id)
                return i;
        }

        throw std::exception();
    }

public:
    SocialNetwork() = default;

    graph_key_t add_user(User * user) {
        graph_key_t key = this->add_vertex(user);
        users.add(new user_id_graph_key_t(user->getId(), key));

        return key;
    }

    uint32_t get_users_count() {
        return this->get_vertices_count();
    }

    void add_follower(graph_key_t user, graph_key_t followee) {
        this->add_edge(new Edge<User>(get_user(followee), get_user(user)));
    }

    void add_follower(User * follower, User * followed) {
        this->add_edge(new Edge<User>(get_user(get_key(follower)), get_user(get_key(followed))));
    }

    std::vector<User> get_followers(uint32_t id) {
        Vertex<User> * user = get_user(id);
        std::vector<User> result;

        for (int i = 0; i < user->get_edges_count(); ++i) {
            if (user->get_edge(i)->a != user)
                result.push_back(*user->get_edge(i)->a->get_data());
        }

        return result;
    }

    std::vector<User> get_following(uint32_t id) {
        Vertex<User> * user = get_user(id);
        std::vector<User> result;

        for (int i = 0; i < user->get_edges_count(); ++i) {
            if (user->get_edge(i)->b != user)
                result.push_back(*user->get_edge(i)->b->get_data());
        }

        return result;
    }

    void print_following(std::ostream& os, uint32_t id) {
        Vertex<User> * user = get_user(id);

        for (int i = 0; i < user->get_edges_count(); ++i) {
            if (user->get_edge(i)->b != user)
                os << user->get_edge(i)->b->get_data()->getId() << " ";
        }
    }

    void print_followers(std::ostream& os, uint32_t id) {
        Vertex<User> * user = get_user(id);

        for (int i = 0; i < user->get_edges_count(); ++i) {
            if (user->get_edge(i)->a != user)
                os << user->get_edge(i)->a->get_data()->getId() << " ";
        }
    }

    std::vector<const User *> get_users() {
        std::vector<const User *> result;

        for (graph_key_t key = {0}; key.index < get_users_count(); ++key.index) {
            result.push_back(get_user(key)->get_data());
        }

        return result;
    }

    const User* get_most_active_user() {
        std::vector<const User *> searchable_users=get_users();
        uint32_t max=0,size_of_followees_list;
        const User* most_active_user=NULL;

        for (auto searchable_user: searchable_users) {
            std::vector<User> user_followees= get_following(searchable_user->getId());
            size_of_followees_list=user_followees.size();
            if (max<size_of_followees_list) {
                max=size_of_followees_list;
                most_active_user = searchable_user;
            }
        }
        return most_active_user;
    }
    const User* get_most_influencer_user() {
        std::vector<const User *> searchable_users=get_users();
        uint32_t max=0,size_of_followers_list;
        const User* most_influencer_user=NULL;

        for (auto searchable_user: searchable_users) {
            std::vector<User> user_followers= get_followers(searchable_user->getId());
            size_of_followers_list=user_followers.size();
            if (max<size_of_followers_list) {
                max=size_of_followers_list;
                most_influencer_user = searchable_user;
            }
        }
        return most_influencer_user;
    }

    std::vector<User *> who_does_n_users_follow(std::vector<User > users) {
        std::vector<User *> common_followees;
        uint32_t size_of_users_list=users.size();
        users_hash_table hash_t;

        for (auto searchable_user: users) {
            std::vector<User> user_followers= get_following(searchable_user.getId());
            for (auto followee: user_followers) {
                hash_t[followee.getId()]++;
            }
        }
        std::vector<int> common_ids=hash_t.get_the_keys_with_same_value(size_of_users_list);
        for (auto id: common_ids) {
            common_followees.push_back(get_user(id)->get_data());
        }
        return common_followees;
    }
};


#endif //XML_PARSER_SOCIALNETWORK_H
