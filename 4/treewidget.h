#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget>

#include "binaryTree.h"
#include "generalTree.h"
#include "tree.h"

template <typename T>
void setTree(Tree<T>& tree, QTreeWidget* treeWidget)
{
    if (!tree.root())
        return;

    std::vector<int> itemChildrenCount = tree.childrenCount();
    std::vector<T> preorderData = tree.preorderTravData();

    QTreeWidgetItem* root = new QTreeWidgetItem;

    QString itemText;
    QTextStream *stream = new QTextStream(&itemText);
    *stream << preorderData[0];

    root->setText(0, itemText);
    treeWidget->addTopLevelItem(root);

    int currParent = 0;

    std::stack<QTreeWidgetItem*> items;
    items.push(root);

    std::stack<int> itemsChildren;
    itemsChildren.push(itemChildrenCount[currParent]);

    while (true)
    {
        if (itemsChildren.top() == 0)
        {
            itemsChildren.pop();

            if (itemsChildren.size() == 0)
                break;

            itemsChildren.top()--;

            items.pop();
        }
        else
        {
            QTreeWidgetItem* item = new QTreeWidgetItem;

            QString itemText;
            QTextStream *stream = new QTextStream(&itemText);
            *stream << preorderData[currParent + 1];

            item->setText(0, itemText);

            items.top()->addChild(item);

            items.push(item);

            currParent++;

            itemsChildren.push(itemChildrenCount[currParent]);
        }
    }

    treeWidget->expandAll();
}


template <typename T>
class TreeWidget : public QTreeWidget {
private:
    QTreeWidget* _widget;
    Tree<T>* _tree;

    std::vector<QTreeWidgetItem*> _parentItems(QTreeWidgetItem* item) const;
    std::vector<int> _pathByItems(std::vector<QTreeWidgetItem*> items) const;

public:
    explicit TreeWidget(QTreeWidget* widget, Tree<T>* tree);
    virtual ~TreeWidget();

    void render();
    void clear();
    void update();

    std::vector<int> getPath(QTreeWidgetItem* item) const;

    void setTree(Tree<T>* tree);
};


// ------------------------ TreeWidget ---------------------------

template<typename T>
std::vector<QTreeWidgetItem *> TreeWidget<T>::_parentItems(QTreeWidgetItem *item) const
{
    std::vector<QTreeWidgetItem*> parentItems;
    parentItems.push_back(item);

    while (this->_widget->itemAbove(item) != nullptr)
    {
        parentItems.push_back(this->_widget->itemAbove(item));
    }

    parentItems.pop_back();

    return parentItems;
}

//template<typename T>
//std::vector<int> TreeWidget<T>::_pathByItems(std::vector<QTreeWidgetItem *> items) const
//{
//    std::vector<int> path;

//    QTreeWidgetItem* parent = this->_widget->topLevelItem(0);

//    while (items.size() != 0)
//    {

//    }

//    return path;
//}

template<typename T>
TreeWidget<T>::TreeWidget(QTreeWidget *widget, Tree<T> *tree)
    : _widget(widget), _tree(tree) {}

template<typename T>
TreeWidget<T>::~TreeWidget()
{
    delete this->_widget;
}

template<typename T>
void TreeWidget<T>::render()
{
    if (!this->_tree->root())
        return;

    std::vector<int> itemChildrenCount = this->_tree->childrenCount();
    std::vector<T> preorderData = this->_tree->preorderTravData();

    QTreeWidgetItem* root = new QTreeWidgetItem;

    QString itemText;
    QTextStream *stream = new QTextStream(&itemText);
    *stream << preorderData[0];

    root->setText(0, itemText);
    this->_widget->addTopLevelItem(root);

    int currParent = 0;

    std::stack<QTreeWidgetItem*> items;
    items.push(root);

    std::stack<int> itemsChildren;
    itemsChildren.push(itemChildrenCount[currParent]);

    while (true)
    {
        if (itemsChildren.top() == 0)
        {
            itemsChildren.pop();

            if (itemsChildren.size() == 0)
                break;

            itemsChildren.top()--;

            items.pop();
        }
        else
        {
            QTreeWidgetItem* item = new QTreeWidgetItem;

            QString itemText;
            QTextStream *stream = new QTextStream(&itemText);
            *stream << preorderData[currParent + 1];

            item->setText(0, itemText);

            items.top()->addChild(item);

            items.push(item);

            currParent++;

            itemsChildren.push(itemChildrenCount[currParent]);
        }
    }

    this->_widget->expandAll();
}

template<typename T>
void TreeWidget<T>::clear()
{
    this->_widget->clear();
}

template<typename T>
void TreeWidget<T>::update()
{
    this->clear();
    this->render();
}

template<typename T>
std::vector<int> TreeWidget<T>::getPath(QTreeWidgetItem *item) const
{
    QTreeWidgetItem* currItem = item;

    std::vector<int> path;

    while (currItem->parent() != nullptr)
    {
        path.push_back(indexFromItem(currItem).row());
        currItem = currItem->parent();
    }

    std::reverse(path.begin(), path.end());

    return path;
}

template<typename T>
void TreeWidget<T>::setTree(Tree<T> *tree)
{
    this->_tree = tree;
}


#endif // TREEWIDGET_H
