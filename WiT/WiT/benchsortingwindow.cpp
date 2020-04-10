#include "benchsortingwindow.h"
#include "ui_benchsortingwindow.h"
#include "benchmark.h"

BenchSortingWindow::BenchSortingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BenchSortingWindow)
{
    ui->setupUi(this);
    _comparisonTable = new table(ui->comparisonTable);
    _comparisonTable->setSize(0, 50, {79, 280, 79}, {});

    _countingTable = new table(ui->countingTable);
    _countingTable->setSize(0, 50, {79, 280, 79}, {});

    _radixTable = new table(ui->radixTable);
    _radixTable->setSize(0, 50, {79, 280, 79}, {});
}

BenchSortingWindow::~BenchSortingWindow()
{
    delete ui;
}

void BenchSortingWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}

void BenchSortingWindow::on_benchAllButton_clicked()
{
    int size = ui->sortingArrSizeCounter->value();
    _trains = randomize(size);
    std::vector<train> trains(size);
    std::copy(_trains->begin(), _trains->end(), trains.begin());

    std::vector<train> temp(size);

    std::vector<QString> sortingSequence = getSortingSequence();
    QString sortingSeqStr = getSortingSequenceStr();

    _comparisonTable->insertDataRow({QString::number(size), sortingSeqStr, QString::number(benchSortingBySeq("comparison", sortingSequence, trains, temp))}, 0);

    std::copy(_trains->begin(), _trains->end(), trains.begin());

    _countingTable->insertDataRow({QString::number(size), sortingSeqStr, QString::number(benchSortingBySeq("counting", sortingSequence, trains, temp))}, 0);

    std::copy(_trains->begin(), _trains->end(), trains.begin());

    _radixTable->insertDataRow({QString::number(size), sortingSeqStr, QString::number(benchSortingBySeq("radix", sortingSequence, trains, temp))}, 0);
}

std::vector<QString> BenchSortingWindow::getSortingSequence()
{
    std::vector<QString> res;

    if (ui->typeRadio->isChecked())
        res.push_back("type");
    else if(ui->numberRadio->isChecked())
        res.push_back("number");
    else if (ui->numberTypeRadio->isChecked())
    {
        res.push_back("number");
        res.push_back("type");
    }
    else if (ui->typeNumberRadio->isChecked())
    {
        res.push_back("type");
        res.push_back("number");
    }

    return res;
}

QString BenchSortingWindow::getSortingSequenceStr()
{
    if (ui->typeRadio->isChecked())
        return "type";
    else if(ui->numberRadio->isChecked())
        return "number";
    else if (ui->numberTypeRadio->isChecked())
        return "number > type";
    else if (ui->typeNumberRadio->isChecked())
        return "type > number";
    else return "";
}

void BenchSortingWindow::on_comparisonButton_clicked()
{

}
