/*
	File: BST.cpp - Binary Search Tree Implementation of the Dynamic Set Operations
	c.f.: BST.h

	This class implements a Binary Search Tree of nodes as declared in BST.h.
	Each node contains a word, the number of times the word has appeared, a pointer
	to its parent, and to its left and right children.

	Author: Quinn Kleinfelter
	Class: EECS 2510-001 Non Linear Data Structures Spring 2020
	Instructor: Dr. Thomas
	Last Edited: 2/13/20
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
	// Destructor
}

void BST::insert(string word)
{
}

void BST::remove(string word)
{
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
	}
	cout << word << "0" << endl; // If we didn't find the word in the list, and we fell of the edge of it, print the word with 0 count
}

void BST::traverse(node* node)
{
	if (node == NULL) return;
	traverse(node->left);
	cout << node->word << endl;
	traverse(node->right);
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
	while (p->left != NULL)
	{
		p = p->left;
	}
	cout << p->word << endl;
}

void BST::max()
{
	node* p = root;
	while (p->right != NULL)
	{
		p = p->right;
	}
	cout << p->word << endl;
}

void BST::next(string word)
{
	node* p = findNode(word);
	if (p == NULL) 
	{
		cout << endl;
		return;
	}

}

void BST::prev(string word)
{
	node* p = findNode(word);
	if (p == NULL)
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
	cout << p->parent << endl;
}

void BST::child(string word)
{
	node* p = findNode(word);
	if (p == NULL)
	{
		cout << endl;
		return;
	}
	cout << p->left->word << " " << p->right->word << endl;
}

void BST::list()
{
}
