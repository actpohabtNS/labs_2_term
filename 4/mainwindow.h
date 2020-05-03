#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTimeEdit>
#include <QTextBrowser>

#include "filesystemwidget.h"
#include "treewidget.h"
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

    void clearAddElemInputs();
    void clearAllFilterInputs();

    void clearBinaryInputs();
    void clearIntegerInputs();
    void clearFSInputs();

    void manageInRangeInputs(QLineEdit* min, QLineEdit* max, QPushButton* button);
    void manageInRangeInputs(QTimeEdit* min, QTimeEdit* max, QPushButton* button);

    void printTotalAmountOfElems(int mode = 0);
    void printTimeElem(bool first);

    QTreeWidgetItem* getSelected() const;

    template <typename treeType>
    void updatePathBeforeElemText(const treeType& tree, QTextBrowser* browser)
    {
        QString QStrPaths = tree.getQStrPaths();
        browser->setText(QStrPaths);
    }

private slots:
    //---------------- Binary Tree ------------------

    void on_addBinaryInput_textEdited(const QString &arg1);

    void on_threadizeButton_clicked();

    void on_removeThreadsButton_clicked();

    void on_addBinaryChildButton_clicked();

    void on_newBinaryTreeButton_clicked();

    void on_newBinaryTreeInput_textEdited(const QString &arg1);

    void on_toBinaryRootButton_clicked();

    void on_toBinaryParentButton_clicked();

    void on_binaryChildrenTable_cellClicked(int row, int column);

    void on_binaryTreeDemoButton_clicked();



    //--------------- Integer Tree ------------------

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

    void on_integerTreeDemoButton_clicked();



    //--------------- File system ------------------

    void on_fileSystem_itemSelectionChanged();

    void on_newElemRootInput_textEdited();

    void on_newFileSystemButton_clicked();

    void on_removeSelectedElemButton_clicked();

    void on_isFolderCheckBox_stateChanged(int arg1);

    void on_addElemNameInput_textEdited();

    void on_addElemChildButton_clicked();

    void on_minSizeFilterElemInput_textEdited();

    void on_maxSizeFilterElemInput_textEdited();

    void on_minTimeFilterElemInput_userTimeChanged();

    void on_maxTimeFilterElemInput_userTimeChanged();

    void on_filterElemButton_clicked();

    void on_clearFilterElemButton_clicked();

    void on_getTotalAmountElemButton_clicked();

    void on_getFilesAmountElemButton_clicked();

    void on_getFoldersAmountElemButton_clicked();

    void on_getTotalSizeElemButton_clicked();

    void on_getFirstEditedElemButton_clicked();

    void on_getLastEditedElemButton_clicked();

    void on_fileSystemDemoButton_clicked();

private:
    Ui::MainWindow *ui;

    BinaryTree<int>* _bTree;
    GeneralTree<int>* _tree;
    TreeWidget* _bTW;
    TreeWidget* _tW;
    FileSystemWidget* _fsW;
    InteractiveTreeView<int>* _iBTV;
    InteractiveTreeView<int>* _iTV;
    Console* _console;
    FileSystem* _fs;
    Console* _fsConsole;
};
#endif // MAINWINDOW_H
