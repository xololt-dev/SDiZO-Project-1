#pragma once
#include <string>

struct AVLTreeMember {
	AVLTreeMember* left;
	AVLTreeMember* right;
	AVLTreeMember* parent;
	int data;
	int balance;
};

class AVL {
private:
	AVLTreeMember* root;
	int cnt;		// amount of values in tree

public:
	AVL();			//konstruktor - wywo³ywany automatycznie przy tworzeniu obieku
	~AVL();			//destrukor - wyw³ywany automatycznie przy usuwaniu obiektu

	void postOrderDelete(AVLTreeMember* member);

	void generateAVL(int size, int max_value = INT_MAX);

	int loadFromFile(std::string FileName);

	bool isValueInTree(int value);

	void addValue(int value);

	void deleteFromTree(int value);

	void deleteTreeRoot();

	void setBalance(AVLTreeMember* temp);

	int calcBias(AVLTreeMember* temp);

	void rotateR(AVLTreeMember* temp);

	void rotateL(AVLTreeMember* temp);
	
	void rotateLR(AVLTreeMember* temp);
	
	void rotateRL(AVLTreeMember* temp);

	void balance(AVLTreeMember* member);

	void display();

	void displayTree();

	void inOrder(AVLTreeMember* member);

	void preOrder(AVLTreeMember* member, int level = 0);

	void testFunc();
};