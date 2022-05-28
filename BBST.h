//
// Created by rkuan on 5/28/2022.
//
#include <string>
#include <iostream>
#include <utility>

#ifndef MESPELLRITE_BBST_H
#define MESPELLRITE_BBST_H
using namespace std;


struct BBSTNode {
    string val;
    int height;
    BBSTNode* left;
    BBSTNode* right;
    explicit BBSTNode(string x) {
        val = std::move(x);
        left = right = nullptr;
        height = 0;
    }
};

int subtreeHeight(BBSTNode* ptr)
{
    if (ptr == nullptr)
        return 0;
    else
        return ptr->height;
}

int getBalance(BBSTNode* ptr)
{
    return subtreeHeight(ptr->right) - subtreeHeight(ptr->left);
}

void setBalance(BBSTNode* ptr)
{
    ptr->height = 1 + max(subtreeHeight(ptr->left), subtreeHeight(ptr->right));
}

BBSTNode* rightRotate(BBSTNode* ptr)
{
    BBSTNode* newPtr = ptr->left;
    ptr->left = newPtr->right;
    newPtr->right = ptr;
    setBalance(ptr);
    setBalance(newPtr);

    return newPtr;
}

BBSTNode* leftRotate(BBSTNode* ptr)
{
    BBSTNode* newPtr = ptr->right;
    ptr->right = newPtr->left;
    newPtr->left = ptr;
    setBalance(ptr);
    setBalance(newPtr);

    return newPtr;
}

BBSTNode* leftLeft(BBSTNode* ptr)
{
    ptr = rightRotate(ptr);
    return ptr;
}

BBSTNode* rightRight(BBSTNode* ptr)
{
    ptr = leftRotate(ptr);
    return ptr;
}

BBSTNode* leftRight(BBSTNode* ptr)
{
    ptr->left = leftRotate(ptr->left);
    ptr = leftLeft(ptr);
    return ptr;
}

BBSTNode* rightLeft(BBSTNode* ptr)
{
    ptr->right = leftRotate(ptr->right);
    return rightRight(ptr);
}


BBSTNode* insert(BBSTNode* parent, string x) {
    if (parent == nullptr)
        return new BBSTNode(x);
    if (x < parent->val)
        parent->left = insert(parent->left, x);
    else if (x > parent->val)
        parent->right = insert(parent->right, x);

    if (getBalance(parent) == 2)
        return (getBalance(parent->right) >= 0 ? rightRight(parent) : rightLeft(parent));
    else
    if (getBalance(parent) == -2)
        return (getBalance(parent->left) <= 0 ? leftLeft(parent) : leftRight(parent));

    setBalance(parent);
    return parent;
}


void printValue(BBSTNode* node) {
    if (node == nullptr)
        cout << "nullptr";
    else
        cout << node->val;
    cout << "\n";
}

void printTree(BBSTNode* node, bool isRight, string beginChar) {
    if (node != nullptr)
        printTree(node->left, false, beginChar + (isRight ? "  |      " : "         "));
    cout << beginChar;
    if (isRight)
        cout << "  '-";
    else
        cout << "  ,-";
    cout << "-----> ";
    printValue(node);
    if (node != nullptr)
        printTree(node->right, true, beginChar + (isRight ? "         " : "  |      "));
}

void printTree(BBSTNode* node)
{
    if (node != nullptr)
    {
        printTree(node->left, false, "");
        printValue(node);
        printTree(node->right, true, "");
    }
    else
        throw logic_error("\nThe binary tree is empty!");
}

void delete_tree(BBSTNode* node)
{
    if (node == nullptr)
        return;
    //cout << "\nDeleting tree" << endl;
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}

bool search(BBSTNode* parent, string x)
{
    while (parent != nullptr)
    {
        if (x < parent->val)
            parent = parent->left;
        else if (x > parent->val)
            parent = parent->right;
        else if (x == parent->val)
            return true;
    }

    return false;
}

#endif //MESPELLRITE_BBST_H
