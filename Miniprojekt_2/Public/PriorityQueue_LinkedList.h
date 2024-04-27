#ifndef PRIORITY_QUEUE_LINKED_LIST_H
#define PRIORITY_QUEUE_LINKED_LIST_H

#include "PriorityQueue.h"

// Struktura węzła
struct PriorityQueue_LinkedList_Node
{
	int data = 0;											// Wartość elementu.
	int priority = 0;										// Prioritet elementu.
	PriorityQueue_LinkedList_Node* nextNode = nullptr;	    // Wskaźnik na następny element.
};

// Klasa kolejki priorytetowej zaimplementowanej jako lista wiązana (jednokierunkowa).
class PriorityQueue_LinkedList : public PriorityQueue
{
public:
	// Konstruktor.
	PriorityQueue_LinkedList();

	// Destruktor.
	~PriorityQueue_LinkedList();

    // Wstawia element o podanym priorytecie.
    virtual void insert(int element, int priority) override;

    // Usuwa i zwarca element o najwyższym priorytecie.
    virtual int extractMax() override;

    // Zwraca element o najwyższym priorytecie.
    virtual int peek() override;

    // Modyfikuje priorytet danego elementu.
    virtual void modifyKey(int element, int priority) override;

    // Zwraca rozmiar struktury danych.
    virtual int returnSize() override;

private:
    // Zwraca `true` jeśli kolejka jest pusta, w innym wypadku `false`.
    bool isEmpty() const { return (size <= 0) ? true : false; }

    PriorityQueue_LinkedList_Node* headNode;    // Wskaźnik na początek kolejki.
    int size;                                   // Liczba elementów w kolejce.
};

#endif
