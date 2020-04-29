#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget>
#include "binaryTree.h"
#include "generalTree.h"
#include "tree.h"

template <typename T>
void setTree(Tree<T> & tree, QTreeWidget* treeWidget)
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

//template <typename T>
//void setGeneralTree(const GeneralTree<T>& tree, QTreeWidget* treeWidget)
//{
//    if (!tree.root())
//        return;

//    std::vector<int> itemChildrenCount = tree.childrenCount();
//    std::vector<T> preorderData = tree.preorderTravData();

//    QTreeWidgetItem* root = new QTreeWidgetItem;

//    QString itemText;
//    QTextStream *stream = new QTextStream(&itemText);
//    *stream << preorderData[0];

//    root->setText(0, itemText);
//    treeWidget->addTopLevelItem(root);

//    int currParent = 0;

//    std::stack<QTreeWidgetItem*> items;
//    items.push(root);

//    std::stack<int> itemsChildren;
//    itemsChildren.push(itemChildrenCount[currParent]);

//    while (true)
//    {
//        if (itemsChildren.top() == 0)
//        {
//            itemsChildren.pop();

//            if (itemsChildren.size() == 0)
//                break;

//            itemsChildren.top()--;

//            items.pop();
//        }
//        else
//        {
//            QTreeWidgetItem* item = new QTreeWidgetItem;

//            QString itemText;
//            QTextStream *stream = new QTextStream(&itemText);
//            *stream << preorderData[currParent + 1];

//            item->setText(0, itemText);

//            items.top()->addChild(item);

//            items.push(item);

//            currParent++;

//            itemsChildren.push(itemChildrenCount[currParent]);
//        }
//    }

//    treeWidget->expandAll();
//}

#endif // TREEWIDGET_H


