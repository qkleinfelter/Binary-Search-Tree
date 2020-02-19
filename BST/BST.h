/*
	Quinn Kleinfelter
	EECS 2510-001 Non Linear Data Structures Spring 2020
	Dr. Thomas
	Last Edited: 2/19/20
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

	void traverse(int& index, node* n); // Goes through our list and prints out the contents of each node in order w/ an index
	node* findNode(string word); // Returns a pointer to the node with a given word inside it

	node* min(node* n); // Returns the node with the minimum string in the subtree of n
	node* max(node* n); // Returns the node with the maximum string in the subtree of n
	node* successor(node* n); // Returns the successor node of n

	bool isLeaf(node* n); // Checks if the node n is a leaf (has no children)
	bool isRoot(node* n); // Checks if the node n is the root of the tree
	int getChildCount(node* n); // Counts the number of children of n
	bool isLeftChild(node* n); // Checks if n is the left child of its parent
	bool isRightChild(node* n); // Checks if n is the right child of its parent
	
	void deleteNode(node* n); // Deletes node n and all nodes below it in the subtree - used in the destructor
};