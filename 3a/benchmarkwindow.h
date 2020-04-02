#ifndef BENCHMARKWINDOW_H
#define BENCHMARKWINDOW_H

#include <QWidget>

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

signals:
    void backButtonClicked();
private slots:
    void on_backButton_clicked();
};

#endif // BENCHMARKWINDOW_H
