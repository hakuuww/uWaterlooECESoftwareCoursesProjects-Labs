#include <iostream>
#include "Trie.h"
using namespace std;
/*
    Trie

    all supported functionalities

    root node, array of pointers to all subtrees

*/

/*
    TrieNode

    array of pointers to all subtrees



*/

TrieNode::TrieNode(char value_p)
{
    this->value = value_p;
    this->isEOW = false;
    active_subtrees = 0;
    // set all pointers to subtree to nullptr
    // for (int i = 0; i < DIMENSION_SIZE; i++)
    // {
    //     this->subtrees[i] = nullptr;
    // }
    // cout << "success" << endl;
}
TrieNode::~TrieNode()
{
    this->clear_tree(this, this);
    for (int i = 0; i < DIMENSION_SIZE; i++)
    {
        this->subtrees[i] = nullptr;
    }
}

void TrieNode::print_letter()
{
    cout << this->value;
}

void TrieNode::set_isEOW(bool tf)
{
    isEOW = tf;
}
bool TrieNode::get_isEOW()
{
    return isEOW;
}

void TrieNode::print_tree(char word[], int depth)
{
    // stopping condition, reached EOW, then print the word, add null character to the depth, so printing stops at the depth
    if (this->get_isEOW())
    {
        word[depth] = 0;
        cout << word << ' ';
    }

    for (int i = 0; i < DIMENSION_SIZE; i++)
    {
        if (this->subtrees[i] != nullptr)
        {
            word[depth] = i + 'a';
            this->subtrees[i]->print_tree(word, depth + 1);
        }
    }
}

Trie::Trie()
{
    root = new TrieNode('\0');
    size = 0;
}

Trie::~Trie()
{
    this->root->clear_tree(this->root,this->root);
    for (int i = 0; i < DIMENSION_SIZE; i++)
    {
        this->root->subtrees[i] = nullptr;
    }

    delete root;
}

int Trie::get_size()
{
    return size;
}

// 97  a  97-97 = 0
// 122 z 122-97 = 25
int Trie::insert(string word_p)
{
    /*
    edge cases:
     - we have a one character word, we neeed to check its duplicacy
     - we need to check whether the node of the last letter of the word is EOW
     - invalid argument exception

    */
    //
    TrieNode *p_traverse = this->root;
    ////////////////////////////

    for (int i = 0; i < word_p.length(); i++)
    {
        int index = word_p[i] - 'a';
        if (p_traverse->subtrees[index] == nullptr)
        {
            p_traverse->subtrees[index] = new TrieNode(word_p[i]);
            p_traverse->active_subtrees++;
        }
        p_traverse = p_traverse->subtrees[index];
    }

    if (p_traverse->get_isEOW())
    {
        return 0;
    }

    ////////////////////////////////////////
    p_traverse->set_isEOW(true);
    size++;
    return 1;
    ////////////////////////////////////////////
}

void Trie::print_trie()
{
    char word[43]{};
    int depth = 0;
    if(this->size == 0){
        return;
    }
    root->print_tree(word, depth);
    cout << '\n';
}

bool Trie::empty()
{
    for (int i = 0; i < DIMENSION_SIZE; i++)
    {
        if (root->subtrees[i] != nullptr)
        {
            return false;
        }
    }
    return true;
}

void Trie::clear_trie()
{
    root->clear_tree(root, root);
    cout << "success\n";
    size = 0;
}

void TrieNode::clear_tree(TrieNode *root, TrieNode *self)
{
    // depth first
    // exit condition, node does not point to more trees

    for (int i = 0; i < DIMENSION_SIZE; i++)
    {
        if (this->subtrees[i] != nullptr)
        {
            this->subtrees[i]->clear_tree(root, subtrees[i]);
            this->subtrees[i] = nullptr;
            this->active_subtrees--;
        }
    }

    if (self != root)
    {
        delete this;
        self = nullptr;
    }

    return;
}

int Trie::search(string word_p)
{

    TrieNode *p_traverse = root;
    for (int j = 0; j < word_p.length(); j++)
    {
        int index = word_p[j] - 'a';
        if (p_traverse->subtrees[index] == nullptr)
        {
            return 0;
        }
        else
        {
            p_traverse = p_traverse->subtrees[index];
        }
    }

    if (p_traverse->get_isEOW())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool Trie::erase_trie(string word_p)
{
    if (!this->search(word_p))
    {
        return false;
    }
    size--;
    return root->erase_tree(word_p, 0);
}

bool TrieNode::erase_tree(string word_p, int depth)
{
    // exit condition: if p_traverse is at the bottom of the word
    int index = word_p[depth] - 'a';

    // if we are at the bottom level of the word
    if (word_p.length() == depth + 1)
    {
        if (this->subtrees[index] == nullptr)
        {
            return false;
        }

        this->subtrees[index]->set_isEOW(false);

        // if it doesn't have any subtrees, then we delete this node
        if (this->subtrees[index]->active_subtrees == 0)
        {
            delete this->subtrees[index];
            this->subtrees[index] = nullptr;
            this->active_subtrees--;
        }
        return true;
    }

    this->subtrees[index]->erase_tree(word_p, depth + 1);

    if ((this->subtrees[index]->active_subtrees == 0) && (this->subtrees[index]->get_isEOW() == false)) // no more other branches, and is not end of word
    {
        delete this->subtrees[index];
        this->subtrees[index] = nullptr;
        this->active_subtrees--;
    }
    return true;
}

void Trie::spell_checkTrie(string word_p)
{
    /*
    cases:
    you, youii, young, your

    input yo
    input y
    input yoi
    input null string
    */

    int word_length = word_p.length();

    if (word_length == 0)
    {
        cout << endl;
        return;
    }

    TrieNode *p_traverse = root;

    int index = word_p[0] - 'a';
    int depth = 0;
    char word_array[43]{};

    // if no words start with the first letter
    if (p_traverse->subtrees[index] == nullptr)
    {
        cout << endl;
        return;
    }
    else
    {
        p_traverse = p_traverse->subtrees[index];
        word_array[depth] = index + 'a';
        depth++;
    }

    for (int j = 1; j < word_p.length(); j++) // depth == 1
    {
        index = word_p[j] - 'a';
        if (p_traverse->subtrees[index] == nullptr)
        {
            break;
        }
        else
        {
            word_array[depth] = index + 'a';
            if ((word_array == word_p) && (p_traverse->subtrees[index]->get_isEOW()))
            {
                cout << "correct\n";
                return;
            }
            p_traverse = p_traverse->subtrees[index];
            depth++;
        }
    }

    p_traverse->print_tree(word_array, depth);
    cout << endl;
}


illegal_exception::illegal_exception(){
    
}

void illegal_exception::check_illegal_argument(string word_p)
{
    for (int i = 0; i < word_p.length(); i++)
    {
        char ch = word_p[i];
        if (ch < 'a' || ch > 'z')
        {
            throw illegal_exception();
            break;
        }
    }
}
