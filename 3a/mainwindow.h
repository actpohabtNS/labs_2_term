#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "benchmarkwindow.h"
#include "demowindow.h"

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
    void toMainMenu();

    void on_demoButton_clicked();

    void on_benchmarkButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    DemoWindow DW;
    BenchmarkWindow BW;

};
#endif // MAINWINDOW_H
