#include "../Public/PriorityQueue_Heap.h"

#include <cmath>

PriorityQueue_Heap::PriorityQueue_Heap()
{
    Queue = nullptr;
    Capacity = 0;
    Size = 0;
}

PriorityQueue_Heap::~PriorityQueue_Heap()
{
    delete[] Queue;
}

void PriorityQueue_Heap::insert(int Element, int Priority)
{
    if (Size >= Capacity)
    {
        Capacity = (Capacity == 0) ? 1 : 2 * Capacity;
        PriorityQueue_Heap_Node* NewQueue = new PriorityQueue_Heap_Node[Capacity];
        for (int i = 0; i < Size; i++)
        {
            NewQueue[i] = Queue[i];
        }
        delete Queue;
        Queue = NewQueue;
    }
    PriorityQueue_Heap_Node NewNode;
    NewNode.Element = Element;
    NewNode.Priority = Priority;
    Queue[Size] = NewNode;
    HeapifyUp(Size);
    Size++;
}

int PriorityQueue_Heap::extractMax()
{
    if (Size > 0)
    {
        int MaxElement = Queue[0].Element;
        Swap(Queue[0], Queue[Size - 1]);
        Size--;
        HeapifyDown(0);
        return MaxElement;
    }
}

int PriorityQueue_Heap::peek()
{
    return Queue[0].Element;
}

void PriorityQueue_Heap::modifyKey(int Element, int Priority)
{
    for (int i = 0; i < Size; i++)
    {
        if (Queue[i].Element == Element && Queue[i].Priority != Priority)
        {
            int OldPriority = Queue[i].Priority;
            Queue[i].Priority = Priority;
            if (Priority > OldPriority)
            {
                HeapifyUp(i);
            }
            else
            {
                HeapifyDown(i);
            }
            return;
        }
    }
    return;
}

int PriorityQueue_Heap::returnSize()
{
    return Size;
}

void PriorityQueue_Heap::HeapifyUp(int Index)
{
    while (Index > 0 && Queue[ParentIndex(Index)].Priority < Queue[Index].Priority)
    {
        Swap(Queue[Index], Queue[ParentIndex(Index)]);
        Index = ParentIndex(Index);
    }
}

void PriorityQueue_Heap::HeapifyDown(int Index)
{
    int MaxIndex = Index;
    while ((LeftChildIndex(MaxIndex) < Size && Queue[MaxIndex].Priority <= Queue[LeftChildIndex(MaxIndex)].Priority) 
        || (RightChildIndex(MaxIndex) < Size && Queue[MaxIndex].Priority <= Queue[RightChildIndex(MaxIndex)].Priority))
    {
        MaxIndex = (RightChildIndex(MaxIndex) >= Size || Queue[LeftChildIndex(MaxIndex)].Priority > Queue[RightChildIndex(MaxIndex)].Priority) 
            ? LeftChildIndex(MaxIndex) : RightChildIndex(MaxIndex);
        Swap(Queue[Index], Queue[MaxIndex]);
        Index = MaxIndex;
    }
}

void PriorityQueue_Heap::Swap(PriorityQueue_Heap_Node& FirstNode, PriorityQueue_Heap_Node& SecondNode)
{
    PriorityQueue_Heap_Node TmpNode = FirstNode;
    FirstNode = SecondNode;
    SecondNode = TmpNode;
}

inline int PriorityQueue_Heap::ParentIndex(int Index) const
{
    return static_cast<int>(floor((static_cast<double>(Index) - 1.0) / 2.0));
}

inline int PriorityQueue_Heap::LeftChildIndex(int Index) const
{
    return 2 * Index + 1;
}

inline int PriorityQueue_Heap::RightChildIndex(int Index) const
{
    return 2 * Index + 2;
}
