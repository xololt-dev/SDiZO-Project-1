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
	int cnt;		// amount of values in table

public:
	BST_Tree();		//konstruktor - wywoływany automatycznie przy tworzeniu obieku
	~BST_Tree();	//destrukor - wywływany automatycznie przy usuwaniu obiektu

	// void heapify(int index);
	void postOrderDelete(TreeMember* member);

	void buildTree();

	int loadFromFile(std::string FileName);

	bool isValueInTree(int value);

	void addValue(int value);

	void deleteFromTree(int value);

	void deleteTreeRoot();

	void resize();

	void DSW();

	void rotateR(int index);
	
	void rotateL(int index);

	void display();

	void displayTree();
	
	void inOrder(TreeMember* member);

	void preOrder(TreeMember* member, int level = 0);
};