/********************************************************************
* Max Heap
*
* Author: Paul Thompson
*
* Purpose: Creates the Max_heap class. Max_heap inherits Vector<int>
* and can be instantiated with a list, or element by element with
* push(). When heapify() or siftup() is finished the heap will
* have the maximum element value at it's root.
*
********************************************************************/

#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include "vector.hpp"
#include <iostream>
#include <cmath>

class Max_heap{
private:
    Vector<int> __max_heap;
public:

    Max_heap():
        __max_heap()
    {}

    Max_heap(std::initializer_list<int> list):
        __max_heap()
    {
        for(int n :list) push(n);
    }

    ~Max_heap(){}

    // add an element to the bottom of the tree
    void push(int n) {
        __max_heap.push_back(n);
    }

    // buildheap takes the number of elements to place
    // in the heap and a method for heaping it.
    // A value of 1 in method will use siftup().
    // A value of 0 passed through method only add the elements.
    // Heapify() must be manually called after if this method
    // is choosen.
    //
    // For Max_heap, buildHeap() places the smallest value at
    // the root so we get worst case for testing
    void buildHeap(int elements, int method){
        if(method == 0) {
            for(int i=0;i<elements;++i) push(i);
        }
        if(method == 1){
            for(int i=0;i<elements;++i) {
                push(i);
                siftup(end());
            }
        }
    }

    void pop(){ __max_heap.pop_back(); }
    void clear() {__max_heap.clear();}

    int  size(){ __max_heap.size();}
    int const size() const {return __max_heap.size();}

    int *root() {return __max_heap.begin();}
    int const *root() const {return __max_heap.begin();}

    // Because end() in Vector points passed the last element
    // we need to subtract one to get the last leaf node of
    // the heap
    int *end() {return __max_heap.end()-1;}

    // getter to retrieve the value of any index
    int const get(int index) const { return __max_heap[index];}

    // print the element values from root to end.
    void print() {
        std::cout << "Max heap elements: ";
        for(int *i = __max_heap.begin(); i < __max_heap.end(); ++i)
            std::cout << *i << " ";
        std::cout << "\n";
    }

    // Heapify starts at the last internal node of the tree: n/2.
    // While it hasn't reached the root, it calls siftdown()
    // which recursively compares the node values. The tree will
    // be a max heap when heapify() returns
    void heapify () {
        int *start = rootOf(end());

        while(start >= root()) {
            siftDown(start);
            --start;
        }

    }

    // Siftdown() finds the children of the node given, compares
    // their values and swaps them if necessary. It then recurses
    // on the swapped child since the swap could have upset the
    // heap property on lower subtrees.
    void siftDown(int *node){
        // base case.
        if(isLeaf(node)) return;

        int *left = leftChildOf(node), *right = rightChildOf(node);
        int *max_child = largest(left,right);
        if(*node < *max_child) swapValues(max_child, node);

        // recursion
        siftDown(max_child);
    }

    // Siftup() takes a node that has just been added to the heap
    // and compares it to its parent. It swaps values if necessary
    // and recurses on the parent node until reaching the root.
    void siftup(int *node) {
        // base case
        if(node == root() || size() == 0) return;

        int *parent = rootOf(node);
        if(*node > *parent) swapValues(node, parent);

        // recursion
        return siftup(parent);

    }

    // Find the largest value of two nodes. Return it.
    int *largest(int *left, int *right){
        if(*left >= *right) return left;
        return right;
    }

    // Determine if a node is a leaf by considering the
    // possibility that it could have a left child. If
    // the index of where the left child would be is
    // greater than the size of the vector, it does not exist.
    //
    // NOTE: a node cannot have a right child and not a left
    // in a heap due to it's complete binary tree nature.
    bool isLeaf(int *node) {
        int left = (indexOf(node)*2)+1;
        return left > size()-1;
    }

    // Find the root (parent) of a given node
    int *rootOf(int *node){
        int parent = std::floor(indexOf(node)-1)/2;
        return &__max_heap[parent];
    }

    // Find the left child of the given root. Must make sure
    // the left child exists before calling leftChildOf()
    int *leftChildOf(int *root) {
        int index = indexOf(root);
        return &__max_heap[(2*index)+1];

    }

    // Find the right child of the given root. Must make sure
    // the right child exists before calling leftChildOf()
    int *rightChildOf(int *root) {
        int index = indexOf(root);
        return &__max_heap[(2*index)+2];
    }

    // Swap values between a given child node and its parent
    void swapValues(int *child, int *parent){
        int temp = *child;
        *child = *parent;
        *parent = temp;
    }

    // Return the index of the given node
    int indexOf(int *node){return node-root(); }

};
#endif
