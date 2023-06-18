#include <iostream>
#include <string>
#include "doubleHashing.hpp"
using namespace std;

int main(){

    bool exit = false;
    char userInput;
    cin >> userInput;
    int tableSize;
    cin >>  tableSize;

    doubleHashingHashTable t1(tableSize);

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
            t1.insert(SN,LN);
        }
        else if (userInput2 == "s")
        {
            unsigned int SN;
            cin >> SN;
            t1.search(SN);
        }
        else if (userInput2 == "d")
        {
            unsigned int SN;
            cin >> SN;
            t1.deleteKV(SN);

        }
        
        if (cin.eof())
        {

            return 0;
        }
    }

    return 0;
}