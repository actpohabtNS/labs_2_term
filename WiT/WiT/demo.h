#ifndef DEMO_H
#define DEMO_H

#include <QWidget>

namespace Ui {
class Demo;
}

class Demo : public QWidget
{
    Q_OBJECT

public:
    explicit Demo(QWidget *parent = nullptr);
    ~Demo();

private:
    Ui::Demo *ui;

signals:
    void backButtonClicked();
private slots:
    void on_pushButton_2_clicked();
};

#endif // DEMO_H
