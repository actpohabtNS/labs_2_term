#ifndef BENCHMARKWINDOW_H
#define BENCHMARKWINDOW_H

#include <QWidget>
#include "date.h"
#include "table.h"

namespace Ui {
class BenchmarkWindow;
}

class BenchmarkWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BenchmarkWindow(QWidget *parent = nullptr);
    ~BenchmarkWindow();

private:
    Ui::BenchmarkWindow *ui;

    Date* dateArray();
    QString sortionTypeQString();

    table* m_selectionTable;
    table* m_quickTable;
    table* m_mergeTable;
    table* m_hybridTable;
    table* m_libraryTable;

signals:
    void backButtonClicked();
private slots:
    void on_backButton_clicked();
    void on_testSelectionSortButton_clicked();
    void on_testQuickSortButton_clicked();
    void on_testMergeSortButton_clicked();
    void on_testHybridSortButton_clicked();
    void on_testLibrarySortButton_clicked();
    void on_testAllButton_clicked();
};

#endif // BENCHMARKWINDOW_H
