#include "filesystemwidget.h"

void FileSystemWidget::_setupItem(QTreeWidgetItem *item, const FileSystemElem &fsElem)
{
    item->setText(0, fsElem.name());
    item->setText(1, QString::number(fsElem.size()) + " kB");
    item->setText(2, fsElem.lastChanged().toString("HH:mm"));
    item->setText(3, fsElem.isFolder() ? "+" : "");
}

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
    FileSystemElem mostElem = treeItemToFSElem(item);
    std::vector<QTreeWidgetItem*> items = this->preorderTravData(item);

    for (QTreeWidgetItem* currItem : items)
    {
        FileSystemElem currElem = treeItemToFSElem(currItem);

        if ( first ? mostElem.lastChanged() >= currElem.lastChanged() : mostElem.lastChanged() <= currElem.lastChanged() )
            mostElem = currElem;
    }

    return mostElem;
}

FileSystemWidget::FileSystemWidget(QWidget* parent)
    : TreeWidgetBase<FileSystemElem>(parent), _isFiltered(false) {}

FileSystemWidget::~FileSystemWidget()
{
}

void FileSystemWidget::setAllVisible()
{
    QTreeWidgetItem* item = this->topLevelItem(0);

    std::stack<QTreeWidgetItem*> items;
    items.push(item);

    while (!items.empty())
    {
        QTreeWidgetItem* curr = items.top();
        items.pop();

        item->setHidden(false);

        for (int child = 0; child < curr->childCount(); child++)
        {
            items.push(curr->child(child));
        }
    }

    this->_isFiltered = false;
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

int FileSystemWidget::size(QTreeWidgetItem *item) const
{
    return item->text(1).split(" ")[0].toInt();
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

bool FileSystemWidget::isFiltered() const
{
    return this->_isFiltered;
}

std::vector<QTreeWidgetItem*> FileSystemWidget::preorderTravData(QTreeWidgetItem *item) const
{
    QTreeWidgetItem* curr = item;

    std::stack<QTreeWidgetItem*> items;
    items.push(item);

    std::vector<QTreeWidgetItem*> elems;

    while (!items.empty())
    {
        curr = items.top();
        items.pop();

        elems.emplace_back(curr);

        for (int child = 0; child < curr->childCount(); child++)
        {
            items.push(curr->child(child));
        }
    }

    return elems;
}

void FileSystemWidget::setFileSystem(FileSystem *fs)
{
    this->setTree(fs);
}

FileSystemElem treeItemToFSElem(QTreeWidgetItem *item)
{
    bool isFolder = item->text(3) == "+";
    QString name = item->text(0);
    int size = item->text(1).split(" ")[0].toInt();
    QTime lastChanged = QTime().fromString(item->text(2), "HH:mm");

    return FileSystemElem{isFolder, name, size, lastChanged};
}
