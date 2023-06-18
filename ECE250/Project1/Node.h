#include <iostream>
#include <string>
using namespace std;
#ifndef NODE_H
#define NODE_H

class Node{
  private:
    Node* next;
    Node* prev;
    string data1;
    string data2;
    
  public:
    Node(string data1, string data2);
    Node(); 
    ~Node();
    void set_next(Node* address);
    void set_prev(Node* address);
    Node* get_next();
    Node* get_prev();
    string get_data1();
    string get_data2();
};
#endif