#include <iostream>
#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST

template<typename DataType>
class Node
{
	private:
	DataType data;  // Wartość węzła.
	Node* next; 	// Wskaźnik na następny element.

	public:
	Node(DataType d) // Konstruktor węzła (ustawienie domyślych danych).
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
	Node<DataType>* firstElement;		// Wskaźnik na pierwszy element tablicy.

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
	this->firstElement= nullptr;
}

template<typename DataType>
void SinglyLinkedList<DataType>::pushFront(DataType Element)
{
	Node<DataType>* newNode = new Node<DataType>(Element); // Tworzenie nowego węzła z podanym elementem.
	if (this->m_Size == 0)
	{
		this->firstElement = newNode;
	}
	else
	{
		newNode->next = this->firstElement; // Ustawienie wskaźnika next nowego węzła na obecny pierwszy element.
		this->firstElement = newNode; 		// Nowy węzeł staje się pierwszym elementem listy.
    }
	this->m_Size++;
}

template<typename DataType>
void SinglyLinkedList<DataType>::pushBack(DataType Element)
{
	Node<DataType>* newNode = new Node<DataType>(Element); // Tworzenie nowego węzła z podanym elementem.
	if (this->m_Size == 0)
	{
		this->firstElement = newNode;
	}
	else
	{
		Node<DataType>* currentNode = this->firstElement;
		while (currentNode->next != nullptr) // Pętla szukająca ostaniego elementu listy.
		{
			currentNode = currentNode->next; // Przechodzi dalej po kolejnych elementach listy.
		}
		currentNode->next = newNode; // Ustawienie wskaźnika ostatniego elementu na nowy ostatni element.
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
	Node<DataType>* newNode = new Node<DataType>(Element); // Tworzenie nowego węzła z podanym elementem.
	Node<DataType>* currentNode = this->firstElement;
	for (unsigned int i = 0; i < Index - 1; i++) // Przesuń się do elementu poprzedzającego wstawiany indeks.
    {
        currentNode = currentNode->next;
    }
	newNode->next = currentNode->next; // Nowy element wskazuje na następny element.
    currentNode->next = newNode; // Poprzedni element wskazuje na nowy element.
	this->m_Size++;
	
}

template<typename DataType>
void SinglyLinkedList<DataType>::popFront()
{
	if (this->m_Size != 0)
	{
		Node<DataType>* currentNode = this->firstElement;
		this->firstElement = this->firstElement->next; // Przesuwa wskaźnik na pierwszy element na następny.
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
   		Node<DataType>* currentNode = this->firstElement;
    	while (currentNode->next->next != nullptr) // Pętla znajduje przedostatni element.
    	{
        	currentNode = currentNode->next;
    	}

    	delete currentNode->next; // Usuwa ostatni element.
    	currentNode->next = nullptr; // Ustawia wskaźnik next ostatniego elementu na nullptr.
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
		Node<DataType>* currentNode = this->firstElement;
		for (unsigned int i = 0; i < Index - 1; i++) // Przesuwamy się do elementu poprzedzającego wstawiany indeks.
		{
			currentNode = currentNode->next;
		}

		Node<DataType>* temp = currentNode->next; // Zachowaj wskaźnik do elementu, który chcemy usunąć.
		currentNode->next = temp->next; // Zaktualizuj wskaźnik poprzedniego elementu, aby ominąć element, który usuwamy.
		delete temp; // Usuń element z listy.
		m_Size--; // Zmniejsz licznik elementów.
	}
}
#endif