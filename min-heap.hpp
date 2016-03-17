/********************************************************************
* Min Heap
*
* Author: Paul Thompson 
*
* Purpose: Creates the Min_heap class. Min_heap inherits Vector<int>
* and can be instantiated with a list, or element by element with
* push(). When heapify() or siftup() is finished the heap will
* have the minimum element value at it's root.
*
********************************************************************/

#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include "vector.hpp"
#include <iostream>
#include <cmath>

class Min_heap {
private:
    Vector<int> __min_heap;
public:
    Min_heap():
        __min_heap()
    {}

    Min_heap(std::initializer_list<int> list):
        __min_heap()
    {
        for (int n:list) push(n);
        heapify();
    }

    ~Min_heap(){}

    // add an element to the bottom of the tree
    void push(int n) { __min_heap.push_back(n);}
    void clear(){__min_heap.clear();}

    // buildheap takes the number of elements to place
    // in the heap and a method for heaping it.
    // A value of 1 in method will use siftup().
    // A value of 0 passed through method only add the elements.
    // Heapify() must be manually called after if this method
    // is choosen.
    //
    // For Min_heap, buildHeap() places the largest element at
    // the bottom of the tree, so we get worst-case time for
    // testing
    void buildHeap(int elements, int method){
        if(method == 0) {
            for(int i=elements;i>0;--i) push(i);
        }
        if(method == 1){
            for(int i=elements;i>0;--i) {
                push(i);
                siftup(end());
            }
        }
    }

    void pop(){ __min_heap.pop_back(); }

    int size(){ __min_heap.size();}
    int const size() const {return __min_heap.size();}

    int *root() {return __min_heap.begin();}
    int const *root() const {return __min_heap.begin();}

    // Because end() in Vector points passed the last element
    // we need to subtract one to get the last leaf node of
    // the heap
    int *end() {return __min_heap.end()-1;}

    // getter to retrieve the value of any index
    int const get(int index) const {return __min_heap[index];}

    // print the element values from root to end.
    void print() {
        std::cout << "Min heap elements: ";
        for(int *i = __min_heap.begin(); i < __min_heap.end(); ++i)
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
        // base case
        if(isLeaf(node)) return;

        int *left = leftChildOf(node), *right = rightChildOf(node);
        int *min_child = smallest(left,right);
        if(*node > *min_child) swapValues(min_child, node);

        // recursion
        siftDown(min_child);
    }

    // Siftup() takes a node that has just been added to the heap
    // and compares it to its parent. It swaps values if necessary
    // and recurses on the parent node until reaching the root.
    void siftup(int *node) {
        // base case
        if(node == root() || size() == 0) return;

        int *parent = rootOf(node);
        if(*node < *parent) swapValues(node, parent);

        // recursion
        return siftup(parent);
    }

    // Find the smallest value of two nodes. Return it.
    int *smallest(int *left, int *right){
        if(*left <= *right) return left;
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
        return &__min_heap[parent];
    }

    // Find the left child of the given root. Must make sure
    // the left child exists before calling leftChildOf()
    int *leftChildOf(int *root) {
        int index = indexOf(root);
        return &__min_heap[(2*index)+1];

    }

    // Find the right child of the given root. Must make sure
    // the right child exists before calling leftChildOf()
    int *rightChildOf(int *root) {
        int index = indexOf(root);
        return &__min_heap[(2*index)+2];
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
