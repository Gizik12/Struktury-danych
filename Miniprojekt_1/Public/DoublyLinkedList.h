#include "DataStructure.h"
#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

// Węzeł
template<typename DataType>
class DoublyLinkedList_Node final
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
class DoublyLinkedList final : public DataStructure<DataType>
{
public:
	// Konstruktor.
	DoublyLinkedList();

	// Destruktor.
	~DoublyLinkedList();

	// Dodaje węzeł na początku listy.
	virtual void PushFront(DataType Element) override;

	// Dodaje węzeł na końcu listy.
	virtual void PushBack(DataType Element) override;

	// Usuwa węzeł na początku listy.
	virtual void PopFront() override;

	// Usuwa węzeł na końcu listy.
	virtual void PopBack() override;

	// Dodaje węzeł w wybrane miejsce na liście.
	virtual void Insert(DataType Element, unsigned int Index) override;

	// Usuwa węzeł na określonej pozycji listy.
	virtual void RemoveAt(unsigned int Index) override;

	// Przeszukuje strukturę od początku do końca w celu znalezienia wybranego elementu w strukturze i zwraca liczbę jego wystąpień
	virtual unsigned int SearchForElementForward(DataType Element) override;

	// Przeszukuje strukturę od końca do początku w celu znalezienia wybranego elementu w strukturze i zwraca liczbę jego wystąpień
	unsigned int SearchForElementBackward(DataType Element);

	// Tworzy kopie struktury (stosowane w badaniach)
	virtual DataStructure<DataType>* Clone() const override { return new DoublyLinkedList<DataType>(); };

	// Zwraca "głowę" listy.
	DoublyLinkedList_Node<DataType>* GetHeadNode() const { return m_HeadNode; }

	// Ustawia "głowę" listy.
	void SetHeadNode(DoublyLinkedList_Node<DataType>* HeadNode) { m_HeadNode = HeadNode; }

	// Zwraca "ogon" listy.
	DoublyLinkedList_Node<DataType>* GetTailNode() const { return m_TailNode; }

	// Ustawia "ogon" listy.
	void SetTailNode(DoublyLinkedList_Node<DataType>* TailNode) { m_TailNode = TailNode; }

private:
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
	: m_HeadNode(nullptr), m_TailNode(nullptr) { }

template<typename DataType>
DoublyLinkedList<DataType>::~DoublyLinkedList() 
{ 
	if (!DataStructure<DataType>::IsEmpty())
	{
		DoublyLinkedList_Node<DataType>* CurrentNode;

		do
		{
			CurrentNode = m_HeadNode;
			m_HeadNode = m_HeadNode->GetNextNode();
			delete CurrentNode;
		} while (m_HeadNode->GetNextNode() != nullptr);

		delete m_HeadNode;
	}
}

template<typename DataType>
void DoublyLinkedList<DataType>::PushFront(DataType Element)
{
	DoublyLinkedList_Node<DataType>* NewNode = new DoublyLinkedList_Node<DataType>(Element); // Utworzenie nowego węzła.
	if (DataStructure<DataType>::IsEmpty())
	{
		m_TailNode = NewNode; // Jeśli lista jest pusta ustawia NewNode również jako m_TailNode.
	}
	else
	{
		NewNode->SetNextNode(m_HeadNode);		// Następnym węzłem NewNode jest bieżący HeadNode.
		m_HeadNode->SetPreviousNode(NewNode);	// Poprzednim węzłem bieżącego HeadNode jest NewNode.
	}
	m_HeadNode = NewNode; // NewNode zostaje ustawiony jako nowy HeadNode.
	++DataStructure<DataType>::m_Size;
}

template<typename DataType>
void DoublyLinkedList<DataType>::PushBack(DataType Element)
{
	DoublyLinkedList_Node<DataType>* NewNode = new DoublyLinkedList_Node<DataType>(Element); // Utworzenie nowego węzła.
	if (DataStructure<DataType>::IsEmpty())
	{
		m_HeadNode = NewNode; // Jeśli lista jest pusta ustawia NewNode również jako m_HeadNode.
	}
	else
	{
		NewNode->SetPreviousNode(m_TailNode); // Poprzednim węzłem NewNode jest bieżący TailNode.
		m_TailNode->SetNextNode(NewNode);	  // Następnym węzłem bieżącego TailNode jest NewNode.
	}
	m_TailNode = NewNode; // NewNode zostaje ustawiony jako nowy TailNode.
	++DataStructure<DataType>::m_Size;
}

template<typename DataType>
void DoublyLinkedList<DataType>::PopFront()
{
	if (!DataStructure<DataType>::IsEmpty())
	{
		if (m_HeadNode == m_TailNode) // Jeśli jest tylko jeden węzeł.
		{
			delete m_HeadNode;
			m_HeadNode = nullptr;
			m_TailNode = nullptr;
		}
		else
		{
			DoublyLinkedList_Node<DataType>* OldHeadNode = m_HeadNode; // OldHeadNode jest wskaźnikiem na stary HeadNode.

			m_HeadNode = m_HeadNode->GetNextNode(); // Węzeł po HeadNode jest nowym HeadNode.
			m_HeadNode->SetPreviousNode(nullptr);

			delete OldHeadNode; // Usunięcie starego HeadNode.
		}
		--DataStructure<DataType>::m_Size;
	}
}

template<typename DataType>
void DoublyLinkedList<DataType>::PopBack()
{
	if (!DataStructure<DataType>::IsEmpty())
	{
		if (m_HeadNode == m_TailNode) // Jeśli jest tylko jeden węzeł.
		{
			delete m_HeadNode;
			m_HeadNode = nullptr;
			m_TailNode = nullptr;
		}
		else
		{
			DoublyLinkedList_Node<DataType>* OldTailNode = m_TailNode; // OldTailNode jest wskaźnikiem na stary TailNode.

			m_TailNode = m_TailNode->GetPreviousNode(); // Węzeł przed TailNode jest nowym TailNode.
			m_TailNode->SetNextNode(nullptr);

			delete OldTailNode; // Usunięcie starego HeadNode.
		}
		--DataStructure<DataType>::m_Size;
	}
}

template<typename DataType>
void DoublyLinkedList<DataType>::Insert(DataType Element, unsigned int Index)
{
	DoublyLinkedList_Node<DataType>* NewNode = new DoublyLinkedList_Node<DataType>(Element); // Utworzenie nowego węzła.
	DoublyLinkedList_Node<DataType>* CurrentNode;

	if (Index == 0)
	{
		PushFront(Element);
	}
	else if (Index < DataStructure<DataType>::m_Size && Index <= (DataStructure<DataType>::m_Size / 2)) // Jeśli indeks leży w pierwszej połowie listy.
	{
		CurrentNode = m_HeadNode; // Szukanie od początku listy.
		for (unsigned int i = 0; i < Index; i++)
		{
			CurrentNode = CurrentNode->GetNextNode(); // Przechodzenie po następnych węzłach.
		}

		InsertBetween(NewNode, CurrentNode->GetPreviousNode(), CurrentNode);
	}
	else if (Index < DataStructure<DataType>::m_Size && Index >(DataStructure<DataType>::m_Size / 2)) // Jeśli indeks leży w drugiej połowie listy.
	{
		CurrentNode = m_TailNode; // Szukanie od końca listy.
		for (unsigned int i = DataStructure<DataType>::m_Size - 1; i > Index; i--)
		{
			CurrentNode = CurrentNode->GetPreviousNode(); // Przechodzenie po poprzednich węzłach.
		}

		InsertBetween(NewNode, CurrentNode->GetPreviousNode(), CurrentNode);
	}
}

template<typename DataType>
void DoublyLinkedList<DataType>::RemoveAt(unsigned int Index)
{
	if (!DataStructure<DataType>::IsEmpty())
	{
		if (m_HeadNode == m_TailNode) // Jeśli jest tylko jeden węzeł.
		{
			delete m_HeadNode;
			m_HeadNode = nullptr;
			m_TailNode = nullptr;
			--DataStructure<DataType>::m_Size;
		}

		DoublyLinkedList_Node<DataType>* CurrentNode;

		if (Index == 0)
		{
			PopFront();
		}
		else if (Index == DataStructure<DataType>::m_Size - 1)
		{
			PopBack();
		}
		else if (Index < DataStructure<DataType>::m_Size && Index <= (DataStructure<DataType>::m_Size / 2)) // Jeśli indeks leży w pierwszej połowie listy.
		{
			CurrentNode = m_HeadNode; // Szukanie od początku listy.
			for (unsigned int i = 0; i < Index; i++)
			{
				CurrentNode = CurrentNode->GetNextNode(); // Przechodzenie po następnych węzłach.
			}

			CurrentNode->GetPreviousNode()->SetNextNode(CurrentNode->GetNextNode());		// Ustawia wskaźnik NextNode poprzedniego węzła na następny węzeł po CurrentNode.
			CurrentNode->GetNextNode()->SetPreviousNode(CurrentNode->GetPreviousNode());	// Ustawia wskaźnik PrevNode następnego węzła na poprzedni węzeł przed CurrentNode.
			delete CurrentNode;
			--DataStructure<DataType>::m_Size;
		}
		else if (Index < DataStructure<DataType>::m_Size && Index > DataStructure<DataType>::m_Size / 2) // Jeśli indeks leży w drugiej połowie listy.
		{
			CurrentNode = m_TailNode; // Szukanie od końca listy.
			for (unsigned int i = DataStructure<DataType>::m_Size - 1; i > Index; i--)
			{
				CurrentNode = CurrentNode->GetPreviousNode(); // Przechodzenie po poprzednich węzłach.
			}

			CurrentNode->GetPreviousNode()->SetNextNode(CurrentNode->GetNextNode());		// Ustawia wskaźnik NextNode poprzedniego węzła na następny węzeł.
			CurrentNode->GetNextNode()->SetPreviousNode(CurrentNode->GetPreviousNode());	// Ustawia wskaźnik PrevNode następnego węzła na poprzedni węzeł.
			delete CurrentNode;
			--DataStructure<DataType>::m_Size;
		}
	}
}

template<typename DataType>
unsigned int DoublyLinkedList<DataType>::SearchForElementForward(DataType Element)
{
	if (!DataStructure<DataType>::IsEmpty())
	{
		DoublyLinkedList_Node<DataType>* CurrentNode = m_HeadNode; // Szukanie od początku listy.
		unsigned int NumberOfInstances = 0; // Licznik wystąpień elementu

		do
		{
			if (CurrentNode->GetData() == Element)
			{
				NumberOfInstances++; // Zwiększa licznik wystąpień
			}
			CurrentNode = CurrentNode->GetNextNode();
		} while (CurrentNode != nullptr);

		return NumberOfInstances; // Zwraca liczbę wystąpień
	}
	return 0;
}

template<typename DataType>
unsigned int DoublyLinkedList<DataType>::SearchForElementBackward(DataType Element)
{
	if (!DataStructure<DataType>::IsEmpty())
	{
		DoublyLinkedList_Node<DataType>* CurrentNode = m_TailNode; // Szukanie od końca listy.
		unsigned int NumberOfInstances = 0; // Licznik wystąpień elementu

		do
		{
			if (CurrentNode->GetData() == Element)
			{
				NumberOfInstances++; // Zwiększa licznik wystąpień
			}
			CurrentNode = CurrentNode->GetPreviousNode();
		} while (CurrentNode != nullptr);

		return NumberOfInstances; // Zwraca liczbę wystąpień
	}
	return 0;
}

template<typename DataType>
void DoublyLinkedList<DataType>::InsertBetween(DoublyLinkedList_Node<DataType>* NewNode, DoublyLinkedList_Node<DataType>* PreviousNode, DoublyLinkedList_Node<DataType>* NextNode)
{
	PreviousNode->SetNextNode(NewNode);		// Ustawia wskaźnik NextNode poprzedniego węzła na nowy węzeł.
	NewNode->SetPreviousNode(PreviousNode);	// Ustawia wskaźnik PrevNode nowego węzła na poprzedni węzeł.
	NewNode->SetNextNode(NextNode);			// Ustawia wskaźnik NextNode nowego węzła na następny węzeł.
	NextNode->SetPreviousNode(NewNode);		// Ustawia wskaźnik PrevNode następnego węzła na nowy węzeł.
	++DataStructure<DataType>::m_Size;
}


#endif // DOUBLY_LINKED_LIST