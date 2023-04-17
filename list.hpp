#pragma once
#include <string>

struct ListMember {
	ListMember* prev;
	ListMember* next;
	int data;
};

class List {
private:
	ListMember* firstMember;
	ListMember* lastMember;
	int cnt;

public:
	List(); //konstruktor - wywo³ywany automatycznie przy tworzeniu obieku
	~List(); //destrukor - wyw³ywany automatycznie przy usuwaniu obiektu

	int loadFromFile(std::string FileName);

	bool IsValueInList(int value);

	void insertValue(int index, int value);

	void push_frontValue(int value);

	void push_backValue(int value, bool increment = true);

	void deleteFromList(int value);

	void indexDeleteFromList(int index);

	void pop_frontFromList();

	void pop_backFromList();

	void display();

	void generateList(int size, int max_value = INT_MAX);

	void testFunc();
};