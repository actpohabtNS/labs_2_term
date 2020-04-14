#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <QtDebug>
template <typename T>
class Node
{
    Node* left;
    Node* right;
    T data;

public:
    Node(T data)
    {
        left = right = nullptr;
        this->data = data;
    }

    ~Node()
    {
        delete left, right, data;
    }

    void insert(T value)
    {
        if (value <= data)
        {
            if (left == nullptr) left = new Node(value);
            else left->insert(value);
        }
        else
        {
            if (right == nullptr) right = new Node(value);
            else right->insert(value);
        }
    }

    void BTtoArr(T arr[], int &elem)
    {
        if (left != nullptr)
            left->BTtoArr(arr, elem);

        arr[elem++] = data;

        if (right != nullptr)
            right->BTtoArr(arr, elem);
    }

};

#endif // BINARYTREE_H
