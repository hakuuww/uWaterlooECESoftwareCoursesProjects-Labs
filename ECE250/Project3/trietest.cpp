#include <iostream>
#include <string>
#include <fstream>
#include "Trie.h"
#ifndef TRIE_H
#define TRIE_H

using namespace std;



int main()
{

    Trie trie1;

    string addWord;
    illegal_exception ie;
    // while (cin >> cmd)
    // {
    //     if (cmd == "load")
    //     {

    while ((!std::cin.eof()))
    {
        if (cin.eof())
        {
            return 0;
        }

        string userInput2;
        cin >> userInput2;

        try
        {

            if (userInput2 == "load")
            {
                ifstream fin("corpus.txt");
                while (fin >> addWord)
                {
                    ie.check_illegal_argument(addWord);
                    trie1.insert(addWord);
                }
                cout << "success" << endl;
            }
            else if (userInput2 == "i")
            {
                string word;
                cin >> word;
                ie.check_illegal_argument(word);

                int state = trie1.insert(word);

                if (state == 1)
                {
                    cout << "success\n";
                }
                else if (state == 0)
                {
                    cout << "failure\n";
                }
                else if (state == -1)
                {
                }
            }
            else if (userInput2 == "s")
            {
                string word;
                cin >> word;
                ie.check_illegal_argument(word);
                int state = trie1.search(word);

                if (state == 1)
                {
                    cout << "found " << word << "\n";
                }
                else if (state == 0)
                {
                    cout << "not found\n";
                }
                else if (state == -1)
                {
                }
            }
            else if (userInput2 == "e")
            {
                string word;
                cin >> word;
                ie.check_illegal_argument(word);
                int state = trie1.erase_trie(word);

                if (state == 1)
                {
                    cout << "success\n";
                }
                else if (state == 0)
                {
                    cout << "failure\n";
                }
                else if (state == -1)
                {
                }
            }
            else if (userInput2 == "p")
            {
                trie1.print_trie();
            }
            else if (userInput2 == "spellcheck")
            {
                string word;
                cin >> word;
                ie.check_illegal_argument(word);
                trie1.spell_checkTrie(word);
            }
            else if (userInput2 == "empty")
            {
                cout << "empty " << trie1.empty() << endl;
                ;
            }
            else if (userInput2 == "clear")
            {
                trie1.clear_trie();
            }
            else if (userInput2 == "size")
            {
                cout << "number of words is: " << trie1.get_size() << endl;
            }
            else if (userInput2 == "exit")
            {
                return 0;
            }
        }
        catch (illegal_exception e)
        {
            cout << "illegal argument\n";
        }

        if (cin.eof())
        {
            return 0;
        }
    }

    return 0;
}



#endif