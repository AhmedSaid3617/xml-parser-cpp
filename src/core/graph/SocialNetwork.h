#ifndef XML_PARSER_SOCIALNETWORK_H
#define XML_PARSER_SOCIALNETWORK_H

#include <vector>
#include "Graph.h"
#include "data/User.h"
#include "convert/XML_To_Tree2.h"
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

    void add_follower(User * follower, User * followee) {
        this->add_edge(new Edge<User>(get_user(get_key(follower)), get_user(get_key(followee))));
    }

    void add_follower(uint32_t follower, uint32_t followee) {
        this->add_edge(new Edge<User>(get_user(get_key(follower)), get_user(get_key(followee))));
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

    void extract_data(std::string &xml){
        XML_To_Tree2 xml_conv_obj = XML_To_Tree2(xml);
        TreeNode* xml_tree = xml_conv_obj.convert();
        std::vector<TreeNode *> users_nodes = xml_tree->children[0]->children;
        
        for(TreeNode* user_node: users_nodes){
            User* user = new User();
            std::vector<Post>* user_posts = new std::vector<Post>();

            // Loop over user tags.
            for (TreeNode* info_tag : user_node->children)
            {
                // Handle each info tag.
                if (info_tag->tag_name == "name")
                {
                    user->name = info_tag->tag_value;
                }
                else if (info_tag->tag_name == "id")
                {
                    user->id = std::stoi(info_tag->tag_value);
                }
                // Get all posts.
                else if(info_tag->tag_name == "posts")
                {
                    Post* post;
                    for(TreeNode* post_tag : info_tag->children){
                        post = new Post();
                        post->body = post_tag->children[0]->tag_value;

                        for (TreeNode* topic_tag : post_tag->children[1]->children)
                        {
                            post->topics.push_back(topic_tag->tag_value);
                        }
                        user_posts->push_back(*post);
                    }
                    user->post_list = *user_posts;
                }
            }

            // Add the user to the network.
            this->add_user(user);
        }

        // Loop again to add followers.
        for(TreeNode* user_node: users_nodes){
            // Get user followers and add them to the network.
            for(TreeNode* follower_tag: user_node->children[3]->children){
                // TODO: add follower to graph.
            }
        }
    }
};


#endif //XML_PARSER_SOCIALNETWORK_H
