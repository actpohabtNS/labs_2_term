#include "filesystemwidget.h"

FileSystemWidget::FileSystemWidget(QTreeWidget *widget, FileSystem *fs)
    : TreeWidget<FileSystemElem>(widget, dynamic_cast<GeneralTree<FileSystemElem>*>(fs)) {}

FileSystemWidget::~FileSystemWidget()
{
}

void FileSystemWidget::showAll()
{
    QTreeWidgetItem* item = this->_widget->topLevelItem(0);

    while (item != nullptr)
    {
        item->setHidden(false);
    }
}

void FileSystemWidget::filterByName(QString name)
{
    this->_filterByFunc(containsStr, name);
}

void FileSystemWidget::filterBySize(int min, int max)
{
    this->_filterByFunc(isInSizeInterval, min, max);
}

void FileSystemWidget::filterByLastEdited(const QTime &min, const QTime &max)
{
    this->_filterByFunc(isInTimeInterval, min, max);
}
