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
	BST_Tree();		//konstruktor - wywo³ywany automatycznie przy tworzeniu obieku
	~BST_Tree();	//destrukor - wyw³ywany automatycznie przy usuwaniu obiektu

	// void heapify(int index);
	void postOrderDelete(TreeMember* member);

	void buildTree();

	int loadFromFile(std::string FileName);

	bool isValueInTree(int value);

	void addValue(int value);

	void deleteFromTree();

	void resize();

	void DSW();

	void rotateR(int index);
	
	void rotateL(int index);

	void display();
	
	void inOrder(TreeMember* member);
};