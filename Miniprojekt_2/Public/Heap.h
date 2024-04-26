#include "DataStructure.h"
#include <iostream>

#ifndef HEAP_H
#define HEAP_H

class Node // Deklaracja klasy Node.
{
public:
    int priority; // Priorytet węzła.
    int element; // Element węzła.
};

class MaxPriorityQueue : public DataStructure // Deklaracja klasy MaxPriorityQueue dziedziczącej po DataStructure.
{
private:
    Node* queue; // Kolejka węzłów.
    int capacity; // Pojemność kolejki.
    int size; // Rozmiar kolejki.

    void resize(int newCapacity); // Metoda do zmiany rozmiaru kolejki.

    void siftUp(int index); // Metoda do przesuwania w górę węzła.

    void siftDown(int index); // Metoda do przesuwania w dół węzła.

public:
    MaxPriorityQueue(); // Konstruktor.

    ~MaxPriorityQueue(); // Destruktor.

    virtual void insert(int element, int priority); // Metoda do wstawiania elementu do kolejki.

    virtual int extractMax(); // Metoda do usuwania i zwracania elementu o najwyższym priorytecie.

    virtual int peek(); // Metoda do wyświetlania elementu o najwyższym priorytecie.

    virtual void modifyKey(int element, int newPriority); // Metoda do modyfikowania priorytetu elementu.

    virtual int returnSize(); // Metoda zwracająca aktualny rozmiar kolejki.
};
#endif
