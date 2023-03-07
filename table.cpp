#include "table.hpp"
#include <iostream>
#include <fstream>
#include <conio.h>

//ta implementacja poni¿ej powinna znajdowaæ siê w pliku cpp np. table.cpp
Table::Table()
{
	tab = NULL;
	cnt = 0;
}

Table::~Table()
{
	delete [] tab;
	tab = nullptr;
}

/// <summary>
/// Load numbers from file
/// </summary>
/// <param name="FileName - name of the file we want to open"></param>
/// <returns></returns>
int Table::loadFromFile(std::string FileName)
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

		while (file >> temp) {
			tab[i] = temp;
			i++;
		}

		file.close();
	}
	else std::cout << "Plik nie zostal otworzony!\n";

	return 0;
}

/// <summary>
/// Check if the value is in the table
/// </summary>
/// <param name="value - value to be searched for"></param>
/// <returns> bool </returns>
bool Table::IsValueInTable(int value)
{
	for (int i = 0; i < cnt; i++) {
		if (tab[i] == value) return true;
	}
	return false;
}

/// <summary>
/// Insert value to the table
/// </summary>
/// <param name="index - place where to put the value"></param>
/// <param name="value - value to be inserted"></param>
void Table::addValue(int index, int value)
{
	int* tabTemp = new int[cnt + 1];
	bool passedInputValue = false;

	if (index >= cnt) tabTemp[cnt] = value;
	else tabTemp[index] = value;

	// copying the table
	for (int i = 0; i < cnt; i++) {
		if (i == index) passedInputValue = true;

		tabTemp[i + passedInputValue] = tab[i];
	}

	delete[] tab;
	
	tab = new int[++cnt];
	// copying values back
	for (int i = 0; i < cnt; i++) {
		tab[i] = tabTemp[i];
	}

	delete[] tabTemp;
}

/// <summary>
/// Delete value at index from the table
/// </summary>
/// <param name="value - value to delete from the list, if exists"></param>
void Table::deleteFromTable(int index)
{
	if (index >= cnt) {
		std::cout << "Podany indeks jest wiekszy od tablicy!\n"; 
		return;
	}
	// if table is empty, return with message
	if (!cnt) {
		std::cout << "Tablica jest pusta! \n";
		return;
	}

	--cnt;
	int* tabTemp = new int[cnt];

	// copying the values
	for (int i = 0; i <= cnt; i++) {
		if (i < index) {
			tabTemp[i] = tab[i];
			continue;
		}			
		if (i > index) {
			tabTemp[i - 1] = tab[i];
			continue;
		}
		if (i == index) {
			continue;
		}			
	}

	delete[] tab;
	tab = new int[cnt];
	// copying the values back
	for (int i = 0; i < cnt; i++) {
		tab[i] = tabTemp[i];
	}

	delete[] tabTemp;
}

/// <summary>
/// Display the list
/// </summary>
void Table::display()
{
	std::cout << "Size: " << cnt << "\n";
	for (int i = 0; i < cnt; i++) {
		std::cout << tab[i] << " ";
	}
	std::cout << "\n";
}

/// <summary>
/// Generate/increase table size using push_back by size parameter
/// </summary>
/// <param name="size - requested amount of values to be inserted into the list"></param>
void Table::generateTable(int size)
{
	if (size < cnt) {
		std::cout << "Chcesz utworzyæ mniejsza tablice, kontynuowac? (0 - nie, 1 - tak): ";
		char k;
		k = _getche();
		if(k == 48) return;
	}

	int high = 0;
	if(cnt) high = tab[cnt - 1] + 1;
	
	// czy mo¿na vector? 
	int* tabTemp = new int[size];

	for (int i = 0; i < size; i++) {
		if (i < cnt) {
			tabTemp[i] = tab[i];
		}
		else tabTemp[i] = high;
	}

	delete[] tab;
	tab = new int[size];
	
	for (int i = 0; i < size; i++) {
		tab[i] = tabTemp[i];
	}
	
	delete [] tabTemp;

	cnt = size;
}