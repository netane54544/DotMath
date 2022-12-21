#pragma once
#include <string>
using namespace std;

struct node 
{
	string id;
	string value;
	node* left;
	node* right;
};

class btree {
public:
	btree();
	btree(const string _id, const string _value);
	btree(const string _id, const string _value, node* left, node* right);

	node* findNode(const string& _id, const string& _value);
	const node* getRoot();
	void insert(string _id, string _value);
	string getId();
	void setLeft(node* left);
	void setRight(node* right);
	node* getLeft();
	node* getRight();
	void destroy_tree();
	void inorder_print();
	void postorder_print();
	void preorder_print();

private:
	node* findNode(const string& _id, const string& _value, node* root);
	void destroy_tree(node* leaf);
	void inorder_print(node* leaf);
	void postorder_print(node* leaf);
	void preorder_print(node* leaf);

	node* root;
};