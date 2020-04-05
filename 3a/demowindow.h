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

private:
    Ui::DemoWindow *ui;
    table* m_selectionTable;
    table* m_quickTable;
    table* m_mergeTable;
    table* m_hybridTable;
    table* m_libraryTable;

    Date* dateArray();

signals:
    void backButtonClicked();

private slots:
    void on_backButton_clicked();
    void on_generateAllButton_clicked();
};

#endif // DEMOWINDOW_H
