#include "heap.hpp"
#include <iostream>
#include <chrono>
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
	tab = nullptr;
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

		tab = new int[cnt + 3];
		tab_size = cnt + 3;

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

void Heap::generateHeap(int size, int max_value)
{
	delete[] tab;
	tab = nullptr;
	cnt = 0;
	tab_size = 0;

	for (int i = 0; i < size; i++) addValue(rand() % max_value);
}

/// <summary>
/// Checking if value is in the heap
/// </summary>
/// <param name="value - value we're searching for"></param>
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

	int i = ++cnt;
	int parent = floor(i / 2);
	
	while (i > 1 && tab[parent - 1] < value) {
		tab[i - 1] = tab[parent - 1];
		i = parent;
		parent = floor(i / 2);
	}

	tab[i - 1] = value;
}

/// <summary>
/// Delete value from the heap
/// </summary>
/// <param name="index - value we wanna delete is at this index"></param>
void Heap::deleteFromHeap(int index)
{
	if (!cnt) {
		std::cout << "Kopiec pusty!" << std::endl;
		return;
	}

	tab[index] = tab[--cnt];
	tab[cnt + 1] = NULL;
	heapify(index);
}

/// <summary>
/// Resize maximum heap size by 6
/// </summary>
void Heap::resize()
{
	int* tabTemp = nullptr;
	if (cnt != 0) {
		int new_size = pow(2, ceil(log2(cnt)) + 1) - 1;
		tabTemp = new int[new_size];
		tab_size = new_size;
	}
	else {
		tabTemp = new int[cnt + 6];
		tab_size += 6;
	}

	if (tab != nullptr) {
		for (int i = 0; i < cnt; i++) {
			tabTemp[i] = tab[i];
		}

		delete[] tab;
	}

	tab = tabTemp;
}

void Heap::display()
{
	std::cout << "Size: " << cnt << "\n";
	for (int i = 0; i < cnt; i++) {
		std::cout << tab[i] << " ";
	}
	std::cout << "\n";

	if (cnt || tab != NULL) {
		std::cout << "'--";
		std::cout << tab[0] << std::endl;
	}
	displayHeap(1);
	displayHeap(2);
}

void Heap::displayHeap(int index)
{
	if (index >= cnt) return;

	float n = floor(log2(index + 1));

	while (n > 0) {
		std::cout << "   ";
		n--;
	}
	if (cnt > index + 1 && index % 2 == 1) std::cout << "|--";
	else std::cout << "'--";
	std::cout << tab[index] << std::endl;

	displayHeap(2 * index + 1);
	displayHeap(2 * index + 2);
}

void Heap::testFunc()
{
	srand(time(NULL));

	int size[8] = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };
	//int size[2] = { 5000, 8000 };//, 10000, 16000 };
	auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<int64_t, std::nano> elapsed_nano_seconds = end - start;

	std::fstream file;
	std::string txt = ".txt";
	std::string file_name = "Heap_elements_";
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

				generateHeap(size[i]);

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
			// korzeñ
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_delete_random" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateHeap(size[i]);

				int index = 0;
				start = std::chrono::steady_clock::now();

				for (int k = 0; k < size[i] * 0.05; k++) {
					deleteFromHeap(index);
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

				generateHeap(size[i]);

				int value = 0;
				start = std::chrono::steady_clock::now();

				for (int k = 0; k < size[i] * 0.05; k++) {
					value = rand() % INT_MAX;
					isValueInHeap(value);
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

				generateHeap(size[i]);

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

				generateHeap(size[i]);

				int index = 0;
				start = std::chrono::steady_clock::now();

				for (int k = 0; k < size[i] * 0.05; k++) {
					index = rand() % cnt;
					deleteFromHeap(index);
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

				generateHeap(size[i]);

				int value = 0;
				start = std::chrono::steady_clock::now();

				for (int k = 0; k < size[i] * 0.05; k++) {
					value = rand() % 100;
					isValueInHeap(value);
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