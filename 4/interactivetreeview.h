#ifndef INTERACTIVETREEVIEW_H
#define INTERACTIVETREEVIEW_H

#include <QLabel>
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidget>

#include "binaryTree.h"
#include "generalTree.h"

template <typename T>
class InteractiveTreeView
{
private:
    Tree<T>* _tree;
    QPushButton* _parentButton;
    QLabel* _elemLabel;
    QTableWidget* _childrenTable;
    std::vector<int> _currElemPath;

    void _setEqualColumnWidths(const int columnCount);
    void _setupChildrenTable();
    void _setBinaryChildren(const std::vector<int>& path);
    void _setChildren(const std::vector<int>& path);
    void _setParentButton(const std::vector<int>& path);

public:
    explicit InteractiveTreeView(Tree<T>* tree,QPushButton* parentButton, QLabel* elemLabel, QTableWidget* childrenTable);
    //explicit InteractiveTreeView(GeneralTree<T>* tree, QPushButton* parentButton, QLabel* elemLabel, QTableWidget* childrenTable);
    virtual ~InteractiveTreeView();

    void setElem(const std::vector<int>& path);
    void toParent();
    void toChild(int child);
    void toRoot();
    void setEnabled(const bool enabled);

    void setBinaryTree(BinaryTree<T>* bTree);
    void setTree(Tree<T>* tree);
};



// --------------------------- InteractiveTreeView ------------------------------

template<typename T>
void InteractiveTreeView<T>::_setEqualColumnWidths(const int columnCount)
{
    int columnWidth = _childrenTable->width()/columnCount;

    for(int i = 0; i < columnCount; i++)
    {
        _childrenTable->setColumnWidth(i, columnWidth);
    }
}

template<typename T>
void InteractiveTreeView<T>::_setupChildrenTable()
{
    this->_childrenTable->setRowCount(1);

    int height = this->_childrenTable->height();
    this->_childrenTable->verticalHeader()->setDefaultSectionSize(height);

    this->_childrenTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->_childrenTable->setSelectionMode(QAbstractItemView::SingleSelection);
    this->_childrenTable->verticalHeader()->setVisible(false);
    this->_childrenTable->horizontalHeader()->setVisible(false);
    this->_childrenTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

template<typename T>
void InteractiveTreeView<T>::_setBinaryChildren(const std::vector<int>& path)
{
    int size = 2;

    _childrenTable->setColumnCount(size);
    _setEqualColumnWidths(size);

    Qt::ItemFlags disabledFlags;
    disabledFlags &= ~(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);

    QTableWidgetItem *leftItem = new QTableWidgetItem("left");
    leftItem->setTextAlignment(Qt::AlignCenter);

    std::vector<int> childPath(path);
    childPath.push_back(0);

    if (!_tree->nodeExists(childPath))
        leftItem->setFlags(disabledFlags);

    _childrenTable->setItem(0, 0, leftItem);

    QTableWidgetItem *rightItem = new QTableWidgetItem("right");
    rightItem->setTextAlignment(Qt::AlignCenter);

    childPath.pop_back();
    childPath.push_back(1);

    if (!_tree->nodeExists(childPath))
        rightItem->setFlags(disabledFlags);

    _childrenTable->setItem(0, 1, rightItem);
}

template<typename T>
void InteractiveTreeView<T>::_setChildren(const std::vector<int>& path)
{
    int size = this->_tree->childrenCount(path);

    if (size == 0)
    {

        _childrenTable->setColumnCount(0);
        _childrenTable->setEnabled(false);
    }
    else
    {
        _childrenTable->setEnabled(true);
        _childrenTable->setColumnCount(size);
        _setEqualColumnWidths(size);
        QTableWidgetItem *item;

        for (int column = 0; column < size; column++)
        {
           item = new QTableWidgetItem(QString::number(column));
           item->setTextAlignment(Qt::AlignCenter);
           _childrenTable->setItem(0, column, item);
        }
    }
}

template<typename T>
void InteractiveTreeView<T>::_setParentButton(const std::vector<int> &path)
{
    if (path.size() == 0)
        this->_parentButton->setEnabled(false);
    else
        this->_parentButton->setEnabled(true);
}

template<typename T>
InteractiveTreeView<T>::InteractiveTreeView(Tree<T>* tree, QPushButton* parentButton, QLabel *elemLabel, QTableWidget *childrenTable)
    : _tree(tree), _parentButton(parentButton), _elemLabel(elemLabel), _childrenTable(childrenTable), _currElemPath({-1})
{
    _setupChildrenTable();
}

template<typename T>
InteractiveTreeView<T>::~InteractiveTreeView()
{
    delete this->_parentButton;
    delete this->_elemLabel;
    delete this->_childrenTable;
}

template<typename T>
void InteractiveTreeView<T>::setElem(const std::vector<int> &path)
{
    this->_setParentButton(path);

    if (this->_tree->type() == "Binary Tree")
    {
        T data = this->_tree->get(path);

        QString dataQStr;
        QTextStream *stream = new QTextStream(&dataQStr);
        *stream << data;

        this->_elemLabel->setText(dataQStr);

        this->_setBinaryChildren(path);
    }
    else
    {
        T data = this->_tree->get(path);

        QString dataQStr;
        QTextStream *stream = new QTextStream(&dataQStr);
        *stream << data;

        this->_elemLabel->setText(dataQStr);

        this->_setChildren(path);
    }

    this->_currElemPath = path;
}

template<typename T>
void InteractiveTreeView<T>::toParent()
{
    if (this->_currElemPath.size() == 0)
        return;

    this->_currElemPath.pop_back();

    this->setElem(this->_currElemPath);
}

template<typename T>
void InteractiveTreeView<T>::toChild(int child)
{
    this->_currElemPath.push_back(child);

    this->setElem(this->_currElemPath);
}

template<typename T>
void InteractiveTreeView<T>::toRoot()
{
    this->_currElemPath = {};

    this->setElem(this->_currElemPath);
}

template<typename T>
void InteractiveTreeView<T>::setEnabled(const bool enabled)
{
    this->_parentButton->setEnabled(enabled);
    this->_childrenTable->setEnabled(enabled);
}

template<typename T>
void InteractiveTreeView<T>::setTree(Tree<T> *tree)
{
    this->_tree = tree;
}



#endif // INTERACTIVETREEVIEW_H
