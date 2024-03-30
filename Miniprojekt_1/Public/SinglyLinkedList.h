#include <iostream>
#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST

template<typename DataType>
class SinglyLinkedList_Node
{
private:
	DataType data;  // Wartość węzła.
	SinglyLinkedList_Node* next; 	// Wskaźnik na następny element.
public:
	SinglyLinkedList_Node(DataType d) // Konstruktor węzła (ustawienie domyślych danych).
	{
		this->data = d;
		this->next = nullptr;
	}
};

template<typename DataType>
class SinglyLinkedList
{
private:
	unsigned int m_Size;	// Liczba elementów w tablicy.
	SinglyLinkedList_Node<DataType>* firstElement;		// Wskaźnik na pierwszy element tablicy.

public:
	// Konstruktor
	SinglyLinkedList();

	// Destruktor
	~SinglyLinkedList();

	// Zwraca liczbę elementów w tablicy.
	int GetSize() const { return m_Size; }

	// Dodaje element na początku listy.
	void pushFront(DataType Element);

	// Dodaje element na końcu listy.
	void pushBack(DataType Element);

	// Dodaje element na określonej pozycji listy.
	void addAtIndex(DataType Element, unsigned int Index);

	// Usuwa element na początku listy.
	void popFront();

	// Usuwa element na końcu listy.
	void popBack();

	// Usuwa element na określonej pozycji listy.
	void subtractAtIndex(unsigned int Index);

};
template<typename DataType>
SinglyLinkedList<DataType>::SinglyLinkedList()
{
	this->m_Size = 0;
	this->firstElement = nullptr;
}

template<typename DataType>
SinglyLinkedList<DataType>::~SinglyLinkedList()
{
	while(this->m_Size == 0)
	{
		popFront();
	}
}

template<typename DataType>
void SinglyLinkedList<DataType>::pushFront(DataType Element)
{
	SinglyLinkedList_Node<DataType>* newNode = new SinglyLinkedList_Node<DataType>(Element); // Tworzenie nowego węzła z podanym elementem.
	if (this->m_Size == 0)
	{
		this->firstElement = newNode;
	}
	else
	{
		newNode->getNext() = this->firstElement; // Ustawienie wskaźnika next nowego węzła na obecny pierwszy element.
		this->firstElement = newNode; 		// Nowy węzeł staje się pierwszym elementem listy.
	}
	this->m_Size++;
}

template<typename DataType>
void SinglyLinkedList<DataType>::pushBack(DataType Element)
{
	SinglyLinkedList_Node<DataType>* newNode = new SinglyLinkedList_Node<DataType>(Element); // Tworzenie nowego węzła z podanym elementem.
	if (this->m_Size == 0)
	{
		this->firstElement = newNode;
	}
	else
	{
		SinglyLinkedList_Node<DataType>* currentNode = this->firstElement;
		while (currentNode->next != nullptr) // Pętla szukająca ostaniego elementu listy.
		{
			currentNode = currentNode->getNext(); // Przechodzi dalej po kolejnych elementach listy.
		}
		currentNode->getNext() = newNode; // Ustawienie wskaźnika ostatniego elementu na nowy ostatni element.
	}
	this->m_Size++;
}

template<typename DataType>
void SinglyLinkedList<DataType>::addAtIndex(DataType Element, unsigned int Index)
{
	if (Index >= this->m_Size) // Jeśli indeks jest równy lub większy od rozmiaru tablicy dodajemy element na koncu tablicy.
	{
		pushBack(Element);
		return;
	}
	if (Index == 0) // Jeśli indeks jest równy 0 dodajemy element na początku tablicy.
	{
		pushFront(Element);
		return;
	}
	SinglyLinkedList_Node<DataType>* newNode = new SinglyLinkedList_Node<DataType>(Element); // Tworzenie nowego węzła z podanym elementem.
	SinglyLinkedList_Node<DataType>* currentNode = this->firstElement;
	for (unsigned int i = 0; i < Index - 1; i++) // Przesuń się do elementu poprzedzającego wstawiany indeks.
    {
        currentNode = currentNode->getNext();
    }
	newNode->getNext() = currentNode->getNext(); // Nowy element wskazuje na następny element.
    currentNode->getNext() = newNode; // Poprzedni element wskazuje na nowy element.

	this->m_Size++;

}

template<typename DataType>
void SinglyLinkedList<DataType>::popFront()
{
	if (this->m_Size != 0)
	{
		SinglyLinkedList<DataType>* currentNode = this->firstElement;
		this->firstElement = this->firstElement->getNext(); // Przesuwa wskaźnik na pierwszy element na następny.
		delete currentNode; // Usuwa pierwszy element.
		this->m_Size--; // Zmniejsz licznik elementów.
	}
}

template<typename DataType>
void SinglyLinkedList<DataType>::popBack()
{
	if (this->m_Size != 0)
	{
		if (this->m_Size == 1)
		{
			delete this->firstElement;
			this->firstElement = nullptr;
			this->m_Size = 0;
			return;
		}
		SinglyLinkedList_Node<DataType>* currentNode = this->firstElement;
		while (currentNode->next->next != nullptr) // Pętla znajduje przedostatni element.
		{
			currentNode = currentNode->next;
		}
   		SinglyLinkedList<DataType>* currentNode = this->firstElement;
    	while (currentNode->getNext()->getNext() != nullptr) // Pętla znajduje przedostatni element.
    	{
        	currentNode = currentNode->getNext();
    	}

    	delete currentNode->getNext(); // Usuwa ostatni element.
    	currentNode->getNext() = nullptr; // Ustawia wskaźnik next ostatniego elementu na nullptr.
    	m_Size--;
	}
}

template<typename DataType>
void SinglyLinkedList<DataType>::subtractAtIndex(unsigned int Index)
{
	if (this->m_Size != 0)
	{
		if (Index >= this->m_Size) // Jeśli indeks jest równy lub większy od rozmiaru tablicy wypisujemy ostrzeżenie.
		{
			std::cout << "Indeks wykracza poza zakres listy" << std::endl;
			return;
		}
		if (Index == 0) // Jeśli indeks jest równy 0 usuwamy element na początku tablicy.
		{
			popFront();
			return;
		}
		SinglyLinkedList_Node<DataType>* currentNode = this->firstElement;
		for (unsigned int i = 0; i < Index - 1; i++) // Przesuwamy się do elementu poprzedzającego wstawiany indeks.
		{
			currentNode = currentNode->getNext();
		}
		SinglyLinkedList<DataType>* temp = currentNode->getNext(); // Zachowaj wskaźnik do elementu, który chcemy usunąć.
		currentNode->getNext() = temp->getNext(); // Zaktualizuj wskaźnik poprzedniego elementu, aby ominąć element, który usuwamy.
		delete temp; // Usuń element z listy.
		m_Size--; // Zmniejsz licznik elementów.
	}
}
#endif