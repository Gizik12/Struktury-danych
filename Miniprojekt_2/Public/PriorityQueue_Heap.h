#include "PriorityQueue.h"
#include <iostream>
using namespace std;

#ifndef PRIORITYQUEUE_HEAP_H
#define PRIORITYQUEUE_HEAP_H

// Struktura reprezentująca pojedynczy element kolejki priorytetowej na kopcu
struct PriorityQueue_Heap_Node
{
    int element; // Element przechowywany w kolejce
    int priority; // Priorytet danego elementu
};

// Klasa PriorityQueue_Heap dziedzicząca po klasie abstrakcyjnej PriorityQueue
class PriorityQueue_Heap final : public PriorityQueue
{
public:
    PriorityQueue_Heap(); // Konstruktor
    ~PriorityQueue_Heap(); // Destruktor

    // Metoda dodająca nowy element do kolejki priorytetowej
    virtual void insert(int element, int priority) override;

    // Metoda usuwająca i zwracająca element o najwyższym priorytecie z kolejki
    virtual int extractMax() override;

    // Metoda zwracająca element o najwyższym priorytecie z kolejki bez usuwania go
    virtual int peek() const override;
    
    // Metoda modyfikująca priorytet danego elementu w kolejce
    virtual void modifyKey(int element, int priority) override;
    
    // Metoda zwracająca aktualny rozmiar kolejki
    virtual int returnSize() const override;

    // Metoda pomocnicza do zamiany miejscami dwóch elementów w kolejce
    void swap(PriorityQueue_Heap_Node& firstNode, PriorityQueue_Heap_Node& secondNode);

private:
    PriorityQueue_Heap_Node* queue; // Tablica przechowująca elementy kolejki
    int capacity; // Pojemność (rozmiar) tablicy
    int size; // Aktualny rozmiar kolejki

    // Metody pomocnicze do nawigacji po kopcu binarnym
    inline int parentIndex(int index) const;
    inline int leftChildIndex(int index) const;
    inline int rightChildIndex(int index) const;

    // Metoda przywracająca właściwości kopca po dodaniu nowego elementu
    void heapifyUp(int index);

    // Metoda przywracająca właściwości kopca po usunięciu elementu
    void heapifyDown(int index);

    // Metoda tworząca głęboką kopię kolejki
    virtual PriorityQueue* copy() override;
};

#endif