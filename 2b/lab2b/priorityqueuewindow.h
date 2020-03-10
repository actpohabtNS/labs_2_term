#ifndef PRIORITYQUEUEWINDOW_H
#define PRIORITYQUEUEWINDOW_H

#include <QWidget>

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

private:
    Ui::PriorityQueueWindow *ui;

signals:
    void backButtonClicked();
};

#endif // PRIORITYQUEUEWINDOW_H
