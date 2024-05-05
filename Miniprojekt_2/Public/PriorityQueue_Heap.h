#include "PriorityQueue.h"
#include <iostream>
using namespace std;

#ifndef PRIORITY_QUEUE_HEAP_H
#define PRIORITY_QUEUE_HEAP_H

struct PriorityQueue_Heap_Node
{
    int element;
    int priority;
};

class PriorityQueue_Heap final : public PriorityQueue
{
public:

    PriorityQueue_Heap();

    ~PriorityQueue_Heap();

    virtual void insert(int element, int priority) override;

    virtual int extractMax() override;

    virtual int peek() const override;
    
    virtual void modifyKey(int element, int priority) override;
    
    virtual int returnSize() const override;

    void swap(PriorityQueue_Heap_Node& firstNode, PriorityQueue_Heap_Node& secondNode);

private:

    PriorityQueue_Heap_Node* queue;
    int capacity;
    int size;

    inline int parentIndex(int index) const;

    inline int leftChildIndex(int index) const;

    inline int rightChildIndex(int index) const;

    void heapifyUp(int index);

    void heapifyDown(int index);

    virtual PriorityQueue* copy() override;
};

#endif
