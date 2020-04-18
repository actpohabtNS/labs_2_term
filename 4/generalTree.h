#ifndef GENERALTREE_H
#define GENERALTREE_H
#include <vector>

template <typename T>
class Node {
    T data;
    std::vector<Node<T>*> children;

public:
    Node()
    {
        this->children = nullptr;
        this->data = NULL;
    }

    Node(T data)
    {
        this->children = nullptr;
        this->data = data;
    }

    Node* get(std::vector<int> path)
    {
        Node* node = this;

        for (int idx : path)
        {
            node = node->children[idx];
        }

        return node;
    }

    void set(std::vector<int> path, T newData)
    {
        Node* node = this;

        for (int idx : path)
        {
            node = node->children[idx];
        }

        node->data = newData;
    }

    void insert(std::vector<int> path, T data)
    {
        Node* parent = this;

        for (int idx : path)
        {
            parent = parent->children[idx];
        }

        parent->children.push_back(new Node(data));
    }

    std::vector<int> getPath(T searchData)
    {

    }
};

#endif // GENERALTREE_H
