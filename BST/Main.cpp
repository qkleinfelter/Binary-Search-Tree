/*
	Quinn Kleinfelter
	EECS 2510-001 Non Linear Data Structures Spring 2020
	Dr. Thomas
	Last Edited: 2/22/20
*/

#include <iostream>
#include "BST.h"


string toLower(const string& s)
{
	// This is a helper function to return a completely lowercase version of an input string
	string temp(s);
	for (int i = 0; i < s.length(); i++)
		temp[i] = tolower(s[i]); // Loops through the characters of the string, adding them to a temporary string after running c++'s built in tolower on each character
	return temp;
}

void printHelp()
{
	// This is a helper function to print out the commands available to the user
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
	// Instantiate the tree to work with
	BST* tree = new BST();
	while (true) // Loop Forever
	{
		// Create some variables to store our input string, command, and argument
		string instring, command, arg = "";
		getline(cin, instring); // Get an input line from cin and place it in instring
		int spaceLoc = instring.find(" "); // Find out the location of the space character in our input
		if (spaceLoc > 0)
		{
			// If we have a space in the input, set the command to be the substring from the beginning to the character before the space
			command = instring.substr(0, spaceLoc);
			// And set the argument to be anything after the space
			arg = instring.substr(spaceLoc + 1);
		}
		else
		{
			// Otherwise, we just have a command so make it equal to the input string
			command = instring;
		}
		// Make sure the command is all lower case for case insensitive comparison, but DON'T adjust case of argument
		command = toLower(command);
		// Large if statement to dispatch the various commands on our tree
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
			// Make sure we delete our tree before we return out
			delete tree;
			return 0;
		}
		else
		{
			// If we don't recognize the command, just print an empty line
			cout << endl;
		}
	}
	return 0;
}
