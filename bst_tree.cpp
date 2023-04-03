#include "bst_tree.hpp"
#include <iostream>
#include <fstream>

BST_Tree::BST_Tree() 
{
	tab = NULL;
	cnt = 0;
}

BST_Tree::~BST_Tree()
{
	delete[] tab;
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
			delete[] tab;
			tab = nullptr;
			cnt = 0;
		}

		file >> cnt;

		tab = new int[cnt];
		for (int i = 0; i < cnt; i++) tab[i] = NULL;

		// Zrobiæ dodawanie po jednym elem.
		while (file >> temp) {
			addValue(temp);
		}

		file.close();
	}
	else std::cout << "Plik nie zostal otworzony!\n";

	return 0;
}

void BST_Tree::addValue(int value)
{
	if (tab == NULL) {
		cnt = 1;
		tab = new int[cnt];
		tab[0] = value;
		return;
	}

	int temp = 0;
	int x = tab[temp];

	while (x != NULL && temp < cnt) {
		temp *= 2;

		if (value < x) temp += 1;
		else temp += 2;

		x = tab[temp];
	}

	if (temp >= cnt) {
		int* tabTemp = new int[temp + 1];
		
		for (int i = 0; i < cnt; i++) {
			tabTemp[i] = tab[i];
		}

		delete[] tab;

		cnt = temp + 1;
		tab = tabTemp;
	}

	tab[temp] = value;
}

void BST_Tree::DSW() 
{

}

void BST_Tree::rotateR(int index)
{
	int* tabTemp = new int[1];
}

void BST_Tree::display()
{
	// std::cout << "Size: " << cnt << "\n";
	for (int i = 0; i < cnt; i++) {
		if (tab[i] != NULL) std::cout << tab[i] << " ";
		else std::cout << ". ";
	}
	std::cout << "\n";
}
