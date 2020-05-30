#include "spanningtree.h"

// ---------------------------- Node ----------------------------------

SpanningTree::Node::Node(int index, int weight)
    : _index(index), _weight(weight) {}

SpanningTree::Node::~Node()
{
    for (Node* ch : this->_children)
        delete ch;
}

int SpanningTree::Node::index() const
{
    return this->_index;
}

int SpanningTree::Node::weight() const
{
    return this->_weight;
}

std::vector<SpanningTree::Node *> SpanningTree::Node::children() const
{
    return this->_children;
}



// ---------------------------- Spanning Tree ----------------------------------

int SpanningTree::_weight(SpanningTree::Node *node) const
{
    int weight = 0;

    if (node != nullptr)
    {
        weight += node->_weight;

        for (auto child : node->_children)
            weight += _weight(child);
    }

    return weight;
}

SpanningTree::SpanningTree(SpanningTree::Node *root)
    : _root(root) {}

SpanningTree::~SpanningTree()
{
    delete this->_root;
}

void SpanningTree::link(SpanningTree::Node *fnode, SpanningTree::Node *tnode, const int &weight)
{
    if (!this->_root)
        return;

    fnode->_children.emplace_back(tnode);
    tnode->_parent = fnode;
    tnode->_weight = weight;
}

int SpanningTree::weight() const
{
    return this->_weight(this->_root);
}

const SpanningTree::Node *SpanningTree::root() const
{
    return this->_root;
}
