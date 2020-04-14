#include "benchmarkwindow.h"
#include "ui_benchmarkwindow.h"
#include "benchmark.h"
#include "sorting.h"

BenchmarkWindow::BenchmarkWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BenchmarkWindow)
{
    ui->setupUi(this);

    m_selectionTable = new table(ui->selectionTable);
    m_selectionTable->setSize(0, 50, {90, 80, 89}, {"N", "Pre-sort", "Time"});

    m_quickTable = new table(ui->quickTable);
    m_quickTable->setSize(0, 50, {90, 80, 89}, {"N", "Pre-sort", "Time"});

    m_mergeTable = new table(ui->mergeTable);
    m_mergeTable->setSize(0, 50, {90, 80, 89}, {"N", "Pre-sort", "Time"});

    m_hybridTable = new table(ui->hybridTable);
    m_hybridTable->setSize(0, 50, {64, 65, 65, 64}, {"N", "Step", "Pre-sort", "Time"});

    m_libraryTable = new table(ui->libraryTable);
    m_libraryTable->setSize(0, 50, {90, 80, 89}, {"N", "Pre-sort", "Time"});

    m_shakerTable = new table(ui->shakerTable);
    m_shakerTable->setSize(0, 50, {90, 80, 89}, {"N", "Pre-sort", "Time"});

    m_heapTable = new table(ui->heapTable);
    m_heapTable->setSize(0, 50, {90, 80, 89}, {"N", "Pre-sort", "Time"});

    m_binaryTreeTable = new table(ui->binaryTreeTable);
    m_binaryTreeTable->setSize(0, 50, {90, 80, 89}, {"N", "Pre-sort", "Time"});
}

BenchmarkWindow::~BenchmarkWindow()
{
    delete ui;
}

Date *BenchmarkWindow::dateArray()
{
    int size = ui->arrSizeCounter->value();

    if(ui->randomRadio->isChecked()) return randomDateArray(size);
    if(ui->ascendingRadio->isChecked()) return almostSortedDateArray(size);
    if(ui->descendingRadio->isChecked()) return almostSortedDateArray(size, false);

    return sortedDateArray(size, true);
}

QString BenchmarkWindow::sortionTypeQString()
{
    if(ui->randomRadio->isChecked()) return "Ran";
    if(ui->ascendingRadio->isChecked()) return "Asc";
    if(ui->descendingRadio->isChecked()) return "Des";

    return "Error";
}

void BenchmarkWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}

void BenchmarkWindow::on_testSelectionSortButton_clicked()
{
    Date* arr = dateArray();

    std::queue<visualization>* visuals = nullptr;

    int size = ui->arrSizeCounter->value();
    QString sortionType = sortionTypeQString();
    auto time = benchSortAlg(selectionSort, arr, 0, size-1, false, visuals);

    m_selectionTable->insertDataRow({QString::number(size), sortionType, QString::number(time)}, m_selectionTable->rowCount());
}

void BenchmarkWindow::on_testQuickSortButton_clicked()
{
    Date* arr = dateArray();

    std::queue<visualization>* visuals = nullptr;

    int size = ui->arrSizeCounter->value();
    QString sortionType = sortionTypeQString();
    auto time = benchSortAlg(quicksort, arr, 0, size-1, false, visuals);

    m_quickTable->insertDataRow({QString::number(size), sortionType, QString::number(time)}, m_quickTable->rowCount());
}

void BenchmarkWindow::on_testMergeSortButton_clicked()
{
    Date* arr = dateArray();

    std::queue<visualization>* visuals = nullptr;

    int size = ui->arrSizeCounter->value();
    QString sortionType = sortionTypeQString();

    Date* temp = new Date[size];

    auto time = benchSortAlg(mergesort, temp, arr, size, false, visuals);

    m_mergeTable->insertDataRow({QString::number(size), sortionType, QString::number(time)}, m_mergeTable->rowCount());
}

void BenchmarkWindow::on_testHybridSortButton_clicked()
{
    Date* arr = dateArray();

    std::queue<visualization>* visuals = nullptr;

    int size = ui->arrSizeCounter->value();
    int step = ui->stepCounter->value();
    QString sortionType = sortionTypeQString();
    auto time = benchSortAlg(hybridQuicksort, arr, 0, size-1, step, false, visuals);

    m_hybridTable->insertDataRow({QString::number(size), QString::number(step), sortionType, QString::number(time)}, m_hybridTable->rowCount());
}

void BenchmarkWindow::on_testLibrarySortButton_clicked()
{
    Date* arr = dateArray();

    int size = ui->arrSizeCounter->value();
    QString sortionType = sortionTypeQString();
    auto time = benchSortAlg(std::sort, &arr[0], &arr[size-1]);

    m_libraryTable->insertDataRow({QString::number(size), sortionType, QString::number(time)}, m_libraryTable->rowCount());
}

void BenchmarkWindow::on_testShakerSortButton_clicked()
{
    Date* arr = dateArray();

    std::queue<visualization>* visuals = nullptr;

    int size = ui->arrSizeCounter->value();
    QString sortionType = sortionTypeQString();
    auto time = benchSortAlg(shakerSort, arr, size, false, visuals);

    m_shakerTable->insertDataRow({QString::number(size), sortionType, QString::number(time)}, m_shakerTable->rowCount());
}

void BenchmarkWindow::on_testHeapSortButton_clicked()
{
    Date* arr = dateArray();

    std::queue<visualization>* visuals = nullptr;

    int size = ui->arrSizeCounter->value();
    QString sortionType = sortionTypeQString();
    auto time = benchSortAlg(heapSort, arr, size, false, visuals);

    m_heapTable->insertDataRow({QString::number(size), sortionType, QString::number(time)}, m_heapTable->rowCount());
}

void BenchmarkWindow::on_testBinaryTreeSortButton_clicked()
{
    Date* arr = dateArray();

    int size = ui->arrSizeCounter->value();
    QString sortionType = sortionTypeQString();
    auto time = benchSortAlg(binaryTreeSort, arr, size);

    m_binaryTreeTable->insertDataRow({QString::number(size), sortionType, QString::number(time)}, m_binaryTreeTable->rowCount());
}

void BenchmarkWindow::on_testAllButton_clicked()
{
    m_arr = dateArray();

    std::queue<visualization>* visuals = nullptr;

    int size = ui->arrSizeCounter->value();
    m_arr_size = size;
    int step = ui->stepCounter->value();
    QString sortionType = sortionTypeQString();

    Date* arr = new Date[size];
    std::copy(m_arr, m_arr + size, arr);

    auto time = benchSortAlg(selectionSort, arr, 0, size-1, false, visuals);
    m_selectionTable->insertDataRow({QString::number(size), sortionType, QString::number(time)}, m_selectionTable->rowCount());

    std::copy(m_arr, m_arr + size, arr);

    time = benchSortAlg(quicksort, arr, 0, size-1, false, visuals);
    m_quickTable->insertDataRow({QString::number(size), sortionType, QString::number(time)}, m_quickTable->rowCount());

    std::copy(m_arr, m_arr + size, arr);

    Date* temp = new Date[size];

    time = benchSortAlg(mergesort, temp, arr, size, false, visuals);
    m_mergeTable->insertDataRow({QString::number(size), sortionType, QString::number(time)}, m_mergeTable->rowCount());

    std::copy(m_arr, m_arr + size, arr);

    time = benchSortAlg(hybridQuicksort, arr, 0, size-1, step, false, visuals);
    m_hybridTable->insertDataRow({QString::number(size), QString::number(step), sortionType, QString::number(time)}, m_hybridTable->rowCount());

    std::copy(m_arr, m_arr + size, arr);

    time = benchSortAlg(std::sort, &arr[0], &arr[size-1]);
    m_libraryTable->insertDataRow({QString::number(size), sortionType, QString::number(time)}, m_libraryTable->rowCount());

    std::copy(m_arr, m_arr + size, arr);

    time = benchSortAlg(shakerSort, arr, size, false, visuals);
    m_shakerTable->insertDataRow({QString::number(size), sortionType, QString::number(time)}, m_shakerTable->rowCount());

    std::copy(m_arr, m_arr + size, arr);

    time = benchSortAlg(heapSort, arr, size, false, visuals);
    m_heapTable->insertDataRow({QString::number(size), sortionType, QString::number(time)}, m_heapTable->rowCount());

    std::copy(m_arr, m_arr + size, arr);

    time = benchSortAlg(binaryTreeSort, arr, size);
    m_binaryTreeTable->insertDataRow({QString::number(size), sortionType, QString::number(time)}, m_binaryTreeTable->rowCount());
}
