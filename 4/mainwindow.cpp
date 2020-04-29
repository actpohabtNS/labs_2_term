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
    tree->insert({}, 8);
    tree->insert({}, 88);
    tree->insert({}, 888);
    tree->insert({}, 8888);
    tree->insert({}, 88888);
    tree->insert({}, 888888);
    tree->insert({}, 8888888);
    tree->insert({}, 88888888);
    tree->insert({}, 888888888);
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

void MainWindow::setupBinaryTreeUI()
{
    setupBinaryTree();
    //Tree<int>* tree = this->_bTree;
    setTree(*this->_bTree, ui->binaryTree);
    updatePathBeforeElemText(*this->_bTree, ui->pathBeforeElemBinaryTextField);
    _iBTW = new InteractiveTreeView<int>(this->_bTree, ui->toBinaryParentButton, ui->binaryElemLabel, ui->binaryChildrenTable);
    _iBTW->toRoot();
}

void MainWindow::setupTreeUI()
{
    setupTree();
    setTree(*this->_tree, ui->integerTree);
    updatePathBeforeElemText(*this->_tree, ui->pathBeforeElemIntegerTextField);
    _iTW = new InteractiveTreeView<int>(this->_tree, ui->toIntegerParentButton, ui->integerElemLabel, ui->integerChildrenTable);
    _iTW->toRoot();
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
    this->_iBTW->setEnabled(false);

    _bTree->toThreaded();
}

void MainWindow::on_removeThreadsButton_clicked()
{
    manageInputButtonEnabled(ui->addBinaryInput, ui->addBinaryChildButton);
    manageInputButtonEnabled(ui->newBinaryTreeInput, ui->newBinaryTreeButton);

    ui->threadizeButton->setEnabled(true);
    ui->removeThreadsButton->setEnabled(false);

    ui->toBinaryRootButton->setEnabled(true);
    this->_iBTW->setEnabled(true);

    _bTree->removeThreads();
}


void MainWindow::on_addBinaryChildButton_clicked()
{
    if (_bTree->isThreaded())
        return;

    _bTree->add(ui->addBinaryInput->text().toInt());

    ui->addBinaryInput->setText("");

    ui->addBinaryChildButton->setEnabled(false);

    updateTreeTable(setTree, *_bTree, ui->binaryTree);

    updatePathBeforeElemText(*_bTree, ui->pathBeforeElemBinaryTextField);

    this->_iBTW->toRoot();
}

void MainWindow::on_newBinaryTreeButton_clicked()
{
    _bTree = new BinaryTree<int>(ui->newBinaryTreeInput->text().toInt());

    ui->newBinaryTreeInput->setText("");

    ui->newBinaryTreeButton->setEnabled(false);

    updateTreeTable(setTree, *_bTree, ui->binaryTree);

    updatePathBeforeElemText(*_bTree, ui->pathBeforeElemBinaryTextField);

    this->_iBTW->setBinaryTree(this->_bTree);
    this->_iBTW->toRoot();
}

void MainWindow::on_toBinaryRootButton_clicked()
{
    this->_iBTW->toRoot();
}

void MainWindow::on_toBinaryParentButton_clicked()
{
    this->_iBTW->toParent();
}

void MainWindow::on_binaryChildrenTable_cellClicked(int row, int column)
{
    if (ui->binaryChildrenTable->item(row, column)->flags() == Qt::ItemFlag())
        return;

    this->_iBTW->toChild(column);
}

void MainWindow::on_newIntegerTreeButton_clicked()
{

}

void MainWindow::on_newIntegerTreeInput_textEdited()
{
    this->manageInputButtonEnabled(ui->newIntegerTreeInput, ui->newIntegerTreeButton);
}

void MainWindow::on_addIntegerChildButton_clicked()
{

}

void MainWindow::on_addIntegerInput_textEdited()
{

    this->manageInputButtonEnabled(ui->addIntegerInput, ui->addIntegerChildButton);
}

void MainWindow::on_getIntegerPathSelectedButton_clicked()
{

}

void MainWindow::on_getIntegerPathByValueButton_clicked()
{

}

void MainWindow::on_getIntegerPathInput_textEdited()
{
    this->manageInputButtonEnabled(ui->getIntegerPathInput, ui->getIntegerPathByValueButton);
}

void MainWindow::on_removeIntegerSelectedButton_clicked()
{

}

void MainWindow::on_removeIntegerByValueButton_clicked()
{

}

void MainWindow::on_removeIntegerInput_textEdited()
{
    this->manageInputButtonEnabled(ui->removeIntegerInput, ui->removeIntegerByValueButton);
}
