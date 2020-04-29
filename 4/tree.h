#ifndef TREE_H
#define TREE_H

#include <vector>

template <typename T>
class Tree
{
protected:
    class Node {

        friend Tree;
    public:
        Node() = default;
        virtual ~Node() = default;
    };

public:
    Tree() = default;
    virtual ~Tree() = default;

    virtual const Node* root() const = 0;
    virtual std::vector<int> childrenCount() const = 0;
    virtual std::vector<T> preorderTravData() const = 0;
};

#endif // TREE_H
