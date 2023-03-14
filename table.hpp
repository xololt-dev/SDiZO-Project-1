#pragma once

#include <string>

//przyk³adowa implementacja tablicy ale tylko jest TYLKO szkielet 

//normalnie ka¿da klasa powinna zawieraæ definicjê w pliku .h a implementacje metod w pliku .cpp


//staramy siê unikaæ u¿ywania funkcji we/wy w klasie (opócz metody  display)
//ta definicja klast Table powinna normalnie znajdowac siê w pliku .h np. table.h

class Table
{
private:
	int* tab;
	int cnt; //iloœæ elementów w tablicy
public:

	Table(); //konstruktor - wywo³ywany automatycznie przy tworzeniu obieku
	~Table(); //destrukor - wyw³ywany automatycznie przy usuwaniu obiektu

	int loadFromFile(std::string FileName);

	bool IsValueInTable(int value);

	void addValue(int index, int value);

	void deleteFromTable(int index);

	void display();

	void generateTable(int size);

	void testFunc(int size);
};