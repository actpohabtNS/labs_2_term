#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupNumberInputButtons();

    setupBinaryTreeUI();
    setupTreeUI();
    setupFSUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::manageInputButtonEnabled(QLineEdit *input, QPushButton* button)
{
    if (input->text() != "")
        button->setEnabled(true);
    else
        button->setEnabled(false);
}

void MainWindow::manageInputButtonEnabled(QTreeWidget *widget, QPushButton *button)
{
    if (widget->selectedItems().size() == 0)
        button->setEnabled(false);
    else
        button->setEnabled(true);
}

void MainWindow::manageInputButtonEnabled(QLineEdit *input, QTreeWidget *widget, QPushButton *button)
{
    if (widget->selectedItems().size() != 0)
        this->manageInputButtonEnabled(input, button);
    else
        button->setEnabled(false);
}

void MainWindow::setupNumberInputButtons()
{
    ui->newBinaryTreeInput->setValidator( new QIntValidator(0, 10000000, this) );
    ui->addBinaryInput->setValidator( new QIntValidator(0, 10000000, this) );
    ui->addIntegerInput->setValidator( new QIntValidator(0, 10000000, this) );
    ui->newIntegerTreeInput->setValidator( new QIntValidator(0, 10000000, this) );
    ui->getIntegerPathInput->setValidator( new QIntValidator(0, 10000000, this) );
    ui->removeIntegerInput->setValidator( new QIntValidator(0, 10000000, this) );
}

void MainWindow::setupBinaryTree()
{
    BinaryTree<int>* bTree = new BinaryTree<int>(20);

    bTree->add(15);
    bTree->add(25);
    bTree->add(12);
    bTree->add(17);
    bTree->add(6);
    bTree->add(22);
    bTree->add(27);
    bTree->add(16);
    bTree->add(18);
    bTree->add(37);
    bTree->add(26);

    this->_bTree = bTree;
}

void MainWindow::setupTree()
{
    GeneralTree<int> *tree = new GeneralTree<int>(1);

    tree->insert({}, 2);
    tree->insert({}, 5);
    tree->insert({}, 100);
    tree->insert({}, 101);
    tree->insert({}, 102);
    tree->insert({}, 103);
    tree->insert({}, 104);
    tree->insert({}, 105);
    tree->insert({}, 106);
    tree->insert({}, 107);
    tree->insert({}, 108);
    tree->insert({0}, 3);
    tree->insert({0}, 4);
    tree->insert({0}, 9);
    tree->insert({0, 0}, 11);
    tree->insert({0, 2}, 10);
    tree->insert({1}, 6);
    tree->insert({1, 0}, 11);
    tree->insert({1}, 7);

    this->_tree = tree;
}

void MainWindow::setupFS()
{
    FileSystemElem root(true, "Root", 0, {12, 15});
    FileSystem* fs = new FileSystem(root);

    fs->insert({}, {true, "My files", 0, {12, 25}});
    fs->insert({0}, {false, "ThinkingInC++.pdf", 1200, {13, 22}});
    fs->insert({0}, {false, "DescreteMathHW.docx", 23, {23, 58}});
    fs->insert({0}, {true, "Secrets", 0, {12, 42}});
    fs->insert({0, 2}, {false, "whatWeCanUnderstandAboutGirls.txt", 0, {15, 35}});
    fs->insert({}, {true, "System", 0, {12, 15}});
    fs->insert({1}, {true, "Windows", 0, {12, 15}});
    fs->insert({1,0}, {false, "notACrack.exe", 1440, {12, 15}});
    fs->insert({}, {true, "Programs", 0, {13, 00}});
    fs->insert({2}, {false, "VisualStudio2020.exe", 25033, {13, 40}});
    fs->insert({2}, {false, "uTorrent.exe", 4532, {19, 11}});

    this->_fs = fs;
}

void MainWindow::setupBinaryTreeUI()
{
    setupBinaryTree();

    this->_bTW = ui->binaryTree;
    this->_bTW->setTree(this->_bTree);
    this->_bTW->render();

    updatePathBeforeElemText(*this->_bTree, ui->pathBeforeElemBinaryTextField);

    this->_iBTV = new InteractiveTreeView<int>(this->_bTree, ui->toBinaryParentButton, ui->binaryElemLabel, ui->binaryChildrenTable);
    this->_iBTV->toRoot();
}

void MainWindow::setupTreeUI()
{
    setupTree();

    this->_tW = ui->integerTree;
    this->_tW->setTree(this->_tree);
    this->_tW->render();

    updatePathBeforeElemText(*this->_tree, ui->pathBeforeElemIntegerTextField);

    this->_iTV = new InteractiveTreeView<int>(this->_tree, ui->toIntegerParentButton, ui->integerElemLabel, ui->integerChildrenTable);
    this->_iTV->toRoot();

    this->_console = new Console(ui->integerConsole);
}

void MainWindow::setupFSUI()
{
    setupFS();

    ui->fileSystem->setColumnWidth(0, 400);
    ui->fileSystem->setColumnWidth(1, 150);
    ui->fileSystem->setColumnWidth(2, 115);
    ui->fileSystem->setColumnWidth(3, 25);

    this->_fsW = ui->fileSystem;
    this->_fsW->setTree(this->_fs);
    this->_fsW->render();

    this->_fsConsole = new Console(ui->fileConsole);
}

void MainWindow::resetAddElemInputs()
{
    ui->isFolderCheckBox->setChecked(false);
    ui->addElemNameInput->clear();
    ui->addElemSizeInput->clear();
    ui->addElemTimeInput->setTime(QTime(0,0));
}

void MainWindow::manageInRangeInputs(QLineEdit *min, QLineEdit *max, QPushButton *button)
{
    if (max->text() == "")
        return;

    button->setEnabled(min->text().toInt() <= max->text().toInt());
}

void MainWindow::manageInRangeInputs(QTimeEdit *min, QTimeEdit *max, QPushButton *button)
{
    button->setEnabled(min->time() <= max->time());
}

void MainWindow::printTotalAmountOfElems(int mode) // 0 - all elements, 1 - only files, 2 - only folders
{
    QTreeWidgetItem *item = this->getSelected();

    int total;
    QString elem;
    QString name = item->text(0);

    switch (mode) {
    case 0:
        total = this->_fsW->filesCount(item) + this->_fsW->foldersCount(item);
        elem = "elem";
        break;

    case 1:
        total = this->_fsW->filesCount(item);
        elem = "file";
        break;

    case 2:
        total = this->_fsW->foldersCount(item);
        elem = "folder";
        break;

    default:
        total = -1;
        elem = "";
        break;
    }

    this->_fsConsole->newPar();
    this->_fsConsole->printTech("Total number of "+ elem + "s in [ " + name + " ] :");
    this->_fsConsole->newLine();
    this->_fsConsole->print(QString::number(total) + " " + elem + "(s)");

}

void MainWindow::printTimeElem(bool first)
{
    QTreeWidgetItem *item = this->getSelected();
    FileSystemElem elem = first ? this->_fsW->firstChanged(item) : this->_fsW->lastChanged(item);

    QString timeType = first ? "First" : "Last";
    QString insideName = item->text(0);

    this->_fsConsole->newPar();
    this->_fsConsole->printTech("[ " + insideName + " ] " + timeType + " element that was changed:");
    this->_fsConsole->newLine();
    this->_fsConsole->print("Name: " + elem.name());
    this->_fsConsole->newLine();
    this->_fsConsole->print("Size: " + QString::number(elem.size()) + " kB ");
    this->_fsConsole->newLine();
    this->_fsConsole->print("Last changed: " + elem.lastChanged().toString("HH:mm"));
}

QTreeWidgetItem *MainWindow::getSelected() const
{
    QTreeWidgetItem *item;
    if (ui->fileSystem->selectedItems().size() != 0)
        item = ui->fileSystem->selectedItems()[0];
    else
        item = ui->fileSystem->topLevelItem(0);

    return item;
}

void MainWindow::on_addBinaryInput_textEdited(const QString &arg1)
{
    if (arg1 == "" || _bTree->isThreaded())
    {
        ui->addBinaryChildButton->setEnabled(false);
    }

    if (arg1 != "" && !_bTree->isThreaded())
    {
        ui->addBinaryChildButton->setEnabled(true);
    }
}

void MainWindow::on_newBinaryTreeInput_textEdited(const QString &arg1)
{
    if (arg1 == "" || _bTree->isThreaded())
    {
        ui->newBinaryTreeButton->setEnabled(false);
    }

    if (arg1 != "" && !_bTree->isThreaded())
    {
        ui->newBinaryTreeButton->setEnabled(true);
    }
}

void MainWindow::on_threadizeButton_clicked()
{
    ui->addBinaryChildButton->setEnabled(false);
    ui->newBinaryTreeButton->setEnabled(false);
    ui->threadizeButton->setEnabled(false);
    ui->removeThreadsButton->setEnabled(true);

    ui->toBinaryRootButton->setEnabled(false);
    this->_iBTV->setEnabled(false);

    _bTree->toThreaded();
}

void MainWindow::on_removeThreadsButton_clicked()
{
    manageInputButtonEnabled(ui->addBinaryInput, ui->addBinaryChildButton);
    manageInputButtonEnabled(ui->newBinaryTreeInput, ui->newBinaryTreeButton);

    ui->threadizeButton->setEnabled(true);
    ui->removeThreadsButton->setEnabled(false);

    ui->toBinaryRootButton->setEnabled(true);
    this->_iBTV->setEnabled(true);

    _bTree->removeThreads();
}


void MainWindow::on_addBinaryChildButton_clicked()
{
    if (_bTree->isThreaded())
        return;

    _bTree->add(ui->addBinaryInput->text().toInt());

    ui->addBinaryInput->setText("");

    ui->addBinaryChildButton->setEnabled(false);

    this->_bTW->update();

    updatePathBeforeElemText(*_bTree, ui->pathBeforeElemBinaryTextField);

    this->_iBTV->toRoot();
}

void MainWindow::on_newBinaryTreeButton_clicked()
{
    int newRoot = ui->newBinaryTreeInput->text().toInt();

    _bTree->empty(newRoot);

    ui->newBinaryTreeInput->clear();
    ui->newBinaryTreeButton->setEnabled(false);

    this->_bTW->update();

    updatePathBeforeElemText(*_bTree, ui->pathBeforeElemBinaryTextField);

    this->_iBTV->toRoot();
}

void MainWindow::on_toBinaryRootButton_clicked()
{
    this->_iBTV->toRoot();
}

void MainWindow::on_toBinaryParentButton_clicked()
{
    this->_iBTV->toParent();
}

void MainWindow::on_binaryChildrenTable_cellClicked(int row, int column)
{
    if (ui->binaryChildrenTable->item(row, column)->flags() == Qt::ItemFlag())
        return;

    this->_iBTV->toChild(column);
}

void MainWindow::on_binaryTreeDemoButton_clicked()
{
    ui->binaryTreeDemoButton->setEnabled(false);
    ui->tabWidget->setAttribute( Qt::WA_TransparentForMouseEvents );

    QTimer::singleShot(1000, nullptr, [this] {
        ui->newBinaryTreeInput->setText("15"); });

    QTimer::singleShot(2000, nullptr, [this] {
        on_newBinaryTreeButton_clicked(); });

    QTimer::singleShot(3000, nullptr, [this] {
        ui->addBinaryInput->setText("20"); });

    QTimer::singleShot(4000, nullptr, [this] {
        on_addBinaryChildButton_clicked(); });

    QTimer::singleShot(5000, nullptr, [this] {
        ui->addBinaryInput->setText("10"); });

    QTimer::singleShot(6000, nullptr, [this] {
        on_addBinaryChildButton_clicked(); });

    QTimer::singleShot(7000, nullptr, [this] {
        ui->addBinaryInput->setText("5"); });

    QTimer::singleShot(8000, nullptr, [this] {
        on_addBinaryChildButton_clicked(); });

    QTimer::singleShot(9000, nullptr, [this] {
        on_binaryChildrenTable_cellClicked(0, 0);  });

    QTimer::singleShot(10000, nullptr, [this] {
        on_toBinaryParentButton_clicked(); });

    QTimer::singleShot(11000, nullptr, [this] {
        on_threadizeButton_clicked(); });

    QTimer::singleShot(12000, nullptr, [this] {
        on_removeThreadsButton_clicked(); });

    QTimer::singleShot(12500, nullptr, [this] {
        ui->binaryTreeDemoButton->setEnabled(true);
        ui->tabWidget->setAttribute( Qt::WA_TransparentForMouseEvents, false ); });
}

void MainWindow::on_newIntegerTreeButton_clicked()
{
    int newRoot = ui->newIntegerTreeInput->text().toInt();

    _tree->empty(newRoot);

    ui->newIntegerTreeInput->clear();
    ui->newIntegerTreeButton->setEnabled(false);

    this->_tW->update();

    updatePathBeforeElemText(*_tree, ui->pathBeforeElemIntegerTextField);

    this->_iTV->toRoot();

    this->_console->newPar();
    this->_console->printTech("New tree with [ root ] = " + QString::number(newRoot) + " created!");
}

void MainWindow::on_newIntegerTreeInput_textEdited()
{
    this->manageInputButtonEnabled(ui->newIntegerTreeInput, ui->newIntegerTreeButton);
}

void MainWindow::on_addIntegerChildButton_clicked()
{
    int value = ui->addIntegerInput->text().toInt();

    ui->addIntegerInput->clear();
    ui->addIntegerChildButton->setEnabled(false);

    std::vector<int> path = this->_tW->getPath(ui->integerTree->selectedItems()[0]);

    int elem = this->_tree->get(path);

    this->_console->newPar();
    this->_console->printTech("Adding child with [ value ] = " + QString::number(value) + " to selected item { " + QString::number(elem) + " }");
    this->_console->newLine();

    this->_tree->insert(path, value);

    this->_tW->update();

    updatePathBeforeElemText(*_tree, ui->pathBeforeElemIntegerTextField);

    this->_iTV->toRoot();
}

void MainWindow::on_addIntegerInput_textEdited()
{
    this->manageInputButtonEnabled(ui->addIntegerInput, ui->integerTree, ui->addIntegerChildButton);
}

void MainWindow::on_getIntegerPathSelectedButton_clicked()
{
    std::vector<int> path = this->_tW->getPath(ui->integerTree->selectedItems()[0]);

    int elem = this->_tree->get(path);

    this->_console->newPar();
    this->_console->printTech("Path to selected elem { " + QString::number(elem) + " } :");
    this->_console->newLine();

    this->_console->print(pathToQStr(path));
}

void MainWindow::on_getIntegerPathByValueButton_clicked()
{
    int value = ui->getIntegerPathInput->text().toInt();

    ui->getIntegerPathInput->clear();
    ui->getIntegerPathInput->setEnabled(false);

    this->_console->newPar();
    this->_console->printTech("Path to [ elem ] with value = { " + QString::number(value) + " } :");
    this->_console->newLine();

    if (this->_tree->contains(value))
    {
        std::vector<int> path = this->_tree->getPath(value);
        this->_console->print(pathToQStr(path));
    }
    else
    {
        this->_console->printError("There is no [ elem ] with value = " + QString::number(value) + "!");
    }
}

void MainWindow::on_getIntegerPathInput_textEdited()
{
    this->manageInputButtonEnabled(ui->getIntegerPathInput, ui->getIntegerPathByValueButton);
}

void MainWindow::on_removeIntegerSelectedButton_clicked()
{
    std::vector<int> path = this->_tW->getPath(ui->integerTree->selectedItems()[0]);

    int elem = this->_tree->get(path);

    this->_console->newPar();
    this->_console->printTech("Removing selected item { " + QString::number(elem) + " }");
    this->_console->newLine();

    if (path.size() == 0)
    {
        this->_console->printError("You are not able to delete [ root ]! To create new tree use [ New Tree ] button.");
        return;
    }

    this->_tree->removeSubtree(path);

    this->_tW->update();

    updatePathBeforeElemText(*_tree, ui->pathBeforeElemIntegerTextField);

    this->_iTV->toRoot();
}

void MainWindow::on_removeIntegerByValueButton_clicked()
{
    int removeValue = ui->removeIntegerInput->text().toInt();

    ui->removeIntegerInput->clear();
    ui->removeIntegerInput->setEnabled(false);

    this->_console->newPar();
    this->_console->printTech("Removing [ elem ] with value = " + QString::number(removeValue));

    if (!this->_tree->contains(removeValue))
    {
        this->_console->newLine();
        this->_console->printError("There is no [ elem ] with value = " + QString::number(removeValue) + "!");
    }

    if (this->_tree->getPath(removeValue).size() == 0)
    {
        this->_console->newLine();
        this->_console->printError("You are not able to delete [ root ]! To create new tree use [ New Tree ] button.");
        return;
    }

    this->_tree->removeSubtree(removeValue);

    this->_tW->update();

    updatePathBeforeElemText(*_tree, ui->pathBeforeElemIntegerTextField);

    this->_iTV->toRoot();
}

void MainWindow::on_removeIntegerInput_textEdited()
{
    this->manageInputButtonEnabled(ui->removeIntegerInput, ui->removeIntegerByValueButton);
}

void MainWindow::on_toIntegerRootButton_clicked()
{
    this->_iTV->toRoot();
}

void MainWindow::on_toIntegerParentButton_clicked()
{
    this->_iTV->toParent();
}

void MainWindow::on_integerChildrenTable_cellClicked(int row, int column)
{
    if (row > 1)
        return;

    this->_iTV->toChild(column);
}

void MainWindow::on_integerTree_itemSelectionChanged()
{
    this->manageInputButtonEnabled(ui->addIntegerInput, ui->integerTree, ui->addIntegerChildButton);
    this->manageInputButtonEnabled(ui->integerTree, ui->getIntegerPathSelectedButton);
    this->manageInputButtonEnabled(ui->integerTree, ui->removeIntegerSelectedButton);
}

void MainWindow::on_integerTreeDemoButton_clicked()
{
    ui->integerTreeDemoButton->setEnabled(false);
    ui->tabWidget->setAttribute( Qt::WA_TransparentForMouseEvents );

    QTimer::singleShot(1000, nullptr, [this] {
        ui->newIntegerTreeInput->setText("50"); });

    QTimer::singleShot(2000, nullptr, [this] {
        on_newIntegerTreeButton_clicked(); });

    QTimer::singleShot(3000, nullptr, [this] {
        ui->integerTree->topLevelItem(0)->setSelected(true); });

    QTimer::singleShot(4000, nullptr, [this] {
        ui->addIntegerInput->setText("25"); });

    QTimer::singleShot(5000, nullptr, [this] {
        on_addIntegerChildButton_clicked(); });

    QTimer::singleShot(6000, nullptr, [this] {
        ui->integerTree->topLevelItem(0)->setSelected(true); });

    QTimer::singleShot(6000, nullptr, [this] {
        ui->addIntegerInput->setText("75"); });

    QTimer::singleShot(7000, nullptr, [this] {
        on_addIntegerChildButton_clicked(); });

    QTimer::singleShot(8000, nullptr, [this] {
        ui->integerTree->topLevelItem(0)->setSelected(true); });

    QTimer::singleShot(8000, nullptr, [this] {
        ui->addIntegerInput->setText("15"); });

    QTimer::singleShot(9000, nullptr, [this] {
        on_addIntegerChildButton_clicked(); });

    QTimer::singleShot(10000, nullptr, [this] {
        on_integerChildrenTable_cellClicked(1, 0);  });

    QTimer::singleShot(11000, nullptr, [this] {
        on_toIntegerParentButton_clicked(); });

    QTimer::singleShot(12000, nullptr, [this] {
        ui->integerTree->topLevelItem(0)->child(1)->setSelected(true); });

    QTimer::singleShot(13000, nullptr, [this] {
        on_getIntegerPathSelectedButton_clicked(); });

    QTimer::singleShot(14000, nullptr, [this] {
        ui->getIntegerPathInput->setText("75"); });

    QTimer::singleShot(15000, nullptr, [this] {
        on_getIntegerPathByValueButton_clicked(); });

    QTimer::singleShot(16000, nullptr, [this] {
        ui->integerTree->topLevelItem(0)->child(1)->setSelected(true); });

    QTimer::singleShot(17000, nullptr, [this] {
        on_removeIntegerSelectedButton_clicked(); });

    QTimer::singleShot(18000, nullptr, [this] {
        ui->removeIntegerInput->setText("25"); });

    QTimer::singleShot(19000, nullptr, [this] {
        on_removeIntegerByValueButton_clicked(); });

    QTimer::singleShot(19500, nullptr, [this] {
        ui->integerTreeDemoButton->setEnabled(true);
        ui->tabWidget->setAttribute( Qt::WA_TransparentForMouseEvents, false ); });
}

void MainWindow::on_fileSystem_itemSelectionChanged()
{
    this->manageInputButtonEnabled(ui->fileSystem, ui->addElemChildButton);
    this->manageInputButtonEnabled(ui->fileSystem, ui->removeSelectedElemButton);
}

void MainWindow::on_newElemRootInput_textEdited()
{
    this->manageInputButtonEnabled(ui->newElemRootInput, ui->newFileSystemButton);
}

void MainWindow::on_newFileSystemButton_clicked()
{
    FileSystemElem root(true, ui->newElemRootInput->text(), 0, QTime(0,0));
    this->_fs = new FileSystem(root);
    this->_fsW->setFileSystem(this->_fs);
    this->_fsW->update();

    this->_fsConsole->newPar();
    this->_fsConsole->printTech("New File System with [ Root ] = { " + root.name() + " } created!");

    ui->newElemRootInput->clear();
    ui->newFileSystemButton->setEnabled(false);
}

void MainWindow::on_removeSelectedElemButton_clicked()
{
    this->_fsConsole->newPar();
    this->_fsConsole->printTech("Removing selected item");

    std::vector<int> path = this->_fsW->getPath(ui->fileSystem->selectedItems()[0]);

    if (path.size() == 0)
    {
        this->_fsConsole->newLine();
        this->_fsConsole->printError("You are not able to delete [ Root ]! To create new Root use [ New root ] button.");
        return;
    }

    this->_fs->removeSubtree(path);
    this->_fsW->update();
}

void MainWindow::on_isFolderCheckBox_stateChanged(int arg1)
{
    if (arg1 > 0)
        ui->addElemSizeInput->setText("0");
}

void MainWindow::on_addElemNameInput_textEdited()
{
    this->manageInputButtonEnabled(ui->addElemNameInput, ui->fileSystem, ui->addElemChildButton);
}

void MainWindow::on_addElemChildButton_clicked()
{
    bool isFolder = ui->isFolderCheckBox->isChecked();
    QString name = ui->addElemNameInput->text();
    int size = ui->addElemSizeInput->text().toInt();
    QTime lastChanged = ui->addElemTimeInput->time();

    FileSystemElem elem(isFolder, name, size, lastChanged);

    std::vector<int> path = this->_fsW->getPath(ui->fileSystem->selectedItems()[0]);

    QString parentName = this->_fs->get(path).name();

    this->_fsConsole->newPar();
    this->_fsConsole->printTech("Adding child with [ name ] = { " + name + " } to selected item { " + parentName + " }.");

    if (!this->_fs->get(path).isFolder())
    {
        this->_fsConsole->newLine();
        this->_fsConsole->printError("Selected elem is not a folder! Child can be added only to a folder!");
        return;
    }

    if (this->_fsW->isFiltered())
    {
        emit on_clearFilterElemButton_clicked();
        this->_fsConsole->newLine();
        this->_fsConsole->print("Filter was cleared to add new [ elem ] !");
    }

    this->_fs->insert(path, elem);
    this->_fsW->update();

    this->resetAddElemInputs();
}

void MainWindow::on_minSizeFilterElemInput_textEdited()
{
    this->manageInRangeInputs(ui->minSizeFilterElemInput, ui->maxSizeFilterElemInput, ui->filterElemButton);
}

void MainWindow::on_maxSizeFilterElemInput_textEdited()
{
    this->manageInRangeInputs(ui->minSizeFilterElemInput, ui->maxSizeFilterElemInput, ui->filterElemButton);
}

void MainWindow::on_minTimeFilterElemInput_userTimeChanged()
{
    this->manageInRangeInputs(ui->minTimeFilterElemInput, ui->maxTimeFilterElemInput, ui->filterElemButton);
}

void MainWindow::on_maxTimeFilterElemInput_userTimeChanged()
{
    this->manageInRangeInputs(ui->minTimeFilterElemInput, ui->maxTimeFilterElemInput, ui->filterElemButton);
}

void MainWindow::on_filterElemButton_clicked()
{
    this->_fsConsole->newPar();
    this->_fsConsole->printTech("Filtering file system with next parameters:");

    QString name = ui->nameFilterElemInput->text();
    int minSize = ui->minSizeFilterElemInput->text().toInt();
    int maxSize = ui->maxSizeFilterElemInput->text().toInt();
    QTime minTime = ui->minTimeFilterElemInput->time();
    QTime maxTime = ui->maxTimeFilterElemInput->time();

    if (name != "")
    {
        this->_fsConsole->newLine();
        this->_fsConsole->print("Name: " + name);
    }

    if (minSize != 0)
    {
        this->_fsConsole->newLine();
        this->_fsConsole->print("Min size: " + QString::number(minSize));
    }

    if (maxSize != 0)
    {
        this->_fsConsole->newLine();
        this->_fsConsole->print("Max size: " + QString::number(maxSize));
    }

    this->_fsConsole->newLine();
    this->_fsConsole->print("Min time: " + minTime.toString("HH:mm"));
    this->_fsConsole->newLine();
    this->_fsConsole->print("Max time: " + maxTime.toString("HH:mm"));

    this->_fsW->filterByName(name);

    if (minSize != 0)
    {
        if (maxSize == 0)
            maxSize = this->_fs->get({}).size();

        this->_fsW->filterBySize(minSize, maxSize);
    }

    if (minTime != QTime(0, 0) && maxTime != QTime(23, 59))
        this->_fsW->filterByLastEdited(minTime, maxTime);

    ui->clearFilterElemButton->setEnabled(true);
}

void MainWindow::on_clearFilterElemButton_clicked()
{
    this->_fsW->setAllVisible();
    this->_fsW->update();
    ui->clearFilterElemButton->setEnabled(false);
}


void MainWindow::on_getTotalAmountElemButton_clicked()
{
    QTreeWidgetItem *item = this->getSelected();

    QString name = item->text(0);

    int files = this->_fsW->filesCount(item);
    int folders= this->_fsW->foldersCount(item);
    int total = files + folders;

    this->_fsConsole->newPar();
    this->_fsConsole->printTech("Elements in [ " + name + " ] :");
    this->_fsConsole->newLine();
    this->_fsConsole->print(QString::number(total) + " elem(s): ");
    this->_fsConsole->print(QString::number(files) + " file(s) and ");
    this->_fsConsole->print( QString::number(folders) + " folder(s)");
}

void MainWindow::on_getFilesAmountElemButton_clicked()
{
    this->printTotalAmountOfElems(1);
}

void MainWindow::on_getFoldersAmountElemButton_clicked()
{
    this->printTotalAmountOfElems(2);
}

void MainWindow::on_getTotalSizeElemButton_clicked()
{
    QTreeWidgetItem *item = this->getSelected();

    int size = this->_fsW->size(item);
    QString name = item->text(0);

    this->_fsConsole->newPar();
    this->_fsConsole->printTech("Size of [ " + name + " ] :");
    this->_fsConsole->newLine();
    this->_fsConsole->print(QString::number(size) + " kBytes");
}

void MainWindow::on_getFirstEditedElemButton_clicked()
{
    this->printTimeElem(true);
}

void MainWindow::on_getLastEditedElemButton_clicked()
{
    this->printTimeElem(false);
}

void MainWindow::on_fileSystemDemoButton_clicked()
{
    ui->fileSystemDemoButton->setEnabled(false);
    ui->tabWidget->setAttribute( Qt::WA_TransparentForMouseEvents );

    QTimer::singleShot(1000, nullptr, [this] {
        ui->fileSystem->topLevelItem(0)->child(0)->setSelected(true); });

    QTimer::singleShot(2000, nullptr, [this] {
        ui->addElemNameInput->setText("MyTest.txt"); });

    QTimer::singleShot(3000, nullptr, [this] {
        ui->addElemSizeInput->setText("256"); });

    QTimer::singleShot(4000, nullptr, [this] {
        ui->addElemTimeInput->setTime(QTime(9, 41)); });

    QTimer::singleShot(5000, nullptr, [this] {
        on_addElemChildButton_clicked(); });

    QTimer::singleShot(6000, nullptr, [this] {
        ui->nameFilterElemInput->setText("M"); });

    QTimer::singleShot(6000, nullptr, [this] {
        ui->minSizeFilterElemInput->setText("512"); });

    QTimer::singleShot(7000, nullptr, [this] {
        on_filterElemButton_clicked(); });

    QTimer::singleShot(11000, nullptr, [this] {
        on_clearFilterElemButton_clicked(); });

    QTimer::singleShot(12000, nullptr, [this] {
        on_getTotalAmountElemButton_clicked(); });

    QTimer::singleShot(13000, nullptr, [this] {
        ui->fileSystem->topLevelItem(0)->child(1)->setSelected(true); });

    QTimer::singleShot(14000, nullptr, [this] {
        on_getFirstEditedElemButton_clicked(); });

    QTimer::singleShot(15000, nullptr, [this] {
        on_getLastEditedElemButton_clicked(); });

    QTimer::singleShot(16000, nullptr, [this] {
        ui->fileSystem->topLevelItem(0)->child(2)->setSelected(true); });

    QTimer::singleShot(17000, nullptr, [this] {
        on_removeSelectedElemButton_clicked(); });

    QTimer::singleShot(18000, nullptr, [this] {
        ui->newElemRootInput->setText("New Root"); });

    QTimer::singleShot(19000, nullptr, [this] {
        on_newFileSystemButton_clicked(); });

    QTimer::singleShot(19500, nullptr, [this] {
        ui->fileSystemDemoButton->setEnabled(true);
        ui->tabWidget->setAttribute( Qt::WA_TransparentForMouseEvents, false ); });
}
