#include "table.h"

#include <QDebug>
#include <QTableWidgetItem>

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

void table::setPrQ(PriorityQueue<QString> prQ) {

    Node<QString>* temp = prQ.getEnd();
    int stCount = 0;

    if (temp == nullptr) return;

    while (temp != nullptr) {

        m_table->insertRow(m_table->rowCount());

        QTableWidgetItem* priorItem = new QTableWidgetItem(QString::number(temp->priority));
        priorItem->setData(Qt::TextAlignmentRole,Qt::AlignCenter);
        m_table->setItem(stCount, 0, priorItem);

        m_table->setItem(stCount, 1, new QTableWidgetItem(temp->data));

        temp = temp->prev;
        stCount++;

    }

    m_table->setRowCount(stCount);

}

void table::setStations(std::vector<Station> stations)
{

    int stCount = 0;

    for (Station st : stations) {

        m_table->insertRow(m_table->rowCount());
        m_table->setItem(stCount, 0, new QTableWidgetItem(st.name));

        stCount++;
    }

}

void table::addQueue(Queue<QString> queue)
{
    QNode<QString>* temp = queue.end();

    int stCount = m_table->rowCount();

    while (temp != nullptr) {

        m_table->insertRow(m_table->rowCount());
        m_table->setItem(stCount, 0, new QTableWidgetItem(*queue.dequeue()));

        temp = temp->prev;
        stCount++;

    }
}

void table::setMlQ(MultilevelQueue<QString> mlQ)
{

    clear();
    setSize(0, 50, {630}, {"Task"});

    QueueNode<QString>* temp = mlQ.lastQueue();

    int stCount = 0;

    while (temp != nullptr) {

        stCount = m_table->rowCount();

        QTableWidgetItem* levelHeader = new QTableWidgetItem("↓ ====== ↓ | Priority = " + QString::number(temp->prior) + " | ↓ ====== ↓");
        levelHeader->setData(Qt::TextAlignmentRole,Qt::AlignCenter);
        levelHeader->setBackground(Qt::lightGray);
        m_table->insertRow(m_table->rowCount());
        m_table->setItem(stCount, 0, levelHeader);

        addQueue(temp->queue);

        stCount = m_table->rowCount();

        temp = temp->prevQueue;
        stCount++;

    }

}

QTableWidget *table::getTable()
{
    return m_table;
}
