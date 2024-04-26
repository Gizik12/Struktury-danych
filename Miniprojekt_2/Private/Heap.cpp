#include "../Public/Heap.h"
#include <iostream>

MaxPriorityQueue::MaxPriorityQueue()
{
    this->queue = nullptr;  // Inicjalizacja wskaźnika na nullptr.
    this->capacity = 0;     // Inicjalizacja pojemności kolejki na 0.
    this->size = 0;         // Inicjalizacja rozmiaru kolejki na 0.
}

MaxPriorityQueue::~MaxPriorityQueue()
{
    delete[] this->queue;   // Zwolnienie pamięci zaalokowanej na kolejkę.
}

void MaxPriorityQueue::resize(int newCapacity)
{
    Node* newQueue = new Node[newCapacity]; // Tworzenie nowej kolejki o nowej pojemności.
    for (int i = 0; i < size; ++i)          // Kopiowanie elementów ze starej kolejki do nowej.
    {
        newQueue[i] = queue[i];
    }
    delete[] queue;                         // Zwolnienie pamięci zajmowanej przez starą kolejkę.
    queue = newQueue;                       // Przypisanie nowej kolejki do wskaźnika.
    capacity = newCapacity;                 // Aktualizacja pojemności.
}

void MaxPriorityQueue::siftUp(int index)
{
    while (index > 0)   // Dopóki nie dotrzemy do korzenia.
    {
        int parentIndex = (index - 1) / 2;                         // Obliczenie indeksu rodzica.
        if (queue[index].priority > queue[parentIndex].priority)   // Jeśli priorytet bieżącego elementu jest większy niż rodzica.
        {
            std::swap(queue[index], queue[parentIndex]);           // Zamiana miejscami bieżącego elementu z rodzicem.
            index = parentIndex;                                   // Aktualizacja indeksu bieżącego elementu.
        } 
        else // Jeśli priorytet bieżącego elementu jest mniejszy lub równy priorytetowi rodzica.
        {
           break; // Przerwanie pętli.
        }
    }
}

void MaxPriorityQueue::siftDown(int index)
{
    int maxIndex = index;                   // Ustalenie maksymalnego indeksu na indeks bieżącego elementu.
    int leftChildIndex = 2 * index + 1;     // Obliczenie indeksu lewego dziecka.
    int rightChildIndex = 2 * index + 2;    // Obliczenie indeksu prawego dziecka.

    if (leftChildIndex < size && queue[leftChildIndex].priority > queue[maxIndex].priority) // Jeśli lewe dziecko istnieje i ma większy priorytet niż bieżący element.
    {
        maxIndex = leftChildIndex; // Zaktualizowanie maksymalnego indeksu.
    }

    if (rightChildIndex < size && queue[rightChildIndex].priority > queue[maxIndex].priority) // Jeśli prawe dziecko istnieje i ma większy priorytet niż bieżący element lub lewe dziecko.
    {
        maxIndex = rightChildIndex; // Zaktualizowanie maksymalnego indeksu.
    }

    if (index != maxIndex) // Jeśli bieżący element nie jest maksymalny.
    {
        std::swap(queue[index], queue[maxIndex]);   // Zamiana miejscami bieżącego elementu z maksymalnym.
        siftDown(maxIndex);                         // Wywołanie rekurencyjne dla nowego indeksu bieżącego elementu.
    }
}

void MaxPriorityQueue::insert(int element, int priority)
{
    if (size == capacity) // Jeśli kolejka jest pełna, należy zmienić jej rozmiar.
    {
        resize((capacity == 0) ? 1 : 2 * capacity); // Podwajanie pojemności, chyba że pojemność jest równa zero.
    }
    queue[size].element = element;      // Przypisanie elementu do kolejki.
    queue[size].priority = priority;    // Przypisanie priorytetu do kolejki.
    ++size;                             // Inkrementacja rozmiaru kolejki.
    siftUp(size - 1);                   // Przesunięcie nowego elementu w górę kolejki.
}

int MaxPriorityQueue::extractMax()
{
    if (size == 0) // Jeśli kolejka jest pusta, rzucamy wyjątek.
    {
        throw std::out_of_range("Queue is empty");
    }
    int maxElement = queue[0].element;  // Zapisanie elementu o najwyższym priorytecie.
    queue[0] = queue[size - 1];         // Zastąpienie korzenia ostatnim elementem kolejki.
    --size;                             // Dekrementacja rozmiaru kolejki.
    siftDown(0);                        // Przesunięcie nowego korzenia w dół kolejki.
    return maxElement;                  // Zwrócenie elementu o najwyższym priorytecie.
}

int MaxPriorityQueue::peek()
{
    if (size == 0) // Jeśli kolejka jest pusta, rzucamy wyjątek.
    {
        throw std::out_of_range("Queue is empty");
    }
    return queue[0].element; // Zwracamy element o najwyższym priorytecie.
}

void MaxPriorityQueue::modifyKey(int element, int newPriority)
{
    for (int i = 0; i < size; ++i) // Przeszukujemy kolejkę w poszukiwaniu elementu.
    {
        if (queue[i].element == element)            // Jeśli znaleźliśmy element.
        {
            int oldPriority = queue[i].priority;    // Zapamiętujemy stary priorytet.
            queue[i].priority = newPriority;        // Nadajemy nowy priorytet.
            if (newPriority > oldPriority)          // Jeśli nowy priorytet jest większy od starego.
            {
                siftUp(i); // Przesuwamy element w górę.
            }
            else
            {
                siftDown(i); // Przesuwamy element w dół.
            }
            return; // Kończymy działanie metody.
        }
    }
    throw std::invalid_argument("Element not found"); // Jeśli element nie został znaleziony, rzucamy wyjątek.
}

int MaxPriorityQueue::returnSize()
{
    return size; // Zwracamy rozmiar.
}


