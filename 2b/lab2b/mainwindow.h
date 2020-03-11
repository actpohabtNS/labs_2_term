#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "priorityqueuewindow.h"
#include "multilevelqueuewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_priorityQueueButton_clicked();

    void on_multilevelQueueButton_clicked();

    void on_exitButton_clicked();

    void toMainMenu();

private:
    Ui::MainWindow *ui;
    PriorityQueueWindow prQW;
    MultilevelQueueWindow mlQW;
};
#endif // MAINWINDOW_H
