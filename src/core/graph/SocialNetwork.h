#ifndef XML_PARSER_SOCIALNETWORK_H
#define XML_PARSER_SOCIALNETWORK_H

#include "Graph.h"

class User {
public:
    uint32_t id;
};

struct user_id_graph_key_t {
    uint32_t id;
    graph_key_t key;

    user_id_graph_key_t(uint32_t id, graph_key_t key): id(id), key(key) {
    }
};

class SocialNetwork: public Graph<User>{
    DynamicArray<user_id_graph_key_t> users;

    SocialNetwork() {
    }

    graph_key_t add_user(User * user) {
        graph_key_t key = add_vertex(user);
        users.add(new user_id_graph_key_t(user->id, key));

        return key;
    }

    Vertex<User> * get_user(uint32_t id) {
        return get_vertex(get_key(id));
    }

    Vertex<User> * get_user(graph_key_t key) {
        return get_vertex(key);
    }

    uint32_t get_users_count() {
        return get_vertices_count();
    }

    void add_follower(graph_key_t user, graph_key_t followee) {
        add_edge(new Edge<User>(get_user(user), get_user(followee)));
    }

    void add_follower(User * user, User * followee) {
        add_edge(new Edge<User>(get_user(get_key(user)), get_user(get_key(followee))));
    }

    graph_key_t get_key(User * user) {
        return get_key(user->id);
    }

    graph_key_t get_key(uint32_t id) {
        for (graph_key_t i = { 0 }; i.index < get_users_count(); ++i.index) {
            if (get_user(i)->get_data()->id == id)
                return i;
        }

        throw std::exception();
    }

    void print_followers(std::ostream os, uint32_t id) {
        Vertex<User> * user = get_user(id);

        for (int i = 0; i < user->get_edges_count(); ++i) {
            os << user->get_edge(i)->a->get_data()->id << " ";
        }
    }
};


#endif //XML_PARSER_SOCIALNETWORK_H
