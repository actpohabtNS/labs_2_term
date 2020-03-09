#include "table.h"
#include <QDebug>

table::table()
{
    m_table = nullptr;
}

table::table(QTableWidget *table) : QTableWidget()
{
    m_table = table;

    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode( QAbstractItemView::SingleSelection);
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

void table::setCLL(CircularLinkedList cll) {

    Node* temp = cll.start;
    int stCount = 0;

    if (temp == nullptr) return;

    do {

        m_table->insertRow(m_table->rowCount());
        m_table->setItem(stCount, 0, new QTableWidgetItem(temp->station->name));

        temp = temp->next;
        stCount++;

    } while (temp != cll.start);

    m_table->setRowCount(stCount);

}

QTableWidget *table::getTable()
{
    return m_table;
}
