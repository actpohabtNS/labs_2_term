#ifndef TABLE_H
#define TABLE_H
#include <QTableWidget>
#include <vector>
#include <QString>
#include "circularlinkedlist.h"
#include "ui_interactwindow.h"


class table : public QTableWidget
{
    QTableWidget* m_table;

public:
    table();
    table(QTableWidget* table);

    void setSize(int rowCount, int rowHeight, std::vector<int> columnWidths, std::vector<QString> headLabels = {});

    void setCLL(CircularLinkedList cll);

    QTableWidget* getTable();

};


#endif // TABLE_H
