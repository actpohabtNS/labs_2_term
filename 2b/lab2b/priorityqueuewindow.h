#ifndef PRIORITYQUEUEWINDOW_H
#define PRIORITYQUEUEWINDOW_H

#include <QWidget>
#include "priorityqueue.h"

namespace Ui {
class PriorityQueueWindow;
}

class PriorityQueueWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PriorityQueueWindow(QWidget *parent = nullptr);
    ~PriorityQueueWindow();

private slots:
    void on_backButton_clicked();

    void on_loadStationDeepButton_clicked();

    void on_loadStationShallowButton_clicked();

    void on_loadTunnelDeepButton_clicked();

    void on_loadTunnelShallowButton_clicked();

    void on_addTaskListButton_clicked();

    void on_addTaskButton_clicked();

    void on_removeTaskButton_clicked();

    void on_addRandomEventButton_clicked();

    void on_demoButton_clicked();

    void setTaskButtonsEnabled(bool enabled);

    void enableRandomEvents();

private:
    Ui::PriorityQueueWindow *ui;

    PriorityQueue<QString> m_prQ;

    std::vector<Task*> m_randomEvents;

signals:
    void backButtonClicked();
};

#endif // PRIORITYQUEUEWINDOW_H
