#include <iostream>
#include <string>
#ifndef DEQUEUE_H
#define DEQUEUE_H
#include "LinkedList.h"


using namespace std;

class Dequeue: public LinkedList
{
    private:
        const unsigned int MAX_SIZE;
    public:
        Dequeue(unsigned int dequeue_Max_Size);

        void insert_at_head(string data1_p, string data2_p);
        void insert_at_tail(string data1_p, string data2_p);
};

#endif



