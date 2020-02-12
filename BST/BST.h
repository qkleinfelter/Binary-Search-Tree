#pragma once
#include <string>
using namespace std;
class BST {
public:
	BST();
	~BST();
	void insert(string word);
	void remove(string word);
	void search(string word);

	void min();
	void max();

	void next(string word);
	void prev(string word);
	void parent(string word);
	void child(string word);
private:
	struct node
	{
		string word;
		int    count = 1;
		node* left = NULL;
		node* right = NULL;
	};
};