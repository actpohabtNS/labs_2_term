#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget>
#include "binaryTree.h"
#include "generalTree.h"

class TreeWidget
{
public:
    TreeWidget();
    virtual ~TreeWidget();

    void setBinaryTree(const BinaryTree<int>& bTree, const QTreeWidget* treeWidget) const;
    void setGeneralTree(const Tree<int>& tree, const QTreeWidget* treeWidget) const;
};

#endif // TREEWIDGET_H
