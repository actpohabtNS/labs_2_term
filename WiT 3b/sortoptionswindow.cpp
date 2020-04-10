#include "sortoptionswindow.h"
#include "ui_sortoptionswindow.h"
#include <QDebug>

sortoptionswindow::sortoptionswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sortoptionswindow)
{
    ui->setupUi(this);
}

sortoptionswindow::~sortoptionswindow()
{
    delete ui;
}

void sortoptionswindow::showSortingOptions(ushort sortingAlg, std::vector<QString> sortingSequence)
{
    m_sortingAlg = sortingAlg;
    m_sortingCompSequence = sortingSequence;

    switch (sortingAlg) {
    case 1:
        ui->comparisonRadio->setChecked(true);
        break;
    case 2:
        ui->countingRadio->setChecked(true);
        break;
    case 3:
        ui->radixRadio->setChecked(true);
        break;
    }

    vecToLabelText(ui->sortSequenceLabel, m_sortingCompSequence, " > ");
}

void sortoptionswindow::editSortingSequence(QString field, bool add)
{
    if (add)
    {
        if (field == "number" || field == "type")
        {
            m_sortingNonCompSequence.push_back(field);
        }

        m_sortingCompSequence.push_back(field);
    }
    else
    {
        eraseString(m_sortingCompSequence, field);
        eraseString(m_sortingNonCompSequence, field);
    }
}

void sortoptionswindow::checkApplySort()
{
    if ((m_sortingAlg == 1 && m_sortingCompSequence.size() != 0) ||
        ((m_sortingAlg == 2 || m_sortingAlg == 3) && m_sortingNonCompSequence.size() != 0))
        ui->applySortButton->setEnabled(true);
    else
        ui->applySortButton->setEnabled(false);
}

void sortoptionswindow::manageSortAlgType(ushort sortAlg)
{
    m_sortingAlg = sortAlg;

    if (sortAlg == 1)
    {
        setNonCompCheckBoxesEnabled(true);
        vecToLabelText(ui->sortSequenceLabel, m_sortingCompSequence, " > ");
    }
    else if (sortAlg == 2 || sortAlg == 3)
    {
        setNonCompCheckBoxesEnabled(false);
        vecToLabelText(ui->sortSequenceLabel, m_sortingNonCompSequence, " > ");
    }

    setSortAlgText(sortAlg);

    checkApplySort();
}

void sortoptionswindow::manageSortingField(QString field, bool add)
{
    editSortingSequence(field, add);

    if (m_sortingAlg == 2 || m_sortingAlg == 3)
    {
        vecToLabelText(ui->sortSequenceLabel, m_sortingNonCompSequence, " > ");
    }
    else
    {
        vecToLabelText(ui->sortSequenceLabel, m_sortingCompSequence, " > ");
    }

    checkApplySort();
}

void sortoptionswindow::setSortAlgText(ushort sortAlg)
{
    QString text = "";

    switch (sortAlg) {
    case 1:
        text = "Comparison sort:";
        break;
    case 2:
        text = "Counting sort:";
        break;
    case 3:
        text = "Radix sort:";
        break;
    }

    ui->sortTypeLabel->setText(text);
}

void sortoptionswindow::setNonCompCheckBoxesEnabled(bool enabled)
{
    ui->idCheckBox->setEnabled(enabled);
    ui->fromCheckBox->setEnabled(enabled);
    ui->toCheckBox->setEnabled(enabled);
    ui->arrTimeCheckBox->setEnabled(enabled);
    ui->depTimeCheckBox->setEnabled(enabled);
    ui->rateCheckBox->setEnabled(enabled);
}

void sortoptionswindow::vecToLabelText(QLabel* label, std::vector<QString> vec, QString delimeter)
{
    label->setText(vecToStr(vec, delimeter));
}

QString vecToStr(std::vector<QString> vec, QString delimeter)
{
    if (vec.size() == 0) return "";

    QString str = "";

    for (uint elem = 0; elem < vec.size()-1; elem++)
    {
        str += vec[elem] + delimeter;
    }

    str += vec[vec.size()-1];

    return str;
}

int findString(std::vector<QString> vec, QString string)
{
    int pos = -1;

    for (uint elem = 0; elem < vec.size(); elem++)
    {
        if (vec[elem] == string) pos = elem;
    }

    return pos;
}

void eraseString(std::vector<QString>& vec, QString string)
{
    int pos = findString(vec, string);

    if (pos == -1) return;

    vec.erase(vec.begin() + pos);
}

void sortoptionswindow::on_cancelButton_clicked()
{
    close();
}

void sortoptionswindow::on_comparisonRadio_clicked()
{
    manageSortAlgType(1);
}


void sortoptionswindow::on_countingRadio_clicked()
{
    manageSortAlgType(2);
}

void sortoptionswindow::on_radixRadio_clicked()
{
    manageSortAlgType(3);
}

void sortoptionswindow::on_idCheckBox_clicked(bool checked)
{
    manageSortingField("id", checked);
}

void sortoptionswindow::on_numberCheckBox_clicked(bool checked)
{
    manageSortingField("number", checked);
}

void sortoptionswindow::on_fromCheckBox_clicked(bool checked)
{
    manageSortingField("from", checked);
}

void sortoptionswindow::on_toCheckBox_clicked(bool checked)
{
    manageSortingField("to", checked);
}

void sortoptionswindow::on_arrTimeCheckBox_clicked(bool checked)
{
    manageSortingField("arrTime", checked);
}

void sortoptionswindow::on_depTimeCheckBox_clicked(bool checked)
{
    manageSortingField("depTime", checked);
}

void sortoptionswindow::on_typeCheckBox_clicked(bool checked)
{
    manageSortingField("type", checked);
}

void sortoptionswindow::on_rateCheckBox_clicked(bool checked)
{
    manageSortingField("rate", checked);
}

void sortoptionswindow::on_applySortButton_clicked()
{
    std::vector<QString>* sortingSequence;

    if (m_sortingAlg == 1)
        sortingSequence = &m_sortingCompSequence;
    else if (m_sortingAlg == 2 || m_sortingAlg == 3)
        sortingSequence = &m_sortingNonCompSequence;
    else sortingSequence = nullptr;

    emit sortingApplied(m_sortingAlg, *sortingSequence);
    close();
}
