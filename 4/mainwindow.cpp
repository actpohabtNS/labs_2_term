#include "mainwindow.h"
#include "ui_mainwindow.h"


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

    this->_bTW = new TreeWidget<int>(ui->binaryTree, this->_bTree);
    this->_bTW->render();

    updatePathBeforeElemText(*this->_bTree, ui->pathBeforeElemBinaryTextField);

    this->_iBTV = new InteractiveTreeView<int>(this->_bTree, ui->toBinaryParentButton, ui->binaryElemLabel, ui->binaryChildrenTable);
    this->_iBTV->toRoot();
}

void MainWindow::setupTreeUI()
{
    setupTree();

    this->_tW = new TreeWidget<int>(ui->integerTree, this->_tree);
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

    this->_fsW = new FileSystemWidget(ui->fileSystem, this->_fs);
    this->_fsW->render();
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
    ui->addIntegerInput->setEnabled(false);

    this->_console->newPar();
    this->_console->printTech("Adding child with [ value ] = " + QString::number(value) + " to selected item");
    this->_console->newLine();

    std::vector<int> path = this->_tW->getPath(ui->integerTree->selectedItems()[0]);

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
    this->_console->newPar();
    this->_console->printTech("Path to selected elem:");
    this->_console->newLine();

    std::vector<int> path = this->_tW->getPath(ui->integerTree->selectedItems()[0]);

    this->_console->print(pathToQStr(path));
}

void MainWindow::on_getIntegerPathByValueButton_clicked()
{
    int value = ui->getIntegerPathInput->text().toInt();

    ui->getIntegerPathInput->clear();
    ui->getIntegerPathInput->setEnabled(false);

    this->_console->newPar();
    this->_console->printTech("Path to [ elem ] with value = " + QString::number(value) + ":");
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
    this->_console->newPar();
    this->_console->printTech("Removing selected item");
    this->_console->newLine();

    std::vector<int> path = this->_tW->getPath(ui->integerTree->selectedItems()[0]);

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

void MainWindow::on_fileSystem_itemSelectionChanged()
{
//    if (ui->fileSystem->selectedItems().size() == 0)
//        return;

//    qDebug() << ui->fileSystem->selectedItems()[0]->text(0);
}

void MainWindow::on_filterElemButton_clicked()
{
    this->_fsW->filterByName("o");
    //
}
