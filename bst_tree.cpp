#include "bst_tree.hpp"
#include <iostream>
#include <chrono>
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

void BST_Tree::generateBST(int size, int max_value)
{
	postOrderDelete(root);
	root = nullptr;
	cnt = 0;

	for (int i = 0; i < size; i++) addValue(rand() % max_value);
}

int BST_Tree::loadFromFile(std::string FileName)
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
	TreeMember* parentAddress = nullptr; // new TreeMember;

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
	if (parentAddress != nullptr) {
		if (parentAddress->data < value) parentAddress->right = temp;
		else parentAddress->left = temp;
	}
	
	if (root == nullptr) root = temp;
	
	cnt++;

	DSW();
}

void BST_Tree::deleteFromTree(int value)
{
	if (!cnt || root == nullptr) return;

	if (value == root->data) {
		deleteTreeRoot();
		return;
	}

	TreeMember* temp = root;
	
	// find the node with the right value
	while(temp->data != value) {
		if (temp->data > value) {
			if(temp->left != NULL) temp = temp->left;
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
		TreeMember* tempSwap = temp;

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

	DSW();
}

void BST_Tree::deleteTreeRoot()
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

	DSW();
}

void BST_Tree::DSW() 
{
	TreeMember* temp = root;

	// unfold the tree
	while (temp != NULL) {
		if (temp->left != NULL) {
			rotateR(temp);
			temp = temp->parent;
		}
		else temp = temp->right;
	}

	int m = pow(2, floor(log2(cnt + 1))) - 1;
	temp = root;

	// n-m rotations left, from root, every second member
	for (int i = cnt - m; i > 0; i--) {
		if (temp != NULL) {
			if (temp->right != NULL) rotateL(temp);
			temp = temp->parent->right;
		}
	}	

	while (m > 1) {
		// m rotations left, from root, every second member
		m = floor(m / 2);
		temp = root;

		for (int i = m; i > 0; i--) {
			if (temp != NULL) {
				if (temp->right != NULL) rotateL(temp);
				temp = temp->parent->right;
			}
		}		
	}
}

void BST_Tree::rotateR(TreeMember* temp)
{
	temp->left->parent = temp->parent;
	if (temp->parent != NULL) temp->parent->right = temp->left;
	temp->parent = temp->left;
	temp->left = temp->left->right;
	if (temp->left != NULL) temp->left->parent = temp;
	temp->parent->right = temp;
	if (temp == root) root = temp->parent;
}

void BST_Tree::rotateL(TreeMember* temp)
{
	temp->right->parent = temp->parent;
	if (temp->parent != NULL) temp->parent->right = temp->right;
	temp->parent = temp->right;
	temp->right = temp->parent->left;
	if (temp->right != NULL) temp->right->parent = temp;
	temp->parent->left = temp;
	if (temp == root) root = temp->parent;
}

void BST_Tree::display()
{	
	if (root == nullptr || !cnt) std::cout << "Drzewo jest puste." << std::endl;
	else {
		std::cout << "Size: " << cnt << "\n";
		
		TreeMember* temp = root;
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

void BST_Tree::displayTree()
{
	if (root != NULL) {
		TreeMember* temp = root;

		std::cout << "'--";
		std::cout << temp->data << std::endl;
		
		// preorder
		preOrder(temp->left, 1);
		preOrder(temp->right, 1);
	}
	else std::cout << "Drzewo jest puste." << std::endl;
}

void BST_Tree::preOrder(TreeMember* member, int level)
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
		if (member->data < member->parent->data && member->parent->right != NULL) std::cout << "|--";
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

void BST_Tree::testFunc()
{
	srand(time(NULL));

	int size[8] = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };
	//int size[2] = { 5000, 8000 };//, 10000, 16000 };
	auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<int64_t, std::nano> elapsed_nano_seconds = end - start;

	std::fstream file;
	std::string txt = ".txt";
	std::string file_name = "BST_elements_";
	std::string main_folder = "results/";
	std::string size_string = "";

	for (int i = 0; i < 8; i++) {
		size_string = std::to_string(size[i]);
		// bez limitu
			// dodaj	
				// losowo
		file.open(main_folder + size_string + "/" + file_name + size_string + "_add_rand " + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));
				
				generateBST(size[i]);

				int value = 0;
				start = std::chrono::steady_clock::now();

				for (int k = 0; k < size[i] * 0.05; k++) {
					value = rand() % INT_MAX;
					addValue(value);
				}
				end = std::chrono::steady_clock::now();
				elapsed_nano_seconds = end - start;

				file << elapsed_nano_seconds.count() << "\n";
			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";
		// usun
			// losowo
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_delete_random" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateBST(size[i]);

				start = std::chrono::steady_clock::now();

				for (int k = 0; k < size[i] * 0.05; k++) {
					deleteTreeRoot();
				}
				end = std::chrono::steady_clock::now();
				elapsed_nano_seconds = end - start;

				file << elapsed_nano_seconds.count() << "\n";
			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";

		// wyszukaj
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_search" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateBST(size[i]);

				int value = 0;
				start = std::chrono::steady_clock::now();

				for (int k = 0; k < size[i] * 0.05; k++) {
					value = rand() % INT_MAX;
					isValueInTree(value);
				}
				end = std::chrono::steady_clock::now();
				elapsed_nano_seconds = end - start;

				file << elapsed_nano_seconds.count() << "\n";
			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";

		// limit
			// dodaj
				// losowo
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_add_rand_limit" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateBST(size[i]);

				int value = 0;
				start = std::chrono::steady_clock::now();

				for (int k = 0; k < size[i] * 0.05; k++) {
					value = rand() % 100;
					addValue(value);
				}
				end = std::chrono::steady_clock::now();
				elapsed_nano_seconds = end - start;

				file << elapsed_nano_seconds.count() << "\n";

			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";

		// usun
			// losowo
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_delete_random_limit" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateBST(size[i]);

				start = std::chrono::steady_clock::now();

				for (int k = 0; k < size[i] * 0.05; k++) {
					deleteTreeRoot();
				}

				end = std::chrono::steady_clock::now();
				elapsed_nano_seconds = end - start;

				file << elapsed_nano_seconds.count() << "\n";
			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";

		// wyszukaj
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_search_limit" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateBST(size[i]);

				int value = 0;
				start = std::chrono::steady_clock::now();

				for (int k = 0; k < size[i] * 0.05; k++) {
					value = rand() % 100;
					isValueInTree(value);
				}
				end = std::chrono::steady_clock::now();
				elapsed_nano_seconds = end - start;

				file << elapsed_nano_seconds.count() << "\n";
			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";
	}
}
