#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;

LinkedList::LinkedList()
{
    head = new Node();
    tail = new Node();
    head->set_next(tail);
    head->set_prev(nullptr);
    tail->set_next(nullptr);
    tail->set_prev(head);
    size = 0;
}

LinkedList::~LinkedList()
{
    while(size!=0){
        this->delete_at_head_no_output();
    }
    delete this->head;
    delete this->tail;
}

void LinkedList::insert_at_head(string data1_p, string data2_p)
{
    Node *newNode = new Node(data1_p, data2_p);
    head->get_next()->set_prev(newNode);
    newNode->set_next(head->get_next());
    newNode->set_prev(head);
    head->set_next(newNode);
    size++;
    cout << "success\n";
    // head's next's previous node is set to new node
    // new node's next node is set to head's next node
    // new node's previous node is set to head node
    // head's next node is set to new node
    // head's previous node is set to new node
}
void LinkedList::insert_at_tail(string data1_p, string data2_p)
{
    Node *newNode = new Node(data1_p, data2_p);
    tail->get_prev()->set_next(newNode);
    newNode->set_prev(tail->get_prev());
    newNode->set_next(tail);
    tail->set_prev(newNode);
    size++;
    cout << "success\n";
}

void LinkedList::delete_at_head()
{
    if (is_empty())
    {
        cout << "failure\n";
        return;
    }
    Node *temp = head->get_next();
    head->set_next(temp->get_next());
    temp->get_next()->set_prev(head);
    delete temp;
    size--;
    cout << "success\n";
}
void LinkedList::delete_at_tail()
{
    if (is_empty())
    {
        cout << "failure\n";
        return;
    }
    Node *temp = tail->get_prev();
    tail->set_prev(temp->get_prev());
    temp->get_prev()->set_next(tail);
    delete temp;
    size--;
    cout << "success\n";
}

void LinkedList::clear()
{
    while(size!=0){
        this->delete_at_head_no_output();
    }
    cout<<"success\n";
    return;
}

void LinkedList::get_size()
{
    cout << "size is " << this->size << "\n";
}

void LinkedList::get_front()
{
    if (is_empty())
    {
        cout << "failure\n";
        return;
    }
    cout << "front is ";
    print_node(head->get_next());
    return;
}

void LinkedList::get_back()
{
    if (is_empty())
    {
        cout << "failure\n";
        return;
    }
    cout << "back is ";
    print_node(tail->get_prev());
    return;
}

bool LinkedList::is_empty()
{
    if (size == 0)
    {
        return true;
    }else
    {
        return false;
    }
}

void LinkedList::find(string url_name)
{
    if (this->is_empty())
    {
        cout << "not found " << url_name << "\n";
        return;
    }

    Node *temp = tail->get_prev();

    while (temp != head)
    {
        if (temp->get_data1() == url_name)
        {
            cout << "found "  << url_name << " " << temp->get_data2() << "\n";
            return;
        }

        temp = temp->get_prev();
    }
    cout << "not found " << url_name << "\n";
}

void LinkedList::print()
{
    if (this->is_empty())
    {
        cout << "deque is empty\n";
        return;
    }
    Node *temp = tail->get_prev();

    while (temp != head)
    {
        print_node(temp);
        temp = temp->get_prev();
    }
    return;
}

void LinkedList::deleteList()
{
}

void LinkedList::print_node(Node *node)
{
    cout << node->get_data1() << " " << node->get_data2() << "\n";
}

void LinkedList::delete_at_head_no_output()
{
    Node *temp = head->get_next();
    head->set_next(temp->get_next());
    temp->get_next()->set_prev(head);
    delete temp;
    size--;
}

void LinkedList::delete_at_tail_no_output()
{
    Node *temp = tail->get_prev();
    tail->set_prev(temp->get_prev());
    temp->get_prev()->set_next(tail);
    delete temp;
    size--;
}
