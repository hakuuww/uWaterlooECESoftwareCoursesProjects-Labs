#include <iostream>
#include <string>
#include "chaining.hpp"
using namespace std;

int main()
{

    bool exit = false;
    char userInput;
    cin >> userInput;
    int tableSize;
    cin >> tableSize;

    chainingHashTable t1(tableSize);

    while (exit == false || (!std::cin.eof()))
    {
        if (cin.eof())
        {
            return 0;
        }

        string userInput2;
        cin >> userInput2;

        if (userInput2 == "i")
        {
            unsigned int SN;
            string LN;
            cin >> SN;
            cin >> LN;
            t1.insert(SN, LN);
        }
        else if (userInput2 == "s")
        {
            unsigned int SN;
            cin >> SN;
            t1.search(SN, 0, t1.chainSize(t1.h1(SN)) - 1);
        }
        else if (userInput2 == "d")
        {
            unsigned int SN;
            cin >> SN;
            t1.deleteKV(SN);
        }
        else if (userInput2 == "p")
        {
            int i;
            cin >> i;
            t1.printChain(i);
        }
        else if (userInput2 == "size")
        {
            int i;
            cin >> i;
            cout<<t1.chainSize(i)<<endl;
        }

        if (cin.eof())
        {

            return 0;
        }
    }

    return 0;
}