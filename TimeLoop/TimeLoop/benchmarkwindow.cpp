#include "benchmarkwindow.h"
#include "ui_benchmarkwindow.h"
#include "vectcircularlinkedlist.h"
#include "arrcilcularlinkedlist.h"
#include "table.h"
#include "benchmark.h"
#include <QtDebug>

benchmarkWindow::benchmarkWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::benchmarkWindow)
{
    ui->setupUi(this);

   table arrayTable(ui->arrayTable);
   arrayTable.setSize(0, 40, {60, 60, 60, 50, 50, 50, 50, 60});

   table vectorTable(ui->vectorTable);
   vectorTable.setSize(0, 40, {60, 60, 60, 50, 50, 50, 50, 60});

   table specStructTable(ui->specStructTable);
   specStructTable.setSize(0, 40, {60, 60, 60, 50, 50, 50, 50, 60});

}

benchmarkWindow::~benchmarkWindow()
{
    delete ui;
}


void benchmarkWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}


void benchmarkWindow::on_testArrayButton_clicked()
{
    int n = ui->NCounter->value();
    int startN = ui->startNCounter->value();

    loadBenchResults<arrCilcularLinkedList>(n, startN, ui->arrayTable);
}

void benchmarkWindow::on_testVectorButton_clicked()
{
    int n = ui->NCounter->value();
    int startN = ui->startNCounter->value();

    loadBenchResults<vectCircularLinkedList>(n, startN, ui->vectorTable);
}

void benchmarkWindow::on_testSpecStructButton_clicked()
{
    int n = ui->NCounter->value();
    int startN = ui->startNCounter->value();

    loadBenchResults<CircularLinkedList>(n, startN, ui->specStructTable);
}

void benchmarkWindow::on_testAllButton_clicked()
{
    int n = ui->NCounter->value();
    int startN = ui->startNCounter->value();

    loadBenchResults<arrCilcularLinkedList>(n, startN, ui->arrayTable);

    loadBenchResults<vectCircularLinkedList>(n, startN, ui->vectorTable);

    loadBenchResults<CircularLinkedList>(n, startN, ui->specStructTable);
}
