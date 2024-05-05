#include "../Public/PriorityQueue_Heap.h"

#include <cmath>

// Konstruktor klasy PriorityQueue_Heap
PriorityQueue_Heap::PriorityQueue_Heap()
{
    // Inicjalizuje wskaźnik na tablicę na nullptr, co oznacza brak przypisanej pamięci.
    queue = nullptr;
    // Inicjalizuje pojemność kolejki na 0.
    capacity = 0;
    // Inicjalizuje rozmiar kolejki na 0.
    size = 0;
}

// Destruktor klasy PriorityQueue_Heap
PriorityQueue_Heap::~PriorityQueue_Heap()
{
    // Zwolnienie pamięci zajętej przez tablicę przechowującą elementy kolejki.
    delete[] queue;
}

// Metoda insert, która dodaje nowy element do kolejki
void PriorityQueue_Heap::insert(int element, int priority)
{
    // Sprawdzenie, czy aktualny rozmiar kolejki jest większy lub równy pojemności
    if (size >= capacity)
    {
        // Jeśli tak, zwiększa pojemność kolejki o dwukrotność aktualnej pojemności
        capacity = (capacity == 0) ? 1 : 2 * capacity;
        // Tworzy nową tablicę o zwiększonej pojemności
        PriorityQueue_Heap_Node* newQueue = new PriorityQueue_Heap_Node[capacity];
        // Kopiuje elementy z aktualnej kolejki do nowej
        for (int i = 0; i < size; i++)
        {
            newQueue[i] = queue[i];
        }
        // Zwolnienie pamięci zajętej przez starą kolejkę
        delete queue;
        // Przypisanie nowej kolejki do wskaźnika
        queue = newQueue;
    }
    // Tworzy nowy węzeł kolejki
    PriorityQueue_Heap_Node newNode;
    newNode.element = element;
    newNode.priority = priority;
    // Dodaje nowy węzeł do kolejki
    queue[size] = newNode;
    // Przywraca właściwości kopca
    heapifyUp(size);
    // Zwiększa rozmiar kolejki
    size++;
}

// Metoda extractMax, która usuwa i zwraca element o najwyższym priorytecie z kolejki
int PriorityQueue_Heap::extractMax()
{
    // Sprawdza, czy kolejka nie jest pusta
    if (size > 0)
    {
        // Zapisuje element o najwyższym priorytecie
        int maxElement = queue[0].element;
        // Zamienia miejscami pierwszy i ostatni element kolejki
        swap(queue[0], queue[size - 1]);
        // Zmniejsza rozmiar kolejki
        size--;
        // Przywraca właściwości kopca
        heapifyDown(0);
        // Zwraca element o najwyższym priorytecie
        return maxElement;
    }
}

// Metoda peek, która zwraca element o najwyższym priorytecie z kolejki bez usuwania go
int PriorityQueue_Heap::peek() const
{
    // Zwraca element o najwyższym priorytecie (pierwszy element kolejki)
    return queue[0].element;
}

// Metoda modifyKey, która modyfikuje priorytet danego elementu w kolejce
void PriorityQueue_Heap::modifyKey(int element, int priority)
{
    // Szuka elementu w kolejce
    for (int i = 0; i < size; i++)
    {
        // Jeśli element zostanie znaleziony i jego priorytet różni się od nowego priorytetu
        if (queue[i].element == element && queue[i].priority != priority)
        {
            // Zapisuje stary priorytet
            int oldPriority = queue[i].priority;
            // Zmienia priorytet elementu
            queue[i].priority = priority;
            // Naprawia właściwości kopca w zależności od zmiany priorytetu
            if (priority > oldPriority)
            {
                heapifyUp(i);
            }
            else
            {
                heapifyDown(i);
            }
            // Zakończenie pętli
            return;
        }
    }
}

// Metoda returnSize, która zwraca aktualny rozmiar kolejki
int PriorityQueue_Heap::returnSize() const
{
    // Zwraca rozmiar kolejki
    return size;
}

// Metoda heapifyUp, która przywraca właściwości kopca po dodaniu nowego elementu
void PriorityQueue_Heap::heapifyUp(int index)
{
    // Pętla wykonuje się dopóki indeks jest większy od 0 i priorytet rodzica jest mniejszy niż priorytet bieżącego węzła
    while (index > 0 && queue[parentIndex(index)].priority < queue[index].priority)
    {
        // Zamienia miejscami rodzica i bieżący węzeł
        swap(queue[index], queue[parentIndex(index)]);
        // Przesuwa się w górę kopca
        index = parentIndex(index);
    }
}

// Metoda heapifyDown, która przywraca właściwości kopca po usunięciu elementu
void PriorityQueue_Heap::heapifyDown(int index)
{
    // Zmienna przechowująca indeks węzła z najwyższym priorytetem
    int maxIndex = index;
    // Pętla wykonuje się dopóki lewe dziecko znajduje się w granicach kolejki i priorytet rodzica jest mniejszy lub równy priorytetowi lewego dziecka,
    // lub dopóki prawe dziecko znajduje się w granicach kolejki i priorytet rodzica jest mniejszy lub równy priorytetowi prawego dziecka
    while ((leftChildIndex(maxIndex) < size && queue[maxIndex].priority <= queue[leftChildIndex(maxIndex)].priority)
        || (rightChildIndex(maxIndex) < size && queue[maxIndex].priority <= queue[rightChildIndex(maxIndex)].priority))
    {
        // Ustala indeks węzła z najwyższym priorytetem, wybierając większe dziecko lub lewe dziecko, jeśli oba mają równy priorytet
        maxIndex = (rightChildIndex(maxIndex) >= size || queue[leftChildIndex(maxIndex)].priority > queue[rightChildIndex(maxIndex)].priority)
            ? leftChildIndex(maxIndex) : rightChildIndex(maxIndex);
        // Zamienia miejscami bieżący węzeł z węzłem o najwyższym priorytecie
        swap(queue[index], queue[maxIndex]);
        // Przesuwa się w dół kopca
        index = maxIndex;
    }
}

// Metoda copy, która tworzy głęboką kopię kolejki
PriorityQueue* PriorityQueue_Heap::copy()
{
    // Sprawdza, czy kolejka nie jest pusta
    if (size > 0)
    {
        // Tworzy nowy obiekt kopii kolejki
        PriorityQueue_Heap* copiedHeap = new PriorityQueue_Heap;
        // Przypisuje pojemność i alokuje pamięć na kopię kolejki
        copiedHeap->capacity = capacity;
        copiedHeap->queue = new PriorityQueue_Heap_Node[capacity];

        // Kopiuje elementy z oryginalnej kolejki do kopii
        for (int i = 0; i < size; i++)
        {
            int copiedElement = queue[i].element;
            int copiedPriority = queue[i].priority;
            copiedHeap->insert(copiedElement, copiedPriority);
        }
        // Zwraca kopię kolejki
        return copiedHeap;
    }
}

// Metoda swap, która zamienia miejscami dwa elementy kolejki
void PriorityQueue_Heap::swap(PriorityQueue_Heap_Node& firstNode, PriorityQueue_Heap_Node& secondNode)
{
    // Zamienia wartości dwóch węzłów kolejki za pomocą zmiennej tymczasowej
    PriorityQueue_Heap_Node tmpNode = firstNode;
    firstNode = secondNode;
    secondNode = tmpNode;
}

// Metoda parentIndex, która zwraca indeks rodzica danego węzła w kopcu
inline int PriorityQueue_Heap::parentIndex(int index) const
{
    // Oblicza indeks rodzica za pomocą formuły (index - 1) / 2 i zaokrągla wynik w dół
    return static_cast<int>(floor((static_cast<double>(index) - 1.0) / 2.0));
}

// Metoda leftChildIndex, która zwraca indeks lewego dziecka danego węzła w kopcu
inline int PriorityQueue_Heap::leftChildIndex(int index) const
{
    // Oblicza indeks lewego dziecka za pomocą formuły 2 * index + 1
    return 2 * index + 1;
}

// Metoda rightChildIndex, która zwraca indeks prawego dziecka danego węzła w kopcu
inline int PriorityQueue_Heap::rightChildIndex(int index) const
{
    // Oblicza indeks prawego dziecka za pomocą formuły 2 * index + 2
    return 2 * index + 2;
}
