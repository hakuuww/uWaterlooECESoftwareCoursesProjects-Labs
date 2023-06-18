#include <iostream>
#include <string>
#include <vector>
#include "chaining.hpp"
using namespace std;

chainingHashTable::chainingHashTable(int table_size_p) : TABLE_SIZE(table_size_p)
{
    p_kvPairArr = new vector<KVPair>[TABLE_SIZE] {};

    cout << "success" << endl;
}

chainingHashTable::~chainingHashTable()
{
    delete[] p_kvPairArr; // delete the array of pointers to KVPairs
}

void chainingHashTable::insert(unsigned int studentNumber_p, string lastName_p)
{
    int h1 = this->h1(studentNumber_p);
    KVPair newKVPair(studentNumber_p, lastName_p);

    if (p_kvPairArr[h1].empty())
    {
        p_kvPairArr[h1].insert(p_kvPairArr[h1].begin(), newKVPair);
        cout << "success\n";
        return;
    }

    if (studentNumber_p > p_kvPairArr[h1][0].get_SN())
    {
        p_kvPairArr[h1].insert(p_kvPairArr[h1].begin(), newKVPair);
        cout << "success\n";
        return;
    }

    int last_index = chainSize(studentNumber_p) - 1;
    if (studentNumber_p < p_kvPairArr[h1][last_index].get_SN())
    {
        p_kvPairArr[h1].push_back(newKVPair);
        cout << "success\n";
        return;
    }

    int index = search_for_Insert(studentNumber_p, 0, chainSize(studentNumber_p) - 1);

    if (p_kvPairArr[h1][index].compare(studentNumber_p)) // key already there
    {
        cout << "failure\n";
        return;
    }else{
        p_kvPairArr[h1].insert(p_kvPairArr[h1].begin()+index, newKVPair);
    }
}

int chainingHashTable::search(unsigned int studentNumber_p, int start, int end) // binary search
{
    int h1 = this->h1(studentNumber_p);
    if (chainSize(studentNumber_p) == 0)
    {
        cout << "not found\n";
        return -1;
    }

    if (start > end)
    {
        cout << "not found\n";
        return -1;
    }

    int mid = (end + start) / 2;
    if (p_kvPairArr[h1][mid].get_SN() == studentNumber_p)
    {
        cout << "found " << p_kvPairArr[h1][mid].get_LN() << " in " << h1 << endl;
        return mid;
    }
    else if (p_kvPairArr[h1][mid].get_SN() < studentNumber_p)
    {
        return this->search(studentNumber_p, start, mid - 1);
    }
    else
    {
        return this->search(studentNumber_p, mid + 1, end);
    }
}

int chainingHashTable::search_no_Output(unsigned int studentNumber_p, int start, int end) // binary search
{
    if (start > end)
    {
        return -1;
    }
    int h1 = this->h1(studentNumber_p);
    int mid = (end + start) / 2;
    if (p_kvPairArr[h1][mid].get_SN() == studentNumber_p)
    {
        return mid;
    }
    else if (p_kvPairArr[h1][mid].get_SN() < studentNumber_p)
    {
        return this->search_no_Output(studentNumber_p, start, mid - 1);
    }
    else
    {
        return this->search_no_Output(studentNumber_p, mid + 1, end);
    }
}

int chainingHashTable::search_for_Insert(unsigned int studentNumber_p, int start, int end)
// binary search,
// need to ensure that the input student number
// is not larger than all elements in the list and
// not smaller than all elements in the list
{
    int h1 = this->h1(studentNumber_p);

    if (((end - start) == 1) && (p_kvPairArr[h1][end].get_SN() < studentNumber_p) && (p_kvPairArr[h1][start].get_SN() > studentNumber_p))
    {
        return end;
    }

    int mid = (end + start) / 2;
    if (p_kvPairArr[h1][mid].get_SN() == studentNumber_p)
    {
        return mid;
    }
    else if (p_kvPairArr[h1][mid].get_SN() < studentNumber_p)
    {
        return this->search_for_Insert(studentNumber_p, start, mid);
    }
    else
    {
        return this->search_for_Insert(studentNumber_p, mid, end);
    }
}

int chainingHashTable::chainSize(unsigned int studentNumber_p)
{
    int h1 = this->h1(studentNumber_p);
    int chain_Size = p_kvPairArr[h1].size();
    return chain_Size;
}

void chainingHashTable::deleteKV(unsigned int studentNumber_p) // binary search
{
    int position = search_no_Output(studentNumber_p, 0, this->chainSize(studentNumber_p) - 1);
    if (position != -1)
    {
        p_kvPairArr[h1(studentNumber_p)].erase(p_kvPairArr[h1(studentNumber_p)].begin() + position);
        cout << "success\n";
    }
    else
    {
        cout << "failure\n";
    }
}

void chainingHashTable::printChain(int chain_Num)
{
    if (p_kvPairArr[chain_Num].empty())
    {
        cout << "chain is empty\n";
        return;
    }
    for (vector<KVPair>::iterator it = p_kvPairArr[chain_Num].begin(); it != p_kvPairArr[chain_Num].end(); ++it)
    {
        int index = it - p_kvPairArr[chain_Num].begin();
        cout << p_kvPairArr[chain_Num][index].get_SN() << " ";
    }

    cout << "\n";
    return;
}
int chainingHashTable::h1(unsigned int k)
{
    int ret = (k % TABLE_SIZE);
    return ret;
}

/////////////////////////////////////////////////////

KVPair::KVPair(unsigned int studentNumber_p, string lastName_p) : STUDENT_NUMBER(studentNumber_p), LAST_NAME(lastName_p)
{
}

KVPair::~KVPair()
{
}

unsigned int KVPair::get_SN() const
{
    return STUDENT_NUMBER;
}

string KVPair::get_LN() const
{
    return LAST_NAME;
}

bool KVPair::compare(unsigned int studentNumber_p) const
{
    if (studentNumber_p == STUDENT_NUMBER)
    {
        return true;
    }

    return false;
}
