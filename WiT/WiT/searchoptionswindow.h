#ifndef SEARCHOPTIONSWINDOW_H
#define SEARCHOPTIONSWINDOW_H

#include <QDialog>
#include "ui_searchoptionswindow.h"

const std::vector<bool> ALL_SEARCH_OPTIONS = {false, true, true, true, true, true, true, true, true};

namespace Ui {
class searchOptionsWindow;
}

class searchOptionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit searchOptionsWindow(QWidget *parent = nullptr, bool demo = false);
    ~searchOptionsWindow();

    void uncheckCheckButtons(QCheckBox* caller);
    void trackCheckButtons();
    void showSettings(std::vector<bool> settings);

signals:
    void searchSettingApplied(std::vector<bool> settings);
    void changeSearchField(QString newRequest);

private slots:
    void on_applySearchOptionsButton_clicked();

    void on_applySearchOptionsButton_2_clicked();

    void on_allCheckBox_clicked();

    void on_stringCheckBox_clicked();

    void on_integerCheckBox_clicked();

    void on_timeCheckBox_clicked();

    void on_idCheckBox_clicked();

    void on_numberCheckBox_clicked();

    void on_fromCheckBox_clicked();

    void on_toCheckBox_clicked();

    void on_typeCheckBox_clicked();

    void on_depTimeCheckBox_clicked();

    void on_arrTimeCheckBox_clicked();

    void on_rateCheckBox_clicked();

    void selectFromField_delay();


private:
    Ui::searchOptionsWindow *ui;
    QCheckBox* allCheckBox;
    QCheckBox* stringCheckBox;
    QCheckBox* integerCheckBox;
    QCheckBox* timeCheckBox;
    QCheckBox* idCheckBox;
    QCheckBox* numberCheckBox;
    QCheckBox* fromCheckBox;
    QCheckBox* toCheckBox;
    QCheckBox* typeCheckBox;
    QCheckBox* depTimeCheckBox;
    QCheckBox* arrTimeCheckBox;
    QCheckBox* rateCheckBox;

};


#endif // SEARCHOPTIONSWINDOW_H
