//
// Created by rkuan on 5/28/2022.
//
#include <string>
#include <list>

#ifndef MESPELLRITE_HASHTABLE_H
#define MESPELLRITE_HASHTABLE_H
using namespace std;

class Hashtable {
private:
    const static int hashSize = 2017;
    list<string> table[hashSize];
public:
    bool isEmpty() const;

    static int hashFunction(string s);

    void insertString(const string& s);

    void removeString(string s);

    bool searchTable(string s);

    void printTable();

    ~Hashtable();
};


#endif //MESPELLRITE_HASHTABLE_H
