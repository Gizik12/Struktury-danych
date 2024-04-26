#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

class DataStructure // Deklaracja klasy abstrakcyjnej DataStructure.
{
public:
    // Wstawienie elementu o priorytecie.
    virtual void insert(int e, int p) = 0;

    // Usunięcie i zwrócenie elementu o najwyższym priorytecie.
    virtual int extractMax() = 0;

    // Zwrócenie elementu o najwyższym priorytecie.
    virtual int peek() = 0;

    // Modyfikacja priorytetu danego elementu.
    virtual void modifyKey(int e, int p) = 0;

    // Metoda zwracająca rozmiar struktury danych.
    virtual int returnSize();
};

#endif
