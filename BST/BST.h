/*
	Quinn Kleinfelter
	EECS 2510-001 Non Linear Data Structures Spring 2020
	Dr. Thomas
	Last Edited: 2/14/20
*/


#pragma once
#include <string>
using namespace std;
class BST {
public:
	BST();
	~BST();
	void insert(string word); // Adds the word to the tree
	void remove(string word); // Removes the word from the tree, or decrements its count if count > 1
	void search(string word); // Searches for the word and prints how many of them we have
	void min(); // Outputs the minimum string in the tree
	void max(); // Outputs the maximum string in the tree
	void next(string word); // Outputs the successor of a given string if it is in the set, or a blank line
	void prev(string word); // Outputs the predecessor of a given string if it is in the set, or a blank line
	void parent(string word); // Outputs the string contained in the parent of the node whose key is the input, or a blank line
	void child(string word); // Outputs the string(s) contained in the child(ren) of the node whose key is the input, or NULL
	void list(); // Prints out the list (in order)

private:
	// Basic node struct used as the baseline of the BST
	struct node
	{
		string word; // The word (key) of the node
		int count = 1; // Count of how many times we have inserted the word into the set, one by default
		node* left = NULL; // A pointer to the left child of the node, NULL by default
		node* right = NULL; // A pointer to the right child of the node, NULL by default
		node* parent = NULL; // A pointer to the parent of the node, NULL by default
	};

	node* root = NULL; // A pointer to the root of our tree, NULL until we add a node to the tree

	void traverse(int& index, node* n);
	node* findNode(string word); // Returns a pointer to the node with a given word inside it

	node* min(node* n);
	node* max(node* n);
};