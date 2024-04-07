#include "DataStructure.h"
#ifndef SINGLY_LINKED_LIST_HEAD_TAIL_H
#define SINGLY_LINKED_LIST_HEAD_TAIL_H

// Węzeł
template<typename DataType>
class SinglyLinkedList_Node_HeadTail final
{
public:
    // Konstruktor.
    SinglyLinkedList_Node_HeadTail(DataType Data);

    // Zwraca wartość węzła.
    DataType GetData() const { return m_Data; }

    // Zwraca następny węzeł.
    SinglyLinkedList_Node_HeadTail<DataType>* GetNextNode() const { return m_NextNode; }

    // Ustawia następny węzeł.
    void SetNextNode(SinglyLinkedList_Node_HeadTail<DataType>* NextNode) { m_NextNode = NextNode; }

private:
    DataType m_Data;                                    // Wartość węzła.
    SinglyLinkedList_Node_HeadTail<DataType>* m_NextNode;        // Wskaźnik na następny węzeł.
};

// Lista
template<typename DataType>
class SinglyLinkedList_HeadTail final : public DataStructure<DataType>
{
public:
    // Konstruktor.
    SinglyLinkedList_HeadTail();

    // Destruktor.
    ~SinglyLinkedList_HeadTail();

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
    virtual DataStructure<DataType>* Clone() const override { return new SinglyLinkedList_HeadTail<DataType>(*this); }

private:
    SinglyLinkedList_Node_HeadTail<DataType>* m_HeadNode;       // Pierwszy element listy.
    SinglyLinkedList_Node_HeadTail<DataType>* m_TailNode;       // Ostatni element listy.
};

template<typename DataType>
SinglyLinkedList_Node_HeadTail<DataType>::SinglyLinkedList_Node_HeadTail(DataType Data)
    : m_Data(Data), m_NextNode(nullptr) {}

template<typename DataType>
SinglyLinkedList_HeadTail<DataType>::SinglyLinkedList_HeadTail()
    : m_HeadNode(nullptr), m_TailNode(nullptr) {}

template<typename DataType>
SinglyLinkedList_HeadTail<DataType>::~SinglyLinkedList_HeadTail()
{
    if (!DataStructure<DataType>::IsEmpty())
    {
        SinglyLinkedList_Node_HeadTail<DataType>* CurrentNode = m_HeadNode;
        SinglyLinkedList_Node_HeadTail<DataType>* NextNode = nullptr;

        while (CurrentNode != nullptr)
        {
            NextNode = CurrentNode->GetNextNode();
            delete CurrentNode;
            CurrentNode = NextNode;
        }
    }
}

template<typename DataType>
void SinglyLinkedList_HeadTail<DataType>::PushFront(DataType Element)
{
    SinglyLinkedList_Node_HeadTail<DataType>* NewNode = new SinglyLinkedList_Node_HeadTail<DataType>(Element);
    NewNode->SetNextNode(m_HeadNode);
    m_HeadNode = NewNode;
    if (m_TailNode == nullptr)
    {
        m_TailNode = NewNode;
    }
    ++DataStructure<DataType>::m_Size;
}

template<typename DataType>
void SinglyLinkedList_HeadTail<DataType>::PushBack(DataType Element)
{
    SinglyLinkedList_Node_HeadTail<DataType>* NewNode = new SinglyLinkedList_Node_HeadTail<DataType>(Element);
    if (DataStructure<DataType>::IsEmpty())
    {
        m_HeadNode = NewNode;
    }
    else
    {
        m_TailNode->SetNextNode(NewNode);
    }
    m_TailNode = NewNode;
    ++DataStructure<DataType>::m_Size;
}

template<typename DataType>
void SinglyLinkedList_HeadTail<DataType>::PopFront()
{
    if (!DataStructure<DataType>::IsEmpty())
    {
        SinglyLinkedList_Node_HeadTail<DataType>* OldHeadNode = m_HeadNode;
        m_HeadNode = m_HeadNode->GetNextNode();
        delete OldHeadNode;
        --DataStructure<DataType>::m_Size;
        if (m_HeadNode == nullptr)
        {
            m_TailNode = nullptr;
        }
    }
}

template<typename DataType>
void SinglyLinkedList_HeadTail<DataType>::PopBack()
{
    if (!DataStructure<DataType>::IsEmpty())
    {
        if (m_HeadNode == m_TailNode)
        {
            delete m_HeadNode;
            m_HeadNode = nullptr;
            m_TailNode = nullptr;
        }
        else
        {
            SinglyLinkedList_Node_HeadTail<DataType>* CurrentNode = m_HeadNode;
            while (CurrentNode->GetNextNode() != m_TailNode)
            {
                CurrentNode = CurrentNode->GetNextNode();
            }
            delete m_TailNode;
            m_TailNode = CurrentNode;
            m_TailNode->SetNextNode(nullptr);
        }
        --DataStructure<DataType>::m_Size;
    }
}

template<typename DataType>
void SinglyLinkedList_HeadTail<DataType>::Insert(DataType Element, unsigned int Index)
{
    if (Index == 0)
    {
        PushFront(Element);
    }
    else if (Index >= DataStructure<DataType>::m_Size)
    {
        PushBack(Element);
    }
    else
    {
        SinglyLinkedList_Node_HeadTail<DataType>* NewNode = new SinglyLinkedList_Node_HeadTail<DataType>(Element);
        SinglyLinkedList_Node_HeadTail<DataType>* CurrentNode = m_HeadNode;
        for (unsigned int i = 0; i < Index - 1; ++i)
        {
            CurrentNode = CurrentNode->GetNextNode();
        }
        NewNode->SetNextNode(CurrentNode->GetNextNode());
        CurrentNode->SetNextNode(NewNode);
        ++DataStructure<DataType>::m_Size;
    }
}

template<typename DataType>
void SinglyLinkedList_HeadTail<DataType>::RemoveAt(unsigned int Index)
{
    if (!DataStructure<DataType>::IsEmpty())
    {
        if (Index == 0)
        {
            PopFront();
        }
        else if (Index >= DataStructure<DataType>::m_Size - 1)
        {
            PopBack();
        }
        else
        {
            SinglyLinkedList_Node_HeadTail<DataType>* CurrentNode = m_HeadNode;
            for (unsigned int i = 0; i < Index - 1; ++i)
            {
                CurrentNode = CurrentNode->GetNextNode();
            }
            SinglyLinkedList_Node_HeadTail<DataType>* NodeToRemove = CurrentNode->GetNextNode();
            CurrentNode->SetNextNode(NodeToRemove->GetNextNode());
            delete NodeToRemove;
            --DataStructure<DataType>::m_Size;
        }
    }
}

template<typename DataType>
unsigned int SinglyLinkedList_HeadTail<DataType>::SearchForElementForward(DataType Element)
{
    if (!DataStructure<DataType>::IsEmpty())
    {
        SinglyLinkedList_Node_HeadTail<DataType>* CurrentNode = m_HeadNode;
        unsigned int NumberOfInstances = 0;

        while (CurrentNode != nullptr)
        {
            if (CurrentNode->GetData() == Element)
            {
                ++NumberOfInstances;
            }
            CurrentNode = CurrentNode->GetNextNode();
        }
        return NumberOfInstances;
    }
    return 0;
}

#endif // SINGLY_LINKED_LIST_HEAD_TAIL_H