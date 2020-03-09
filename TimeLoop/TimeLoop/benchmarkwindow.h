#ifndef BENCHMARKWINDOW_H
#define BENCHMARKWINDOW_H

#include "table.h"
#include "ui_benchmarkwindow.h"
#include "benchmark.h"
#include <QWidget>

namespace Ui {
class benchmarkWindow;
}

class benchmarkWindow : public QWidget
{
    Q_OBJECT

public:
    explicit benchmarkWindow(QWidget *parent = nullptr);
    ~benchmarkWindow();

private:
    Ui::benchmarkWindow *ui;

    template<typename T> void loadBenchResults(int N, int startN, QTableWidget* table) {

        auto res = benchmarkCLL<T>(startN, N);

        int vectorRows = table->rowCount();

        if (vectorRows >= 13) table->setColumnWidth(0, 45);

        table->insertRow(vectorRows);

        QTableWidgetItem * item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignCenter);
        item->setText(QString::number(N));
        table->setItem(vectorRows, 0, item);

        QTableWidgetItem * newItem = item->clone();
        newItem->setText(QString::number(startN));
        table->setItem(vectorRows, 1, newItem);

        for (unsigned int i = 2; i < res.size()+2; i++) {

            QTableWidgetItem * newItem = item->clone();
            newItem->setText(QString::number(res[i-2]));
            table->setItem(vectorRows, i, newItem);

        }

    }

signals:
    void backButtonClicked();
private slots:
    void on_backButton_clicked();
    void on_testArrayButton_clicked();
    void on_testVectorButton_clicked();
    void on_testSpecStructButton_clicked();
    void on_testAllButton_clicked();
};

#endif // BENCHMARKWINDOW_H
