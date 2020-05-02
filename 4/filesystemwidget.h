#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H

#include <QTreeWidget>

#include "treewidget.h"
#include "filesystem.h"

class FileSystemWidget : public TreeWidget<FileSystemElem>
{
private:
    template <typename ...Types>
    void _filterByFunc(bool includesByFilter(const FileSystemElem&, Types ...Args), Types ...Args);

    template <typename ...Types>
    void _filterByFunc(bool includesByFilter(const FileSystemElem&, const Types& ...Args), const Types& ...Args);

    int _countElems(QTreeWidgetItem* item, bool files) const;
    FileSystemElem _timeChanged(QTreeWidgetItem* item, bool first) const;

public:
    explicit FileSystemWidget(QTreeWidget* widget, FileSystem* fs);
    virtual ~FileSystemWidget();

    void showAll();

    void filterByName(QString name);
    void filterBySize(int min, int max);
    void filterByLastEdited(const QTime& min, const QTime& max);

    int filesCount(QTreeWidgetItem* item) const;
    int foldersCount(QTreeWidgetItem* item) const;
    FileSystemElem firstChanged(QTreeWidgetItem* item) const;
    FileSystemElem lastChanged(QTreeWidgetItem* item) const;
};

FileSystemElem treeItemToFSElem(QTreeWidgetItem* item);

template <typename ...Types>
void FileSystemWidget::_filterByFunc(bool includesByFilter(const FileSystemElem&, Types ...Args), Types ...Args)
{
    QTreeWidgetItem* item = this->_widget->topLevelItem(0);

    while (item != nullptr)
    {
        FileSystemElem elem = treeItemToFSElem(item);

        if (!includesByFilter(elem, Args...))
            item->setHidden(true);

        item = this->_widget->itemBelow(item);
    }
}

template <typename ...Types>
void FileSystemWidget::_filterByFunc(bool includesByFilter(const FileSystemElem&, const Types& ...Args), const Types& ...Args)
{
    this->_filterByFunc(includesByFilter, Args...);
}

#endif // FILESYSTEMWIDGET_H
