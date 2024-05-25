#include "../Public/HashTable_List.h"

HashTable_List::HashTable_List()
{
    hashTable = new HashTable_List_Node*[HASH_TABLE_CAPACITY]; // Utworzenie tablicy mieszającej.

    for (int i = 0; i < HASH_TABLE_CAPACITY; i++)
    {
        hashTable[i] = nullptr; // Ustawienie domyślnych wartości kubełków na nullptr.
    }
}

HashTable_List::~HashTable_List()
{
    HashTable_List_Node* currentNode;   // Węzeł do przechodzenia po liście w kubełku.
    HashTable_List_Node* prevNode;      // Węzeł do usunięcia.

    for (int i = 0; i < HASH_TABLE_CAPACITY; i++)
    {
        currentNode = hashTable[i]; // Przechodzenia po liście od pierwszego elementu w kubełku.

        while (currentNode != nullptr)
        {
            prevNode = currentNode;                 // Ustawienie węzła do usunięcia na obecny węzeł.
            currentNode = currentNode->nextNode;    // Przejście na następny węzeł.
            delete prevNode;                        // Usunięcie poprzedniego węzła.
        }
    }
    delete[] hashTable; // Usunięcie pustej tablicy mieszającej.
}

void HashTable_List::insert(int key, int value)
{
    int hashIndex = hashFunction(key);                          // Obliczenie indeksu kubełka gdzie zostanie dodany/zaktualizowany węzeł.
    HashTable_List_Node* newNode = new HashTable_List_Node;     // Utworzenie nowego węzła.
    newNode->key = key;                                         // Przypisanie klucza.
    newNode->value = value;                                     // Przypisanie wartości.

    if (hashTable[hashIndex] == nullptr)
    {
        hashTable[hashIndex] = newNode; // Jeśli kubełek jest pusty, ustawia nowy węzeł jako pierwszy w danym kubełku.
    }
    else
    {
        HashTable_List_Node* currentNode = hashTable[hashIndex]; // Wskaźnik na pierwszy węzeł w kubełku.

        while (currentNode->nextNode != nullptr)
        {
            if (currentNode->key == key)
            {
                currentNode->value = value; // Jeśli klucz już istnieje, aktualizuje jego wartość.
                delete newNode;             // Usuwa niepotrzebny nowy węzeł.
                return;
            }
            currentNode = currentNode->nextNode; // Przejście na następny węzeł.
        }
        if (currentNode->key == key)
        {
            currentNode->value = value; // Jeśli klucz już istnieje, aktualizuje jego wartość.
            delete newNode;             // Usuwa niepotrzebny nowy węzeł.
            return;
        }
        else
        {
            currentNode->nextNode = newNode; // Wstawienie nowego węzła.
        }

    }
}

int HashTable_List::search(int key) const
{
    int hashIndex = hashFunction(key); // Obliczenie indeksu kubełka (może) znajdować się węzeł o szukanym kluczu.

    if (hashTable[hashIndex] != nullptr)
    {
        HashTable_List_Node* currentNode = hashTable[hashIndex]; // Wskaźnik na pierwszy węzeł w kubełku.

        while (currentNode != nullptr)
        {
            if (currentNode->key == key)
            {
                return currentNode->value; // Zwraca wartość ze znalezionej pary klucz-wartość.
            }
            currentNode = currentNode->nextNode; // Przejście na następny węzeł.
        }
    }

    return -1; // Równoznaczne z nieznalezieniem węzła o podanym kluczu.
}

void HashTable_List::remove(int key)
{
    int hashIndex = hashFunction(key); // Obliczenie indeksu kubełka gdzie (może) znajdować się węzeł do usunięcia.

    if (hashTable[hashIndex] != nullptr)
    {
        HashTable_List_Node* currentNode = hashTable[hashIndex];    // Wskaźnik na pierwszy węzeł w kubełku.
        HashTable_List_Node* prevNode = nullptr;                    // Węzeł poprzedzający węzeł do usunięcia.

        while (currentNode != nullptr && currentNode->key != key)
        {
            prevNode = currentNode;                 // Ustawienie potencjalnego węzła do usunięcia na obecny węzeł.
            currentNode = currentNode->nextNode;    // Przejście na następny węzeł.
        }
        if (currentNode != nullptr)
        {
            if (prevNode == nullptr)
            {
                hashTable[hashIndex] = currentNode->nextNode; // Jeżeli węzeł do usunięcia jest na początku, ustawia następny węzeł jako pierwszy w kubełku.
            }
            else
            {
                prevNode->nextNode = currentNode->nextNode; // Załatanie "dziury" przez usunięciem węzła.
            }
            delete currentNode; // Usunięcie znalezionego węzła.
        }
    }
}

HashTable* HashTable_List::copy()
{
    HashTable_List* copiedHashTable = new HashTable_List;   // Utworzenie nowej kopii tablicy mieszającej.
    HashTable_List_Node* currentNode = nullptr;             // Wskaźnik na kolejne węzły w kubełkach.

    for (int i = 0; i < HASH_TABLE_CAPACITY; i++)
    {
        currentNode = hashTable[i]; // Ustawienie wskaźnika na początek obecnego kubełka.
        while (currentNode != nullptr)
        {
            int copiedKey = currentNode->key;                   // Kopia klucza.
            int copiedValue = currentNode->value;               // Kopia wartości.
            copiedHashTable->insert(copiedKey, copiedValue);    // Wstawienie skopiowanej pary klucz-wartość.
            currentNode = currentNode->nextNode;                // Przejście na następny węzeł
        }
    }

    return copiedHashTable; // Zwraca nową kopię tablicy mieszającej.
}

int HashTable_List::hashFunction(int key) const
{
    return key % HASH_TABLE_CAPACITY;
}
