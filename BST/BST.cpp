/*
	File: BST.cpp - Binary Search Tree Implementation of the Dynamic Set Operations
	c.f.: BST.h

	This class implements a Binary Search Tree of nodes as declared in BST.h.
	Each node contains a word, the number of times the word has appeared, a pointer
	to its parent, and to its left and right children.

	Author: Quinn Kleinfelter
	Class: EECS 2510-001 Non Linear Data Structures Spring 2020
	Instructor: Dr. Thomas
	Last Edited: 2/19/20
	Copyright: Copyright 2020 by Quinn Kleinfelter. All rights reserved.
*/

#include "BST.h"
#include <iostream>
#include <string>

BST::BST() 
{
	// Constructor, nothing to do here except make sure we don't have a root already.
	// This is redundant since it defaults to NULL, but we do it anyway for clarity
	root = NULL; // New Trees don't have a root until we insert an item.
}

BST::~BST()
{
	// Deletes the node at the root of the tree, and all nodes in its subtrees
	deleteNode(root);
	root = NULL; // After we have deleted all of our nodes make the root of the tree null
}

void BST::deleteNode(node* n)
{
	// This method uses a post-order traversal of all of the subtrees of node n to delete each node.
	// We must delete the nodes in the left and right subtrees first to ensure that we still have access to them
	// If we had deleted n at the beginning (pre-order) or in the middle (in-order), we would not have access to the left and/or right subtrees to delete anymore
	if (n->left != NULL) deleteNode(n->left); // If the left subtree isn't null, recursively delete it
	if (n->right != NULL) deleteNode(n->right); // If the right subtree isn't null, recursively delete it
	delete n; // After we've deleted the subtrees, delete n
}

void BST::insert(string word)
{
	// To add a word to the tree, we first traverse the tree, looking for the word
	// If we find it, we increment the counter, print and return; otherwise we store the position where it belongs,
	// create a new node, and append it to the bottom of the tree in the appropriate position
	node* x = root; // Start at the root
	node* y = nullptr; // Y will lag one step behind x, to ensure we keep track of where we fall off the tree
	while (x != NULL) 
	{
		y = x; // Save our current location in y
		if (x->word == word) 
		{
			// If the word in x matches our word we increment the count, print and return
			x->count++;
			cout << x->word << " " << x->count << endl;
			return;
		}
		// The word didn't match our word, so we check to see if the word we want to insert should go to the left or right of the current word,
		// and make x the pointer from our current words appropriate direction
		x = word < x->word ? x->left : x->right;
	}
	// We made it here so we must not have found the word in the list
	// Therefore, create a new node to store the word
	node* newNode = new node;
	newNode->count = 1; // Redundantly set the count in the new node to 1
	newNode->word = word; // Set the word in the new node to be the word we are adding to the list
	newNode->left = NULL; // We only add new nodes as leaves so set the left and right pointers to null
	newNode->right = NULL;
	newNode->parent = y; // Set the parent of our new node to be the location we were at before we dropped off
	
	if (y == NULL)
	{
		// y is only NULL if the root was null so our new node must be the first in the tree, therefore make it the root
		root = newNode;
	}
	else if (newNode->word < y->word)
	{
		// If newNode's word is less than the parents word, make it the left child
		y->left = newNode;
	}
	else
	{
		// Otherwise, we know it must go to the right of the parent
		y->right = newNode;
	}
	// Print out our new word and its count per spec.
	cout << newNode->word << " " << newNode->count << endl;
}

void BST::remove(string word)
{
	// This method removes a given word from the binary tree
	// If we find a node with the word we want to remove, first we check if its count is > 1, if so decrement the count, print and return
	// if the nodes count == 1 then we actually delete the node. If we can't find the node at all simply print out the word and -1 to indicate not found
	node* p = findNode(word); // Get a pointer to the node containing the word we want to remove 
	if (p == NULL)
	{
		// If we couldn't find a node with the word we want to remove, it doesn't exist in the tree, so print the word and -1 to indicate we didn't find it.
		cout << word << " -1" << endl;
		return;
	}
	// If the count in the node we found is > 1 we simply decrement the count and print out
	if (p->count > 1)
	{
		p->count = p->count--;
		cout << p->word << " " << p->count << endl;
		return;
	}
	// No children (leaf) node case
	if (isLeaf(p)) // If the node we want to remove is a leaf (no children)
	{
		if (isRoot(p)) 
		{
			// If the node we want to remove has no kids and is the root, simply delete the node, and set root to NULL, before printing and exiting
			delete p;
			root = NULL;
			cout << word << " 0" << endl;
			return;
		}
		else if (isLeftChild(p))
		{
			// Here we know the node is a leaf, that isn't the root, and is a left child of something
			p->parent->left = NULL; // Set the parent's left pointer to be NULL, before deleting p, printing and exiting
			delete p;
			cout << word << " 0" << endl;
			return;
		}
		else if (isRightChild(p))
		{
			// Here we know the node is a leaf, that isn't the root, and is a right child of something
			p->parent->right = NULL; // Set the parent's right pointer to be NULL, before deleting p, printing and exiting
			delete p;
			cout << word << " 0" << endl;
			return;
		}
	}
	// One Child Case
	if (getChildCount(p) == 1) // If the node we want to remove has a single child
	{
		if (isRoot(p))
		{
			// If we want to remove a node that is the root, and has one child, we simply make that child the root, delete p, print and exit
			root = p->left != NULL ? p->left : p->right; // If the left child of p is not null, set the root to that, otherwise set the root to the right child. We know it only has one child
			delete p; 
			cout << word << " 0" << endl;
			return;
		}
		else if (isLeftChild(p))
		{
			// Here we know the node has one child, is not the root and is the left child of another node
			node* q = p->left != NULL ? p->left : p->right; // Get the pointer to the child of the node we want to delete, using the ternary operator to get the child pointer that isn't null
			p->parent->left = q; // Set p's parent's left child to be q (p's child)
			q->parent = p->parent; // Set q's parent to be p's parent
			delete p; // Delete p
			cout << word << " 0" << endl; // Print out what we did
			return; // Exit
		}
		else if (isRightChild(p))
		{
			// Here we know the node has one child, is not the root, and is the right child of another node
			node* q = p->left != NULL ? p->left : p->right; // Get the pointer to the child of the node we want to delete, using the ternary operator to get the child pointer that isn't null
			p->parent->right = q; // Set p's parent's right child to be q (p's child)
			q->parent = p->parent; // Set q's parent to be p's parent
			delete p; // Delete p
			cout << word << " 0" << endl; // Print out what we did
			return; // Exit
		}
	}
	// Two Children Case
	else if (getChildCount(p) == 2) // If the node we want to remove has 2 children (final case!)
	{
		// First, we want to get the successor of the node want to remove
		node* q = successor(p);
		if (q == p->right) // If p's successor (q) is p's immediate right child
		{
			// Copy q's contents into p and set p's right child to be q's right child
			// Effectively splicing out q, then delete q
			p->word = q->word; // Copy q's word into p
			p->count = q->count; // Copy q's count into p
			p->right = q->right; // Make p's right child be q's right child
			delete q; // Delete q now that we have spliced it out
			cout << word << " 0" << endl; // Print out what we did
			return; // Exit
		}
		else
		{
			// Now we know that its successor must be somewhere in its right subtree but not immediately
			// Here we want to copy q's contents into p and set p's right child's left child to be q's right child
			// This effectively splices out q, so we can safely delete it
			p->word = q->word; // Copy q's word into p
			p->count = q->count; // Copy q's count into p
			p->right->left = q->right; // Make p's right child's left child q's right child, splicing out q
			delete q; // Delete q now that we've spliced it out
			cout << word << " 0" << endl; // Print out what we did
			return; // Exit
		}
	}
}

void BST::search(string word)
{
	// This method searches the tree for "word". If its found we print out the word and its count.
	// If we are unable to find the word, i.e. it doesn't exist, we print out the word and a 0 count.
	node* p = root; // Start looking at the root of our tree
	while (p != NULL) // As long as we haven't fallen off of a leaf yet, keep looping
	{
		if (p->word == word) // If we found the word, print it out!
		{
			cout << p->word << " " << p->count << endl;
		}
		// If we didn't find the word yet, check if it should be to the left or right of the current word,
		// then set p to the left or right node.
		p = word < p->word ? p->left : p->right;
		return;
	}
	cout << word << " 0"<< endl; // If we didn't find the word in the list, and we fell of the edge of it, print the word with 0 count
}

void BST::list()
{
	// This method lists out our nodes in the tree through a recursive in-order traversal
	if (root == NULL)
	{
		// If our root is null, then we must have an empty set, so print out as such and exit
		cout << "Set is empty" << endl;
		return;
	}
	// If we do have stuff in the tree, print out "Set contains: " per spec, before setting up an index variable and calling our recursive traversal method
	cout << "Set contains: ";
	int index = 0;
	traverse(index, root); // Starts our recursive traversal on the root, with an initial index of 0 (this is going to be incremented before each print, and we want an initial index of 1)
	cout << endl; // Print out an endline since we don't want to do so inside the traversal
}

void BST::traverse(int& index, node* n)
{
	// This method does a recursive in-order traversal of the nodes in the tree to print them out with an index and their counts
	// We also pull in an index parameter, passed as a reference, so that no matter which recursive call we are in, the correct index will be printed with proper incrementing
	// This indexing also could have been implemented as a class variable in the BST, but I believe this passing an int by reference makes it cleaner since we don't have a class variable that is barely used
	if (n == NULL) return; // If we have a null node, we don't have any work to do, simply return out
	if (n->left != NULL)
	{
		// If our left child is not null, we want to recursively traverse that child
		traverse(index, n->left);
		cout << ", "; // We know that there will be something that comes after this, because our current node isn't null, so we want to add a comma after our left child is printed
	}
	cout << "(" << ++index << ") " << n->word << " " << n->count; // Print out the index (pre-incremented), followed by our word and its count
	if (n->right != NULL)
	{
		// If our right child is not null, we want to recursively traverse that child
		cout << ", "; // We print the comma here, and not immediately after printing the current child, because we want to be sure that there is something to the right before we do so
		traverse(index, n->right); 
	}
}

BST::node* BST::findNode(string word)
{
	node* p = root;
	while (p != NULL)
	{
		if (p->word == word) return p;
		p = word < p->word ? p->left : p->right;
	}
	return p;
}

void BST::min()
{
	node* p = root;
	if (p == NULL)
	{
		cout << endl;
		return;
	}
	p = min(p);
	cout << p->word << endl;
}

BST::node* BST::min(node* n) 
{
	while (n->left != NULL)
	{
		n = n->left;
	}
	return n;
}

void BST::max()
{
	node* p = root;
	if (p == NULL)
	{
		cout << endl;
		return;
	}
	p = max(p);
	cout << p->word << endl;
}

BST::node* BST::max(node* n)
{
	while (n->right != NULL)
	{
		n = n->right;
	}
	return n;
}

void BST::next(string word)
{
	node* p = findNode(word);
	if (p == NULL) 
	{
		cout << endl;
		return;
	}
	if (p->right != NULL) {
		node* successor = min(p->right);
		cout << successor->word << endl;
		return;
	}
	node* q = p->parent;
	while (q != NULL && p == q->right)
	{
		p = q;
		q = q->parent;
	}
	if (q != NULL)
	{
		cout << q->word << endl;
	}
	else
	{
		cout << endl;
		return;
	}
}

BST::node* BST::successor(node* n)
{
	if (n->right != NULL)
	{
		return min(n->right);
	}
	node* p = n->parent;
	while (p != NULL && n == p->right)
	{
		n = p;
		p = p->parent;
	}
	return p;
}

void BST::prev(string word)
{
	node* p = findNode(word);
	if (p == NULL)
	{
		cout << endl;
		return;
	}
	if (p->left != NULL) {
		node* successor = max(p->left);
		cout << successor->word << endl;
		return;
	}
	node* q = p->parent;
	while (q != NULL && p == q->left)
	{
		p = q;
		q = q->parent;
	}
	if (q != NULL)
	{
		cout << q->word << endl;
	}
	else
	{
		cout << endl;
		return;
	}
}

void BST::parent(string word)
{
	node* p = findNode(word);
	if (p == NULL || p->parent == NULL)
	{
		cout << endl;
		return;
	}
	cout << p->parent->word << endl;
}

void BST::child(string word)
{
	node* p = findNode(word);
	if (p == NULL)
	{
		cout << endl;
		return;
	}
	if (p->left != NULL && p->right != NULL)
	{
		cout << p->left->word << " " << p->right->word << endl;
		return;
	}
	else if (p->left == NULL && p->right != NULL)
	{
		cout << "NULL " << p->right->word << endl;
		return;
	}
	else if (p->left != NULL && p->right == NULL)
	{
		cout << p->left->word << " NULL" << endl;
		return;
	}
	else {
		cout << "NULL NULL" << endl;
		return;
	}
}

bool BST::isLeaf(node* n)
{
	return n->left == nullptr && n->right == nullptr;
}

bool BST::isRoot(node* n)
{
	return n == root;
}

bool BST::isLeftChild(node* n)
{
	return n == n->parent->left;
}

bool BST::isRightChild(node* n)
{
	return n == n->parent->right;
}

int BST::getChildCount(node* n)
{
	if (n == nullptr) return -1; // can�t count children of no node!
	if (isLeaf(n)) return 0; // leaves have no child nodes
	if (n->left != nullptr && n->right != nullptr) return 2; // 2 children
	if (n->left != nullptr && n->right == nullptr) return 1; // 1 (l child)
	if (n->left == nullptr && n->right != nullptr) return 1; // 1 (r child)
	// it should not be possible to get here
	cout << "Internal error in getChildCount\n"; // practice defensive
	exit(1);									 // programming!
}