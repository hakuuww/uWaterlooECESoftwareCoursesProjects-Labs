#include <iostream>
#include <string>
#include "Node.h"
using namespace std;



Node::Node(string data1_p, string data2_p)
{
    data1 = data1_p;
    data2 = data2_p;
    next = nullptr;
    prev = nullptr;
}

Node::Node(){
    next = nullptr;
    prev = nullptr;
}

Node::~Node()
{
    next = nullptr;
    prev = nullptr;
}

Node*  Node::get_next()
{
    return next;
}
Node* Node::get_prev()
{
    return prev;
}

void Node::set_next(Node* address)
{
    next = address;
}

void Node::set_prev(Node* address)
{
    prev = address;
}


string Node::get_data1()
{
    return data1;
}

string Node::get_data2()
{
    return data2;
}
