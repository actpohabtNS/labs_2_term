#ifndef TABLE_H
#define TABLE_H
#include <QTableWidget>
#include <vector>
#include <QString>
#include "ui_administrate.h"
#include "train.h"

const unsigned int MAX_ROW_C_NO_CH = 9;

const std::vector<QString> TRAIN_TABLE_HEAD_LABELS = {"id", "№", "From", "To", "Type", "Dep. time", "Arr. time", "Rate"};

class table : public QTableWidget
{
    QTableWidget* m_table;

public:
    table(QTableWidget* table);

    void setSize(int rowCount, int rowHeight, std::vector<int> columnWidths, std::vector<QString> headLabels = {});
    void setSizeTrainTable(std::vector<train> trains);
    void setTrainTable(std::vector<train> trains);
    void searchTable(std::vector<train> trains, QString search, std::vector<bool> settings);
    void sortTable(std::vector<bool> settings);
    void insertDataRow(std::vector<QString> data, int after);

    void squeezeColumns(int shift);

    int getRowsHeight();
    int getColumnsWidth();
    QTableWidget* getTable();
};

#endif // TABLE_H
