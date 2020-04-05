#include "demowindow.h"
#include "ui_demowindow.h"
#include "sorting.h"
#include <QTimer>

DemoWindow::DemoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DemoWindow)
{
    ui->setupUi(this);

    m_selectionTable = new table(ui->selectionTable, ui->selectionTable->height(), 1);
    m_quickTable = new table(ui->quickTable, ui->quickTable->height(), 1);
    m_mergeTable = new table(ui->mergeTable, ui->mergeTable->height(), 1);
    m_hybridTable = new table(ui->hybridTable, ui->hybridTable->height(), 1);
    m_libraryTable = new table(ui->libraryTable, ui->libraryTable->height(), 1);

//    int delay = 2000;
//    QTableWidget* table = ui->selectionTable;
//    int elem1 = 5;

//    QTimer::singleShot(delay, [table, elem1]{table->item(0, elem1)->setText("TEST");});

}

DemoWindow::~DemoWindow()
{
    delete ui;
}

Date* DemoWindow::dateArray()
{
    int size = ui->arrSizeCounter->value();

    if(ui->randomRadio->isChecked()) return randomDateArray(size);
    if(ui->ascendingRadio->isChecked()) return almostSortedDateArray(size);
    if(ui->descendingRadio->isChecked()) return almostSortedDateArray(size, false);

    return sortedDateArray(size, true);
}

void DemoWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}

void DemoWindow::on_generateAllButton_clicked()
{
    m_arr = dateArray();
    m_arr_size = ui->arrSizeCounter->value();
    Date* arr = new Date[m_arr_size];
    int delay = 500;

    m_selectionTable->setDateArray(m_arr, m_arr_size);

    qDebug() << "before sort" << m_arr_size-1;
    selectionSort(m_arr, 0, m_arr_size-1, true, m_selectionTable, &delay);

    for (int i = 0; i < m_arr_size; i++)
    {
        qDebug() << m_arr[i];
    }
}
