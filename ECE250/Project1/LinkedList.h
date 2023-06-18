#include <iostream>
#include <string>
using namespace std;
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"



class LinkedList
{
protected:
    Node *head;
    Node *tail;
    unsigned int size;

public:
    LinkedList();
    ~LinkedList();
    void insert_at_head(string data1_p, string data2_p);
    void insert_at_tail(string data1_p, string data2_p);
    void delete_at_head();
    void delete_at_tail();
    void clear();
    void get_size();
    void get_front();
    void get_back();
    bool is_empty();
    void find(string url_name);
    void print();
    void deleteList();
    void print_node(Node* node);
    void delete_at_head_no_output();
    void delete_at_tail_no_output();
};

#endif