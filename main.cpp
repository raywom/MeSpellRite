#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <chrono>
#include "BBST.h"
#include "Trie.h"
#include "Hashtable.h"
using namespace std;
int main() {
    string word;
    ifstream words(R"(C:\Users\rkuan\CLionProjects\MeSpellRite\words.txt)");
    using chrono::nanoseconds;
    nanoseconds totalNaive(0), totalTree(0), totalTrie(0), totalHashtable(0), dictionaryNaive(0), dictionaryTree(
            0), dictionaryTrie(0), dictionaryHashtable(0);
    ofstream results("ex1_results_search.txt"), dictionariesResults("ex1_results_inserts.csv");
    results << "size		Naive		BBST		Trie		HashTable" << endl;
    dictionariesResults << "size		Naive		BBST		Trie		Hashtable" << endl;

    int dictionarySize = 0;

    while (getline(words, word)) {
        ++dictionarySize;
    }
    words.clear();
    words.seekg(0);

    cout << dictionarySize << endl;

    auto *tree = new BBSTNode("a");
    Trie trie1;
    Hashtable table;
    list<string> naive;

    //Dictionary building

    for (int j = 0; j < dictionarySize; j++) {
        getline(words, word);

        //Naive
        auto start = chrono::steady_clock::now();
        naive.push_back(word);
        auto end = chrono::steady_clock::now();
        dictionaryNaive += end - start;

        //BBST
        start = chrono::steady_clock::now();
        tree = insert(tree, word);
        //tree.insert(word);
        end = chrono::steady_clock::now();
        dictionaryTree += end - start;


        //Trie
        start = chrono::steady_clock::now();
        trie1.insert(word);
        end = chrono::steady_clock::now();
        dictionaryTrie += end - start;

        //Hashtable
        start = chrono::steady_clock::now();
        table.insertString(word);
        end = chrono::steady_clock::now();
        dictionaryHashtable += end - start;

        dictionariesResults << j << "		" << dictionaryNaive.count() << "		" << dictionaryTree.count()
                            << "	" << dictionaryTrie.count() << "		" << dictionaryHashtable.count()
                            << endl;
    }



    //Search
    ifstream text(R"(C:\Users\rkuan\CLionProjects\MeSpellRite\text.txt)");
    string spell, wordsFromSpell;

    int sizeSpell = 0;
    while (getline(text, spell)) {
        ++sizeSpell;
    }
    text.clear();
    text.seekg(0);

    int sizeSpellChecked = 0;

    int countOfWords=0;
    for (int j = 0; j < sizeSpell; j++) {
        getline(text, spell);
        sizeSpellChecked += spell.length();
        for (char k: spell) {
            if ((k >= 65 && k <= 90) || (k >= 97 && k <= 122)) {
                wordsFromSpell += k;
                continue;
            }
            countOfWords++;

            words.clear();
            words.seekg(0);

            //Naive algorithm
            auto start = chrono::steady_clock::now();
            for (auto &it: naive) {
                if (it == wordsFromSpell)
                    break;
            }
            auto end = chrono::steady_clock::now();
            totalNaive += end - start;

            //BBST
            start = chrono::steady_clock::now();
            search(tree, wordsFromSpell);
            //tree.find(wordsFromSpell);
            end = chrono::steady_clock::now();
            totalTree += end - start;

            //Trie
            start = chrono::steady_clock::now();
            trie1.search(wordsFromSpell);
            end = chrono::steady_clock::now();
            totalTrie += end - start;


            //Hashtable
            start = chrono::steady_clock::now();
            table.searchTable(wordsFromSpell);
            end = chrono::steady_clock::now();
            totalHashtable += end - start;

            wordsFromSpell = "";
            results << countOfWords << "\t" << totalNaive.count() << "		" << totalTree.count() << "		"
                    << totalTrie.count() << "		" << totalHashtable.count() << endl;
        }
    }





    words.close();
    return 0;
}