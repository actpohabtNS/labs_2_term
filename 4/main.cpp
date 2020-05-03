#include "mainwindow.h"

#include <QApplication>

/*
 * Variant: 1, 2, 3, _(8,9), 11, 12, 13, 15, 18, 20, 26
 *
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
