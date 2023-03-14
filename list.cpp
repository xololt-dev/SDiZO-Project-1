#include "list.hpp"
#include <iostream>
#include <fstream>

List::List()
{
	cnt = 0;
	firstMember = lastMember = NULL;
}

List::~List()
{
	ListMember* temp;

	while (firstMember != lastMember) {
		temp = firstMember->next;
		delete firstMember;
		firstMember = temp;
	}
	delete lastMember;
}

/// <summary>
/// Load numbers from file
/// </summary>
/// <param name="FileName - name of the file we want to open"></param>
/// <returns></returns>
int List::loadFromFile(std::string FileName)
{
	std::fstream file;
	file.open(FileName, std::ios::in);
	if (file.good()) {
		int temp = 0;

		if (cnt) {
			ListMember* tempLM;

			// clear the list
			while (firstMember != firstMember) {
				tempLM = firstMember->next;
				delete firstMember;
				firstMember = tempLM;
				display();
			}
			
			lastMember = firstMember = NULL;
			
			cnt = 0;
		}

		file >> cnt;

		while (file >> temp) {
			push_backValue(temp, false);
		}

		file.close();
	}
	else {
		std::cout << "Plik nie zostal otworzony!\n";
	}

	return 0;
}

/// <summary>
/// Check if the value is on the list
/// </summary>
/// <param name="value - value to be searched for"></param>
/// <returns> bool </returns>
bool List::IsValueInList(int value)
{
	ListMember* temp = firstMember;
	for (int i = 0; i < cnt; i++) {
		if (temp->data == value) return true;
		else temp = temp->next;
	}
	return false;
}

/// <summary>
/// Insert value to the list
/// </summary>
/// <param name="index - place where to put the value"></param>
/// <param name="value - value to be inserted"></param>
void List::insertValue(int index, int value)
{
	// std::cout << "Przed: \n";
	// display();

	// if list empty simply set value at index 0
	if (firstMember == NULL && lastMember == NULL) {
		ListMember* temp = new ListMember;
		temp->data = value;
		temp->prev = NULL;
		temp->next = NULL;
		
		firstMember = temp;
		lastMember = temp;

		cnt++;
		return;
	}

	ListMember* temp;
	ListMember* tempNew = new ListMember;

	tempNew->data = value;

	// searching from the "bottom"
	if (index <= cnt / 2) {
		temp = firstMember;
		/*
		for (int i = 0; i < cnt; i++) {
			if (i != index) temp = temp->next;
			else {
				tempNew->prev = temp->prev;
				tempNew->next = temp;

				temp->prev = tempNew;
				temp->prev->next = tempNew;
				if (!index) firstMember = tempNew;
				break;
			}
		}
		*/
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}
		tempNew->prev = temp->prev;
		tempNew->next = temp;	
		
		if (index == 0) firstMember = tempNew;
		else temp->prev->next = tempNew;

		temp->prev = tempNew;
	}
	// searching from the "top"
	else {
		temp = lastMember;

		for (int i = cnt - 1; i >= 0; i--) {
			if (index >= cnt) break; 
			temp = temp->prev;
			if (i == index) break;
		}

		// if index value was higher than the length of the list, we assume it should go to the last position
		if (index >= cnt) {
			tempNew->next = NULL;
			lastMember = tempNew;
		}
		else {
			tempNew->next = temp->next;
			tempNew->next->prev = tempNew;
		}
		tempNew->prev = temp;
		temp->next = tempNew;
	}
	cnt++;

	// std::cout << "\nPo: \n";
}

/// <summary>
/// Add value at the beginning of the list
/// </summary>
/// <param name="value - value to be saved to the list"></param>
void List::push_frontValue(int value)
{
	ListMember* temp;

	temp = new ListMember;

	if (firstMember != NULL) firstMember->prev = temp;

	temp->data = value;
	temp->next = firstMember;
	temp->prev = NULL;

	firstMember = temp;

	if (lastMember == NULL) lastMember = temp;

	cnt++;
}

/// <summary>
/// Add value at the back of the list
/// </summary>
/// <param name="value - value to be saved to the list"></param>
void List::push_backValue(int value, bool increment)
{
	ListMember* temp = new ListMember;

	if (lastMember != NULL) lastMember->next = temp;

	temp->data = value;
	temp->next = NULL;
	temp->prev = lastMember;

	lastMember = temp;

	if (firstMember == NULL) firstMember = temp;

	if (increment) cnt++;
}

/// <summary>
/// Delete value at index from the list
/// </summary>
/// <param name="value - value to delete from the list, if exists"></param>
void List::deleteFromList(int value)
{
	// if list is empty, return with information
	if (!cnt) {
		//std::cout << "Lista jest pusta! \n";
		return;
	}

	ListMember* temp = firstMember;

	for (int i = 0; i < cnt; i++) {
		// go through each list member until value is found
		if (temp->data != value) {
			temp = temp->next;
		}
		else {
			// std::cout << "Przed: \n";
			// display();
			/*
			// checks for last/first elements
			if (temp->prev == NULL) {
				temp->next->prev = NULL;
				firstMember = temp->next;				
			}
			else temp->prev->next = temp->next;
			if (temp->next == NULL) {
				lastMember = temp->prev;
				temp->prev->next = NULL;
			}
			else temp->next->prev = temp->prev;
			*/
			if (temp->prev == NULL) {
				if (temp->next == NULL) firstMember = lastMember = NULL;
				else {
					temp->next->prev = NULL;
					firstMember = temp->next;
				}
			}
			else {
				temp->prev->next = temp->next;
				if (temp->next == NULL) {
					lastMember = temp->prev;
					temp->prev->next = NULL;
				}
				else temp->next->prev = temp->prev;
			}

			delete temp;
			//std::cout <<
				// "Usunieto wartosc " << value << "\n";
			cnt--;

			// std::cout << "\nPo: \n";
			return;			
		}
	}
	// if value not found, return a message
	std::cout << "Nie znaleziono wartosci do usuniecia!\n";
}

/// <summary>
/// Delete first value from the list
/// </summary>
void List::pop_frontFromList()
{
	if (firstMember) {
		ListMember* temp = firstMember;

		firstMember = temp->next;
		if (firstMember == NULL) lastMember = NULL;
		else firstMember->prev = NULL;

		delete temp;

		cnt--;
	}
}

/// <summary>
/// Delete last value from the list
/// </summary>
void List::pop_backFromList()
{
	if (lastMember) {
		ListMember* temp = lastMember;

		lastMember = temp->prev;
		if (lastMember == NULL) firstMember = NULL;
		else lastMember->next = NULL;

		delete temp;

		cnt--;
	}
}

/// <summary>
/// Display the list
/// </summary>
void List::display()
{
	ListMember* temp;

	if (!firstMember) std::cout << "Lista jest pusta." << std::endl;
	else
	{
		std::cout << "Size: " << cnt << "\n";
		temp = firstMember;
		while (temp)
		{
			std::cout << temp->data << " "; //<< "\n";
			temp = temp->next;
		}
		std::cout << "\n" << std::endl;
		temp = lastMember;
		while (temp)
		{
			std::cout << temp->data << " "; //<< "\n";
			temp = temp->prev;
		}
		std::cout << std::endl;
	}
}

/// <summary>
/// Generate/increase list size using push_back by size parameter
/// </summary>
/// <param name="size - requested amount of values to be inserted into the list"></param>
void List::generateList(int size)
{
	for (int i = 0; i < size; i++) {
		// list->push_backValue(i);
		this->push_backValue(i);
	}
}
