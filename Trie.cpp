//
// Created by rkuan on 5/28/2022.
//

#include "Trie.h"
void Trie::remove(const string& str) {
    node* nodeptr = root;
    for (int i = 0; i < str.length(); i++) {
        if (nodeptr->kids[i] == nullptr)
            return;
        nodeptr = nodeptr->kids[i];
    }
    if (nodeptr->counter > 0)
        nodeptr->counter--;
    else
        return;
}

Trie::Trie() {
    count = 0;
    root = nullptr;
}

Trie::~Trie() {};

Trie::node::node() {
    counter = 0;
    for (auto & kid : kids)
        kid = nullptr;
}

void Trie::insert(const string& str) {
    if (root == nullptr)
        root = new node;
    node* nodeptr = root;
    for (char c : str) {
        if (nodeptr->kids[c] == nullptr)
            nodeptr->kids[c] = new node;
        nodeptr = nodeptr->kids[c];
    }
    nodeptr->counter++;
    count++;
}

unsigned int Trie::search(const string& str) {
    if (root == nullptr)
        return 0;
    node* nodeptr = root;
    for (char c : str) {
        if (nodeptr->kids[c] == nullptr)
            return 0;
        nodeptr = nodeptr->kids[c];
    }
    return nodeptr->counter;
}

unsigned int Trie::size() const {
    return count;
}