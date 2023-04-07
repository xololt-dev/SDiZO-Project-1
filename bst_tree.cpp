#include "bst_tree.hpp"
#include <iostream>
#include <fstream>

BST_Tree::BST_Tree() 
{
	root = nullptr;
	cnt = 0;
}

BST_Tree::~BST_Tree()
{
	postOrderDelete(root);
}

void BST_Tree::postOrderDelete(TreeMember* member)
{
	if (member == NULL) return;
	postOrderDelete(member->left);
	postOrderDelete(member->right);
	delete member;
	member = nullptr;
}

int BST_Tree::loadFromFile(std::string FileName)
{
	std::fstream file;
	file.open(FileName, std::ios::in);
	if (file.good()) {
		int temp = 0;
		int i = 0;

		// clear the table
		if (cnt) {
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

bool BST_Tree::isValueInTree(int value)
{
	TreeMember* temp = root;

	while (temp != NULL) {
		if (temp->data == value) return true;

		if (value < temp->data) temp = temp->left;
		else temp = temp->right;
	}
	return false;
}

void BST_Tree::addValue(int value)
{
	TreeMember* temp;
	TreeMember* parentAddress = new TreeMember;
	if (root != nullptr) {
		temp = root;
		
		while (temp != NULL) {
			parentAddress = temp;
			if (temp->data > value) temp = temp->left;
			else temp = temp->right;
		}
	}

	temp = new TreeMember;
	temp->data = value;
	temp->parent = parentAddress;
	temp->left = temp->right = NULL;
	if (parentAddress->data < value) parentAddress->right = temp;
	else parentAddress->left = temp;
	
	if (root == nullptr) root = temp;
	
	cnt++;
}

void BST_Tree::deleteFromTree()
{
	if (!cnt || root == nullptr) return;

	if (root->right == NULL && root->left == NULL) {
		delete root;
		root = nullptr;
	}
	else {
		TreeMember* temp = nullptr;

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
			if(temp->left != NULL) temp->left->parent = temp;
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
			if(temp->right != NULL) temp->right->parent = temp;
		}
		temp->parent = NULL;
		delete root;
		root = temp;
	}
	cnt--;
}

void BST_Tree::DSW() 
{

}

void BST_Tree::rotateR(int index)
{

}

void BST_Tree::display()
{
	TreeMember* temp;
	
	if (root == nullptr || !cnt) std::cout << "Drzewo jest puste." << std::endl;
	else
	{
		std::cout << "Size: " << cnt << "\n";
		
		temp = root;
		inOrder(root->left);
		std::cout << temp->data << " ";
		inOrder(root->right);
		std::cout << "\n" << std::endl;
	}
}

void BST_Tree::inOrder(TreeMember* member)
{
	if (member == NULL) return;
	
	inOrder(member->left);
	std::cout << member->data << " ";
	inOrder(member->right);
}
