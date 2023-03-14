#pragma once

#include <string>

//przyk�adowa implementacja tablicy ale tylko jest TYLKO szkielet 

//normalnie ka�da klasa powinna zawiera� definicj� w pliku .h a implementacje metod w pliku .cpp


//staramy si� unika� u�ywania funkcji we/wy w klasie (op�cz metody  display)
//ta definicja klast Table powinna normalnie znajdowac si� w pliku .h np. table.h

class Table
{
private:
	int* tab;
	int cnt; //ilo�� element�w w tablicy
public:

	Table(); //konstruktor - wywo�ywany automatycznie przy tworzeniu obieku
	~Table(); //destrukor - wyw�ywany automatycznie przy usuwaniu obiektu

	int loadFromFile(std::string FileName);

	bool IsValueInTable(int value);

	void addValue(int index, int value);

	void deleteFromTable(int index);

	void display();

	void generateTable(int size);

	void testFunc(int size);
};