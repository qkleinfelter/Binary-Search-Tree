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

void printHelp()
{
	cout << "Available Commands: " << endl;
	cout << "insert <string>" << endl;
	cout << "delete <string>" << endl;
	cout << "search <string>" << endl;
	cout << "min" << endl;
	cout << "max" << endl;
	cout << "next <string>" << endl;
	cout << "prev <string>" << endl;
	cout << "list" << endl;
	cout << "parent <string>" << endl;
	cout << "child <string>" << endl;
	cout << "quit" << endl;
}


int main()
{
	BST* tree = new BST();
	while (true)
	{
		string instring, command, arg = "";
		getline(cin, instring);
		int spaceLoc = instring.find(" ");
		if (spaceLoc > 0)
		{
			command = instring.substr(0, spaceLoc);
			arg = instring.substr(spaceLoc + 1);
		}
		else
		{
			command = instring;
		}
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
			printHelp();
		}
		else if (command == "quit")
		{
			delete tree;
			return 0;
		}
		else
		{
			cout << "Unknown Command" << endl;
		}
	}
	return 0;
}
