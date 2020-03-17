#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>
#include <vector>
#include <QString>
#include "priorityqueue.h"
#include "ui_priorityqueuewindow.h"
#include "multilevelqueue.h"
#include "ui_multilevelqueuewindow.h"
#include "functs.h"


class table : public QTableWidget
{
    QTableWidget* m_table;

public:
    table();
    table(QTableWidget* table);

    void setSize(int rowCount, int rowHeight, std::vector<int> columnWidths, std::vector<QString> headLabels = {});

    void setPrQ(PriorityQueue<QString> prQ);

    void setStations(std::vector<Station> stations);

    void addQueue(Queue<QString> queue);

    void setMlQ(MultilevelQueue<QString> mlQ);

    QTableWidget* getTable();

};

#endif // TABLE_H
