#include "table.h"
#include "functs.h"

table::table(QTableWidget *table) : QTableWidget()
{
    m_table = table;

    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void table::setSize(int rowCount, int rowHeight, std::vector<int> columnWidths, std::vector<QString> headLabelsStr)
{
    m_table->setRowCount(rowCount);
    m_table->setColumnCount(columnWidths.size());

    for (unsigned int i = 0; i < columnWidths.size(); i++) {
        m_table->setColumnWidth(i, columnWidths[i]);
    }

    QHeaderView *verticalHeader = m_table->verticalHeader();

    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(rowHeight);
    verticalHeader->setVisible(false);


    if (headLabelsStr.size() == 0) return;

    QStringList headLabels;

    for (QString Qst : headLabelsStr) {
        headLabels << Qst;
    }

    m_table->setHorizontalHeaderLabels(headLabels);


}

void table::setSizeTrainTable(std::vector<train> trains)
{
    std::vector<int> columnWidths = {130, 80, 300, 300, 300, 130, 130};

    if (trains.size() <= MAX_ROW_C_NO_CH) {
        columnWidths.push_back(88);
    } else {
        columnWidths.push_back(60);
    }

    int rowCount = trains.size() == 0 ? 1 : trains.size();

    this->setSize(rowCount, 60, columnWidths, TRAIN_TABLE_HEAD_LABELS);
}

void table::setTrainTable(std::vector<train> trains)
{

    setSizeTrainTable(trains);

    if (trains.size() == 0) {
        m_table->setColumnCount(1);
        m_table->setColumnWidth(0, 1600);

        m_table->setItem(0, 0, new QTableWidgetItem("Your table is EMPTY. Add trains using button above."));

        return;
    }

    for (unsigned int i = 0; i < trains.size(); i++) {

        for (int j = 0; j < 8; j++) {
             m_table->setItem(i, j, new QTableWidgetItem(trains[i].getInfo()[j]));
        }

    }

}

void table::searchTable(std::vector<train> trains, QString search, std::vector<bool> settings)
{
    if (m_table->item(0, 0)->text().contains("EMPTY")) return;

    if (search == "") setTrainTable(trains);

    setSizeTrainTable(trains);

     m_table->setRowCount(trains.size());
     short rowNum = 0;

     if (settings[0]) {

         QString intervalMode = getIntervalMask(search);


         QStringList intervals = search.split("-");

         train::time depTime, arrTime;
         int fromNum = 0, toNum = 0;
         double fromRate = 0, toRate = 0;

         if (intervalMode == "Time") {

             depTime = {stos(intervals[0].split(":")[0].toLocal8Bit().constData()), stos(intervals[0].split(":")[1].toLocal8Bit().constData())};
             arrTime = {stos(intervals[1].split(":")[0].toLocal8Bit().constData()), stos(intervals[1].split(":")[1].toLocal8Bit().constData())};

         } else if (intervalMode == "Number") {

             fromNum = intervals[0].toInt();
             toNum = intervals[1].toUInt();

         } else if (intervalMode == "Rate") {

             fromRate = intervals[0].toDouble();
             toRate = intervals[1].toDouble();

         }


         for (unsigned int row = 0; row < trains.size(); row++) {
             bool suits = false;


             if (intervalMode == "Time") {

                 if (trains[row].getDepTime().getTime() >= depTime.getTime() && trains[row].getArrTime().getTime() <= arrTime.getTime()) {
                     suits = true;
                 }

             } else if (intervalMode == "Number") {

                 if (trains[row].getTrainNumber() >= fromNum && trains[row].getTrainNumber() <= toNum) {
                     suits = true;
                 }

             } else if (intervalMode == "Rate") {

                 if (trains[row].getTrainRate() >= fromRate && trains[row].getTrainRate() <= toRate) {
                     suits = true;
                 }

             }

             if (suits) rowNum++;

             for (int j = 0; suits && j < 8; j++) {
                  m_table->setItem(rowNum - 1, j, new QTableWidgetItem(trains[row].getInfo()[j]));
             }
         }

     } else {

         for (unsigned int row = 0; row < trains.size(); row++) {
             bool suits = false;

             for (unsigned int propNum = 0; propNum < 8; propNum++) {
                 if (settings[propNum+1] && trains[row].getInfo()[propNum].toLower().contains(search.toLower())) {
                     suits = true;
                 }
             }

             if (suits) rowNum++;

             for (int j = 0; suits && j < 8; j++) {
                  //qDebug() << trains[row].getInfo()[j];
                  m_table->setItem(rowNum - 1, j, new QTableWidgetItem(trains[row].getInfo()[j]));
             }

         }

     }


    if (rowNum != 0) {

        m_table->setRowCount(rowNum);

    } else {
        m_table->setRowCount(1);
        m_table->setColumnCount(1);
        m_table->setColumnWidth(0, 1600);

        m_table->setItem(0, 0, new QTableWidgetItem("No such elements found! Change your request or add a new train."));
    }

}


void table::sortTable(std::vector<bool> settings)
{
    settings[0] = false;
}

void table::insertDataRow(std::vector<QString> data, int after)
{
    if (m_table->height() < getRowsHeight() && m_table->width() < getColumnsWidth()+22)
    {
        squeezeColumns(22);
    }

    m_table->insertRow(after);

    for (uint data_idx = 0; data_idx < data.size(); data_idx++)
    {
        QTableWidgetItem * item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignCenter);
        item->setText(data[data_idx]);
        m_table->setItem(after, data_idx, item);
    }
}

int table::getRowsHeight()
{
    int height = 75;

    for(int row = 0; row < getTable()->rowCount(); row++)
    {
        height += getTable()->rowHeight(row);
    }

    return height;
}

int table::getColumnsWidth()
{
    int width = 0;

    for(int column = 0; column < getTable()->columnCount(); column++)
    {
        width += getTable()->columnWidth(column);
    }

    return width;
}

void table::squeezeColumns(int shift)
{
    int oneShift = shift/getTable()->columnCount();

    for(int column = 0; column < getTable()->columnCount(); column++)
    {
        getTable()->setColumnWidth(column, getTable()->columnWidth(column) - oneShift);
    }
}

QTableWidget* table::getTable()
{
    return m_table;
}
