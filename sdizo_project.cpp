// menu.cpp : Defines the entry point for the console application.
//

#include <conio.h>
#include <string>
#include <iostream>

#include "table.hpp"
#include "list.hpp"
#include "heap.hpp"
#include "bst_tree.hpp"

using namespace std;

//właściwy program

void displayMenu(string info)
{
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Usun" << endl;
	cout << "3.Dodaj" << endl;
	cout << "4.Znajdz" << endl;
	cout << "5.Utworz losowo" << endl;
	cout << "6.Wyswietl" << endl;
	cout << "7.Test (pomiary)" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}

Table myTab; //myTab może być dynamiczna, może byc takze zadeklarowana w manu_table albo tutaj jako zmienna globalna
List myList;
Heap myHeap;
BST_Tree myBSTTree;

void menu_table()
{
	char opt;
	string fileName;
	int index, value;

	do {
		displayMenu("--- TABLICA ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //tutaj wczytytwanie  tablicy z pliku
			cout << " Podaj nazwę zbioru:";
			cin >> fileName;
			myTab.loadFromFile(fileName);
			myTab.display();
			break;

		case '2': //tutaj usuwanie elemenu z tablicy
			cout << " podaj index:";
			cin >> index;
			myTab.deleteFromTable(index);
			myTab.display();
			break;

		case '3': //tutaj dodawanie elemetu do tablicy
			cout << " podaj index:";
			cin >> index;
			cout << " podaj wartość:";
			cin >> value;

			myTab.addValue(index, value);
			myTab.display();
			break;

		case '4': //tutaj znajdowanie elemetu w tablicy
			cout << " podaj wartosc:";
			cin >> value;
			if (myTab.IsValueInTable(value))
				cout << "podana wartosc jest w tablicy";
			else
				cout << "podanej wartosci NIE ma w tablicy";
			break;

		case '5':  //tutaj generowanie  tablicy
			cout << "Podaj ilosc elementów tablicy:";
			cin >> value;
			myTab.generateTable(value);
			myTab.display();
			break;

		case '6':  //tutaj wyświetlanie tablicy
			myTab.display();
			break;

		case '7': //tutaj nasza funkcja do eksperymentów (pomiary czasów i generowanie daneych) - nie będzie testowana przez prowadzącego 
			// można sobie tu dodać własne dodatkowe case'y
			cout << "Podaj ilosc elementów tablicy:";
			cin >> value;
			//for (int i = 0; i < 10; i++) {
			myTab.testFunc(value);
		//	}			
			// myTab.display();
			break;
		}

	} while (opt != '0');
}

void menu_list()
{
	//analogicznie jak menu_table()

	char opt;
	string fileName;
	int index, value;

	do {
		displayMenu("--- LISTA ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //tutaj wczytytwanie  tablicy z pliku
			cout << " Podaj nazwę zbioru:";
			cin >> fileName;
			myList.loadFromFile(fileName);
			myList.display();
			break;

		case '2': //tutaj usuwanie elemenu z tablicy
			cout << " podaj wartosc:";
			cin >> value;
			myList.deleteFromList(value);
			myList.display();
			break;

		case '3': //tutaj dodawanie elemetu do tablicy
			cout << " podaj index:";
			cin >> index;
			cout << " podaj wartość:";
			cin >> value;

			myList.insertValue(index, value);
			myList.display();
			break;

		case '4': //tutaj znajdowanie elemetu w tablicy
			cout << " podaj wartosc:";
			cin >> value;
			if (myList.IsValueInList(value))
				cout << "podana wartosc jest w tablicy";
			else
				cout << "podanej wartosci NIE ma w tablicy";
			break;

		case '5':  //tutaj generowanie  tablicy
			cout << "Podaj ilosc elementów tablicy:";
			cin >> value;
			myList.generateList(value);
			myList.display();
			break;

		case '6':  //tutaj wyświetlanie tablicy
			myList.display();
			break;

		case '7': //tutaj nasza funkcja do eksperymentów (pomiary czasów i generowanie daneych) - nie będzie testowana przez prowadzącego 
			// można sobie tu dodać własne dodatkowe case'y
			cout << "Podaj ilosc elementów tablicy:";
			cin >> value;
			for (int i = 0; i < 10; i++) {
				myList.testFunc(value);
			}
			myList.display();
			break;
		}

	} while (opt != '0');
}

void menu_heap()
{
	char opt;
	string fileName;
	int index, value;

	do {
		displayMenu("--- KOPIEC ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //tutaj wczytytwanie  tablicy z pliku
			cout << " Podaj nazwę zbioru:";
			cin >> fileName;
			myHeap.loadFromFile(fileName);
			myHeap.display();
			break;

		case '2': //tutaj usuwanie elemenu z tablicy
			cout << " podaj index:";
			cin >> index;
			myHeap.deleteFromHeap(index);
			myHeap.display();
			break;

		case '3': //tutaj dodawanie elemetu do tablicy
			cout << " podaj wartość:";
			cin >> value;

			myHeap.addValue(value);
			myHeap.display();
			break;

		case '4': //tutaj znajdowanie elemetu w tablicy
			cout << " podaj wartosc:";
			cin >> value;
			if (myHeap.isValueInHeap(value))
				cout << "podana wartosc jest w kopcu";
			else
				cout << "podanej wartosci NIE ma w kopcu";
			break;

		case '5':  //tutaj generowanie  tablicy
			cout << "Podaj ilosc elementów kopca:";
			cin >> value;
			// myHeap.generateTable(value);
			myHeap.display();
			break;

		case '6':  //tutaj wyświetlanie tablicy
			myHeap.display();
			// myHeap.displayHeap();
			break;

		case '7': //tutaj nasza funkcja do eksperymentów (pomiary czasów i generowanie daneych) - nie będzie testowana przez prowadzącego 
			// można sobie tu dodać własne dodatkowe case'y
			cout << "Podaj ilosc elementów kopca:";
			cin >> value;
			//for (int i = 0; i < 10; i++) {
			// myHeap.testFunc(value);
			//	}			
				// myTab.display();
			break;
		}

	} while (opt != '0');
}

void menu_BST_Tree()
{
	char opt;
	string fileName;
	int index, value;

	do {
		displayMenu("--- DRZEWO BST ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //tutaj wczytytwanie  tablicy z pliku
			cout << " Podaj nazwę zbioru:";
			cin >> fileName;
			myBSTTree.loadFromFile(fileName);
			myBSTTree.display();
			break;

		case '2': //tutaj usuwanie elemenu z tablicy
			cout << " podaj wartosc:";
			cin >> value;
			myBSTTree.deleteFromTree(value);
			myBSTTree.display();
			break;

		case '3': //tutaj dodawanie elemetu do tablicy
			cout << " podaj wartość:";
			cin >> value;

			myBSTTree.addValue(value);
			myBSTTree.display();
			break;

		case '4': //tutaj znajdowanie elemetu w tablicy
			cout << " podaj wartosc:";
			cin >> value;
			if (myBSTTree.isValueInTree(value))
				cout << "podana wartosc jest w kopcu";
			else
				cout << "podanej wartosci NIE ma w kopcu";
			break;

		case '5':  //tutaj generowanie  tablicy
			cout << "Podaj ilosc elementów kopca:";
			cin >> value;
			// myHeap.generateTable(value);
			myBSTTree.display();
			break;

		case '6':  //tutaj wyświetlanie tablicy
			myBSTTree.display();
			myBSTTree.displayTree();
			break;

		case '7': //tutaj nasza funkcja do eksperymentów (pomiary czasów i generowanie daneych) - nie będzie testowana przez prowadzącego 
			// można sobie tu dodać własne dodatkowe case'y
			// cout << "Podaj ilosc elementów kopca:";
			// cin >> value;
			//for (int i = 0; i < 10; i++) {
			// myHeap.testFunc(value);
			//	}			
				// myTab.display();
			myBSTTree.DSW();
			break;
		}

	} while (opt != '0');
}


int main(int argc, char* argv[])
{
	char option;
	do {
		cout << endl;
		cout << "==== MENU GLOWNE ===" << endl;
		cout << "1.Tablica" << endl;
		cout << "2.Lista" << endl;
		cout << "3.Kopiec" << endl;
		cout << "4.Drzewo BST" << endl;
		cout << "0.Wyjscie" << endl;
		cout << "Podaj opcje:";
		option = _getche();
		cout << endl;

		switch (option) {
		case '1':
			menu_table();
			break;

		case '2':
			menu_list();
			break;

		case '3':
			menu_heap();
			break;

		case '4':
			menu_BST_Tree();
			break;
		}
	} while (option != '0');

	return 0;
}
