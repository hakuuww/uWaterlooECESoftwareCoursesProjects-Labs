#include <iostream>
#include <string>
#include "doubleHashing.hpp"
using namespace std;

/*
Calling a destructor releases the resources owned by the object, but it does not release the memory allocated to the object itself. stackoverflow

so the correct way to delete is to call the delete keyword which will call the destructor,
as well as deallocating the memory space occupied by the object
delete should be called on a pointer
*/

/*
insert will run the hash function first

then dynamically allocate a new object of KVPair, and let the pointer at the correct position point to that

delete will delete the object and set the pointer to null
*/

doubleHashingHashTable::doubleHashingHashTable(int table_size_p) : TABLE_SIZE(table_size_p)
{
    p_kvPairArr = new KVPair *[TABLE_SIZE] {};
    empty_space = TABLE_SIZE;
    cout << "success" << endl;
}

doubleHashingHashTable::~doubleHashingHashTable()
{
    for (int i{}; i < TABLE_SIZE; i++)
    {
        delete p_kvPairArr[i]; // free the memory occupied by each individual KVPair
    }
    delete[] p_kvPairArr; // delete the array of pointers to KVPairs
}

void doubleHashingHashTable::insert(unsigned int studentNumber_p, string lastName_p)
{
    // if full, return
    if (empty_space == 0)
    {
        cout << "failure\n";
        return;
    }
    //

    int i{0};
    int h3 = this->h3(studentNumber_p, i);

    while (p_kvPairArr[h3] != nullptr)
    {
        if (p_kvPairArr[h3]->compare(studentNumber_p))
        {
            cout << "failure\n";
            return;
        }
        i++;
        h3 = this->h3(studentNumber_p, i);
        if (i > -(TABLE_SIZE - 1))
        {
            cout << "failure\n";
            return;
        }
    }

    KVPair *newKVPair = new KVPair(studentNumber_p, lastName_p);

    p_kvPairArr[h3] = newKVPair;
    empty_space--;
    cout << "success\n";

    return;
}

int doubleHashingHashTable::search(unsigned int studentNumber_p)
{
    if (empty_space == TABLE_SIZE)
    {
        cout << "not found\n";
        return -1;
    }

    int i{0};
    int h3 = this->h3(studentNumber_p, i);
    while (i < TABLE_SIZE)
    {
        if (p_kvPairArr[h3] == nullptr)
        {
        }
        else if (p_kvPairArr[h3]->compare(studentNumber_p))
        {
            cout << "found " << p_kvPairArr[h3]->get_LN() << " in " << h3 << "\n";
            return h3;
        }
        i++;
        h3 = this->h3(studentNumber_p, i);
    }
    cout << "not found\n";
    return -1;
}

int doubleHashingHashTable::search_no_Output(unsigned int studentNumber_p)
{
    if (empty_space == TABLE_SIZE)
    {
        return -1;
    }

    int i{0};
    int h3 = this->h3(studentNumber_p, i);
    while (i < TABLE_SIZE)
    {
        if (p_kvPairArr[h3] == nullptr)
        {
        }
        else if (p_kvPairArr[h3]->compare(studentNumber_p))
        {
            return h3;
        }
        i++;
        h3 = this->h3(studentNumber_p, i);
    }
    return -1;
}

void doubleHashingHashTable::deleteKV(unsigned int studentNumber_p) // deallocate the memory, set it to null
{
    int i = this->search_no_Output(studentNumber_p);
    if (i == -1)
    {
        cout << "failure\n";
        return;
    }
    else
    {
        delete p_kvPairArr[i];
        p_kvPairArr[i] = nullptr; // set to nullptr to indicate empty
        empty_space++;
        cout << "success\n";
        return;
    }
}

int doubleHashingHashTable::h1(unsigned int k)
{
    int ret = (k % TABLE_SIZE);

    return ret;
}

int doubleHashingHashTable::h2(unsigned int k) //ℎ2(𝑘) = ⌊ 𝑘/𝑚⌋ 𝑚𝑜𝑑 𝑚 , h2(k) must be a odd number
{
    int temp = k / TABLE_SIZE;
    int ret = temp % TABLE_SIZE;

    if (ret % 2 == 0)
    {
        ret++;
    }

    return ret;
}

int doubleHashingHashTable::h3(unsigned int k, int i)
{

    int ret = ((h1(k) + i * h2(k)) % TABLE_SIZE);

    return ret;
}

/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

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
