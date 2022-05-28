//
// Created by rkuan on 5/28/2022.
//
#include <string>

#ifndef MESPELLRITE_TRIE_H
#define MESPELLRITE_TRIE_H
using namespace std;

class Trie {
    struct node {
        unsigned int counter;
        struct node *kids[127];

        node();
    } *root;

    unsigned int count;
public:
    Trie();

    ~Trie();

    void insert(const string &);

    unsigned int search(const string &);

    void remove(const string &);

    unsigned int size() const;
};


#endif //MESPELLRITE_TRIE_H
