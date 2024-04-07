#include "DataStructure.h"
#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST

// Węzeł
template<typename DataType>
class SinglyLinkedList_Node final
{
public:
    // Konstruktor.
    SinglyLinkedList_Node(DataType Data);

    // Zwraca wartość węzła.
    DataType GetData() const { return m_Data; }

    // Zwraca następny węzeł.
    SinglyLinkedList_Node<DataType>* GetNextNode() const { return m_NextNode; }

    // Ustawia następny węzeł.
    void SetNextNode(SinglyLinkedList_Node<DataType>* NextNode) { m_NextNode = NextNode; }

private:
    DataType m_Data;                                    // Wartość węzła.
    SinglyLinkedList_Node<DataType>* m_NextNode;        // Wskaźnik na następny węzeł.
};

// Lista
template<typename DataType>
class SinglyLinkedList final : public DataStructure<DataType>
{
public:
    // Konstruktor.
    SinglyLinkedList();

    // Destruktor.
    ~SinglyLinkedList();

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

    // Tworzy kopie struktury (stosowane w badaniach)
    virtual DataStructure<DataType>* Clone() const override { return new SinglyLinkedList<DataType>(*this); }

private:
    SinglyLinkedList_Node<DataType>* m_HeadNode;       // Pierwszy element listy.
};

template<typename DataType>
SinglyLinkedList_Node<DataType>::SinglyLinkedList_Node(DataType Data)
    : m_Data(Data), m_NextNode(nullptr) { }

template<typename DataType>
SinglyLinkedList<DataType>::SinglyLinkedList()
    : m_HeadNode(nullptr) { }

template<typename DataType>
SinglyLinkedList<DataType>::~SinglyLinkedList()
{
    if (!DataStructure<DataType>::IsEmpty())
    {
        SinglyLinkedList_Node<DataType>* CurrentNode = m_HeadNode;
        SinglyLinkedList_Node<DataType>* NextNode = nullptr;

        while (CurrentNode != nullptr)
        {
            NextNode = CurrentNode->GetNextNode();
            delete CurrentNode;
            CurrentNode = NextNode;
        }
    }
}

template<typename DataType>
void SinglyLinkedList<DataType>::PushFront(DataType Element)
{
    SinglyLinkedList_Node<DataType>* NewNode = new SinglyLinkedList_Node<DataType>(Element); // Utworzenie nowego węzła.
    NewNode->SetNextNode(m_HeadNode);    // Następnym węzłem NewNode jest obecny HeadNode.
    m_HeadNode = NewNode;                // NewNode zostaje ustawiony jako nowy HeadNode.
    ++DataStructure<DataType>::m_Size;
}

template<typename DataType>
void SinglyLinkedList<DataType>::PushBack(DataType Element)
{
    SinglyLinkedList_Node<DataType>* NewNode = new SinglyLinkedList_Node<DataType>(Element); // Utworzenie nowego węzła.

    if (DataStructure<DataType>::IsEmpty())
    {
        m_HeadNode = NewNode; // Jeśli lista jest pusta, nowy węzeł jest zarówno głową, jak i ogonem.
    }
    else
    {
        SinglyLinkedList_Node<DataType>* CurrentNode = m_HeadNode;
        while (CurrentNode->GetNextNode() != nullptr)
        {
            CurrentNode = CurrentNode->GetNextNode(); // Przechodzenie do ostatniego węzła na liście.
        }
        CurrentNode->SetNextNode(NewNode); // Ustawienie następnego węzła ostatniego węzła na nowy węzeł.
    }
    ++DataStructure<DataType>::m_Size;
}

template<typename DataType>
void SinglyLinkedList<DataType>::PopFront()
{
    if (!DataStructure<DataType>::IsEmpty())
    {
        SinglyLinkedList_Node<DataType>* OldHeadNode = m_HeadNode; // Zapamiętanie starego HeadNode.
        m_HeadNode = m_HeadNode->GetNextNode(); // HeadNode staje się następnym węzłem.
        delete OldHeadNode; // Usunięcie starego HeadNode.
        --DataStructure<DataType>::m_Size;
    }
}

template<typename DataType>
void SinglyLinkedList<DataType>::PopBack()
{
    if (!DataStructure<DataType>::IsEmpty())
    {
        if (m_HeadNode->GetNextNode() == nullptr) // Jeśli jest tylko jeden węzeł.
        {
            delete m_HeadNode;
            m_HeadNode = nullptr;
        }
        else
        {
            SinglyLinkedList_Node<DataType>* CurrentNode = m_HeadNode;
            while (CurrentNode->GetNextNode()->GetNextNode() != nullptr)
            {
                CurrentNode = CurrentNode->GetNextNode(); // Przechodzenie do przedostatniego węzła.
            }
            delete CurrentNode->GetNextNode(); // Usunięcie ostatniego węzła.
            CurrentNode->SetNextNode(nullptr); // Przypisanie nullptr do węzła przedostatniego jako nowego ostatniego węzła.
        }
        --DataStructure<DataType>::m_Size;
    }
}

template<typename DataType>
void SinglyLinkedList<DataType>::Insert(DataType Element, unsigned int Index)
{
    if (Index == 0)
    {
        PushFront(Element); // Wstawienie na początek listy.
    }
    else if (Index >= DataStructure<DataType>::m_Size)
    {
        PushBack(Element); // Wstawienie na koniec listy.
    }
    else
    {
        SinglyLinkedList_Node<DataType>* NewNode = new SinglyLinkedList_Node<DataType>(Element); // Utworzenie nowego węzła.
        SinglyLinkedList_Node<DataType>* CurrentNode = m_HeadNode;

        for (unsigned int i = 0; i < Index - 1; ++i)
        {
            CurrentNode = CurrentNode->GetNextNode(); // Przejście do węzła poprzedzającego miejsce wstawienia.
        }
        NewNode->SetNextNode(CurrentNode->GetNextNode()); // Nowy węzeł wskazuje na następny węzeł obecnego węzła.
        CurrentNode->SetNextNode(NewNode); // Obecny węzeł wskazuje na nowy węzeł jako następny.
        ++DataStructure<DataType>::m_Size;
    }
}

template<typename DataType>
void SinglyLinkedList<DataType>::RemoveAt(unsigned int Index)
{
    if (!DataStructure<DataType>::IsEmpty())
    {
        if (Index == 0)
        {
            PopFront(); // Usunięcie pierwszego elementu.
        }
        else if (Index >= DataStructure<DataType>::m_Size - 1)
        {
            PopBack(); // Usunięcie ostatniego elementu.
        }
        else
        {
            SinglyLinkedList_Node<DataType>* CurrentNode = m_HeadNode;
            for (unsigned int i = 0; i < Index - 1; ++i)
            {
                CurrentNode = CurrentNode->GetNextNode(); // Przejście do węzła poprzedzającego usuwany.
            }
            SinglyLinkedList_Node<DataType>* NodeToRemove = CurrentNode->GetNextNode(); // Węzeł do usunięcia.
            CurrentNode->SetNextNode(NodeToRemove->GetNextNode()); // Przepięcie wskaźnika na następny.
            delete NodeToRemove; // Usunięcie węzła.
            --DataStructure<DataType>::m_Size;
        }
    }
}

template<typename DataType>
unsigned int SinglyLinkedList<DataType>::SearchForElementForward(DataType Element)
{
    if (!DataStructure<DataType>::IsEmpty())
    {
        SinglyLinkedList_Node<DataType>* CurrentNode = m_HeadNode; // Przeszukiwanie od początku.
        unsigned int NumberOfInstances = 0; // Licznik wystąpień elementu

        while (CurrentNode != nullptr)
        {
            if (CurrentNode->GetData() == Element)
            {
                ++NumberOfInstances; // Zwiększa licznik wystąpień
            }
            CurrentNode = CurrentNode->GetNextNode();
        }
        return NumberOfInstances; // Zwraca liczbę wystąpień
    }
    return 0;
}

#endif // SINGLY_LINKED_LIST