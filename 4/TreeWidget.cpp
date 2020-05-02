#include "treewidget.h"

template<>
void TreeWidget<FileSystemElem>::_setupItem(QTreeWidgetItem *item, const FileSystemElem &fsElem)
{
    item->setText(0, fsElem.name());
    item->setText(1, QString::number(fsElem.size()) + "kB");
    item->setText(2, fsElem.lastChanged().toString());
}
