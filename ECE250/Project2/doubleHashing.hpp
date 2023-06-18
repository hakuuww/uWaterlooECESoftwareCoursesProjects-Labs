#include <iostream>
#include <string>
#ifndef DOUBLEHASHING_H
#define DOUBLEHASHING_H

using namespace std;

class KVPair
{

private:
    const unsigned int STUDENT_NUMBER;
    const string LAST_NAME;

public:
    KVPair(unsigned int studentNumber_p, string lastName_p);
    ~KVPair();
    bool compare(unsigned int studentNumber_p) const;
    unsigned int get_SN() const;
    string get_LN() const;
};

/////////////////////////////////////////////////////////////////


class doubleHashingHashTable{
    private:
    const int TABLE_SIZE;
    int empty_space;
    KVPair **p_kvPairArr;
    int h1(unsigned int k);
    int h2(unsigned int k);
    int h3(unsigned int k,int i);
    int search_no_Output(unsigned int studentNumber_p);

    public:
    doubleHashingHashTable(int table_size_p);
    ~doubleHashingHashTable();
    void insert(unsigned int studentNumber_p, string lastName_p);
    int search(unsigned int studentNumber_p);

    void deleteKV(unsigned int studentNumber_p);
};





#endif