#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>

#include "filesystemwidget.h"
#include "interactivetreeview.h"
#include "console.h"
#include "filesystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void manageInputButtonEnabled(QLineEdit* input, QPushButton* button);
    void manageInputButtonEnabled(QTreeWidget* widget, QPushButton* button);
    void manageInputButtonEnabled(QLineEdit* input, QTreeWidget* widget, QPushButton* button);

    void setupNumberInputButtons();
    void setupBinaryTree();
    void setupTree();
    void setupFS();
    void setupBinaryTreeUI();
    void setupTreeUI();
    void setupFSUI();

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

    void on_toIntegerRootButton_clicked();

    void on_toIntegerParentButton_clicked();

    void on_integerChildrenTable_cellClicked(int row, int column);

    void on_integerTree_itemSelectionChanged();

    void on_fileSystem_itemSelectionChanged();

    void on_filterElemButton_clicked();

private:
    Ui::MainWindow *ui;

    BinaryTree<int>* _bTree;
    GeneralTree<int>* _tree;
    TreeWidget<int>* _bTW;
    TreeWidget<int>* _tW;
    FileSystemWidget* _fsW;
    InteractiveTreeView<int>* _iBTV;
    InteractiveTreeView<int>* _iTV;
    Console* _console;
    FileSystem* _fs;
};
#endif // MAINWINDOW_H
