#include "../Public/PriorityQueue_Heap.h"

#include <cmath>

// Konstruktor
PriorityQueue_Heap::PriorityQueue_Heap()
{
    queue = nullptr;
    capacity = 0;
    size = 0;
}

// Destruktor
PriorityQueue_Heap::~PriorityQueue_Heap()
{
    delete[] queue;
}

// Metoda dodająca nowy element do kolejki
void PriorityQueue_Heap::insert(int element, int priority)
{
    // Rozszerzenie tablicy, jeśli jest potrzebne
    if (size >= capacity)
    {
        capacity = (capacity == 0) ? 1 : 2 * capacity;
        PriorityQueue_Heap_Node* newQueue = new PriorityQueue_Heap_Node[capacity];
        for (int i = 0; i < size; i++)
        {
            newQueue[i] = queue[i];
        }
        delete queue;
        queue = newQueue;
    }
    // Tworzenie nowego węzła
    PriorityQueue_Heap_Node newNode;
    newNode.element = element;
    newNode.priority = priority;
    // Dodawanie węzła do kolejki i naprawa kopca
    queue[size] = newNode;
    heapifyUp(size);
    size++;
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
        return maxElement;
    }
}

// Metoda zwracająca element o najwyższym priorytecie bez usuwania go
int PriorityQueue_Heap::peek() const
{
    return queue[0].element;
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
                heapifyUp(i);
            }
            else
            {
                heapifyDown(i);
            }
            return;
        }
    }
    return;
}

// Metoda zwracająca aktualny rozmiar kolejki
int PriorityQueue_Heap::returnSize() const
{
    return size;
}

// Naprawianie kopca po dodaniu elementu
void PriorityQueue_Heap::heapifyUp(int index)
{
    while (index > 0 && queue[parentIndex(index)].priority < queue[index].priority)
    {
        swap(queue[index], queue[parentIndex(index)]);
        index = parentIndex(index);
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
        swap(queue[index], queue[maxIndex]);
        index = maxIndex;
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
            copiedHeap->insert(copiedElement, copiedPriority);
        }
        return copiedHeap;
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
    return static_cast<int>(floor((static_cast<double>(index) - 1.0) / 2.0));
}

inline int PriorityQueue_Heap::leftChildIndex(int index) const
{
    return 2 * index + 1;
}

inline int PriorityQueue_Heap::rightChildIndex(int index) const
{
    return 2 * index + 2;
}