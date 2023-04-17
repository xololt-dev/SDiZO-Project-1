#include "avl.hpp"
#include <iostream>
#include <fstream>

AVL::AVL()
{
	root = nullptr;
	cnt = 0;
}

AVL::~AVL()
{
	postOrderDelete(root);
}

void AVL::postOrderDelete(AVLTreeMember* member)
{
	if (member == NULL) return;
	postOrderDelete(member->left);
	postOrderDelete(member->right);
	delete member;
	member = nullptr;
}

void AVL::generateAVL(int size, int max_value)
{
	for (int i = 0; i < size; i++) addValue(rand() % (1000 + 1));
}

int AVL::loadFromFile(std::string FileName)
{
	std::fstream file;
	file.open(FileName, std::ios::in);
	if (file.good()) {
		int temp = 0;
		int i = 0;

		// clear the table
		if (cnt || root != nullptr) {
			postOrderDelete(root);
			root = nullptr;
			cnt = 0;
		}

		file >> temp;

		// Zrobiæ dodawanie po jednym elem.
		while (file >> temp) {
			addValue(temp);
		}

		file.close();
	}
	else std::cout << "Plik nie zostal otworzony!\n";

	return 0;
}

bool AVL::isValueInTree(int value)
{
	AVLTreeMember* temp = root;

	while (temp != NULL) {
		if (temp->data == value) return true;

		if (value < temp->data) temp = temp->left;
		else temp = temp->right;
	}
	return false;
}

void AVL::addValue(int value)
{
	AVLTreeMember* temp;
	AVLTreeMember* parentAddress = nullptr; // new TreeMember;

	if (root != nullptr) {
		temp = root;

		while (temp != NULL) {
			parentAddress = temp;
			if (temp->data > value) temp = temp->left;
			else temp = temp->right;
		}
	}

	temp = new AVLTreeMember;
	temp->data = value;
	temp->parent = parentAddress;
	temp->balance = 0;
	temp->left = temp->right = NULL;
	if (parentAddress != nullptr) {
		if (parentAddress->data < value) {
			parentAddress->right = temp;
			parentAddress->balance -= 1;
		}
		else {
			parentAddress->left = temp;
			parentAddress->balance += 1;
		}
	}

	if (root == nullptr) root = temp;
	else balance(temp);
	
	cnt++;
	
	displayTree();
}

void AVL::deleteFromTree(int value)
{
	if (!cnt || root == nullptr) return;

	if (value == root->data) {
		deleteTreeRoot();
		return;
	}

	AVLTreeMember* temp = root;

	// find the node with the right value
	while (temp->data != value) {
		if (temp->data > value) {
			if (temp->left != NULL) temp = temp->left;
			else std::cout << "Wartosc nie istnieje! \n";
		}
		else {
			if (temp->right != NULL) temp = temp->right;
			else std::cout << "Wartosc nie istnieje! \n";
		}
	}

	// if node doesn't have children, simply delete it
	if (temp->left == NULL && temp->right == NULL) {
		if (temp->parent != NULL) {
			if (temp->parent->data > value) temp->parent->left = nullptr;
			else temp->parent->right = nullptr;
		}
	}
	// node has children, find a node to swap to
	else {
		AVLTreeMember* tempSwap = temp;

		if (tempSwap->left == NULL || tempSwap->right == NULL) {
			// 1 subtree
			if (tempSwap->left != NULL) {
				// search min value from left subtree
				tempSwap = tempSwap->left;
				// ?
				if (temp->data > temp->parent->data) temp->parent->right = tempSwap;
				else temp->parent->left = tempSwap;

				tempSwap->parent = temp->parent;
			}
			else {
				// search min value from right subtree
				tempSwap = tempSwap->right;
				// ?
				if (temp->data > temp->parent->data) temp->parent->right = tempSwap;
				else temp->parent->left = tempSwap;

				tempSwap->parent = temp->parent;
			}
		}
		else {
			// 2 subtrees
			// find next value
			if (tempSwap->right != NULL) {
				// search min value from right subtree
				tempSwap = tempSwap->right;
				while (tempSwap->left != NULL) tempSwap = tempSwap->left;

				// if double null/right null
				if (tempSwap->parent != temp) {
					if (tempSwap->right != NULL) tempSwap->right->parent = tempSwap->parent;
					tempSwap->parent->left = tempSwap->right;

					temp->data = tempSwap->data;

					delete tempSwap;
					tempSwap = nullptr;
					cnt--;
					return;
				}
				else {
					tempSwap->left = temp->left;
					temp->left->parent = tempSwap;
					temp->parent->right = tempSwap;
					tempSwap->parent = temp->parent;
				}
			}
		}
	}
	delete temp;
	temp = nullptr;

	cnt--;
}

void AVL::deleteTreeRoot()
{
	if (!cnt || root == nullptr) return;

	if (root->right == NULL && root->left == NULL) {
		delete root;
		root = nullptr;
	}
	else {
		AVLTreeMember* temp = nullptr;

		if (root->right != NULL) {
			temp = root->right;

			while (temp->left != NULL) temp = temp->left;

			if (temp->parent != root) {
				temp->parent->left = temp->right;
				if (temp->right != NULL) temp->right->parent = temp->parent;

				temp->right = root->right;
				temp->right->parent = temp;
			}
			temp->left = root->left;
			if (temp->left != NULL) temp->left->parent = temp;
		}
		else if (root->left != NULL) {
			temp = root->left;

			while (temp->right != NULL) temp = temp->right;

			if (temp->parent != root) {
				temp->parent->right = temp->left;
				if (temp->left != NULL) temp->left->parent = temp->parent;

				temp->left = root->left;
				temp->left->parent = temp;
			}

			temp->right = root->right;
			if (temp->right != NULL) temp->right->parent = temp;
		}
		temp->parent = NULL;
		delete root;
		root = temp;
	}
	cnt--;
}

void AVL::setBalance(AVLTreeMember* temp)
{
	int balance_temp = 0;
	if (temp->right == NULL && temp->left == NULL) {
		temp->balance = balance_temp;
		return;
	}

	if (temp->left != NULL) balance_temp = abs(temp->left->balance) + 1;

	if (temp->right != NULL && abs(temp->right->balance) >= balance_temp) balance_temp = -(abs(temp->right->balance) + 1);
	/*
	if (temp->left == NULL && temp->right != NULL) temp->balance = -(abs(temp->right->balance) + 1);
	else if (temp->right == NULL && temp->left != NULL) temp->balance = abs(temp->left->balance) + 1;
	else if (temp->right == NULL && temp->left == NULL) temp->balance = 0;
	else {
		temp->balance = abs(temp->left->balance) - abs(temp->right->balance);
	}
	*/
}

void AVL::rotateR(AVLTreeMember* temp)
{
	temp->left->parent = temp->parent;
	if (temp->parent != NULL) temp->parent->left = temp->left;
	temp->parent = temp->left;
	temp->left = temp->parent->right;
	if (temp->left != NULL) temp->left->parent = temp;
	temp->parent->right = temp;

	if (temp == root) root = temp->parent;

	setBalance(temp);
	if (temp->parent->left != NULL) setBalance(temp->parent->left);
	setBalance(temp->parent);
}

void AVL::rotateL(AVLTreeMember* temp)
{
	temp->right->parent = temp->parent;
	if (temp->parent != NULL) temp->parent->right = temp->right;
	temp->parent = temp->right;
	temp->right = temp->parent->left;
	if (temp->right != NULL) temp->right->parent = temp;
	temp->parent->left = temp;
	if (root == temp) root = temp->parent;

	setBalance(temp);

	if (temp->parent->right != NULL) setBalance(temp->parent->right);

	setBalance(temp->parent);
}

void AVL::rotateLR(AVLTreeMember* temp)
{
	temp->right->parent = temp->parent;
	temp->parent->left = temp->right;
	temp->parent = temp->right;
	temp->parent->left = temp;
	temp->right = temp->parent->right;
	temp->balance += 1;
	temp->parent->balance -= 1;

	rotateR(temp->parent->parent);
}

void AVL::rotateRL(AVLTreeMember* temp)
{
	temp->left->parent = temp->parent;
	temp->parent->right = temp->left;
	temp->parent = temp->left;
	temp->parent->right = temp;
	temp->left = temp->parent->left;
	temp->balance += 1;
	temp->parent->balance -= 1;

	rotateL(temp->parent->parent);
}

void AVL::balance(AVLTreeMember* member)
{
	// change balance to be height of the tree cause idk

	if (member == nullptr) return;

	if (member->left == NULL && member->right == NULL) {
		balance(member->parent);
		return;
	}
	//if (member->data > member->parent->data) member->parent->balance -= 1;
	//else member->parent->balance += 1;
	
	setBalance(member);
	
	/*
	if (member->data > member->parent->data) {
		if (member->parent->left == NULL) difference = -(member->balance);
		else difference = member->parent->left->balance - member->balance;
	}
	else {
		if (member->parent->right == NULL) difference = member->balance;
		else difference = member->balance - member->parent->right->balance;
	}
	*/

	if (member->balance > 1) {
		if (member->left->right != NULL) {
			// rotate LR
			rotateLR(member->left);
		}
		else {
			do {
				rotateR(member);
			} while (member->balance > 1);
		}

		return;
	}
	else if (member->balance < -1) {
		if (member->right->left != NULL) {
			// rotate RL
			rotateRL(member->right);
		}
		else {
			do {
				rotateL(member);
			} while (member->balance < -1);
		}

		return;
	}
	/*
	if (member->parent->balance > 1) {
		if (member->right != NULL) {
			// rotate LR
			rotateLR(member);
		}
		else {
			rotateR(member->parent);
		}
		
		return;
	}
	else if (member->parent->balance < -1) {
		if (member->left != NULL) {
			rotateRL(member);
		}
		else {
			rotateL(member->parent);
		}

		return;
	}
	*/
	balance(member->parent);
}

void AVL::display()
{
	if (root == nullptr || !cnt) std::cout << "Drzewo jest puste." << std::endl;
	else {
		std::cout << "Size: " << cnt << "\n";

		AVLTreeMember* temp = root;
		inOrder(root->left);
		std::cout << temp->data << " ";
		inOrder(root->right);
		std::cout << "\n" << std::endl;
	}
}

void AVL::displayTree()
{
	if (root != NULL) {
		AVLTreeMember* temp = root;

		std::cout << "'--";
		std::cout << temp->data << std::endl;

		// preorder
		preOrder(temp->left, 1);
		preOrder(temp->right, 1);
	}
	else std::cout << "Drzewo jest puste." << std::endl;
}

void AVL::inOrder(AVLTreeMember* member)
{
	if (member == NULL) return;

	inOrder(member->left);
	std::cout << member->data << " ";
	inOrder(member->right);
}

void AVL::preOrder(AVLTreeMember* member, int level)
{
	if (member == NULL) return;

	// #1 is it left from root
	// #2 is it left from parent

	if (member->data <= root->data) {
		// left from root
		for (int i = level; i > 0; i--) {
			if (level > 1 && i < level) {
				std::cout << "|  ";
			}
			else std::cout << "   ";
		}
		if (member->data < member->parent->data&& member->parent->right != NULL) std::cout << "|--";
		else std::cout << "'--";
	}
	else {
		// right from root
		for (int i = level; i > 0; i--) {
			if (level > 2 && i < level - 1 && (member->parent->parent->right != NULL && member->parent->parent->right != member->parent)) {
				std::cout << "|  ";
			}
			else std::cout << "   ";
		}
		if (member->data < member->parent->data && member->parent->right != NULL) std::cout << "|--";
		else std::cout << "'--";
	}
	std::cout << member->data << std::endl;

	preOrder(member->left, level + 1);
	preOrder(member->right, level + 1);
}
