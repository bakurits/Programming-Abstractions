#include <string>
#include "console.h"
#include "simpio.h"
#include <iostream>
using namespace std;


struct Node {
	string value;
	Node *left, *right;
};

Node * find(Node * root, string s) {
	if (root == NULL)
		return NULL;

	if (root->value == s) {
		return root;
	} if (root->value < s) {
		return find(root->right, s);
	} 

	return find(root->left, s);
}

void insert(Node * &root, string s) {
	if (root == NULL) {
		root = new Node;
		root->value = s;
		root->left = NULL;
		root->right = NULL;
	}

	if (root->value == s)
		return;
	else if (root->value < s)
		insert(root->right, s);
	else 
		insert(root->left, s);
}


int main() {
	Node * root = NULL;
	while (true) {
		string name;
		cout << "Enter name: " << endl;
		cin >> name;
		if (name == "")
			break;
		if (find(root, name))
			cout << "Already exists!!" << endl;
		else
			insert(root, name);
	}

	return 0;
}


