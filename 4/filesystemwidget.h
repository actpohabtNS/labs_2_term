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

public:
    explicit FileSystemWidget(QTreeWidget* widget, FileSystem* fs);
    virtual ~FileSystemWidget();

    void showAll();

    void filterByName(QString name);
    void filterBySize(int min, int max);
    void filterByLastEdited(const QTime& min, const QTime& max);
};

template <typename ...Types>
void FileSystemWidget::_filterByFunc(bool includesByFilter(const FileSystemElem&, Types ...Args), Types ...Args)
{
    QTreeWidgetItem* item = this->_widget->topLevelItem(0);

    while (item != nullptr)
    {
        FileSystemElem elem(false, item->text(0), item->text(1).toInt(), QTime().fromString(item->text(2), "HH:mm:ss"));

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
