#ifndef GENERALTREE_H
#define GENERALTREE_H

#include <vector>
#include <stack>
#include <queue>
#include <utility>
#include <iostream>
#include <cassert>
#include <QDebug>

#include <functs.h>

template <typename T>
class Tree {

private:
    class Node {

        friend Tree;

    private:
        T _data;
        std::vector<Node*> _children;

    public:
        explicit Node(T _data);
        explicit Node(T _data, std::vector<Node*> _children);
        virtual ~Node();

        const T& data() const;
        const std::vector<Node*>& children() const;

        friend std::ostream& operator<<(std::ostream& ostream, const Node& node)
        {
            return ostream << node._data;
        }

        friend QTextStream& operator<<(QTextStream &ostream, const Node& node)
        {
            return ostream << node._data;
        }
    };

    Node* _root;

    std::vector<int> getMaxChildrenMap() const;

public:
    Tree();
    explicit Tree(T _data);
    explicit Tree(Node* node);
    virtual ~Tree();

    bool contains(const T& searchData) const;

    void insert(const std::vector<int>& path, const T& data);

    Tree* removeSubtree(const std::vector<int>& path);
    void removeSubtree(const T& removingData);

    std::vector<int> getPath(const T& searchData) const;
    Node* getNode(const std::vector<int>& path) const;

    const Node* root() const;
    const T& get(const std::vector<int>& path) const;
    void set(const std::vector<int>& path, const T& data);

    QString getQStrPaths() const;

    void print() const;
};



// --------------------------- Node ------------------------------

template <typename T>
Tree<T>::Node::Node(T _data) : _data(_data) {}

template<typename T>
Tree<T>::Node::Node(T _data, std::vector<Tree::Node *> _children)
    : _data(_data), _children(_children) {}

template <typename T>
Tree<T>::Node::~Node()
{
    for (auto& child : this->_children)
    {
        delete child;
    }
}

template <typename T>
const T& Tree<T>::Node::data() const
{
    return this->_data;
}

template <typename T>
const std::vector<typename Tree<T>::Node*>& Tree<T>::Node::children() const
{
    return this->_children;
}



// --------------------------- Tree ------------------------------


template<typename T>
Tree<T>::Tree() : _root(nullptr) {}

template <typename T>
Tree<T>::Tree(T _data) : _root(new Node(_data)) {}

template<typename T>
Tree<T>::Tree(Tree::Node *node) : _root(new Node(node->_data, node->_children)) {}

template <typename T>
Tree<T>::~Tree()
{
    delete _root;
}

template<typename T>
std::vector<int> Tree<T>::getMaxChildrenMap() const
{
    if (!_root)
        return {};

    std::queue<Node*> nodes;
    nodes.push(this->_root);

    std::vector<int> maxChildrenMap;

    int thisLevelNodes = 1;
    int nextLevelNodes = 0;
    int levelMaxDigits = getDigitsNum(this->_root->_children.size() - 1);

    while (!nodes.empty())
    {
        Node* current = nodes.front();
        nodes.pop();

        if (thisLevelNodes == 0)
        {
            thisLevelNodes = nextLevelNodes;
            nextLevelNodes = 0;
            maxChildrenMap.push_back(levelMaxDigits);
            levelMaxDigits = getDigitsNum(current->_children.size() - 1);
        }

        int levelDigits = getDigitsNum(current->_children.size() - 1);

        if (levelMaxDigits < levelDigits)
        {
            levelMaxDigits = levelDigits;
        }

        if (current->_children.size() != 0)
        {
            for (uint idx = 0; idx < current->_children.size(); idx++)
            {
                nodes.push(current->_children[idx]);
            }
        }

        nextLevelNodes += current->_children.size();
        thisLevelNodes--;
    }

    return maxChildrenMap;
}

template<typename T>
bool Tree<T>::contains(const T &searchData) const
{
    if (!_root)
        return false;

    std::stack<Node*> nodes;

    nodes.push(this->_root);

    while (!nodes.empty())
    {
        Node* current = nodes.top();
        nodes.pop();

        if (current->_data == searchData)
            return true;

        if (current->_children.size() != 0)
        {
            for(int idx = current->_children.size() - 1; idx >= 0; idx--)
            {
                nodes.push(current->_children[idx]);
            }
        }
    }

    return false;
}

template<typename T>
void Tree<T>::insert(const std::vector<int> &path, const T &data)
{
    if (!_root)
    {
        _root = new Node(data);
        return;
    }

    Node* parent = this->getNode(path);
    parent->_children.push_back(new Node(data));
}

template<typename T>
void Tree<T>::removeSubtree(const T &removingData)
{
    if (!_root)
        return;

    std::vector<int> removingPath;

    while (this->contains(removingData))
    {
        removingPath = this->getPath(removingData);
        this->removeSubtree(removingPath);
    }
}

template<typename T>
std::vector<int> Tree<T>::getPath(const T &searchData) const
{
    if (!_root)
        return {-1};

    std::stack<Node*> nodes;
    nodes.push(this->_root);

    std::stack<std::vector<int>> intPaths;
    intPaths.push({});

    while (!nodes.empty())
    {
        Node* current = nodes.top();
        nodes.pop();

        if (current->_data == searchData)
        {
            return intPaths.top();
        }

        std::vector<int> parentPath = intPaths.top();
        intPaths.pop();

        if (current->_children.size() != 0)
        {
            for (int idx = current->_children.size() - 1; idx >= 0; idx--)
            {
                std::vector<int> extendedPath(parentPath);
                extendedPath.push_back(idx);

                nodes.push(current->_children[idx]);
                intPaths.push(extendedPath);
            }
        }
    }

    return {-1};
}

template<typename T>
Tree<T>* Tree<T>::removeSubtree(const std::vector<int> &path)
{
    if (!_root)
        return new Tree();

    Node* node = this->getNode(path);

    Tree* newTree = new Tree(node);

    if (path.size() != 0)
    {
        std::vector<int> parentPath(path);
        parentPath.pop_back();

        Node* parentNode = this->getNode(parentPath);

        parentNode->_children.erase(parentNode->_children.begin() + path.back());
    }
    else
    {
        _root = nullptr;
    }

    return newTree;
}

template <typename T>
const typename Tree<T>::Node* Tree<T>::root() const
{
    return this->_root;
}

template<typename T>
const T& Tree<T>::get(const std::vector<int> &path) const
{
    if (!_root)
        return NULL;

    return getNode(path)->_data;
}

template<typename T>
typename Tree<T>::Node* Tree<T>::getNode(const std::vector<int> &path) const
{
    if (!_root)
        return nullptr;

    Node* node = this->_root;

    for (uint idx : path)
    {
        assert(idx <= node->_children.size() - 1);
        node = node->_children[idx];
    }

    return node;
}

template<typename T>
void Tree<T>::set(const std::vector<int> &path, const T &data)
{
    if (!_root)
        _root = new Node(data);

    Node* node = this->_root;

    for (int idx : path)
    {
        assert(idx <= node->_children.size() - 1);
        node = node->_children[idx];
    }

    node->_data = data;
}

template<typename T>
QString Tree<T>::getQStrPaths() const
{
    if (!_root)
        return "";

    std::vector<int> maxChildrenMap = this->getMaxChildrenMap();

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

        subtreeQStr += pathToQStr(parentPath, maxChildrenMap);

        QTextStream *stream = new QTextStream(&subtreeQStr);
        *stream << "     { " << *current << " }\n";

        if (current->_children.size() != 0)
        {
            for (int idx = current->_children.size() - 1; idx >= 0; idx--)
            {
                std::vector<int> extendedPath(parentPath);
                extendedPath.push_back(idx);

                nodes.push(current->_children[idx]);
                intPaths.push(extendedPath);
            }
        }
    }

    return subtreeQStr;
}

template<typename T>
void Tree<T>::print() const
{
    if (!_root)
        return;

    std::stack<Node*> nodes;

    nodes.push(this->_root);

    while (!nodes.empty())
    {
        Node* current = nodes.top();
        nodes.pop();

        qDebug() << current->_data;

        if (current->_children.size() != 0)
        {
            for (int idx = current->_children.size() - 1; idx >= 0; idx--)
            {
                nodes.push(current->_children[idx]);
            }
        }
    }
}

#endif // GENERALTREE_H

