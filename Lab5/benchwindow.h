#ifndef BENCHWINDOW_H
#define BENCHWINDOW_H

#include <QWidget>

namespace Ui {
class BenchWindow;
}

class BenchWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BenchWindow(QWidget *parent = nullptr);
    ~BenchWindow();

signals:
    void backButtonClicked();

private slots:
    void on_backButton_clicked();

private:
    Ui::BenchWindow *ui;
};

#endif // BENCHWINDOW_H
