#ifndef DEMOWINDOW_H
#define DEMOWINDOW_H

#include <QWidget>
#include "table.h"

namespace Ui {
class DemoWindow;
}

class DemoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DemoWindow(QWidget *parent = nullptr);
    ~DemoWindow();

    Date* m_arr;
    int m_arr_size;
    void setRunButtonsEnabled(bool enabled);

private:
    Ui::DemoWindow *ui;
    table* m_selectionTable;
    table* m_quickTable;
    table* m_mergeTable;
    table* m_hybridTable;
    table* m_libraryTable;
    table* m_combTable;
    table* m_gnomeTable;
    table* m_shakerTable;
    table* m_oddEvenTable;
    table* m_heapTable;

    Date* dateArray();

signals:
    void backButtonClicked();

private slots:
    void on_backButton_clicked();
    void on_generateAllButton_clicked();
    void on_runSelectionButton_clicked();
    void on_runQuickButton_clicked();
    void on_runMergeButton_clicked();
    void on_runHybridButton_clicked();
    void on_runLibraryButton_clicked();
    void on_runAllButton_clicked();
    void on_runShakerButton_clicked();
    void on_runHeapButton_clicked();
    void on_runGnomeButton_clicked();
    void on_runCombButton_clicked();
    void on_runOddEvenButton_clicked();
};

#endif // DEMOWINDOW_H
