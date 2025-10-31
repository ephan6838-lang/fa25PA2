//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    //Insert a new node index into the heap
    void push(int idx, int weightArr[]) {
        if (size >= CAP) return;
        data[size] = idx;
        upheap(size);
        size++;
    }

    //Return (but don't remove) smallest element
    int top() const{
        if (size == 0) return -1;
        return data[0];
    }


    //Remove and return the smallest element
    int pop(int weightArr[]) {
       if (size == 0) return -1;
       int ret = data[0];
       size--;
       if (size > 0){
           data[0] = data[size];
           downheap(0);
       }
       return ret;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif