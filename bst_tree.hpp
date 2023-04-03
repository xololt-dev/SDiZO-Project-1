#pragma once
#include <string>

class BST_Tree
{
private:
	int* tab;
	int cnt;		// amount of values in table

public:
	BST_Tree();		//konstruktor - wywoływany automatycznie przy tworzeniu obieku
	~BST_Tree();	//destrukor - wywływany automatycznie przy usuwaniu obiektu

	// void heapify(int index);

	void buildTree();

	int loadFromFile(std::string FileName);

	bool isValueInTree(int value);

	void addValue(int value);

	void deleteFromTree(int index);

	void resize();

	void DSW();

	void rotateR(int index);
	
	void rotateL(int index);

	void display();
};