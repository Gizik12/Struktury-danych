#include "PriorityQueue.h"
#include <iostream>
using namespace std;

#ifndef PRIORITY_QUEUE_HEAP_H
#define PRIORITY_QUEUE_HEAP_H

class PriorityQueue_Heap : public PriorityQueue
{
private:
    struct PriorityQueue_Heap_Node {
        int Element;
        int Priority;
    };

    PriorityQueue_Heap_Node *Queue;
    int Capacity;
    int Size;

    inline int ParentIndex(int Index) const;
    inline int LeftChildIndex(int Index) const;
    inline int RightChildIndex(int Index) const;

    void HeapifyUp(int Index);

    void HeapifyDown(int Index);

public:
 
    PriorityQueue_Heap();

    ~PriorityQueue_Heap();

    void Swap(PriorityQueue_Heap_Node& FirstNode, PriorityQueue_Heap_Node& SecondNode);

    void modifyKey(int Element, int Priority);
    
    int peek();

    void insert(int Element, int Priority);
    int extractMax();
    int returnSize();
};
#endif
