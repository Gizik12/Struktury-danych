#include "PriorityQueue.h"
#include <iostream>

#ifndef PRIORITY_QUEUE_HEAP_H
#define PRIORITY_QUEUE_HEAP_H

class PriorityQueue_Heap_Node // Deklaracja klasy Node.
{
public:
    int priority; // Priorytet węzła.
    int element; // Element węzła.
};

class PriorityQueue_Heap : public PriorityQueue // Deklaracja klasy MaxPriorityQueue dziedziczącej po PriorityQueue.
{
private:
    PriorityQueue_Heap_Node* queue; // Kolejka węzłów.
    int capacity; // Pojemność kolejki.
    int size; // Rozmiar kolejki.

    void resize(int newCapacity); // Metoda do zmiany rozmiaru kolejki.

    void shiftUp(int index); // Metoda do przesuwania w górę węzła.

    void shiftDown(int index); // Metoda do przesuwania w dół węzła.

public:
    PriorityQueue_Heap(); // Konstruktor.

    ~PriorityQueue_Heap(); // Destruktor.

    virtual void insert(int element, int priority) override; // Metoda do wstawiania elementu do kolejki.

    virtual int extractMax() override; // Metoda do usuwania i zwracania elementu o najwyższym priorytecie.

    virtual int peek() override; // Metoda do wyświetlania elementu o najwyższym priorytecie.

    virtual void modifyKey(int element, int newPriority) override; // Metoda do modyfikowania priorytetu elementu.

    virtual int returnSize() override; // Metoda zwracająca aktualny rozmiar kolejki.
};

#endif
