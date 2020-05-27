#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graphswindow.h"
#include "benchwindow.h"

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

    void on_graphsButton_clicked();

    void on_benchmarkButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    GraphsWindow _GW;
    BenchWindow _BW;
};
#endif // MAINWINDOW_H
