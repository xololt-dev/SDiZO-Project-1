#include "table.hpp"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <chrono>

//ta implementacja poni¿ej powinna znajdowaæ siê w pliku cpp np. table.cpp
Table::Table()
{
	tab = NULL;
	cnt = 0;
}

Table::~Table()
{
	delete [] tab;
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
	
	++cnt;
	
	tab = tabTemp; /*
	// copying values back
	for (int i = 0; i < cnt; i++) {
		tab[i] = tabTemp[i];
	}
	*/
	// delete[] tabTemp;
}

/// <summary>
/// Delete value at index from the table
/// </summary>
/// <param name="value - value to delete from the list, if exists"></param>
void Table::deleteFromTable(int index)
{
	// if table is empty, return with message
	if (!cnt) {
		std::cout << "Tablica jest pusta! \n";
		return;
	}
	if (index >= cnt) {
		std::cout << "Podany indeks jest wiekszy od tablicy!\n";
		return;
	}

	--cnt;
	if (!cnt) {
		delete[] tab;
		tab = NULL;
	}
	else {
		int* tabTemp = new int[cnt];

		// copying the values
		int i = 0;
		for (; i < index; i++) {
			tabTemp[i] = tab[i];
		}
		for (i = index + 1; i <= cnt; i++) {
			tabTemp[i - 1] = tab[i];
		}

		delete[] tab;

		tab = tabTemp;
	}
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
void Table::generateTable(int size, int limit)
{
	/*
	if (size < cnt) {
		std::cout << "Chcesz utworzyæ mniejsza tablice, kontynuowac? (0 - nie, 1 - tak): ";
		char k;
		k = _getche();
		if(k == 48) return;
	}

	int high = 0;
	if(cnt) high = tab[cnt - 1] + 1;
	
	int* tabTemp = new int[size];

	for (int i = 0; i < size; i++) {
		if (i < cnt) {
			tabTemp[i] = tab[i];
		}
		else tabTemp[i] = high;
	}*/

	delete[] tab;

	tab = new int[size];
	for (int i = 0; i < size; i++) {
		tab[i] = rand() % limit;
	}	
	
	//tab = tabTemp;

	cnt = size;
}

void Table::testFunc()
{
	srand(time(NULL));

	//int size[8] = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };
	int size[4] = { 5000, 8000, 10000, 16000 };
	auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double, std::nano> elapsed_nano_seconds = end - start;

	std::fstream file;
	std::string txt = ".txt";
	std::string file_name = "Table_elements_";// +size + txt;
	std::string main_folder = "results/";
	std::string size_string = "";

	for (int i = 0; i < 4; i++) {
		size_string = std::to_string(size[i]);
		// bez limitu
			// dodaj
				// poczatek
		file.open(main_folder + size_string + "/" + file_name + size_string + "_add_start" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateTable(size[i]);

				int index = 0;
				int value = 0;

				for (int k = 0; k < size[i] * 0.05; k++) {
					index = 0;
					value = rand() % INT_MAX;
					start = std::chrono::steady_clock::now();

					addValue(index, value);

					end = std::chrono::steady_clock::now();
					elapsed_nano_seconds = end - start;

					file << elapsed_nano_seconds.count() << "\n";
				}
			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";
				// koniec
		file.open(main_folder + size_string + "/" + file_name + size_string + "_add_end" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));
			
				generateTable(size[i]);

				int index = 0;
				int value = 0;

				for (int k = 0; k < size[i] * 0.05; k++) {
					index = cnt;
					value = rand() % INT_MAX;
					
					start = std::chrono::steady_clock::now();

					addValue(index, value);

					end = std::chrono::steady_clock::now();
					elapsed_nano_seconds = end - start;

					file << elapsed_nano_seconds.count() << "\n";
				}
			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";
				// losowo
		file.open(main_folder + size_string + "/" + file_name + size_string + "_add_rand " + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));
			
				generateTable(size[i]);

				int index = 0;
				int value = 0;

				for (int k = 0; k < size[i] * 0.05; k++) {
					index = rand() % INT_MAX;
					value = rand() % INT_MAX;
					start = std::chrono::steady_clock::now();

					addValue(index, value);

					end = std::chrono::steady_clock::now();
					elapsed_nano_seconds = end - start;

					file << elapsed_nano_seconds.count() << "\n";
				}
				
			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";
			// usun
				// poczatek
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_delete_start" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateTable(size[i]);

				for (int k = 0; k < size[i] * 0.05; k++) {
					start = std::chrono::steady_clock::now();

					deleteFromTable(0);

					end = std::chrono::steady_clock::now();
					elapsed_nano_seconds = end - start;

					file << elapsed_nano_seconds.count() << "\n";
				}
			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";
		
				// koniec
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_delete_end" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateTable(size[i]);

				for (int k = 0; k < size[i] * 0.05; k++) {
					start = std::chrono::steady_clock::now();

					deleteFromTable(cnt - 1);

					end = std::chrono::steady_clock::now();
					elapsed_nano_seconds = end - start;

					file << elapsed_nano_seconds.count() << "\n";
				}

			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";

				// losowo
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_delete_random" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateTable(size[i]);

				int index = 0;

				for (int k = 0; k < size[i] * 0.05; k++) {
					index = rand() % cnt;
					start = std::chrono::steady_clock::now();

					deleteFromTable(index);

					end = std::chrono::steady_clock::now();
					elapsed_nano_seconds = end - start;

					file << elapsed_nano_seconds.count() << "\n";
				}

			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";

			// wyszukaj
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_search" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateTable(size[i]);

				int value = 0;
				start = std::chrono::steady_clock::now();
				for (int k = 0; k < size[i] * 0.05; k++) {
					value = rand() % INT_MAX;

					IsValueInTable(value);
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
				// poczatek
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_add_start_limit" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateTable(size[i], 100);

				int index = 0;
				int value = 0;

				for (int k = 0; k < size[i] * 0.05; k++) {
					index = 0;
					value = rand() % 100;

					start = std::chrono::steady_clock::now();

					addValue(index, value);

					end = std::chrono::steady_clock::now();
					elapsed_nano_seconds = end - start;

					file << elapsed_nano_seconds.count() << "\n";
				}
			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";
				// koniec
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_add_end_limit" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateTable(size[i], 100);

				int index = 0;
				int value = 0;

				for (int k = 0; k < size[i] * 0.05; k++) {
					index = cnt;
					value = rand() % 100;

					start = std::chrono::steady_clock::now();

					addValue(index, value);

					end = std::chrono::steady_clock::now();
					elapsed_nano_seconds = end - start;

					file << elapsed_nano_seconds.count() << "\n";
				}

			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";
		
				// losowo
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_add_rand_limit" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateTable(size[i], 100);

				int index = 0;
				int value = 0;

				for (int k = 0; k < size[i] * 0.05; k++) {
					index = rand() % INT_MAX;
					value = rand() % 100;
					start = std::chrono::steady_clock::now();

					addValue(index, value);

					end = std::chrono::steady_clock::now();
					elapsed_nano_seconds = end - start;

					file << elapsed_nano_seconds.count() << "\n";
				}

			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";
		
			// usun
				// poczatek
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_delete_start_limit" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateTable(size[i], 100);

				for (int k = 0; k < size[i] * 0.05; k++) {
					start = std::chrono::steady_clock::now();

					deleteFromTable(0);

					end = std::chrono::steady_clock::now();
					elapsed_nano_seconds = end - start;

					file << elapsed_nano_seconds.count() << "\n";
				}

			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";
		
				// koniec
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_delete_end_limit" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateTable(size[i], 100);

				for (int k = 0; k < size[i] * 0.05; k++) {
					start = std::chrono::steady_clock::now();

					deleteFromTable(cnt - 1);

					end = std::chrono::steady_clock::now();
					elapsed_nano_seconds = end - start;

					file << elapsed_nano_seconds.count() << "\n";
				}
			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";

				// losowo
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_delete_random_limit" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateTable(size[i], 100);

				int index = 0;

				for (int k = 0; k < size[i] * 0.05; k++) {
					index = rand() % cnt;
					start = std::chrono::steady_clock::now();

					deleteFromTable(index);

					end = std::chrono::steady_clock::now();
					elapsed_nano_seconds = end - start;

					file << elapsed_nano_seconds.count() << "\n";
				}
			}
			file.close();
		}
		else std::cout << "Plik nie zostal otworzony!\n";
			
			// wyszukaj
		file.open(main_folder + std::to_string(size[i]) + "/" + file_name + std::to_string(size[i]) + "_search_limit" + txt, std::ios::out | std::ios::app);
		if (file.good()) {
			for (int j = 0; j < 100; j++) {
				srand(time(NULL));

				generateTable(size[i], 100);

				int value = 0;
				start = std::chrono::steady_clock::now();

				for (int k = 0; k < size[i] * 0.05; k++) {
					value = rand() % 100;

					IsValueInTable(value);
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