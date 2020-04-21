#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
#include <stack>
#include <queue>
#include <utility>
#include <functs.h>
#include <QDebug>

template <typename T>
class BinaryTree {

private:
    class Node {

    friend BinaryTree;

    private:
        T _data;
        Node* _right;
        Node* _left;

    public:
        Node(T _data);
        virtual ~Node();

        T data() const;
        Node* right() const;
        Node* left() const;
    };

    Node* _root;

public:
    BinaryTree(T _data);
    virtual ~BinaryTree();

    Node* root() const;
};



// --------------------------- Node ------------------------------

template <typename T>
BinaryTree<T>::Node::Node(T _data) : _data(_data) {}

template <typename T>
BinaryTree<T>::Node::~Node()
{
    delete right;
    delete left;
}

template <typename T>
T BinaryTree<T>::Node::data() const
{
    return _data;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Node::right() const
{
    return _right;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Node::left() const
{
    return _left;
}



// ------------------------ Binary Tree ---------------------------

template <typename T>
BinaryTree<T>::BinaryTree(T _data) : _root(new Node(_data)) {}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    delete _root;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::root() const
{
    return _root;
}
#endif // BINARYTREE_H
