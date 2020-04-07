#ifndef SORTOPTIONSWINDOW_H
#define SORTOPTIONSWINDOW_H

#include <QDialog>
#include <QLabel>

namespace Ui {
class sortoptionswindow;
}

class sortoptionswindow : public QDialog
{
    Q_OBJECT

public:
    explicit sortoptionswindow(QWidget *parent = nullptr);
    ~sortoptionswindow();

    void showSortingOptions(ushort sortingAlg, std::vector<QString> sortingSequence);

signals:
    void sortingApplied(ushort sortingAlg, std::vector<QString> sortingSequence);

private slots:
    void on_cancelButton_clicked();

    void on_comparisonRadio_clicked();

    void on_countingRadio_clicked();

    void on_radixRadio_clicked();

    void on_idCheckBox_clicked(bool checked);

    void on_arrTimeCheckBox_clicked(bool checked);

    void on_numberCheckBox_clicked(bool checked);

    void on_fromCheckBox_clicked(bool checked);

    void on_toCheckBox_clicked(bool checked);

    void on_depTimeCheckBox_clicked(bool checked);

    void on_typeCheckBox_clicked(bool checked);

    void on_rateCheckBox_clicked(bool checked);

    void on_applySortButton_clicked();

private:
    Ui::sortoptionswindow *ui;
    ushort m_sortingAlg = 0;
    std::vector<QString> m_sortingNonCompSequence = {};
    std::vector<QString> m_sortingCompSequence = {};

    void editSortingSequence(QString field, bool add = true);
    void checkApplySort();
    void manageSortAlgType(ushort sortAlg);
    void manageSortingField(QString field, bool add);
    void setSortAlgText(ushort sortAlg);
    void setNonCompCheckBoxesEnabled(bool enabled);
    void vecToLabelText(QLabel* label, std::vector<QString> vec, QString delimeter);
};

int findString(std::vector<QString> vec, QString string);
QString vecToStr(std::vector<QString> vec, QString delimeter = "");
void eraseString(std::vector<QString>& vec, QString string);

#endif // SORTOPTIONSWINDOW_H
