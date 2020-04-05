#ifndef TABLE_H
#define TABLE_H
#include <QTableWidget>
#include <vector>
#include <QString>
#include "date.h"
#include <QColor>

class table : public QTableWidget
{
    QTableWidget* m_table;

public:
    table();
    table(QTableWidget* table);
    table(QTableWidget* table, int rowHeight, int columnCount);

    void setSize(int rowCount, int rowHeight, std::vector<int> columnWidths, std::vector<QString> headLabels = {});
    void setEqualColumnWidths(int columnCount);
    void setVisTable(int rowHeight, int columnCount);
    void setDateArray(Date arr[], int size);
    void insertDataRow(std::vector<QString> data, int after);

    void highlightItems(int row1, int column1, int row2, int column2, QColor color);
    void squeezeColumns(int shift);
    void swapItemsText(int row1, int column1, int row2, int column2);

    int getRowsHeight();
    int getColumnsWidth();

    QTableWidget* getTable();

};

void visualizeComparison(table* table, int& delay, int elem1, int elem2);
void visualizeSwap(table* table, int& delay, int elem1, int elem2);
bool compareVisualizeDates(Date& d1, Date& d2, table* table, int &delay);

#endif // TABLE_H
