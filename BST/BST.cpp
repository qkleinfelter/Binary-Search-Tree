/*
	File: BST.cpp - Binary Search Tree Implementation of the Dynamic Set Operations
	c.f.: BST.h

	This class implements a Binary Search Tree of nodes as declared in BST.h.
	Each node contains a word, the number of times the word has appeared, a pointer
	to its parent, and to its left and right children.

	Author: Quinn Kleinfelter
	Class: EECS 2510-001 Non Linear Data Structures Spring 2020
	Instructor: Dr. Thomas
	Last Edited: 2/14/20
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
	node* x = root;
	node* y = nullptr;
	while (x != NULL)
	{
		y = x;
		if (x->word == word)
		{
			x->count++;
			cout << x->word << " " << x->count << endl;
			return;
		}
		x = word < x->word ? x->left : x->right;
	}
	node* newNode = new node;
	newNode->count = 1;
	newNode->word = word;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = y;
	
	if (y == NULL)
	{
		root = newNode;
	}
	else if (newNode->word < y->word)
	{
		y->left = newNode;
	}
	else
	{
		y->right = newNode;
	}
	cout << newNode->word << " " << newNode->count << endl;
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
		return;
	}
	cout << word << " 0"<< endl; // If we didn't find the word in the list, and we fell of the edge of it, print the word with 0 count
}

void BST::list()
{
	if (root == nullptr)
	{
		cout << "Set is empty" << endl;
		return;
	}
	cout << "Set contains: ";
	int index = 0;
	traverse(index, root);
}

void BST::traverse(int& index,node* n)
{
	if (n == NULL) return;
	if (n->left != NULL)
	{
		traverse(index, n->left);
		cout << ", ";
	}
	cout << "(" << ++index << ") " << n->word << " " << n->count++;
	if (n->right != NULL)
	{
		cout << ", ";
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
	cout << q->word << endl;
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
	cout << q->word << endl;

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
	cout << p->left->word << " " << p->right->word << endl;
}
