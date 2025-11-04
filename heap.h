//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

extern int weightArr[];

struct MinHeap {
    static const int CAP = 64;
    int data[64];
    int size;


    MinHeap() { size = 0; }

    int getSize() const { return size; }

    //Insert a new node index into the heap
    void push(int idx) {
        if (size >= CAP) return; //don't do anything if full
        data[size] = idx; //add index to end of the heap
        upheap(size); //move upward to restore order
        size++; //increase heap size
    }

    //Return (but don't remove) smallest element
    int top() const{
        if (size == 0) return -1; //empty heap case
        return data[0];
    }


    //Remove and return the smallest element
    int pop() {
       if (size == 0) return -1; //nothing to pop
       int ret = data[0]; //store smallest element to return
       size--; //reduce heap size by 1
       if (size > 0){
           data[0] = data[size]; //move last element to root
           downheap(0);
       }
       return ret; //return smallest index
    }

    //Moves the node upward until heap property is restored
    void upheap(int i) {
        while (i > 0){
            int p = (i - 1) / 2; //parent index
            //Compare by node weight
            if (weightArr[data[i]] < weightArr[data[p]]){
                //Swap child and parent if the child is smaller
                int t = data[i]; data[i] = data[p]; data[p] = t;
                i = p; //move up to parent
            } else break; //stops if heap properly holds
        }
    }

    //Moves the node downward until heap property is restored
    void downheap(int i) {
        while (true){
            int l = 2 * i * 1; //index of left child
            int r = 2 * i + 2; //index of right child
            int smallest = i;

            //Check if the left child is smaller
            if (l < size && weightArr[data[l]] < weightArr[data[smallest]])
                smallest = l;
            //Check if the right child is smaller
            if (r < size && weightArr[data[r]] < weightArr[data[smallest]])
                smallest = r;

            //If the current node is already at its smallest, stop
            if (smallest == i) break;
            //If not, swap with the smaller child
            swap(data[i], data[smallest]);
            i = smallest; //Continue downward
        }
    }
};

#endif