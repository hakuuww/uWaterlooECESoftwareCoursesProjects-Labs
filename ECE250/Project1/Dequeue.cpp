#include <iostream>
#include <string>
#include "Dequeue.h"
using namespace std;

Dequeue::Dequeue(unsigned int dequeue_Max_Size) : MAX_SIZE(dequeue_Max_Size)
{
}



void Dequeue::insert_at_head(string data1_p, string data2_p)
{
    if (size == MAX_SIZE)
    {
        this->delete_at_tail_no_output();
    }
    Node *newNode = new Node(data1_p, data2_p);
    head->get_next()->set_prev(newNode);
    newNode->set_next(head->get_next());
    newNode->set_prev(head);
    head->set_next(newNode);
    size++;
    cout << "success\n";
}
void Dequeue::insert_at_tail(string data1_p, string data2_p)
{
    if (size == MAX_SIZE)
    {
        this->delete_at_head_no_output();
    }
    Node *newNode = new Node(data1_p, data2_p);
    tail->get_prev()->set_next(newNode);
    newNode->set_prev(tail->get_prev());
    newNode->set_next(tail);
    tail->set_prev(newNode);
    size++;
    cout << "success\n";
}

