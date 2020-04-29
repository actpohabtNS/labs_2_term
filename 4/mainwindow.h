#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>

#include "treewidget.h"
#include "interactivetreeview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void manageInputButtonEnabled(QLineEdit *input, QPushButton* button);
    void setupNumberInputButtons();
    void setupBinaryTree();
    void setupTree();
    void setupBinaryTreeUI();
    void setupTreeUI();

    template <typename T>
    void updateTreeTable(void setTree(Tree<T>&, QTreeWidget*), Tree<T>& tree, QTreeWidget* treeWidget)
    {
        treeWidget->clear();
        setTree(tree, treeWidget);
    }

    template <typename treeType>
    void updatePathBeforeElemText(const treeType& tree, QTextBrowser* browser)
    {
        QString QStrPaths = tree.getQStrPaths();
        browser->setText(QStrPaths);
    }

private slots:
    void on_addBinaryInput_textEdited(const QString &arg1);

    void on_threadizeButton_clicked();

    void on_removeThreadsButton_clicked();

    void on_addBinaryChildButton_clicked();

    void on_newBinaryTreeButton_clicked();

    void on_newBinaryTreeInput_textEdited(const QString &arg1);

    void on_toBinaryRootButton_clicked();

    void on_toBinaryParentButton_clicked();

    void on_binaryChildrenTable_cellClicked(int row, int column);

    void on_newIntegerTreeButton_clicked();

    void on_newIntegerTreeInput_textEdited();

    void on_addIntegerChildButton_clicked();

    void on_addIntegerInput_textEdited();

    void on_getIntegerPathSelectedButton_clicked();

    void on_getIntegerPathByValueButton_clicked();

    void on_getIntegerPathInput_textEdited();

    void on_removeIntegerSelectedButton_clicked();

    void on_removeIntegerByValueButton_clicked();

    void on_removeIntegerInput_textEdited();

private:
    Ui::MainWindow *ui;

    BinaryTree<int>* _bTree;
    GeneralTree<int>* _tree;
    InteractiveTreeView<int>* _iBTW;
    InteractiveTreeView<int>* _iTW;
};
#endif // MAINWINDOW_H
