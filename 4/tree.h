#ifndef TREE_H
#define TREE_H

#include <QString>

#include <vector>


template <typename T>
class Tree
{
protected:
    class Node {

        friend Tree;
    public:
        Node() = default;
        Node(const T&);
        virtual ~Node() = default;
    };

public:
    Tree() = default;
    virtual ~Tree() = default;

    virtual const Node* root() const = 0;

    virtual T get(const std::vector<int>& path) const = 0;

    virtual bool nodeExists(const std::vector<int>& path) const = 0;

    virtual int childrenCount(const std::vector<int>& path) const = 0;

    virtual std::vector<int> childrenCount() const = 0;
    virtual std::vector<T> preorderTravData() const = 0;

    virtual QString type() const = 0;
};

#endif // TREE_H
