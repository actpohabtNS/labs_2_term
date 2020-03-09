#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QStackedWidget>
#include <administrate.h>
#include <demo.h>
#include <tests.h>

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
    Administrate administrateWindow;
    Demo demoWindow;
    Tests testsWindow;

private slots:
    void on_administrateButton_clicked();
    void on_demoButton_clicked();
    void on_testsButton_clicked();
    void on_exitButton_clicked();
    void toMainMenu();
};
#endif // MAINWINDOW_H
