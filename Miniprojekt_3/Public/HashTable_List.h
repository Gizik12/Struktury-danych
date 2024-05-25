#include "HashTable.h"

#ifndef HASH_TABLE_LIST
#define HASH_TABLE_LIST

// Struktura węzła. Węzeł przechowuje klucz, wartość i wskaźnik na następny węzeł.
struct HashTable_List_Node
{
	int key;									// Klucz.
	int value;									// Wartość.
	HashTable_List_Node* nextNode = nullptr;	// Wskaźnik na następny węzeł.
};

// Klasa tablicy mieszającej.
// Wariant: kubełki przechowują listę wiązaną.
class HashTable_List final : public HashTable
{
public:
	// Konstruktor.
	HashTable_List();

	// Destruktor.
	~HashTable_List();

	// Dodaje parę klucz-wartość do słownika.
	virtual void insert(int key, int value) override;

	// Zwraca wartość odpowiadającą podanemu kluczowi.
	virtual int search(int key) const override;

	// Usuwa parę związaną z kluczem.
	virtual void remove(int key) override;

	// Tworzący kopię kolejki.
	virtual HashTable* copy() override;

private:
	// Funkcja mieszająca.
	virtual int hashFunction(int key) const override;

	HashTable_List_Node** hashTable;	// Tablica mieszająca.
	const int HASH_TABLE_CAPACITY = 10;	// Pojemność tablicy mieszającej (indeksy od 0 - 9 nadają się dla funkcji mieszającej h(x) = x % 10).
};

#endif