#include "tests.h"
#include "ui_tests.h"
#include "table.h"
#include "benchmark.h"

Tests::Tests(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tests)
{
    ui->setupUi(this);

    table vectorTable(ui->vectorTable);
    vectorTable.setSize(0, 40, {80, 90, 90, 90, 90});

    table textfileTable(ui->textFileTable);
    textfileTable.setSize(0, 40, {80, 70, 70, 70, 70, 80});

    table binfileTable(ui->binaryFileTable);
    binfileTable.setSize(0, 40, {80, 70, 70, 70, 70, 80});



}

Tests::~Tests()
{
    delete ui;
}

void Tests::testVector()
{
    int n = ui->NCounter->value();

    auto vectorRes = benchmarkVector(n);

    QTableWidget* vectorTable = ui->vectorTable;
    int vectorRows = vectorTable->rowCount();

    if (vectorRows >= 13) vectorTable->setColumnWidth(0, 59);

    vectorTable->insertRow(vectorRows);

    QTableWidgetItem * item = new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::number(n));
    vectorTable->setItem(vectorRows, 0, item);

    for (unsigned int i = 1; i < vectorRes.size()+1; i++) {

        QTableWidgetItem * newItem = item->clone();
        newItem->setText(QString::number(vectorRes[i-1]));
        vectorTable->setItem(vectorRows, i, newItem);

    }
}

void Tests::testTextfile()
{
    int n = ui->NCounter->value();

    auto vectorRes = benchmarkTextFile(n);


    QTableWidget* textfileTable = ui->textFileTable;
    int vectorRows = textfileTable->rowCount();

    if (vectorRows >= 13) textfileTable->setColumnWidth(0, 59);

    textfileTable->insertRow(vectorRows);

    QTableWidgetItem * item = new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::number(n));
    textfileTable->setItem(vectorRows, 0, item);

    for (unsigned int i = 1; i < vectorRes.size()+1; i++) {

        QTableWidgetItem * newItem = item->clone();
        newItem->setText(QString::number(vectorRes[i-1]));
        textfileTable->setItem(vectorRows, i, newItem);

    }
}

void Tests::testBinfile()
{
    int n = ui->NCounter->value();

    auto vectorRes = benchmarkBinFile(n);


    QTableWidget* binfileTable = ui->binaryFileTable;
    int vectorRows = binfileTable->rowCount();

    if (vectorRows >= 13) binfileTable->setColumnWidth(0, 59);

    binfileTable->insertRow(vectorRows);

    QTableWidgetItem * item = new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::number(n));
    binfileTable->setItem(vectorRows, 0, item);

    for (unsigned int i = 1; i < vectorRes.size()+1; i++) {

        QTableWidgetItem * newItem = item->clone();
        newItem->setText(QString::number(vectorRes[i-1]));
        binfileTable->setItem(vectorRows, i, newItem);

    }
}

void Tests::on_pushButton_3_clicked()
{
    emit backButtonClicked();
}

void Tests::on_testAllButton_clicked()
{

    testVector();

    testTextfile();

    testBinfile();

}

void Tests::on_testVectorButton_clicked()
{
    testVector();
}

void Tests::on_testTextFileButton_clicked()
{
    testTextfile();
}

void Tests::on_testBinaryFileButton_clicked()
{
    testBinfile();
}
