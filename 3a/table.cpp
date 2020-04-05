#include "table.h"
#include <QDebug>
#include <QHeaderView>
#include <QTimer>

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

table::table(QTableWidget *table, int rowHeight, int columnCount)
{
    m_table = table;
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectItems);

    setVisTable(rowHeight, columnCount);
}

void table::setSize(int rowCount, int rowHeight, std::vector<int> columnWidths, std::vector<QString> headLabelsStr)
{
    m_table->setRowCount(rowCount);
    m_table->setColumnCount(columnWidths.size());

    for (unsigned int i = 0; i < columnWidths.size(); i++)
    {
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

void table::setEqualColumnWidths(int columnCount)
{
    int columnWidth = m_table->width()/columnCount;

    for(int i = 0; i < columnCount; i++)
    {
        m_table->setColumnWidth(i, columnWidth);
    }
}

void table::setVisTable(int rowHeight, int columnCount)
{
    m_table->setRowCount(1);
    m_table->setColumnCount(columnCount);

    setEqualColumnWidths(columnCount);

    QHeaderView *verticalHeader = m_table->verticalHeader();

    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(rowHeight);
    verticalHeader->setVisible(false);

    m_table->horizontalHeader()->setVisible(false);
    m_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void table::setDateArray(Date arr[], int size)
{
    if(size > 50) size = 50;

    m_table->setColumnCount(size);
    setEqualColumnWidths(size);
    QTableWidgetItem *item;

    for (int column = 0; column < size; column++)
    {
       item = new QTableWidgetItem(arr[column].getTwoRowsText());
       item->setTextAlignment(Qt::AlignCenter);
       m_table->setItem(0, column, item);
    }
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

void table::highlightItems(int row1, int column1, int row2, int column2, QColor color)
{
   qDebug() << column1 << column2;

   m_table->item(row1, column1)->setBackground(color);
   m_table->item(row2, column2)->setBackground(color);
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

void table::swapItemsText(int row1, int column1, int row2, int column2)
{
    QString item1Text = m_table->item(row1, column1)->text();
    m_table->item(row1, column1)->setText(m_table->item(row2, column2)->text());
    m_table->item(row2, column2)->setText(item1Text);
}


QTableWidget *table::getTable()
{
    return m_table;
}

void visualizeComparison(table *table, int& delay, int elem1, int elem2)
{
    delay+=50;

    QTimer::singleShot(delay, [table, elem1, elem2]{table->highlightItems(0, elem1, 0, elem2, Qt::lightGray);});

    delay+=500;

    QTimer::singleShot(delay, [table, elem1, elem2]{table->highlightItems(0, elem1, 0, elem2, Qt::white); qDebug() << "whitened";});

    delay+=50;
}

void visualizeSwap(table *table, int &delay, int elem1, int elem2)
{
    QTimer::singleShot(delay, [table, elem1, elem2]{table->highlightItems(0, elem1, 0, elem2, Qt::yellow);});

    delay+=500;

    QTimer::singleShot(delay, [table, elem1, elem2]{table->swapItemsText(0, elem1, 0, elem2);});

    delay += 500;

    QTimer::singleShot(delay, [table, elem1, elem2]{table->highlightItems(0, elem1, 0, elem2, Qt::white);});

    delay += 500;
}

