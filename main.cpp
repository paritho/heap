#include <iostream>
#include "max_heap.hpp"
#include "min_heap.hpp"
#include "Complexity_Timer.hpp"

enum Method{
    exec_su = 0x01,
    exec_sd = 0x02,
    exec_sud = exec_su | exec_sd
};

enum HeapType {
    exec_max = 0x01,
    exec_min = 0x02,
    exec_both = exec_max | exec_min
};

int main(int argc, char** argv) {

    //set flags
    Method method = exec_sud;
    HeapType type = exec_both;
    int elements = 10;

    if(argc == 2) elements = std::stoi(argv[1]);

    if(argc == 3){
        std::string heaptype = argv[1];
        if (heaptype == "max") type = exec_max;
        if (heaptype == "min") type = exec_min;
        elements = std::stoi(argv[2]);
    }

    if(argc == 4) {
        std::string heaptype = argv[1];
        std::string method_to_heap = argv[2];
        if (heaptype == "max") type = exec_max;
        if (heaptype == "min") type = exec_min;
        if (method_to_heap == "su") method = exec_su;
        if (method_to_heap == "sd") method = exec_sd;
        elements = std::stoi(argv[3]);
    }

    Max_heap max;
    Min_heap min;
    Timer time;

    if(type & exec_max){
        time.reset_vectors();
        if(method & exec_sd) {
            max.buildHeap(elements,0);
            if(elements <11) { std::cout << "\nBefore heapify:\n"; max.print(); }
            time.restart();
            max.heapify();
            time.stop();
            if(elements <11) { std::cout << "\nAfter heapify:\n" ;max.print();}
            std::cout << "\nTime to siftdown max heap of " << elements << " elements: " << time.time();
            std::cout << std::endl;
        }
        if(method & exec_su) {
            time.reset_vectors();
            time.record();
            max.buildHeap(elements, 1);
            time.stop();
            std::cout << "\nTime to siftup max heap of " << elements << " elements: " << time.time() << std::endl;
            std::cout << std::endl;
        }
    }

    if(type & exec_min){
        time.reset_vectors();
        if(method & exec_sd) {
            min.buildHeap(elements,0);
            if(elements <11) { std::cout << "\nBefore heapify:\n"; min.print(); }
            time.record();
            min.heapify();
            time.stop();
            if(elements <11) { std::cout << "\nAfter heapify:\n" ;min.print();}
            std::cout << "\nTime to siftdown min heap of " << elements << " elements: " << time.time();
            std::cout << std::endl;
        }
        if(method & exec_su) {
            time.reset_vectors();
            time.record();
            min.buildHeap(elements, 1);
            time.stop();
            std::cout << "\nTime to siftup min heap of " << elements << " elements: " << time.time() << std::endl;
            std::cout << std::endl;
        }
    }

}
