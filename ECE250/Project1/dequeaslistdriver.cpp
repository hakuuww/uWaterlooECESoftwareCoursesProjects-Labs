#include <iostream>
#include <string>
#include "Dequeue.h"
using namespace std;

int main()
{
    bool exit = false;
    char userInput;
    cin >> userInput;
    int dequeueSize;
    cin >> dequeueSize;

    Dequeue List1(dequeueSize);
    cout<<"success\n";

    while (exit == false || (!std::cin.eof()))
    {
        if (cin.eof())
        {
            return 0;
        }

        string userInput2;
        cin >> userInput2;

        if (userInput2 == "push_front")
        {
            string url_name;
            string url;
            cin >> url_name;
            cin >> url;
            List1.insert_at_head(url_name,url);
        }
        else if (userInput2 == "push_back")
        {
            string url_name;
            string url;
            cin >> url_name;
            cin >> url;
            List1.insert_at_tail(url_name,url);
        }
        else if (userInput2 == "pop_front")
        {
            List1.delete_at_head();
        }
        else if (userInput2 == "pop_back")
        {
            List1.delete_at_tail();
        }
        else if (userInput2 == "clear")
        {
            List1.clear();
        }
        else if (userInput2 == "size")
        {
            List1.get_size();
        }
        else if (userInput2 == "front")
        {
            List1.get_front();
        }
        else if (userInput2 == "back")
        {
            List1.get_back();
        }
        else if (userInput2 == "empty")
        {
            bool boolean = List1.is_empty();
            if(boolean){
                cout<<"empty 1\n";
            }else{
                cout<<"empty 0\n";
            }
        }
        else if (userInput2 == "find")
        {
            string url_name;
            cin >> url_name;
            List1.find(url_name);
        }
        else if (userInput2 == "print")
        {
            List1.print();
        }
        else if (userInput2 == "exit")
        {
            exit = true;
            return 0;
        }

        if (cin.eof())
        {

            return 0;
        }
    }

    return 0;
}