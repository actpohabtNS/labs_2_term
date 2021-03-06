#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "interactwindow.h"
#include "benchmarkwindow.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    interactWindow iW;
    benchmarkWindow dW;
    benchmarkWindow bW;


private slots:
    void on_interactButton_clicked();
    void on_demoButton_clicked();
    void on_benchmarkButton_clicked();
    void on_exitButton_clicked();
    void toMainMenu();
};
#endif // MAINWINDOW_H
