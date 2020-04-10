#ifndef TESTS_H
#define TESTS_H

#include <QWidget>

namespace Ui {
class Tests;
}

class Tests : public QWidget
{
    Q_OBJECT

public:
    explicit Tests(QWidget *parent = nullptr);
    ~Tests();

private:
    Ui::Tests *ui;

    void testVector();

    void testTextfile();

    void testBinfile();

signals:
    void backButtonClicked();
private slots:
    void on_pushButton_3_clicked();
    void on_testAllButton_clicked();
    void on_testVectorButton_clicked();
    void on_testTextFileButton_clicked();
    void on_testBinaryFileButton_clicked();
};

#endif // TESTS_H
