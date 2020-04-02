#include "benchmarkwindow.h"
#include "ui_benchmarkwindow.h"

BenchmarkWindow::BenchmarkWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BenchmarkWindow)
{
    ui->setupUi(this);
}

BenchmarkWindow::~BenchmarkWindow()
{
    delete ui;
}

void BenchmarkWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}
