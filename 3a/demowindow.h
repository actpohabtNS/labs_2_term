#ifndef DEMOWINDOW_H
#define DEMOWINDOW_H

#include <QWidget>

namespace Ui {
class DemoWindow;
}

class DemoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DemoWindow(QWidget *parent = nullptr);
    ~DemoWindow();

private:
    Ui::DemoWindow *ui;

signals:
    void backButtonClicked();

private slots:
    void on_backButton_clicked();
};

#endif // DEMOWINDOW_H
