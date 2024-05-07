#include "../Public/PriorityQueue_Heap.h"

#include <cmath> // Dołączenie biblioteki cmath dla funkcji matematycznych

// Konstruktor
PriorityQueue_Heap::PriorityQueue_Heap()
{
    queue = nullptr; // Inicjalizacja wskaźnika na nullptr
    capacity = 0; // Inicjalizacja pojemności kolejki na 0
    size = 0; // Inicjalizacja rozmiaru kolejki na 0
}

// Destruktor
PriorityQueue_Heap::~PriorityQueue_Heap()
{
    delete[] queue; // Zwolnienie pamięci zaalokowanej na kolejkę
}

// Metoda dodająca nowy element do kolejki
void PriorityQueue_Heap::insert(int element, int priority)
{
    // Rozszerzenie tablicy, jeśli jest potrzebne
    if (size >= capacity)
    {
        capacity = (capacity == 0) ? 1 : 2 * capacity; // Podwajanie pojemności kolejki
        PriorityQueue_Heap_Node* newQueue = new PriorityQueue_Heap_Node[capacity]; // Tworzenie nowej tablicy o podwójnej pojemności
        for (int i = 0; i < size; i++)
        {
            newQueue[i] = queue[i]; // Kopiowanie istniejących elementów
        }
        delete queue; // Zwolnienie pamięci poprzedniej tablicy
        queue = newQueue; // Aktualizacja wskaźnika na nową tablicę
    }
    // Tworzenie nowego węzła
    PriorityQueue_Heap_Node newNode;
    newNode.element = element;
    newNode.priority = priority;
    // Dodawanie węzła do kolejki i naprawa kopca
    queue[size] = newNode; // Dodanie nowego węzła na koniec kolejki
    heapifyUp(size); // Naprawa kopca w górę
    size++; // Zwiększenie rozmiaru kolejki
}

// Metoda usuwająca i zwracająca element o najwyższym priorytecie
int PriorityQueue_Heap::extractMax()
{
    if (size > 0)
    {
        // Zamiana miejscami pierwszego i ostatniego elementu
        int maxElement = queue[0].element;
        swap(queue[0], queue[size - 1]);
        size--;
        // Naprawa kopca
        heapifyDown(0);
        return maxElement; // Zwrócenie elementu o najwyższym priorytecie
    }
}

// Metoda zwracająca element o najwyższym priorytecie bez usuwania go
int PriorityQueue_Heap::peek() const
{
    return queue[0].element; // Zwrócenie pierwszego elementu kolejki
}

// Metoda modyfikująca priorytet danego elementu w kolejce
void PriorityQueue_Heap::modifyKey(int element, int priority)
{
    // Znalezienie elementu w kolejce
    for (int i = 0; i < size; i++)
    {
        if (queue[i].element == element && queue[i].priority != priority)
        {
            int oldPriority = queue[i].priority;
            queue[i].priority = priority;
            // Naprawa kopca w zależności od zmiany priorytetu
            if (priority > oldPriority)
            {
                heapifyUp(i); // Naprawa kopca w górę
            }
            else
            {
                heapifyDown(i); // Naprawa kopca w dół
            }
            return;
        }
    }
    return;
}

// Metoda zwracająca aktualny rozmiar kolejki
int PriorityQueue_Heap::returnSize() const
{
    return size; // Zwrócenie rozmiaru kolejki
}

// Naprawianie kopca po dodaniu elementu
void PriorityQueue_Heap::heapifyUp(int index)
{
    while (index > 0 && queue[parentIndex(index)].priority < queue[index].priority)
    {
        swap(queue[index], queue[parentIndex(index)]); // Zamiana miejscami elementów
        index = parentIndex(index); // Przejście do rodzica
    }
}

// Naprawianie kopca po usunięciu elementu
void PriorityQueue_Heap::heapifyDown(int index)
{
    int maxIndex = index;
    while ((leftChildIndex(maxIndex) < size && queue[maxIndex].priority <= queue[leftChildIndex(maxIndex)].priority)
        || (rightChildIndex(maxIndex) < size && queue[maxIndex].priority <= queue[rightChildIndex(maxIndex)].priority))
    {
        maxIndex = (rightChildIndex(maxIndex) >= size || queue[leftChildIndex(maxIndex)].priority > queue[rightChildIndex(maxIndex)].priority)
            ? leftChildIndex(maxIndex) : rightChildIndex(maxIndex);
        swap(queue[index], queue[maxIndex]); // Zamiana miejscami elementów
        index = maxIndex; // Aktualizacja indeksu
    }
}

// Tworzenie głębokiej kopii kolejki
PriorityQueue* PriorityQueue_Heap::copy()
{
    if (size > 0)
    {
        PriorityQueue_Heap* copiedHeap = new PriorityQueue_Heap;
        copiedHeap->capacity = capacity;
        copiedHeap->queue = new PriorityQueue_Heap_Node[capacity];

        for (int i = 0; i < size; i++)
        {
            int copiedElement = queue[i].element;
            int copiedPriority = queue[i].priority;
            copiedHeap->insert(copiedElement, copiedPriority); // Wstawianie kopii elementów do nowej kolejki
        }
        return copiedHeap; // Zwrócenie głębokiej kopii kolejki
    }
}

// Metoda pomocnicza do zamiany miejscami dwóch elementów w kolejce
void PriorityQueue_Heap::swap(PriorityQueue_Heap_Node& firstNode, PriorityQueue_Heap_Node& secondNode)
{
    PriorityQueue_Heap_Node tmpNode = firstNode;
    firstNode = secondNode;
    secondNode = tmpNode;
}

// Metody pomocnicze do nawigacji po kopcu binarnym
inline int PriorityQueue_Heap::parentIndex(int index) const
{
    return static_cast<int>(floor((static_cast<double>(index) - 1.0) / 2.0)); // Obliczanie indeksu rodzica
}

inline int PriorityQueue_Heap::leftChildIndex(int index) const
{
    return 2 * index + 1; // Obliczanie indeksu lewego dziecka
}

inline int PriorityQueue_Heap::rightChildIndex(int index) const
{
    return 2 * index + 2; // Obliczanie indeksu prawego dziecka
}