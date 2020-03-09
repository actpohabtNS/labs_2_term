#ifndef ADDTRAINWINDOW_H
#define ADDTRAINWINDOW_H

#include "train.h"
#include <QDialog>

namespace Ui {
class addTrainWindow;
}

class addTrainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addTrainWindow(QWidget *parent = nullptr, QString mode = "add", bool test = false);
    ~addTrainWindow();


    void showTrainData(train train);
    void setTrain(train train);

signals:
    void trainAdded(train newTrain);
    void trainEdited(train newTrain);

private slots:
    void on_applyAddTrainButton_clicked();

    void on_cancelButton_clicked();

    void showTrain_delay();

    void changeTrainTo_delay();

private:
    Ui::addTrainWindow *ui;

    QString m_mode;
    train m_train;

    train getTrainFromForm(int id = 0);
};

#endif // ADDTRAINWINDOW_H
