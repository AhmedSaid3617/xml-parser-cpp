#include "main.h"
TreeNode* TreeNode::Parse_XML(const string data) {
	// store the root node in order to delete all the nodes after parsing 
	TreeNode* root = new TreeNode();
	TreeNode* curr_node = root;
	TreeNode* prev_node = root;

	int i = 0;
	string curr_tag, curr_text{};

	// Parsing loop and creating XML tree structure
	while (data[i] != '\0') {
		if (data[i] == '<') {
			if (data[i + 1] == '/')
				goto up;
			i++;
			//obtaining the tag
			while (data[i] != '>')
			{
				curr_tag += data[i];
				i++;
				// neglecting the tag attributes
				if (data[i] == ' ')
					break;
			}
			i++;
			// obtaining the text
			while (data[i] != '<')
			{
				curr_text += data[i];
				i++;
			}
			if (root->tag_name == "") {
				root->tag_name = curr_tag;
				root->tag_value = curr_text;
			}
			// if the root is created then we should create child node to that root
			else {
				prev_node = curr_node;
				curr_node = new TreeNode(curr_tag, curr_text,prev_node);
				prev_node->children.push_back(curr_node);
			}
			curr_tag.clear();
			curr_text.clear();

			// after obtaining the text and creating our node, we either gonna hit a closing tag for the our opened tag or another new tag
			// checking if we hit the closing tag for our opened tag and we are not at the root cause the root has no parent
		up:
			if (data[i + 1] == '/')
			{
				i++;
				while (data[i] != '<')
				{
					i++;
					if (i == data.size())
						break;
				}
				if (curr_node != root)
					curr_node = curr_node->parent;
			}
			continue;
		}
		i++;
	}
	// returning the root node of the constructed tree
	return root;
}

// freeing all the XML tree allocated nodes
void  TreeNode::Free_XML(TreeNode* root) {
	if (root) {
		for (auto& child : root->children) {
			Free_XML(child);
			delete child;
		}
		if (root->parent == NULL)
			delete root;
	}
}
string insert_taps(int level){
	string out="";
for (int i=0;i<level;i++){
	out+= "\t";
}
return out;
}