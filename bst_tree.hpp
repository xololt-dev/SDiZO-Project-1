#pragma once
#include <string>

struct TreeMember {
	TreeMember* left;
	TreeMember* right;
	TreeMember* parent;
	int data;
};

class BST_Tree
{
private:
	TreeMember* root;
	int cnt;		// amount of values in tree

public:
	BST_Tree();		//konstruktor - wywo�ywany automatycznie przy tworzeniu obieku
	~BST_Tree();	//destrukor - wyw�ywany automatycznie przy usuwaniu obiektu

	void postOrderDelete(TreeMember* member);

	void generateBST(int size, int max_value = INT_MAX);

	int loadFromFile(std::string FileName);

	bool isValueInTree(int value);

	void addValue(int value);

	void deleteFromTree(int value);

	void deleteTreeRoot();

	void DSW();

	void rotateR(TreeMember* temp);
	
	void rotateL(TreeMember* temp);

	void display();

	void displayTree();
	
	void inOrder(TreeMember* member);

	void preOrder(TreeMember* member, int level = 0);
};