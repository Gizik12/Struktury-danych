#ifndef HASH_TABLE
#define HASH_TABLE

// Klasa bazowa tablicy mieszającej.
class HashTable
{
public:
	// Dodaje parę klucz-wartość do tablicy mieszającej.
	virtual void insert(int key, int value) = 0;

	// Zwraca wartość odpowiadającą podanemu kluczowi.
	virtual int search(int key) const = 0;

	// Usuwa parę związaną z kluczem.
	virtual void remove(int key) = 0;

	// Tworzący kopię tablicy mieszającej.
	virtual HashTable* copy() = 0;

protected:
	// Funkcja mieszająca.
	virtual int hashFunction(int key) const = 0;
};

#endif