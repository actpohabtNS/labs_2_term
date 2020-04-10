#ifndef BENCHSORTINGWINDOW_H
#define BENCHSORTINGWINDOW_H
#include "table.h"
#include <QWidget>

namespace Ui {
class BenchSortingWindow;
}

class BenchSortingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BenchSortingWindow(QWidget *parent = nullptr);
    ~BenchSortingWindow();
    table* _comparisonTable;
    table* _countingTable;
    table* _radixTable;
    std::vector<train>* _trains;

signals:
    void backButtonClicked();

private slots:
    void on_backButton_clicked();
    void on_benchAllButton_clicked();

    void on_comparisonButton_clicked();

private:
    Ui::BenchSortingWindow *ui;
    std::vector<QString> getSortingSequence();
    QString getSortingSequenceStr();
};

#endif // BENCHSORTINGWINDOW_H
