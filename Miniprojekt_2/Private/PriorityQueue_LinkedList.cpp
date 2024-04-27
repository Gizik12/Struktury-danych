#include "../Public/PriorityQueue_LinkedList.h"

PriorityQueue_LinkedList::PriorityQueue_LinkedList()
{
    headNode = nullptr;
    size = 0;
}

PriorityQueue_LinkedList::~PriorityQueue_LinkedList()
{
    while (headNode)
    {
        PriorityQueue_LinkedList_Node* oldHeadNode = headNode;  // Wskaźnik na stary headNode.
        headNode = headNode->nextNode;                          // Następny węzeł jest nowym headNode.
        delete oldHeadNode;                                     // Usunięcie starego headNode.
    }
}

void PriorityQueue_LinkedList::insert(int element, int priority)
{
    PriorityQueue_LinkedList_Node* newNode = new PriorityQueue_LinkedList_Node; // Nowy węzeł.
    newNode->data = element;                                                    // Ustawienie wartości newNode.
    newNode->priority = priority;                                               // Ustawienie priorytetu newNode.

    if (isEmpty())
    {
        headNode = newNode; // Dodanie pierwszego węzła jeśli kolejka jest pusta.
    }
    else if (priority > headNode->priority)
    {
        newNode->nextNode = headNode;   // Następnym węzłem newNode jest obecny headNode.
        headNode = newNode;             // Węzeł newNode jest nowym headNode.
    }
    else
    {
        PriorityQueue_LinkedList_Node* currentNode = headNode; // Przechodzenie po kolejce zaczyna się od headNode.
        while (currentNode->nextNode && currentNode->nextNode->priority >= priority)
        {
            currentNode = currentNode->nextNode; // Przejście na kolejny węzeł.
        }
        newNode->nextNode = currentNode->nextNode;  // Ustawienie następnego węzła po newNode na węzeł po currentNode.
        currentNode->nextNode = newNode;            // Wstawienie newNode między currentNode, a currentNode->nextNode.
    }
    size++; // Zwiększenie liczby elementów w kolejce.
}

int PriorityQueue_LinkedList::extractMax()
{
    if (!isEmpty())
    {
        int maxData = headNode->data;                           // Wartość headNode.
        PriorityQueue_LinkedList_Node* oldHeadNode = headNode;  // Wskaźnik na stary headNode.
        headNode = headNode->nextNode;                          // Następny węzeł jest nowym headNode.
        delete oldHeadNode;                                     // Usunięcie starego headNode.
        size--;                                                 // Zmniejszenie liczby elementów kolejki.

        return maxData; // Zwraca wartość starego headNode.
    }
}

int PriorityQueue_LinkedList::peek()
{
    if (!isEmpty())
    {
        return headNode->data; // Zwraca wartość headNode.
    }
}

void PriorityQueue_LinkedList::modifyKey(int element, int priority)
{
    if (!isEmpty())
    {
        PriorityQueue_LinkedList_Node* changedNode = headNode;  // Pierwsze wystąpienie węzła o podanej wartości.
        PriorityQueue_LinkedList_Node* prevNode = nullptr;      // Wskaźnik na węzeł poprzedzający currentNode.

        while (changedNode != nullptr && changedNode->data != element)
        {
            prevNode = changedNode;                 // Zapamiętanie ostatnio odzwiedzonego węzła.
            changedNode = changedNode->nextNode;    // Przejście na kolejny węzeł.
        }
        if (changedNode != nullptr)
        {
            changedNode->priority = priority;   // Zmiana priorytetu pierwszego znalezionego elementu o podanej wartości.
            if (prevNode != nullptr)
            {
                prevNode->nextNode = changedNode->nextNode; // Połączenie węzłów, pomiędzy którymi znajduje się changedNode.
            }
            else
            {
                headNode = changedNode->nextNode; // Ustawienie nowego headNode.
            }

            if (priority > headNode->priority)
            {
                changedNode->nextNode = headNode;   // Ustawienie węzła po changedNode na obecny headNode.
                headNode = changedNode;             // Węzeł changedNode jest nowym headNode.
            }
            else
            {
                PriorityQueue_LinkedList_Node* currentNode = headNode; // Przechodzenie po kolejce zaczyna się od headNode.
                while (currentNode->nextNode && currentNode->nextNode->priority >= priority)
                {
                    currentNode = currentNode->nextNode; // Przejście na kolejny węzeł.
                }
                changedNode->nextNode = currentNode->nextNode;  // Ustawienie następnego węzła po changedNode na węzeł po currentNode.
                currentNode->nextNode = changedNode;            // Wstawienie changedNode między currentNode, a currentNode->nextNode.
            }
        }
    }
}

int PriorityQueue_LinkedList::returnSize()
{
    return size;
}
