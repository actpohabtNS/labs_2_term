#ifndef MULTILEVELQUEUEWINDOW_H
#define MULTILEVELQUEUEWINDOW_H

#include <QWidget>
#include "functs.h"
#include "table.h"

namespace Ui {
class MultilevelQueueWindow;
}

class MultilevelQueueWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MultilevelQueueWindow(QWidget *parent = nullptr);
    ~MultilevelQueueWindow();

private:
    Ui::MultilevelQueueWindow *ui;

    void takeTaskSetEnabled(bool enabled);
    void clearWorkersTasks();
    void enableRandomEvents();

    QString m_fromSt = "";
    QString m_toSt = "";
    std::vector<Station> m_stations;
    std::vector<Task*> m_randomEvents;

    table* m_table;
    MultilevelQueue<QString> m_mlQ;

signals:
    void backButtonClicked();
private slots:
    void on_backButton_clicked();
    void on_trainLineTable_itemSelectionChanged();
    void on_worker1_takeTaskButton_clicked();
    void on_worker2_takeTaskButton_clicked();
    void on_addRandomEventButton_clicked();
    void on_addTaskListButton_clicked();
    void on_addTaskButton_clicked();
    void on_demoButton_clicked();
};

#endif // MULTILEVELQUEUEWINDOW_H
