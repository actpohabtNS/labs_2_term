#include "benchwindow.h"
#include "ui_benchwindow.h"

BenchWindow::BenchWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BenchWindow)
{
    ui->setupUi(this);
}

BenchWindow::~BenchWindow()
{
    delete ui;
}

void BenchWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}
