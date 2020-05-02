#include "filesystemwidget.h"

int FileSystemWidget::_countElems(QTreeWidgetItem *item, bool files) const
{
    int elems = 0;

    std::stack<QTreeWidgetItem*> items;
    items.push(item);

    while (!items.empty())
    {
        QTreeWidgetItem* curr = items.top();
        items.pop();

        for (int child = 0; child < curr->childCount(); child++)
        {
            if (curr->isHidden())
                continue;

            if (files)
            {
                if (treeItemToFSElem(curr->child(child)).isFolder())
                    items.push(curr->child(child));
                else
                    elems++;
            }
            else
            {
                if (treeItemToFSElem(curr->child(child)).isFolder())
                {
                    items.push(curr->child(child));
                    elems++;
                }
            }

        }
    }

    return elems;
}

FileSystemElem FileSystemWidget::_timeChanged(QTreeWidgetItem *item, bool first) const
{
    QTreeWidgetItem* curr = this->_widget->itemBelow(item);
    FileSystemElem mostElem = treeItemToFSElem(item);

    while (curr != nullptr)
    {
        FileSystemElem currElem = treeItemToFSElem(curr);

        if ( first ? mostElem.lastChanged() > currElem.lastChanged() : mostElem.lastChanged() < currElem.lastChanged() )
            mostElem = currElem;

        curr = this->_widget->itemBelow(item);
    }

    return mostElem;
}

FileSystemWidget::FileSystemWidget(QTreeWidget *widget, FileSystem *fs)
    : TreeWidget<FileSystemElem>(widget, fs->fileTree()) {}

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

int FileSystemWidget::filesCount(QTreeWidgetItem *item) const
{
    return this->_countElems(item, true);
}

int FileSystemWidget::foldersCount(QTreeWidgetItem *item) const
{
    return this->_countElems(item, false);
}

FileSystemElem FileSystemWidget::firstChanged(QTreeWidgetItem *item) const
{
    return this->_timeChanged(item, true);
}

FileSystemElem FileSystemWidget::lastChanged(QTreeWidgetItem *item) const
{
    return this->_timeChanged(item, false);
}

FileSystemElem treeItemToFSElem(QTreeWidgetItem *item)
{
    bool isFolder = item->text(3) == "+";
    QString name = item->text(0);
    int size = item->text(1).split(" ")[0].toInt();
    QTime lastChanged = QTime().fromString(item->text(2), "HH:mm:ss");

    return FileSystemElem{isFolder, name, size, lastChanged};
}
