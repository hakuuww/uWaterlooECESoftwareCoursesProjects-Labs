#include <iostream>
using namespace std;
#define DIMENSION_SIZE 26

class TrieNode
{
private:
    char value;
    bool isEOW; // indicate if is leaf

public:
    int active_subtrees;
    TrieNode *subtrees[DIMENSION_SIZE]{}; // 26 ary array storing pointers to Trie
    TrieNode(char value_p);
    ~TrieNode();
    void print_letter();
    void set_isEOW(bool tf);
    bool get_isEOW();
    void print_tree(char word[], int depth);
    void clear_tree(TrieNode *root, TrieNode *self);
    bool erase_tree(string word_p, int depth);
    void spell_checkNode(string word_p);
};

class Trie
{
private:
    int size;
    // TrieNode *subtrees[DIMENSION_SIZE]; // 26 ary array storing pointers to sub Tries
    TrieNode *root;
public:

    Trie();
    ~Trie();
    int insert(string word_p);
    int search(string word_p);
    bool erase_trie(string word_p);
    void print_trie();
    bool empty();
    void clear_trie();
    int get_size();
    void spell_checkTrie(string word_p);
};

class illegal_exception
{
public:
    illegal_exception();
    void check_illegal_argument(string word_p);
};
