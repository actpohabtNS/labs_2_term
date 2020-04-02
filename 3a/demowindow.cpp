#include "demowindow.h"
#include "ui_demowindow.h"

DemoWindow::DemoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DemoWindow)
{
    ui->setupUi(this);
}

DemoWindow::~DemoWindow()
{
    delete ui;
}

void DemoWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}
