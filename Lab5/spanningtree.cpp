#include <QDebug>
#include <stack>

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

void SpanningTree::Node::print() const
{
    qDebug() << this->QStr();
}

QString SpanningTree::Node::QStr() const
{
    return QString::number(this->_weight) + " -> [ " + QString::number(this->_index) + " ]";
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

void SpanningTree::_QStr(SpanningTree::Node *node, int level, QString& QStr) const
{
    if (!node)
        return;

    QStr += node->QStr();

    if (!node->_children.empty())
    {
        QStr += "\n";

        for (uint i = 0; i < node->_children.size(); i++)
        {
            for (int j = 0; j <= level; j++)
                 QStr += "\t";

            this->_QStr(node->_children[i], level + 1, QStr);
        }
    } else
        QStr += "\n";
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

void SpanningTree::print() const
{
    qDebug().noquote() << this->QStr();
}

QString SpanningTree::QStr() const
{
    QString QStr = "";

    this->_QStr(this->_root, 0, QStr);

    return QStr;
}

const SpanningTree::Node *SpanningTree::root() const
{
    return this->_root;
}
