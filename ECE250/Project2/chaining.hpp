#include <iostream>
#include <string>
#include <vector>
#ifndef CHAINING_H
#define CHAINING_H

using namespace std;

class KVPair
{

private:
    unsigned int STUDENT_NUMBER;
    string LAST_NAME;

public:
    KVPair(unsigned int studentNumber_p, string lastName_p);
    ~KVPair();
    bool compare(unsigned int studentNumber_p) const;
    unsigned int get_SN() const;
    string get_LN() const;
};

/////////////////////////////////////////////////////////////////


class chainingHashTable{
    private:
    const int TABLE_SIZE;
    vector<KVPair> *p_kvPairArr;
    int search_no_Output(unsigned int studentNumber_p,int start, int end);
    int search_for_Insert(unsigned int studentNumber_p,int start, int end);

    public:
    chainingHashTable(int table_size_p);
    ~chainingHashTable();
    void insert(unsigned int studentNumber_p, string lastName_p);
    int search(unsigned int studentNumber_p,int start, int end);
    void deleteKV(unsigned int studentNumber_p);
    void printChain(int chain_Num);
    int chainSize(unsigned int studentNumber_p);
    int h1(unsigned int k);
};





#endif