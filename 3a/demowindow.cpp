#include "demowindow.h"
#include "ui_demowindow.h"
#include "sorting.h"
#include <QTimer>

DemoWindow::DemoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DemoWindow)
{
    ui->setupUi(this);

    m_selectionTable = new table(ui->selectionTable, ui->selectionTable->height(), 1);
    m_quickTable = new table(ui->quickTable, ui->quickTable->height(), 1);
    m_mergeTable = new table(ui->mergeTable, ui->mergeTable->height(), 1);
    m_hybridTable = new table(ui->hybridTable, ui->hybridTable->height(), 1);
    m_libraryTable = new table(ui->libraryTable, ui->libraryTable->height(), 1);
    m_combTable = new table(ui->combTable, ui->combTable->height(), 1);
    m_gnomeTable = new table(ui->gnomeTable, ui->gnomeTable->height(), 1);
    m_shakerTable = new table(ui->shakerTable, ui->shakerTable->height(), 1);
    m_oddEvenTable = new table(ui->oddEvenTable, ui->oddEvenTable->height(), 1);
    m_heapTable = new table(ui->heapTable, ui->heapTable->height(), 1);
}

DemoWindow::~DemoWindow()
{
    delete ui;
}

void DemoWindow::setRunButtonsEnabled(bool enabled)
{
    ui->runSelectionButton->setEnabled(enabled);
    ui->runQuickButton->setEnabled(enabled);
    ui->runMergeButton->setEnabled(enabled);
    ui->runHybridButton->setEnabled(enabled);
    ui->runLibraryButton->setEnabled(enabled);
    ui->runCombButton->setEnabled(enabled);
    ui->runGnomeButton->setEnabled(enabled);
    ui->runShakerButton->setEnabled(enabled);
    ui->runOddEvenButton->setEnabled(enabled);
    ui->runHeapButton->setEnabled(enabled);
    ui->runAllButton->setEnabled(enabled);
}

Date* DemoWindow::dateArray()
{
    int size = ui->arrSizeCounter->value();

    if(ui->randomRadio->isChecked()) return randomDateArray(size);
    if(ui->ascendingRadio->isChecked()) return almostSortedDateArray(size);
    if(ui->descendingRadio->isChecked()) return almostSortedDateArray(size, false);

    return sortedDateArray(size, true);
}

void DemoWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}

void DemoWindow::on_generateAllButton_clicked()
{
    m_arr = dateArray();
    m_arr_size = ui->arrSizeCounter->value();

    m_selectionTable->setDateArray(m_arr, m_arr_size);
    m_quickTable->setDateArray(m_arr, m_arr_size);
    m_mergeTable->setDateArray(m_arr, m_arr_size);
    m_hybridTable->setDateArray(m_arr, m_arr_size);
    m_libraryTable->setDateArray(m_arr, m_arr_size);
    m_combTable->setDateArray(m_arr, m_arr_size);
    m_gnomeTable->setDateArray(m_arr, m_arr_size);
    m_shakerTable->setDateArray(m_arr, m_arr_size);
    m_oddEvenTable->setDateArray(m_arr, m_arr_size);
    m_heapTable->setDateArray(m_arr, m_arr_size);

    setRunButtonsEnabled(true);
}

void DemoWindow::on_runSelectionButton_clicked()
{
    Date* arr = new Date[m_arr_size];
    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* visuals = new std::queue<visualization>;
    selectionSort(arr, 0, m_arr_size-1, true, visuals);
    visualizeItems(visuals, m_selectionTable);

    ui->runSelectionButton->setEnabled(false);
    ui->runAllButton->setEnabled(false);
}

void DemoWindow::on_runQuickButton_clicked()
{
    Date* arr = new Date[m_arr_size];
    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* visuals = new std::queue<visualization>;
    quicksort(arr, 0, m_arr_size-1, true, visuals);
    visualizeItems(visuals, m_quickTable);

    ui->runSelectionButton->setEnabled(false);
    ui->runAllButton->setEnabled(false);
}

void DemoWindow::on_runMergeButton_clicked()
{
    Date* arr = new Date[m_arr_size];
    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* visuals = new std::queue<visualization>;

    Date* temp = new Date[m_arr_size];

    mergesort(arr, temp, m_arr_size, true, visuals);
    visualizeItems(visuals, m_mergeTable);

    ui->runMergeButton->setEnabled(false);
    ui->runAllButton->setEnabled(false);
}

void DemoWindow::on_runHybridButton_clicked()
{
    int step = ui->stepCounter->value();

    Date* arr = new Date[m_arr_size];
    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* visuals = new std::queue<visualization>;
    hybridQuicksort(arr, 0, m_arr_size-1, step, true, visuals);
    visualizeItems(visuals, m_hybridTable);

    ui->runHybridButton->setEnabled(false);
    ui->runAllButton->setEnabled(false);
}

void DemoWindow::on_runLibraryButton_clicked()
{
    dateElem* arr = dateArrToDateElemArr(m_arr, m_arr_size);

    std::queue<visualization>* visuals = new std::queue<visualization>;
    std::sort(arr, arr + m_arr_size,
              [visuals](const dateElem d1, const dateElem d2)
                {
                    visuals->push({0, (int)d1.index, (int)d2.index, ""});

                    return d1 < d2;
                });

    visualizeItems(visuals, m_libraryTable, dateElemArrToDateArr(arr, m_arr_size));

    ui->runLibraryButton->setEnabled(false);
    ui->runAllButton->setEnabled(false);
}

void DemoWindow::on_runCombButton_clicked()
{
    Date* arr = new Date[m_arr_size];
    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* visuals = new std::queue<visualization>;
    combSort(arr, m_arr_size, true, visuals);
    visualizeItems(visuals, m_combTable);

    ui->runCombButton->setEnabled(false);
    ui->runAllButton->setEnabled(false);
}

void DemoWindow::on_runGnomeButton_clicked()
{
    Date* arr = new Date[m_arr_size];
    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* visuals = new std::queue<visualization>;
    gnomeSort(arr, m_arr_size, true, visuals);
    visualizeItems(visuals, m_gnomeTable);

    ui->runGnomeButton->setEnabled(false);
    ui->runAllButton->setEnabled(false);
}

void DemoWindow::on_runShakerButton_clicked()
{
    Date* arr = new Date[m_arr_size];
    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* visuals = new std::queue<visualization>;
    shakerSort(arr, m_arr_size, true, visuals);
    visualizeItems(visuals, m_shakerTable);

    ui->runShakerButton->setEnabled(false);
    ui->runAllButton->setEnabled(false);
}

void DemoWindow::on_runOddEvenButton_clicked()
{
    Date* arr = new Date[m_arr_size];
    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* visuals = new std::queue<visualization>;
    oddEvenSort(arr, m_arr_size, true, visuals);
    visualizeItems(visuals, m_oddEvenTable);

    ui->runOddEvenButton->setEnabled(false);
    ui->runAllButton->setEnabled(false);
}

void DemoWindow::on_runHeapButton_clicked()
{
    Date* arr = new Date[m_arr_size];
    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* visuals = new std::queue<visualization>;
    heapSort(arr, m_arr_size, true, visuals);
    visualizeItems(visuals, m_heapTable);

    ui->runHeapButton->setEnabled(false);
    ui->runAllButton->setEnabled(false);
}

void DemoWindow::on_runAllButton_clicked()
{
    Date* arr = new Date[m_arr_size];
    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* selectionVisuals = new std::queue<visualization>;
    selectionSort(arr, 0, m_arr_size-1, true, selectionVisuals);
    visualizeItems(selectionVisuals, m_selectionTable);

    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* quickVisuals = new std::queue<visualization>;
    quicksort(arr, 0, m_arr_size-1, true, quickVisuals);
    visualizeItems(quickVisuals, m_quickTable);

    std::copy(m_arr, m_arr + m_arr_size, arr);
    Date* tempArr = new Date[m_arr_size];

    std::queue<visualization>* mergeVisuals = new std::queue<visualization>;
    mergesort(arr, tempArr, m_arr_size, true, mergeVisuals);
    visualizeItems(mergeVisuals, m_mergeTable);

    std::copy(m_arr, m_arr + m_arr_size, arr);

    int step = ui->stepCounter->value();

    std::queue<visualization>* hybridVisuals = new std::queue<visualization>;
    hybridQuicksort(arr, 0, m_arr_size-1, step, true, hybridVisuals);
    visualizeItems(hybridVisuals, m_hybridTable);

    dateElem* dateElemArr = dateArrToDateElemArr(m_arr, m_arr_size);

    std::queue<visualization>* libraryVisuals = new std::queue<visualization>;
    std::sort(dateElemArr, dateElemArr + m_arr_size,
              [libraryVisuals](const dateElem d1, const dateElem d2)
                {
                    libraryVisuals->push({0, (int)d1.index, (int)d2.index, ""});

                    return d1 < d2;
                });

    visualizeItems(libraryVisuals, m_libraryTable, dateElemArrToDateArr(dateElemArr, m_arr_size));

    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* combVisuals = new std::queue<visualization>;
    combSort(arr, m_arr_size, true, combVisuals);
    visualizeItems(combVisuals, m_combTable);

    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* gnomeVisuals = new std::queue<visualization>;
    gnomeSort(arr, m_arr_size, true, gnomeVisuals);
    visualizeItems(gnomeVisuals, m_gnomeTable);

    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* shakerVisuals = new std::queue<visualization>;
    shakerSort(arr, m_arr_size, true, shakerVisuals);
    visualizeItems(shakerVisuals, m_shakerTable);

    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* oddEvenVisuals = new std::queue<visualization>;
    oddEvenSort(arr, m_arr_size, true, oddEvenVisuals);
    visualizeItems(oddEvenVisuals, m_oddEvenTable);

    std::copy(m_arr, m_arr + m_arr_size, arr);

    std::queue<visualization>* heapVisuals = new std::queue<visualization>;
    heapSort(arr, m_arr_size, true, heapVisuals);
    visualizeItems(heapVisuals, m_heapTable);

    setRunButtonsEnabled(false);
}
