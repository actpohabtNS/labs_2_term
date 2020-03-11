#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>
#include <vector>
#include <QString>
#include "priorityqueue.h"
#include "ui_priorityqueuewindow.h"


class table : public QTableWidget
{
    QTableWidget* m_table;

public:
    table();
    table(QTableWidget* table);

    void setSize(int rowCount, int rowHeight, std::vector<int> columnWidths, std::vector<QString> headLabels = {});

    void setPrQ(PriorityQueue<QString> prQ);

    QTableWidget* getTable();

};

#endif // TABLE_H
