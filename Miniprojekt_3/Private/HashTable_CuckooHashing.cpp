#include "../Public/HashTable_CuckooHashing.h"

HashTable_CuckooHashing::HashTable_CuckooHashing(int capacity)
{
    hashTableCapacity = capacity;   // Ustawienie pojemności tablicy mieszającej.
    size = 0;                       // Ustawienie rozmiaru tablicy mieszającej na 0.

    hashTable = new Pair[hashTableCapacity];     // Alokacja tablicy głównej. 
    hashTableAlt = new Pair[hashTableCapacity];  // Alokacja tablicy alternatywnej.
}

HashTable_CuckooHashing::~HashTable_CuckooHashing()
{
    delete[] hashTable;     // Usunięcie tablicy głównej.
    delete[] hashTableAlt;  // Usunięcie tablicy alternatywnej.
}

void HashTable_CuckooHashing::insert(int key, int value)
{
    int hashIndex = hashFunction(key); // Potencjalna pozycja pary w tablicy głównej.
    if (hashTable[hashIndex].key != -1 && hashTable[hashIndex].key == key)
    {
        hashTable[hashIndex].value = value; // Jeśli para o podanym kluczu już istnieje, aktualizuje jej wartość.
        return;
    }

    int hashIndexAlt = hashFunctionAlt(key); // Potencjalna pozycja pary w tablicy alternatywnej.
    if (hashTableAlt[hashIndexAlt].key != -1 && hashTableAlt[hashIndexAlt].key == key)
    {
        hashTableAlt[hashIndexAlt].value = value; // Jeśli para o podanym kluczu już istnieje, aktualizuje jej wartość.
        return;
    }
    
    if (size >= hashTableCapacity / 2)
    {
        rehash(); // Jeśli `load factor` jest większy lub równy 0.5, zwiększa pojemność.
    }

    Pair insertedPair = { key, value }; // Nowa para klucz-wartość.
    int originalKey = key;              // Oryginalny klucz - punkt odniesienia w indentyfikacji cyklu.
    int insertAttempts = 0;             // Liczba prób wstawienia nowej pary.

    while (insertAttempts <= INSERT_ATTEMPTS_LIMIT)
    {
        hashIndex = hashFunction(insertedPair.key); // Pozycja klucza w tablicy głównej.
        if (hashTable[hashIndex].key == -1)
        {
            hashTable[hashIndex] = insertedPair;    // Jeśli miejsce w tablicy głównej jest wolne, wstawia nową parę/starą parę z tablicy alternatywnej.
            size++;                                 // Inkrementacja rozmiaru.
            return;
        }

        swap(insertedPair, hashTable[hashIndex]); // Jeśli wstawienie do tablicy głównej się nie udało, wstawia nową parę i szuka miejsca dla starej pary z tablicy głównej.

        hashIndexAlt = hashFunctionAlt(insertedPair.key); // Pozycja klucza w tablicy alternatywnej.
        if (hashTableAlt[hashIndexAlt].key == -1)
        {
            hashTableAlt[hashIndexAlt] = insertedPair;  // Jeśli miejsce w tablicy alternatywnej jest wolne, wstawia nową parę.
            size++;                                     // Inkrementacja rozmiaru.
            return;
        }

        swap(insertedPair, hashTableAlt[hashIndexAlt]); // Jeśli wstawienie starej pary z tablicy głównej do tablicy alternatywnej się nie udało, wstawia starą parę z tablicy głównej i szuka miejsca dla starej pary z tablicy alternatywnej.

        insertAttempts++; // Inkrementacja prób wstawienia nowej pary.
    }

    rehash();           // Jeśli przekroczono limit prób wstawienia nowej pary, przemieszanie.
    insert(key, value); // Ponowna próba wstawienia nowej pary do przemieszanej tablicy mieszającej.
}

int HashTable_CuckooHashing::search(int key) const
{
    int hashIndex = hashFunction(key); // Pozycja klucza w tablicy głównej.
    if (hashTable[hashIndex].key != -1 && hashTable[hashIndex].key == key)
    {
        return hashTable[hashIndex].value; // Zwraca wartość, jeśli znajduje się w tablicy głównej.
    }

    int hashIndexAlt = hashFunctionAlt(key); // Pozycja klucza w tablicy alternatywnej.
    if (hashTableAlt[hashIndexAlt].key != -1 && hashTableAlt[hashIndexAlt].key == key)
    {
        return hashTableAlt[hashIndexAlt].value; // Zwraca wartość, jeśli znajduje się w tablicy alternatywnej.
    }

    return -1; // Równoznaczne z nieznalezieniem wartości dla szukanego klucza.
}

void HashTable_CuckooHashing::remove(int key)
{
    int hashIndex = hashFunction(key); // Pozycja klucza w tablicy głównej.
    if (hashTable[hashIndex].key != -1 && hashTable[hashIndex].key == key)
    {
        hashTable[hashIndex] = { -1, -1 };  // Przywraca domyślną parę klucz-wartość w tablicy głównej.
        size--;                             // Dekrementacja rozmiaru.
        return;
    }

    int hashIndexAlt = hashFunctionAlt(key); // Pozycja klucza w tablicy alternatywnej.
    if (hashTableAlt[hashIndexAlt].key != -1 && hashTableAlt[hashIndexAlt].key == key)
    {
        hashTableAlt[hashIndexAlt] = { -1, -1 };    // Przywraca domyślną parę klucz-wartość w tablicy alternatywnej.
        size--;                                     // Dekrementacja rozmiaru.
        return;
    }
}

HashTable* HashTable_CuckooHashing::copy()
{
    HashTable_CuckooHashing* copiedHashTable = new HashTable_CuckooHashing(hashTableCapacity);  // Nowa kopia tablicy mieszającej.
    copiedHashTable->hashTableCapacity = hashTableCapacity;                                     // Ustawienie pojemności kopii na pojemność oryginału.
    copiedHashTable->size = size;                                                               // Ustawienie rozmiaru kopii na rozmiar oryginału.
    
    for (int i = 0; i < hashTableCapacity; i++)
    {
        if (hashTable[i].key != -1)
        {
            copiedHashTable->hashTable[i] = hashTable[i]; // Przepisuje wartości z tablicy głównej do jej kopii.
        }
        if (hashTableAlt[i].key != -1)
        {
            copiedHashTable->hashTableAlt[i] = hashTableAlt[i]; // Przepisuje wartości z tablicy alternatywnej do jej kopii. 
        }
    }

    return copiedHashTable; // Zwraca kopię tablicy mieszającej.
}

int HashTable_CuckooHashing::hashFunction(int key) const
{
    return key % hashTableCapacity;
}

int HashTable_CuckooHashing::hashFunctionAlt(int key) const
{
    return (key / hashTableCapacity) % hashTableCapacity;
}

void HashTable_CuckooHashing::rehash()
{
    Pair* oldHashTable = hashTable;         // Wskaźnik na obecną tablicę główną.
    Pair* oldHashTableAlt = hashTableAlt;   // Wskaźnik na obecną tablicę alternatywną.

    int oldCapacity = hashTableCapacity;    // Obecna pojemność.
    hashTableCapacity *= 2;                 // Zwiększenie pojemności tablic na dwukrotnie większą.

    hashTable = new Pair[hashTableCapacity];    // Nowa tablica główna o większej pojemności.
    hashTableAlt = new Pair[hashTableCapacity]; // Nowa tablica alternatywna o większej pojemności.

    for (int i = 0; i < oldCapacity; i++)
    {
        if (oldHashTable[i].key != -1)
        {
            insert(oldHashTable[i].key, oldHashTable[i].value); // Wstawianie par klucz-wartość ze starej tablicy głównej do nowej.
        }

        if (oldHashTableAlt[i].key != -1)
        {
            insert(oldHashTableAlt[i].key, oldHashTableAlt[i].value); // Wstawianie par klucz-wartość ze starej tablicy alternatywnej do nowej.
        }
    }

    delete[] oldHashTable;      // Usunięcie starej tablicy głównej.
    delete[] oldHashTableAlt;   // Usunięcie starej tablicy alternatywnej.
}

void HashTable_CuckooHashing::swap(Pair& firstPair, Pair& secondPair)
{
    Pair tmpPair = firstPair;   // Tymczasowe przechowanie pierwszej pary.
    firstPair = secondPair;     // Wstawienie drugiej pary w miejce pierwszej.
    secondPair = tmpPair;       // Wstawienie przechowanej pierwszej pary w miejsce drugiej.
}
