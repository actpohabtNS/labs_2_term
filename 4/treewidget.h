#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include "TreeWidgetBase.h"


class TreeWidget : public TreeWidgetBase<int> {

    Q_OBJECT

public:
    explicit TreeWidget(QWidget* parent = nullptr);
    virtual ~TreeWidget();

};

#endif // TREEWIDGET_H
