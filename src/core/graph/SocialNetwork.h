#ifndef XML_PARSER_SOCIALNETWORK_H
#define XML_PARSER_SOCIALNETWORK_H

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
class SocialNetwork{
    DynamicArray<user_id_graph_key_t> users;
    Graph<User> users_graph = Graph<User>();

public:
    SocialNetwork() {
    }

    graph_key_t add_user(User * user) {
        graph_key_t key = users_graph.add_vertex(user);
        users.add(new user_id_graph_key_t(user->getId(), key));

        return key;
    }

    Vertex<User> * get_user(uint32_t id) {
        return users_graph.get_vertex(get_key(id));
    }

    Vertex<User> * get_user(graph_key_t key) {
        return users_graph.get_vertex(key);
    }

    uint32_t get_users_count() {
        return users_graph.get_vertices_count();
    }

    void add_follower(graph_key_t user, graph_key_t followee) {
        users_graph.add_edge(new Edge<User>(get_user(followee), get_user(user)));
    }

    void add_follower(User * user, User * followee) {
        users_graph.add_edge(new Edge<User>(get_user(get_key(user)), get_user(get_key(followee))));
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

    void print_following(std::ostream& os, uint32_t id) {
        Vertex<User> * user = get_user(id);

        for (int i = 0; i < user->get_edges_count(); ++i) {
            if (user->get_edge(i)->b != user)
                os << user->get_edge(i)->b->get_data()->getId() << " ";
        }
    }

    void print_followers(uint32_t id) {
        Vertex<User> * user = get_user(id);

        for (int i = 0; i < user->get_edges_count(); ++i) {
            if (user->get_edge(i)->a != user)
                os << user->get_edge(i)->a->get_data()->getId() << " ";
        }
    }
};


#endif //XML_PARSER_SOCIALNETWORK_H
