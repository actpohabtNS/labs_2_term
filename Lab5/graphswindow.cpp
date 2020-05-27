#include "graphswindow.h"
#include "ui_graphswindow.h"

GraphsWindow::GraphsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphsWindow)
{
    ui->setupUi(this);
}

GraphsWindow::~GraphsWindow()
{
    delete ui;
}

void GraphsWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}
