#ifndef XML_PARSER_SOCIALNETWORK_H
#define XML_PARSER_SOCIALNETWORK_H

#include <vector>
#include "Graph.h"
#include "data/User.h"
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
};


#endif //XML_PARSER_SOCIALNETWORK_H
