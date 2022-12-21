#include "Tree.h"
#include <iostream>
#include <queue>

btree::btree() {
	root = nullptr;
}

btree::btree(const string _id, const string _value)
{
	root = new node();
	root->id = _id;
	root->value = _value;
}

btree::btree(const string _id, const string _value, node* left, node* right)
{
	root = new node();
	root->id = _id;
	root->value = _value;
	root->left = left;
	root->right = right;
}

string btree::getId() 
{
	return root->id;
}

node* btree::findNode(const string& _id, const string& _value) 
{
	return findNode(_id, _value, root);
}

node* btree::findNode(const string& _id, const string& _value, node* _root)
{
	if (_root->id == _id && _root->value == _value)
		return _root;

	auto x1 = findNode(_id, _value, getLeft());
	auto x2 = findNode(_id, _value, getRight());

	return (x1 == nullptr) ? x2 : x1;
}

void btree::insert(string _id, string _value)
{
	node* root = this->root;

	queue<node*> q;
	q.push(root);

	// Do level order traversal until we find an empty place.
	while (!q.empty()) {
		node* root = q.front();
		q.pop();

		if (!root->left) {
			root->left = new node();
			root->left->id = _id;
			root->left->value = _value;
			break;
		}
		else
			q.push(root->left);

		if (!root->right) {
			root->right = new node();
			root->right->id = _id;
			root->right->value = _value;
			break;
		}
		else
			q.push(root->right);
	}
}

void btree::setLeft(node* left) 
{
	root->left = left;
}

void btree::setRight(node* right) 
{
	root->right = right;
}

node* btree::getLeft() 
{
	return root->left;
}

node* btree::getRight() 
{
	return root->right;
}

void btree::destroy_tree(node* leaf) {
	if (leaf != nullptr) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

const node* btree::getRoot() 
{
	return root;
}

void btree::destroy_tree() {
	destroy_tree(root);
	//delete(root);
}

void btree::inorder_print() {
	inorder_print(root);
	cout << "\n";
}

void btree::inorder_print(node* leaf) {
	if (leaf != nullptr) {
		inorder_print(leaf->left);
		cout << leaf->value << ",";
		inorder_print(leaf->right);
	}
}

void btree::postorder_print() {
	postorder_print(root);
	cout << "\n";
}

void btree::postorder_print(node* leaf) {
	if (leaf != nullptr) {
		inorder_print(leaf->left);
		inorder_print(leaf->right);
		cout << leaf->value << ",";
	}
}

void btree::preorder_print() {
	preorder_print(root);
	cout << "\n";
}

void btree::preorder_print(node* leaf) {
	if (leaf != nullptr) {
		cout << leaf->value << ",";
		inorder_print(leaf->left);
		inorder_print(leaf->right);
	}
}