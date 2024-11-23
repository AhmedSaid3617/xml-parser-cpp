    #include "main.h"
    TreeNode::TreeNode(){
        tag_name="";
        tag_value="";
        parent=NULL;
    }
    TreeNode::TreeNode(string name,string value,TreeNode *parent){
        tag_name=name;
        tag_value=value;
        this->parent=parent;
    }
    TreeNode::TreeNode(string name,string value,TreeNode *parent,vector<TreeNode *> children){
        tag_name=name;
        tag_value=value;
        this->parent=parent;
        set_children(children);
    }
    void TreeNode::set_children(vector<TreeNode *> children){
        for (int i=0;i<children.size();i++){
            (this->children).push_back(children[i]);
    }
    }
    bool TreeNode::children_same_type(){
        for (int i=0;i<children.size()-1;i++){
           if ((children[i]->tag_name)!=(children[i+1]->tag_name)) return false;
    }
        return true;
    }