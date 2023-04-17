#pragma once
#include <string>

class Heap {
private:
	int* tab;
	int cnt;		// amount of values in table
	int tab_size;	// table size

public:
	Heap();		//konstruktor - wywo³ywany automatycznie przy tworzeniu obieku
	~Heap();	//destrukor - wyw³ywany automatycznie przy usuwaniu obiektu

	void heapify(int index);
	
	void buildHeap();

	int loadFromFile(std::string FileName);

	void generateHeap(int size, int max_value = INT_MAX);

	bool isValueInHeap(int value);

	void addValue(int value);

	void deleteFromHeap(int index);

	void resize();

	void display();

	void displayHeap(int index);
};