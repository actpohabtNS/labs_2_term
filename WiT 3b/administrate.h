#ifndef ADMINISTRATE_H
#define ADMINISTRATE_H
#include "addtrainwindow.h"
#include "sortoptionswindow.h"
#include "ui_administrate.h"
#include "train.h"
#include "table.h"
#include <QWidget>

namespace Ui {
class Administrate;
}

class Administrate : public QWidget
{
    Q_OBJECT

public:
    explicit Administrate(QWidget *parent = nullptr,  bool demo = false);
    ~Administrate();


private:
    Ui::Administrate *ui;
    addTrainWindow m_addTrainWindow;
    sortoptionswindow* m_sOW;
    std::vector<bool> m_searchSettings = {false, true, true, true, true, true, true, true, true};
    ushort m_sortingAlg = 0;                //0 - not set yet, 1 - comparison sort, 2 - counting sort, 3 - radix sort
    std::vector<QString> m_sortingSequence = {};
    std::vector<train> m_trains;
    std::vector<train> m_trains_bin;
    std::vector<train> m_trains_arr;

    bool m_demoMode = false;

signals:
    void backButtonClicked();

private slots:
    void on_pushButton_1_clicked();
    void on_optionsButton_clicked();
    void on_addTrainButton_clicked();
    void on_addTrainButton_clicked_delay();
    void on_searchField_returnPressed();
    void on_clearSearchButton_clicked();
    void on_trainAdded(train newTrain);
    void saveSettings(std::vector<bool> settings);
    void changeSearchField(QString newRequest);
    void sort(ushort sortingAlg, std::vector<QString> sortingSequence);
    void on_trainTable_itemSelectionChanged();
    void on_removeTrainButton_clicked(bool demo = false);
    void on_trainEditButton_clicked();
    void on_trainEdited(train newTrain);
    void on_textFileButton_clicked(bool checked);
    void on_arrayButton_clicked(bool checked);
    void on_searchField_textChanged(QString);

    void searchFieldWrite_delay();
    void makeSearchRequest_delay();
    void on_optionsButton_clicked_delay();
    void selectRow_delay();
    void on_trainEditButton_clicked_delay();
    void on_removeTrainButton_clicked_delay();
    void on_sortingButton_clicked();
};

#endif // ADMINISTRATE_H
