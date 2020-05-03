#ifndef TREEWIDGETBASE_H
#define TREEWIDGETBASE_H

#include <QTreeWidget>
#include <stack>
#include <QTextStream>

#include "tree.h"


template <typename T>
class TreeWidgetBase : public QTreeWidget {

protected:
    Tree<T>* _tree;

    virtual void _setupItem(QTreeWidgetItem* item, const T& data);

public:
    explicit TreeWidgetBase(QWidget* parent = nullptr);
    virtual ~TreeWidgetBase();

    void render();
    void clear();
    void update();

    std::vector<int> getPath(QTreeWidgetItem* item) const;

    void setTree(Tree<T>* tree);
};


// ------------------------ TreeWidget ---------------------------

template<typename T>
void TreeWidgetBase<T>::_setupItem(QTreeWidgetItem *item, const T& data)
{
    QString itemText;
    QTextStream *stream = new QTextStream(&itemText);
    *stream << data;

    item->setText(0, itemText);
}

template<typename T>
TreeWidgetBase<T>::TreeWidgetBase(QWidget* parent)
    : QTreeWidget(parent) {}

template<typename T>
TreeWidgetBase<T>::~TreeWidgetBase()
{
}

template<typename T>
void TreeWidgetBase<T>::render()
{
    if (!this->_tree->root())
        return;

    std::vector<int> itemChildrenCount = this->_tree->childrenCount();
    std::vector<T> preorderData = this->_tree->preorderTravData();

    QTreeWidgetItem* root = new QTreeWidgetItem;

    this->_setupItem(root, preorderData[0]);

    this->addTopLevelItem(root);

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

            this->_setupItem(item, preorderData[currParent + 1]);

            items.top()->addChild(item);

            items.push(item);

            currParent++;

            itemsChildren.push(itemChildrenCount[currParent]);
        }
    }

    this->expandAll();
}

template<typename T>
void TreeWidgetBase<T>::clear()
{
    this->QTreeWidget::clear();
}

template<typename T>
void TreeWidgetBase<T>::update()
{
    this->clear();
    this->render();
}

template<typename T>
std::vector<int> TreeWidgetBase<T>::getPath(QTreeWidgetItem *item) const
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
void TreeWidgetBase<T>::setTree(Tree<T> *tree)
{
    this->_tree = tree;
}

#endif // TREEWIDGETBASE_H
