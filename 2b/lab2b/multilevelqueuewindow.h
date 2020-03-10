#ifndef MULTILEVELQUEUEWINDOW_H
#define MULTILEVELQUEUEWINDOW_H

#include <QWidget>

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

signals:
    void backButtonClicked();
private slots:
    void on_backButton_clicked();
};

#endif // MULTILEVELQUEUEWINDOW_H
