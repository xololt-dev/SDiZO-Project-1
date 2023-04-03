#include "heap.hpp"
#include <iostream>
#include <fstream>

Heap::Heap()
{
	tab = NULL;
	cnt = 0;
	tab_size = 0;
}

Heap::~Heap()
{
	delete[] tab;
}


void Heap::heapify(int index)
{
	int largest;
	int l = 2 * index + 1;
	int r = 2 * index + 2;
	
	if (l <= cnt && tab[l] > tab[index]) largest = l;
	else largest = index;

	if (r <= cnt && tab[r] > tab[largest]) largest = r;

	if (largest != index) {
		int temp = tab[index];
		tab[index] = tab[largest];
		tab[largest] = temp;
		display();
		heapify(largest);
	}
}

/// <summary>
/// Build heap - Floyd's algorithm
/// </summary>
void Heap::buildHeap()
{
	for (int i = floor(cnt / 2) - 1; i >= 0; i--) heapify(i);
}


/// <summary>
/// Load numbers from file
/// </summary>
/// <param name="FileName - name of the file we want to open"></param>
/// <returns></returns>
int Heap::loadFromFile(std::string FileName)
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

		tab = new int[cnt+1];
		tab_size = cnt + 1;

		// Zrobiæ dodawanie po jednym elem.
		while (file >> temp) {
			tab[i] = temp;
			i++;
		}

		file.close();

		buildHeap();
	}
	else std::cout << "Plik nie zostal otworzony!\n";

	return 0;
}

/// <summary>
/// Insert value to the heap
/// </summary>
/// <param name="value - value to be inserted"></param>
bool Heap::isValueInHeap(int value)
{
	for (int i = 0; i < cnt; i++) {
		if (tab[i] == value) return true;
	}
	return false;
}

/// <summary>
/// Insert value to the heap
/// </summary>
/// <param name="value - value to be inserted"></param>
void Heap::addValue(int value)
{
	// jesli nie ma miejsca, realokujemy
	if (cnt == tab_size) resize();
	tab[cnt] = value;
	cnt++;

	// build heap
	buildHeap();
}

void Heap::deleteFromHeap(int index)
{
	if (!cnt) {
		std::cout << "Kopiec pusty!" << std::endl;
		return;
	}

	tab[index] = tab[--cnt];
	heapify(index);
}

/// <summary>
/// Resize maximum heap size by 6
/// </summary>
void Heap::resize()
{
	int* tabTemp = new int[cnt + 6];
	tab_size += 6;

	for (int i = 0; i < cnt; i++) {
		tabTemp[i] = tab[i];
	}

	delete[] tab;

	tab = tabTemp;
}

void Heap::display()
{
	std::cout << "Size: " << cnt << "\n";
	for (int i = 0; i < cnt; i++) {
		std::cout << tab[i] << " ";
	}
	std::cout << "\n";
}
