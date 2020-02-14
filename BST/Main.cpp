/*
	Quinn Kleinfelter
	EECS 2510-001 Non Linear Data Structures Spring 2020
	Dr. Thomas
	Last Edited: 2/14/20
*/

#include <iostream>
#include "BST.h"


string toLower(const string& s)
{
	string temp(s);
	for (int i = 0; i < s.length(); i++)
		temp[i] = tolower(s[i]);
	return temp;
}


int main()
{
	BST* tree = new BST();
	while (true)
	{
		string command = "";
		string arg = "";
		cin >> command >> arg;
		command = toLower(command);
		if (command == "insert")
		{
			tree->insert(arg);
		}
		else if (command == "delete")
		{
			tree->remove(arg);
		}
		else if (command == "search")
		{
			tree->search(arg);
		}
		else if (command == "min")
		{
			tree->min();
		}
		else if (command == "max")
		{
			tree->max();
		}
		else if (command == "next")
		{
			tree->next(arg);
		}
		else if (command == "prev")
		{
			tree->prev(arg);
		}
		else if (command == "list")
		{
			tree->list();
		}
		else if (command == "parent")
		{
			tree->parent(arg);
		}
		else if (command == "child")
		{
			tree->child(arg);
		}
		else if (command == "help")
		{

		}
		else if (command == "quit")
		{
			return 1;
		}
	}
	return 0;
}
