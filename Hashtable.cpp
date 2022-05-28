//
// Created by rkuan on 5/28/2022.
//

#include <iostream>
#include <cmath>
#include "Hashtable.h"
bool Hashtable::isEmpty() const {
    unsigned long long sum = 0;
    for (const auto & i : table)
    {
        sum += i.size();
    }

    if (sum == 0)
        return true;

    return false;
}

int Hashtable::hashFunction(string s) {
    int hash = 0;
    for (int i = 0; i < s.length(); i++)
    {
        hash = hash + (int)pow(s[i], s.length() - i);
        hash = hash % hashSize;
    }

    return hash;
}

void Hashtable::insertString(const string& s) {
    int hash = hashFunction(s);
    auto& cell = table[hash];
    auto it = begin(cell);
    for (; it != end(cell); it++)
    {
        if (*it == s)
            return;
    }

    cell.emplace_back(s);
}

void Hashtable::removeString(string s) {
    int hash = hashFunction(s);
    auto& cell = table[hash];
    auto it = begin(cell);
    for (; it != end(cell); it++)
    {
        if (*it == s)
        {
            it = cell.erase(it);
            return;
        }
    }

    cout << "String was not removed." << endl;
}

void Hashtable::printTable() {
    for (int i = 0; i < hashSize; i++)
    {
        if (table[i].empty()) continue;

        auto it = table[i].begin();
        for (; it != table[i].end(); it++)
        {
            cout << "Key: " << i << " String: " << *it << endl;
        }
    }
}

bool Hashtable::searchTable(string s) {
    int hash = hashFunction(s);
    auto& cell = table[hash];
    auto it = begin(cell);
    for (; it != end(cell); it++)
    {
        if (*it == s)
        {
            return true;
        }
    }

    return false;
}

Hashtable::~Hashtable() {
    if (isEmpty())
        return;
    for (auto & cell : table)
    {
        //cout << i << endl;
        auto it = begin(cell);
        while(it != end(cell))
        {
            it = cell.erase(it);
        }
    }
    table->clear();
}