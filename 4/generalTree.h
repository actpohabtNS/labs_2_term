#ifndef GENERALTREE_H
#define GENERALTREE_H

#include <vector>
#include <stack>
#include <queue>
#include <utility>
#include <iostream>
#include <cassert>
#include <QDebug>

#include "tree.h"
#include <functs.h>

template <typename T>
class GeneralTree : public Tree<T> {

protected:
    class Node : Tree<T>::Node {

        friend GeneralTree;

    private:
        T _data;
        std::vector<Node*> _children;

    public:
        explicit Node(const T& data);
        explicit Node(const T& data, const std::vector<Node*>& children);
        virtual ~Node();

        const T& data() const;
        const std::vector<Node*>& children() const;
        int childrenCount() const;
        std::vector<T> preorderTravData() const;

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

    std::vector<int> _getMaxChildrenMap() const;
    Node* _getNode(const std::vector<int>& path) const;
    T& _get(const std::vector<int>& path) const;

public:
    GeneralTree();
    explicit GeneralTree(const T& data);
    explicit GeneralTree(Node* node);
    virtual ~GeneralTree();

    void empty();
    void empty(const T& newRoot);

    bool contains(const T& searchData) const;
    virtual bool nodeExists(const std::vector<int>& path) const;

    void insert(const std::vector<int>& path, const T& data);

    GeneralTree* removeSubtree(const std::vector<int>& path);
    void removeSubtree(const T& removingData);

    std::vector<int> getPath(const T& searchData) const;
    virtual int childrenCount(const std::vector<int>& path) const;

    std::vector<int> childrenCount() const;
    std::vector<T> preorderTravData() const;
    std::vector<T> preorderTravData(const std::vector<int>& path) const;

    const Node* root() const;
    virtual T get(const std::vector<int>& path) const;
    void set(const std::vector<int>& path, const T& data);

    QString getQStrPaths() const;

    void print() const;

    virtual QString type() const;
};



// --------------------------- Node ------------------------------

template <typename T>
GeneralTree<T>::Node::Node(const T& data) : _data(data) {}

template<typename T>
GeneralTree<T>::Node::Node(const T& data, const std::vector<GeneralTree::Node *>& children)
    : _data(data), _children(children) {}

template <typename T>
GeneralTree<T>::Node::~Node()
{
    for (auto& child : this->_children)
    {
        delete child;
    }
}

template <typename T>
const T& GeneralTree<T>::Node::data() const
{
    return this->_data;
}

template <typename T>
const std::vector<typename GeneralTree<T>::Node*>& GeneralTree<T>::Node::children() const
{
    return this->_children;
}

template<typename T>
int GeneralTree<T>::Node::childrenCount() const
{
    return this->_children.size();
}

template<typename T>
std::vector<T> GeneralTree<T>::Node::preorderTravData() const
{
    std::stack<const Node*> nodes;
    nodes.push(this);

    std::vector<T> preorderTravData;

    while (!nodes.empty())
    {
        const Node* current = nodes.top();
        nodes.pop();

        preorderTravData.push_back(current->_data);

        if (current->_children.size() != 0)
        {
            for (int idx = current->_children.size() - 1; idx >= 0; idx--)
                nodes.push(current->_children[idx]);
        }
    }

    return preorderTravData;
}
// --------------------------- Tree ------------------------------


template<typename T>
GeneralTree<T>::GeneralTree() : _root(nullptr) {}

template <typename T>
GeneralTree<T>::GeneralTree(const T& data) : _root(new Node(data)) {}

template<typename T>
GeneralTree<T>::GeneralTree(GeneralTree::Node *node) : _root(new Node(node->_data, node->_children)) {}

template <typename T>
GeneralTree<T>::~GeneralTree()
{
    delete _root;
}

template<typename T>
void GeneralTree<T>::empty()
{
    delete this->_root;
}

template<typename T>
void GeneralTree<T>::empty(const T &newRoot)
{
    this->empty();

    this->_root = new Node(newRoot);
}

template<typename T>
std::vector<int> GeneralTree<T>::_getMaxChildrenMap() const
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
typename GeneralTree<T>::Node* GeneralTree<T>::_getNode(const std::vector<int> &path) const
{   
    if (!this->_root)
    {
        qDebug() << "no root";
        return nullptr;
    }

    Node* node = this->_root;

    for (uint idx : path)
    {
        assert(idx <= node->_children.size() - 1);
        node = node->_children[idx];
    }

    return node;
}

template<typename T>
T &GeneralTree<T>::_get(const std::vector<int> &path) const
{
    return this->_getNode(path)->_data;
}

template<typename T>
bool GeneralTree<T>::contains(const T &searchData) const
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
bool GeneralTree<T>::nodeExists(const std::vector<int> &path) const
{
    if (this->_root)
        return false;

    Node* node = this->_root;

    for (uint idx = 0; idx < path.size(); idx++)
    {
        if ((uint)path[idx] > node->_children.size())
            return false;

        node = node->_children[path[idx]];
    }

    return true;
}

template<typename T>
void GeneralTree<T>::insert(const std::vector<int> &path, const T &data)
{
    if (!_root)
    {
        _root = new Node(data);
        return;
    }

    Node* parent = this->_getNode(path);
    parent->_children.push_back(new Node(data));
}

template<typename T>
void GeneralTree<T>::removeSubtree(const T &removingData)
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
std::vector<int> GeneralTree<T>::getPath(const T &searchData) const
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
GeneralTree<T>* GeneralTree<T>::removeSubtree(const std::vector<int> &path)
{
    if (!_root)
        return new GeneralTree();

    Node* node = this->_getNode(path);

    GeneralTree* newTree = new GeneralTree(node);

    if (path.size() != 0)
    {
        std::vector<int> parentPath(path);
        parentPath.pop_back();

        Node* parentNode = this->_getNode(parentPath);

        parentNode->_children.erase(parentNode->_children.begin() + path.back());
    }
    else
    {
        _root = nullptr;
    }

    return newTree;
}

template <typename T>
const typename GeneralTree<T>::Node* GeneralTree<T>::root() const
{
    return this->_root;
}

template<typename T>
T GeneralTree<T>::get(const std::vector<int> &path) const
{
    assert(this->_root);
    return _getNode(path)->_data;
}

template<typename T>
int GeneralTree<T>::childrenCount(const std::vector<int> &path) const
{
    return this->_getNode(path)->childrenCount();
}

template<typename T>
std::vector<int> GeneralTree<T>::childrenCount() const
{
    if (!_root)
        return {-1};

    std::stack<Node*> nodes;
    nodes.push(this->_root);

    std::vector<int> childrenCount;

    while (!nodes.empty())
    {
        Node* current = nodes.top();
        nodes.pop();

        childrenCount.push_back(current->childrenCount());

        if (current->_children.size() != 0)
        {
            for (int idx = current->_children.size() - 1; idx >= 0; idx--)
                nodes.push(current->_children[idx]);
        }
    }

    return childrenCount;
}

template<typename T>
std::vector<T> GeneralTree<T>::preorderTravData() const
{
    assert(this->_root != nullptr);

    return this->_root->preorderTravData();
}

template<typename T>
std::vector<T> GeneralTree<T>::preorderTravData(const std::vector<int> &path) const
{
    assert(this->_root != nullptr);

    assert(this->_getNode(path) != nullptr);

    return this->_getNode(path)->preorderTravData();
}

template<typename T>
void GeneralTree<T>::set(const std::vector<int> &path, const T &data)
{
    if (!_root)
        _root = new Node(data);

    Node* node = this->_root;

    for (uint idx : path)
    {
        assert(idx <= node->_children.size() - 1);
        node = node->_children[idx];
    }

    node->_data = data;
}

template<typename T>
QString GeneralTree<T>::getQStrPaths() const
{
    if (!_root)
        return "";

    std::vector<int> maxChildrenMap = this->_getMaxChildrenMap();

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
void GeneralTree<T>::print() const
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

template<typename T>
QString GeneralTree<T>::type() const
{
    return "General Tree";
}

#endif // GENERALTREE_H
