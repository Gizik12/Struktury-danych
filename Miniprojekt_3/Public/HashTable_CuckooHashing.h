#include "HashTable.h"

#ifndef HASH_TABLE_CUCKOO_HASHING
#define HASH_TABLE_CUCKOO_HASHING

const int INSERT_ATTEMPTS_LIMIT = 5; // Limit prób wstawienia nowej pary do jedenj z tablic, po przekroczeniu następuje przemieszanie.

// Struktura pary klucz-wartość.
struct Pair
{
	int key = -1;	// Klucz.
	int value = -1; // Wartość.
};

// Klasa tablicy mieszającej.
// Wariant: Cuckoo hashing.
class HashTable_CuckooHashing final : public HashTable
{
public:
	// Konstruktor.
	HashTable_CuckooHashing(int capacity);

	// Destruktor.
	~HashTable_CuckooHashing();

	// Dodaje parę klucz-wartość do słownika.
	virtual void insert(int key, int value) override;

	// Zwraca wartość odpowiadającą podanemu kluczowi.
	virtual int search(int key) const override;

	// Usuwa parę związaną z kluczem.
	virtual void remove(int key) override;

	// Tworzący kopie kolejki.
	virtual HashTable* copy() override;

private:
	// Funkcja mieszająca.
	virtual int hashFunction(int key) const override;

	// Funkcja mieszająca dla alternatywnej tablicy.
	int hashFunctionAlt(int key) const;

	// Zwiększa pojemność tablic, tym samym modyfikuje działanie funkcji hashFunction i hashFunctionAlt.
	void rehash();

	// Zamienia pary klucz-wartość miejscem w pamięci.
	void swap(Pair& firstPair, Pair& secondPair);

	Pair* hashTable;			// Tablica główna mieszająca.
	Pair* hashTableAlt;			// Tablica alternatywna mieszająca.
	int hashTableCapacity;		// Pojemność tablicy mieszającej.
	int size;					// Suma par klucz-wartość w tablicy głównej i alternatywnej.
};

#endif