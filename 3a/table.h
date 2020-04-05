#ifndef TABLE_H
#define TABLE_H
#include <QTableWidget>
#include <vector>
#include <QString>


class table : public QTableWidget
{
    QTableWidget* m_table;

public:
    table();
    table(QTableWidget* table);

    void setSize(int rowCount, int rowHeight, std::vector<int> columnWidths, std::vector<QString> headLabels = {});

    void insertDataRow(std::vector<QString> data, int after);

    int getRowsHeight();
    int getColumnsWidth();
    void squeezeColumns(int shift);

    QTableWidget* getTable();

};


#endif // TABLE_H
