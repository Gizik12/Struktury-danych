#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

// Węzeł
template<typename DataType>
class DoublyLinkedList_Node
{
public:
	// Konstruktor.
	DoublyLinkedList_Node(DataType Data);

	// Zwraca wartość węzła.
	DataType GetData() const { return m_Data; }

	// Zwraca poprzedni węzeł.
	DoublyLinkedList_Node<DataType>* GetPreviousNode() const { return m_PrevNode; }

	// Ustawia poprzedni węzeł.
	void SetPreviousNode(DoublyLinkedList_Node<DataType>* PreviousNode) { m_PrevNode = PreviousNode; }

	// Zwraca następny węzeł.
	DoublyLinkedList_Node<DataType>* GetNextNode() const { return m_NextNode; }

	// Ustawia następny węzeł.
	void SetNextNode(DoublyLinkedList_Node<DataType>* NextNode) { m_NextNode = NextNode; }

private:
	DataType m_Data;								// Wartość węzła.
	DoublyLinkedList_Node<DataType>* m_PrevNode;	// Wskaźnik na poprzedni węzeł.
	DoublyLinkedList_Node<DataType>* m_NextNode;	// Wskaźnik na następny węzeł.
};

// Lista
template<typename DataType>
class DoublyLinkedList
{
public:
	// Konstruktor.
	DoublyLinkedList();

	// Destruktor.
	~DoublyLinkedList();

	// Dodaje węzeł na początku listy.
	void PushFront(DataType Element);

	// Dodaje węzeł na końcu listy.
	void PushBack(DataType Element);

	// Usuwa węzeł na początku listy.
	void PopFront();

	// Usuwa węzeł na końcu listy.
	void PopBack();

	// Dodaje węzeł przed wybranym miejscem na liście.
	void InsertBefore(DataType Element, unsigned int Index);

	// Dodaje węzeł po wybranym miejscu na liście.
	void InsertAfter(DataType Element, unsigned int Index);

	// Usuwa węzeł na określonej pozycji listy.
	void RemoveAt(unsigned int Index);

	// Szuka podanego elementu w tablicy i zwraca adres jego pierwszej instancji.
	DoublyLinkedList_Node<DataType>* SearchForward(DataType Element);

	// Szuka podanego elementu w tablicy i zwraca adres jego pierwszej instancji.
	DoublyLinkedList_Node<DataType>* SearchBackward(DataType Element);

	// Sprawdza czy tablica jest pusta.
	bool IsEmpty() { return m_Size ? false : true; }

	// Zwraca liczbę elementów w tablicy.
	int GetSize() const { return m_Size; }

	// Zwraca "głowę" listy.
	DoublyLinkedList_Node<DataType>* GetHeadNode() const { return m_HeadNode; }

	// Ustawia "głowę" listy.
	void SetHeadNode(DoublyLinkedList_Node<DataType>* HeadNode) { m_HeadNode = HeadNode; }

	// Zwraca "ogon" listy.
	DoublyLinkedList_Node<DataType>* GetTailNode() const { return m_TailNode; }

	// Ustawia "ogon" listy.
	void SetTailNode(DoublyLinkedList_Node<DataType>* TailNode) { m_TailNode = TailNode; }

private:
	unsigned int m_Size;							// Liczba elementów na liście.
	DoublyLinkedList_Node<DataType>* m_HeadNode;	// Pierwszy element listy.
	DoublyLinkedList_Node<DataType>* m_TailNode;	// Ostatni element listy.

	// Wstawia nowy węzeł między dwa podane węzły.
	void InsertBetween(DoublyLinkedList_Node<DataType>* InsertedNode, DoublyLinkedList_Node<DataType>* PreviousNode, DoublyLinkedList_Node<DataType>* NextNode);
};

template<typename DataType>
DoublyLinkedList_Node<DataType>::DoublyLinkedList_Node(DataType Data)
	: m_Data(Data), m_PrevNode(nullptr), m_NextNode(nullptr) { }

template<typename DataType>
DoublyLinkedList<DataType>::DoublyLinkedList()
	: m_Size(0), m_HeadNode(nullptr), m_TailNode(nullptr) { }

template<typename DataType>
DoublyLinkedList<DataType>::~DoublyLinkedList() { }

template<typename DataType>
void DoublyLinkedList<DataType>::PushFront(DataType Element)
{
	DoublyLinkedList_Node<DataType>* NewNode = new DoublyLinkedList_Node<DataType>(Element); // Utworzenie nowego węzła.
	if (IsEmpty())
	{
		m_TailNode = NewNode; // Jeśli lista jest pusta ustawia NewNode również jako m_TailNode.
	}
	else
	{
		NewNode->SetNextNode(m_HeadNode);		// Następnym węzłem NewNode jest bieżący HeadNode.
		m_HeadNode->SetPreviousNode(NewNode);	// Poprzednim węzłem bieżącego HeadNode jest NewNode.
	}
	m_HeadNode = NewNode; // NewNode zostaje ustawiony jako nowy HeadNode.
	++m_Size;
}

template<typename DataType>
void DoublyLinkedList<DataType>::PushBack(DataType Element)
{
	DoublyLinkedList_Node<DataType>* NewNode = new DoublyLinkedList_Node<DataType>(Element); // Utworzenie nowego węzła.
	if (IsEmpty())
	{
		m_HeadNode = NewNode; // Jeśli lista jest pusta ustawia NewNode również jako m_HeadNode.
	}
	else
	{
		NewNode->SetPreviousNode(m_TailNode); // Poprzednim węzłem NewNode jest bieżący TailNode.
		m_TailNode->SetNextNode(NewNode);	  // Następnym węzłem bieżącego TailNode jest NewNode.
	}
	m_TailNode = NewNode; // NewNode zostaje ustawiony jako nowy TailNode.
	++m_Size;
}

template<typename DataType>
void DoublyLinkedList<DataType>::PopFront()
{
	if (!IsEmpty())
	{
		DoublyLinkedList_Node<DataType>* OldHeadNode = m_HeadNode; // OldHeadNode jest wskaźnikiem na stary HeadNode.

		m_HeadNode = m_HeadNode->GetNextNode(); // Węzeł po HeadNode jest nowym HeadNode.
		m_HeadNode->SetPreviousNode(nullptr);

		delete OldHeadNode; // Usunięcie starego HeadNode.
		--m_Size;
	}
}

template<typename DataType>
void DoublyLinkedList<DataType>::PopBack()
{
	if (!IsEmpty())
	{
		DoublyLinkedList_Node<DataType>* OldTailNode = m_TailNode; // OldTailNode jest wskaźnikiem na stary TailNode.

		m_TailNode = m_TailNode->GetPreviousNode(); // Węzeł przed TailNode jest nowym TailNode.
		m_TailNode->SetNextNode(nullptr);

		delete OldTailNode; // Usunięcie starego HeadNode.
		--m_Size;
	}
}

template<typename DataType>
void DoublyLinkedList<DataType>::InsertBefore(DataType Element, unsigned int Index)
{
	DoublyLinkedList_Node<DataType>* NewNode = new DoublyLinkedList_Node<DataType>(Element); // Utworzenie nowego węzła.
	DoublyLinkedList_Node<DataType>* CurrentNode;

	if (Index == 0)
	{
		PushFront(Element);
	}
	else if (Index < m_Size && Index <= (m_Size / 2)) // Jeśli indeks leży w pierwszej połowie listy.
	{
		CurrentNode = m_HeadNode; // Szukanie od początku listy.
		for (unsigned int i = 0; i < Index; i++)
		{
			CurrentNode = CurrentNode->GetNextNode(); // Przechodzenie po następnych węzłach.
		}

		InsertBetween(NewNode, CurrentNode->GetPreviousNode(), CurrentNode);
	}
	else if (Index < m_Size && Index >(m_Size / 2)) // Jeśli indeks leży w drugiej połowie listy.
	{
		CurrentNode = m_TailNode; // Szukanie od końca listy.
		for (unsigned int i = m_Size - 1; i > Index; i--)
		{
			CurrentNode = CurrentNode->GetPreviousNode(); // Przechodzenie po poprzednich węzłach.
		}

		InsertBetween(NewNode, CurrentNode->GetPreviousNode(), CurrentNode);
	}
}

template<typename DataType>
void DoublyLinkedList<DataType>::InsertAfter(DataType Element, unsigned int Index)
{
	DoublyLinkedList_Node<DataType>* NewNode = new DoublyLinkedList_Node<DataType>(Element); // Utworzenie nowego węzła.
	DoublyLinkedList_Node<DataType>* CurrentNode;

	if (Index == m_Size - 1)
	{
		PushBack(Element);
	}
	else if (Index < m_Size && Index <= (m_Size / 2)) // Jeśli indeks leży w pierwszej połowie listy.
	{
		CurrentNode = m_HeadNode; // Szukanie od początku listy.
		for (unsigned int i = 0; i < Index; i++)
		{
			CurrentNode = CurrentNode->GetNextNode(); // Przechodzenie po następnych węzłach.
		}

		InsertBetween(NewNode, CurrentNode, CurrentNode->GetNextNode());
	}
	else if (Index < m_Size && Index > m_Size / 2) // Jeśli indeks leży w drugiej połowie listy.
	{
		CurrentNode = m_TailNode; // Szukanie od końca listy.
		for (unsigned int i = m_Size - 1; i > Index; i--)
		{
			CurrentNode = CurrentNode->GetPreviousNode(); // Przechodzenie po poprzednich węzłach.
		}

		InsertBetween(NewNode, CurrentNode, CurrentNode->GetNextNode());
	}
}

template<typename DataType>
void DoublyLinkedList<DataType>::RemoveAt(unsigned int Index)
{
	if (!IsEmpty())
	{
		DoublyLinkedList_Node<DataType>* CurrentNode;

		if (Index == 0)
		{
			PopFront();
		}
		else if (Index == m_Size - 1)
		{
			PopBack();
		}
		else if (Index < m_Size && Index <= (m_Size / 2)) // Jeśli indeks leży w pierwszej połowie listy.
		{
			CurrentNode = m_HeadNode; // Szukanie od początku listy.
			for (unsigned int i = 0; i < Index; i++)
			{
				CurrentNode = CurrentNode->GetNextNode(); // Przechodzenie po następnych węzłach.
			}

			CurrentNode->GetPreviousNode()->SetNextNode(CurrentNode->GetNextNode());		// Ustawia wskaźnik NextNode poprzedniego węzła na następny węzeł po CurrentNode.
			CurrentNode->GetNextNode()->SetPreviousNode(CurrentNode->GetPreviousNode());	// Ustawia wskaźnik PrevNode następnego węzła na poprzedni węzeł przed CurrentNode.
			delete CurrentNode;
			--m_Size;
		}
		else if (Index < m_Size && Index > m_Size / 2) // Jeśli indeks leży w drugiej połowie listy.
		{
			CurrentNode = m_TailNode; // Szukanie od końca listy.
			for (unsigned int i = m_Size - 1; i > Index; i--)
			{
				CurrentNode = CurrentNode->GetPreviousNode(); // Przechodzenie po poprzednich węzłach.
			}

			CurrentNode->GetPreviousNode()->SetNextNode(CurrentNode->GetNextNode());		// Ustawia wskaźnik NextNode poprzedniego węzła na następny węzeł.
			CurrentNode->GetNextNode()->SetPreviousNode(CurrentNode->GetPreviousNode());	// Ustawia wskaźnik PrevNode następnego węzła na poprzedni węzeł.
			delete CurrentNode;
			--m_Size;
		}
	}
}

template<typename DataType>
DoublyLinkedList_Node<DataType>* DoublyLinkedList<DataType>::SearchForward(DataType Element)
{
	DoublyLinkedList_Node<DataType>* CurrentNode = m_HeadNode; // Szukanie od początku listy.

	while (CurrentNode != nullptr)
	{
		if (CurrentNode->GetData() == Element)
		{
			return CurrentNode; // Zwraca adres pierwszej instancji podanego elementu.
		}
		CurrentNode = CurrentNode->GetNextNode(); // Przechodzenie po następnych węzłach.
	}
	return nullptr; // Jeśli nie znajdzie podanego elementu zwraca nullptr.
}

template<typename DataType>
DoublyLinkedList_Node<DataType>* DoublyLinkedList<DataType>::SearchBackward(DataType Element)
{
	DoublyLinkedList_Node<DataType>* CurrentNode = m_TailNode; // Szukanie od końca listy.

	while (CurrentNode != nullptr)
	{
		if (CurrentNode->GetData() == Element)
		{
			return CurrentNode; // Zwraca adres pierwszej instancji podanego elementu.
		}
		CurrentNode = CurrentNode->GetPreviousNode(); // Przechodzenie po poprzednich węzłach.
	}
	return nullptr; // Jeśli nie znajdzie podanego elementu zwraca nullptr.
}

template<typename DataType>
void DoublyLinkedList<DataType>::InsertBetween(DoublyLinkedList_Node<DataType>* NewNode, DoublyLinkedList_Node<DataType>* PreviousNode, DoublyLinkedList_Node<DataType>* NextNode)
{
	PreviousNode->SetNextNode(NewNode);		// Ustawia wskaźnik NextNode poprzedniego węzła na nowy węzeł.
	NewNode->SetPreviousNode(PreviousNode);	// Ustawia wskaźnik PrevNode nowego węzła na poprzedni węzeł.
	NewNode->SetNextNode(NextNode);			// Ustawia wskaźnik NextNode nowego węzła na następny węzeł.
	NextNode->SetPreviousNode(NewNode);		// Ustawia wskaźnik PrevNode następnego węzła na nowy węzeł.
	++m_Size;
}


#endif // DOUBLY_LINKED_LIST