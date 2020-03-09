#include "searchoptionswindow.h"
#include "ui_searchoptionswindow.h"
#include <QDebug>
#include <QTimer>

searchOptionsWindow::searchOptionsWindow(QWidget *parent, bool demo) :
    QDialog(parent),
    ui(new Ui::searchOptionsWindow)
{
    ui->setupUi(this);
    rateCheckBox = ui->rateCheckBox;
    allCheckBox = ui->allCheckBox;
    stringCheckBox = ui->stringCheckBox;
    integerCheckBox = ui->integerCheckBox;
    timeCheckBox = ui->timeCheckBox;
    idCheckBox = ui->idCheckBox;
    numberCheckBox = ui->numberCheckBox;
    fromCheckBox = ui->fromCheckBox;
    toCheckBox = ui->toCheckBox;
    typeCheckBox = ui->typeCheckBox;
    depTimeCheckBox = ui->depTimeCheckBox;
    arrTimeCheckBox = ui->arrTimeCheckBox;


    qDebug("search options");

    if (demo) {
        qDebug("search options DEMO");

        QTimer::singleShot(1500, this, SLOT(selectFromField_delay()));
    }

}


searchOptionsWindow::~searchOptionsWindow()
{
    delete ui;
}

void searchOptionsWindow::uncheckCheckButtons(QCheckBox* caller = NULL)
{
    allCheckBox->setChecked(0);
    stringCheckBox->setChecked(0);
    integerCheckBox->setChecked(0);
    timeCheckBox->setChecked(0);
    idCheckBox->setChecked(0);
    numberCheckBox->setChecked(0);
    fromCheckBox->setChecked(0);
    toCheckBox->setChecked(0);
    typeCheckBox->setChecked(0);
    depTimeCheckBox->setChecked(0);
    arrTimeCheckBox->setChecked(0);
    rateCheckBox->setChecked(0);

    if (caller) caller->setChecked(1);
}

void searchOptionsWindow::trackCheckButtons()
{

    if (idCheckBox->isChecked() && numberCheckBox->isChecked() && rateCheckBox->isChecked()) integerCheckBox->setChecked(1);
    else integerCheckBox->setChecked(0);

    if (fromCheckBox->isChecked() && toCheckBox->isChecked() && typeCheckBox->isChecked()) stringCheckBox->setChecked(1);
    else stringCheckBox->setChecked(0);

    if (depTimeCheckBox->isChecked() && arrTimeCheckBox->isChecked()) timeCheckBox->setChecked(1);
    else timeCheckBox->setChecked(0);

    if ( (idCheckBox->isChecked() && numberCheckBox->isChecked() && fromCheckBox->isChecked() &&
            toCheckBox->isChecked() && typeCheckBox->isChecked() && depTimeCheckBox->isChecked() &&
                arrTimeCheckBox->isChecked() && rateCheckBox->isChecked() ) ||
            ( stringCheckBox->isChecked() && integerCheckBox->isChecked() && timeCheckBox->isChecked() )) {

        stringCheckBox->setChecked(0);
        integerCheckBox->setChecked(0);
        timeCheckBox->setChecked(0);

        allCheckBox->setChecked(1);

    } else {
        allCheckBox->setChecked(0);
        return;
    }




}

void searchOptionsWindow::on_applySearchOptionsButton_clicked()
{

    std::vector<bool> settings;


        settings.push_back(false);
        settings.push_back(idCheckBox->isChecked());
        settings.push_back(numberCheckBox->isChecked());
        settings.push_back(fromCheckBox->isChecked());
        settings.push_back(toCheckBox->isChecked());
        settings.push_back(typeCheckBox->isChecked());
        settings.push_back(depTimeCheckBox->isChecked());
        settings.push_back(arrTimeCheckBox->isChecked());
        settings.push_back(rateCheckBox->isChecked());

    emit searchSettingApplied(settings);

    qDebug() << "search emitted!" << settings[3];


    close();
}

void searchOptionsWindow::on_applySearchOptionsButton_2_clicked()
{
    close();
}

void searchOptionsWindow::on_allCheckBox_clicked()
{

    if (allCheckBox->isChecked()) {

        uncheckCheckButtons(allCheckBox);

        idCheckBox->setChecked(1);
        numberCheckBox->setChecked(1);
        fromCheckBox->setChecked(1);
        toCheckBox->setChecked(1);
        typeCheckBox->setChecked(1);
        depTimeCheckBox->setChecked(1);
        arrTimeCheckBox->setChecked(1);
        rateCheckBox->setChecked(1);

    } else uncheckCheckButtons();;


}

void searchOptionsWindow::on_stringCheckBox_clicked()
{
    if (stringCheckBox->isChecked()) {

        if (allCheckBox->isChecked()) {
            uncheckCheckButtons(stringCheckBox);
        }

        fromCheckBox->setChecked(1);
        toCheckBox->setChecked(1);
        typeCheckBox->setChecked(1);

        trackCheckButtons();

    } else {

        fromCheckBox->setChecked(0);
        toCheckBox->setChecked(0);
        typeCheckBox->setChecked(0);

    }

}

void searchOptionsWindow::on_integerCheckBox_clicked()
{
    if (integerCheckBox->isChecked()) {

        if (allCheckBox->isChecked()) {
            uncheckCheckButtons(integerCheckBox);
        }

        idCheckBox->setChecked(1);
        numberCheckBox->setChecked(1);
        rateCheckBox->setChecked(1);

        trackCheckButtons();

    } else {

        idCheckBox->setChecked(0);
        numberCheckBox->setChecked(0);
        rateCheckBox->setChecked(0);

    }
}

void searchOptionsWindow::on_timeCheckBox_clicked()
{
    if (timeCheckBox->isChecked()) {

        if (allCheckBox->isChecked()) {
            uncheckCheckButtons(timeCheckBox);
        }

        depTimeCheckBox->setChecked(1);
        arrTimeCheckBox->setChecked(1);

        trackCheckButtons();

    } else {

        depTimeCheckBox->setChecked(0);
        arrTimeCheckBox->setChecked(0);

    }
}


void searchOptionsWindow::on_idCheckBox_clicked()
{
    trackCheckButtons();
}

void searchOptionsWindow::on_numberCheckBox_clicked()
{
    trackCheckButtons();
}

void searchOptionsWindow::on_fromCheckBox_clicked()
{
    trackCheckButtons();
}

void searchOptionsWindow::on_toCheckBox_clicked()
{
    trackCheckButtons();
}

void searchOptionsWindow::on_typeCheckBox_clicked()
{
    trackCheckButtons();
}

void searchOptionsWindow::on_depTimeCheckBox_clicked()
{
    trackCheckButtons();
}

void searchOptionsWindow::on_arrTimeCheckBox_clicked()
{
    trackCheckButtons();
}

void searchOptionsWindow::on_rateCheckBox_clicked()
{
    trackCheckButtons();
}

void searchOptionsWindow::showSettings(std::vector<bool> settings)
{

    if (settings[1]) idCheckBox->setChecked(1);
    if (settings[2]) numberCheckBox->setChecked(1);
    if (settings[3]) fromCheckBox->setChecked(1);
    if (settings[4]) toCheckBox->setChecked(1);
    if (settings[5]) typeCheckBox->setChecked(1);
    if (settings[6]) depTimeCheckBox->setChecked(1);
    if (settings[7]) arrTimeCheckBox->setChecked(1);
    if (settings[8]) rateCheckBox->setChecked(1);

    trackCheckButtons();
}


void searchOptionsWindow::selectFromField_delay()
{
    uncheckCheckButtons(fromCheckBox);

    qDebug("select from delay");

    QTimer::singleShot(1500, this, SLOT(on_applySearchOptionsButton_clicked()));
}
