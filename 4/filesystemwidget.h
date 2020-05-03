#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H

#include <QTreeWidget>

#include "treewidget.h"
#include "filesystem.h"

class FileSystemWidget : public TreeWidget<FileSystemElem>
{
private:
    bool _isFiltered;

    template <typename ...Types>
    void _filterByFunc(bool includesByFilter(const FileSystemElem&, Types ...Args), Types ...Args);

    template <typename ...Types>
    void _filterByFunc(bool includesByFilter(const FileSystemElem&, const Types& ...Args), const Types& ...Args);

    int _countElems(QTreeWidgetItem* item, bool files) const;
    FileSystemElem _timeChanged(QTreeWidgetItem* item, bool first) const;

public:
    explicit FileSystemWidget(QTreeWidget* widget, FileSystem* fs);
    virtual ~FileSystemWidget();

    void setAllVisible();

    void filterByName(QString name);
    void filterBySize(int min, int max);
    void filterByLastEdited(const QTime& min, const QTime& max);

    int size(QTreeWidgetItem* item) const;
    int filesCount(QTreeWidgetItem* item) const;
    int foldersCount(QTreeWidgetItem* item) const;
    FileSystemElem firstChanged(QTreeWidgetItem* item) const;
    FileSystemElem lastChanged(QTreeWidgetItem* item) const;

    bool isFiltered() const;
    std::vector<QTreeWidgetItem*> preorderTravData(QTreeWidgetItem* item) const;

    void setFileSystem(FileSystem* fs);
};

FileSystemElem treeItemToFSElem(QTreeWidgetItem* item);

template <typename ...Types>
void FileSystemWidget::_filterByFunc(bool includesByFilter(const FileSystemElem&, Types ...Args), Types ...Args)
{
    QTreeWidgetItem* item = this->_widget->topLevelItem(0);
    item = this->_widget->itemBelow(item);

    while (item != nullptr)
    {
        FileSystemElem elem = treeItemToFSElem(item);

        if (!includesByFilter(elem, Args...))
        {
            QTreeWidgetItem* temp;

            if (elem.isFolder())
                temp = this->_widget->itemAbove(item);
            else
                temp = this->_widget->itemBelow(item);

            item->setHidden(true);

            if (elem.isFolder())
                temp = this->_widget->itemBelow(temp);

            item = temp;
            continue;
        }

        item = this->_widget->itemBelow(item);
    }

    this->_isFiltered = true;
}

template <typename ...Types>
void FileSystemWidget::_filterByFunc(bool includesByFilter(const FileSystemElem&, const Types& ...Args), const Types& ...Args)
{
    this->_filterByFunc(includesByFilter, Args...);
}

#endif // FILESYSTEMWIDGET_H
