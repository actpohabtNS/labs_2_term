#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
#include <stack>
#include <queue>
#include <utility>
#include <iostream>
#include <QDebug>
#include <cassert>

#include "tree.h"
#include <functs.h>

template <typename T>
class BinaryTree : public Tree<T> {

private:
    class Node : Tree<T>::Node {

    friend BinaryTree;

    private:
        T _data;
        Node* _right;
        Node* _left;
        bool _lthreaded;
        bool _rthreaded;

    public:
        explicit Node(const T& data);
        explicit Node(const T& data, Node* right, Node* left);
        explicit Node(const T& data, Node* right, Node* left, const bool lthreaded, const bool rthreaded);
        virtual ~Node();

        T data() const;
        Node* right() const;
        Node* left() const;

        int _childrenCount() const;
        bool _hasLeftChild() const;
        bool _hasRightChild() const;

        friend std::ostream& operator<<(std::ostream& ostream, const Node& node)
        {
             return ostream << node._data;
        }

        friend QTextStream& operator<<(QTextStream &ostream, const Node& node)
        {
             return ostream << node._data;
        }
    };


private:
    Node* _root;
    bool _threaded;

    void _inorderTrav(Node* node, std::vector<Node*>* nodes) const;
    void _toThreaded(Node* node);
    void _removeThreads(Node* node);

    Node* _getNode(const std::vector<int>& path) const;

public:
    BinaryTree();
    explicit BinaryTree(const T& _data);
    virtual ~BinaryTree();

    virtual Node* root() const;
    bool isThreaded() const;

    void add(const T& data);

    void toThreaded();
    void removeThreads();

    virtual std::vector<int> childrenCount() const;
    virtual std::vector<T> preorderTravData() const;

    bool hasLeftChild(const std::vector<int>& path) const;
    bool hasRightChild(const std::vector<int>& path) const;

    T get(const std::vector<int>& path) const;
    std::vector<int> getPath(const T& data) const;
    QString getQStrPaths() const;
    void print() const;
};



// --------------------------- Node ------------------------------

template <typename T>
BinaryTree<T>::Node::Node(const T& data)
    : _data(data), _right(nullptr), _left(nullptr), _lthreaded(false), _rthreaded(false) {}

template <typename T>
BinaryTree<T>::Node::Node(const T& data, Node* right, Node* left)
    : _data(data), _right(right), _left(left), _lthreaded(false), _rthreaded(false) {}

template <typename T>
BinaryTree<T>::Node::Node(const T& data, Node* right, Node* left, const bool lthreaded, const bool rthreaded)
    : _data(data), _right(right), _left(left), _lthreaded(lthreaded), _rthreaded(rthreaded) {}

template <typename T>
BinaryTree<T>::Node::~Node()
{
    if (this->_left && !this->_lthreaded)
        delete this->_left;

    if (this->_right && !this->_rthreaded)
        delete this->_right;
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


template<typename T>
int BinaryTree<T>::Node::_childrenCount() const
{
    int count = 0;

    if (this->_left)
        count++;
    if (this->_right)
        count++;

    return count;
}

template<typename T>
bool BinaryTree<T>::Node::_hasLeftChild() const
{
    return this->_left;
}

template<typename T>
bool BinaryTree<T>::Node::_hasRightChild() const
{
    return this->_right;
}
// ------------------------ Binary Tree ---------------------------

template<typename T>
void BinaryTree<T>::_inorderTrav(BinaryTree::Node* node, std::vector<BinaryTree::Node*>* nodes) const
{
    if (this->_threaded)
        return;

    if (!node)
        return;

    this->_inorderTrav(node->_left, nodes);

    nodes->emplace_back(node);

    this->_inorderTrav(node->_right, nodes);
}

template<typename T>
void BinaryTree<T>::_toThreaded(BinaryTree::Node* node)
{
    if (this->_threaded)
        return;

    std::vector<Node*> inorderTrav;

    this->_inorderTrav(node, &inorderTrav);

    for (uint i = 0; i < inorderTrav.size(); i++)
    {
        if (i != 0 && !inorderTrav[i]->_left)
        {
            inorderTrav[i]->_lthreaded = true;
            inorderTrav[i]->_left = inorderTrav[i - 1];
        }

        if (i != inorderTrav.size() - 1 && !inorderTrav[i]->_right)
        {
            inorderTrav[i]->_rthreaded = true;
            inorderTrav[i]->_right = inorderTrav[i + 1];
        }
    }
}

template<typename T>
void BinaryTree<T>::_removeThreads(BinaryTree::Node* node)
{
    if (!this->_threaded)
        return;

    if (!node)
        return;

    if (!node->_lthreaded)
        this->_removeThreads(node->_left);

    if (node->_lthreaded)
    {
        node->_lthreaded = false;
        node->_left = nullptr;
    }

    if (node->_rthreaded)
    {
        node->_rthreaded = false;
        node->_right = nullptr;
    }

    if (!node->_rthreaded)
        this->_removeThreads(node->_right);
}

template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::_getNode(const std::vector<int> &path) const
{
    Node* node = this->_root;

    for (uint elem = 0; elem < path.size(); elem++)
    {
        if (path[elem] == 0)
        {
            assert(node->_left != nullptr);
            node = node->_left;
        }
        else
        {
            assert(node->_right != nullptr);
            node = node->_right;
        }
    }

    return node;
}

template <typename T>
BinaryTree<T>::BinaryTree() : _root(nullptr), _threaded(false) {}

template <typename T>
BinaryTree<T>::BinaryTree(const T& _data) : _root(new Node(_data)), _threaded(false) {}

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

template<typename T>
bool BinaryTree<T>::isThreaded() const
{
    return _threaded;
}

template<typename T>
void BinaryTree<T>::add(const T &data)
{
    if (this->_threaded)
        return;

    if (!this->_root)
    {
        _root = new Node(data);
        return;
    }

    Node* node = this->_root;
    Node* parent = this->_root;

    while (node != nullptr)
    {
        parent = node;

        if (data < node->_data)
            node = node->left();
        else
            node = node->right();
    }

    Node* newNode = new Node(data);

    if (parent == nullptr)
        parent = newNode;
    else if (data < parent->_data)
        parent->_left = newNode;
    else
        parent->_right = newNode;
}

template<typename T>
void BinaryTree<T>::toThreaded()
{
    this->_toThreaded(this->_root);
    this->_threaded = true;
}

template<typename T>
void BinaryTree<T>::removeThreads()
{
    this->_removeThreads(this->_root);
    this->_threaded = false;
}

template<typename T>
std::vector<int> BinaryTree<T>::childrenCount() const
{
    if (!this->_root)
        return {-1};

    std::stack<Node*> nodes;
    nodes.push(this->_root);

    std::vector<int> childrenCount;

    while (!nodes.empty())
    {
        Node* current = nodes.top();
        nodes.pop();

        childrenCount.push_back(current->_childrenCount());

        if (current->_right)
            nodes.push(current->_right);

        if (current->_left)
            nodes.push(current->_left);
    }

    return childrenCount;
}

template<typename T>
std::vector<T> BinaryTree<T>::preorderTravData() const
{
    if (!this->_root)
        return {};

    std::stack<Node*> nodes;
    nodes.push(this->_root);

    std::vector<T> preorderTravData;

    while (!nodes.empty())
    {
        Node* current = nodes.top();
        nodes.pop();

        preorderTravData.push_back(current->_data);

        if (current->_right)
            nodes.push(current->_right);

        if (current->_left)
            nodes.push(current->_left);
    }

    return preorderTravData;
}

template<typename T>
bool BinaryTree<T>::hasLeftChild(const std::vector<int> &path) const
{
    return this->_getNode(path)->_left;
}

template<typename T>
bool BinaryTree<T>::hasRightChild(const std::vector<int> &path) const
{
    return this->_getNode(path)->_right;
}

template<typename T>
T BinaryTree<T>::get(const std::vector<int> &path) const
{
    if (path[0] == -1)
        return {};

    return this->_getNode(path)->_data;
}

template<typename T>
std::vector<int> BinaryTree<T>::getPath(const T &data) const
{
    if (!this->_root)
        return {-1};

    std::vector<int> path;

    Node* node = this->_root;

    while (true)
    {
        if (node == nullptr)
            return {-1};

        if (data == node->_data)
            break;

        if (data < node->_data)
        {
            node = node->_left;
            path.push_back(0);
        }
        else
        {
            node = node->_right;
            path.push_back(1);
        }

    }

    return path;
}

template<typename T>
QString BinaryTree<T>::getQStrPaths() const
{
    if (!this->_root)
        return "";

    std::stack<Node*> nodes;
    nodes.push(this->_root);

    std::stack<std::vector<int>> intPaths;
    intPaths.push({});

    QString subtreeQStr;

    while (!nodes.empty())
    {
        Node* current = nodes.top();
        nodes.pop();

        std::vector<int> parentPath = intPaths.top();
        intPaths.pop();

        subtreeQStr += pathToQStr(parentPath);

        QTextStream *stream = new QTextStream(&subtreeQStr);
        *stream << "     { " << *current << " }\n";

        if (current->_right)
        {
            std::vector<int> extendedPath(parentPath);
            extendedPath.push_back(1);

            nodes.push(current->_right);
            intPaths.push(extendedPath);
        }

        if (current->_left)
        {
            std::vector<int> extendedPath(parentPath);
            extendedPath.push_back(0);

            nodes.push(current->_left);
            intPaths.push(extendedPath);
        }
    }

    return subtreeQStr;
}

template<typename T>
void BinaryTree<T>::print() const
{
    if (!this->_root)
        return;

    std::stack<Node*> nodes;

    nodes.push(this->_root);

    while (!nodes.empty())
    {
        Node* current = nodes.top();
        nodes.pop();

        qDebug() << current->_data;

        if (current->_right)
            nodes.push(current->_right);

        if (current->_left)
            nodes.push(current->_left);
    }
}
#endif // BINARYTREE_H
