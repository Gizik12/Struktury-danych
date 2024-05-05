#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

class PriorityQueue // Deklaracja klasy abstrakcyjnej PriorityQueue.
{
public:
    // Wstawienie elementu o priorytecie.
    virtual void insert(int element, int priority) = 0;

    // Usunięcie i zwrócenie elementu o najwyższym priorytecie.
    virtual int extractMax() = 0;

    // Zwrócenie elementu o najwyższym priorytecie.
    virtual int peek() = 0;

    // Modyfikacja priorytetu danego elementu.
    virtual void modifyKey(int element, int priority) = 0;

    // Metoda zwracająca rozmiar struktury danych.
    virtual int returnSize() = 0;

    // Metoda zwracająca kopię obecnej kolejki priorytetowej.
    virtual PriorityQueue* copy() = 0;
};

#endif
