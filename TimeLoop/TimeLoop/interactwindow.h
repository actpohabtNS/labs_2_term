#ifndef INTERACTWINDOW_H
#define INTERACTWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include "circularlinkedlist.h"
#include "table.h"

namespace Ui {
class interactWindow;
}

class interactWindow : public QWidget
{
    Q_OBJECT

public:
    explicit interactWindow(QWidget *parent = nullptr, bool demo = false);
    ~interactWindow();

    CircularLinkedList m_cll;

    table* m_table;

    QString m_fromSt = "";

    QString m_toSt = "";

    bool m_demoMode;

    void clearFromToStations();

    void loadLineUI(QString lineName);

    void enableButtonsEditingLine(bool enable);

    QString generateUniqueStName(QString userStName, QString strBeforeNumber);



private slots:
    void on_backButton_clicked();

    void on_loadKUTButton_clicked();

    void on_loadMCCButton_clicked();

    void on_loadMMCButton_clicked();

    void on_trainLineTable_itemSelectionChanged();

    void on_addLineButton_clicked();

    void on_addStButton_clicked();

    void on_removeStButton_clicked();

    void on_changeStButton_clicked();


    void selectRow(int row);

    void setTextInput(QLineEdit* input, QString text);

    void setGoBackEnabled(bool enabled);


private:
    Ui::interactWindow *ui;

signals:
    void backButtonClicked();
};

#endif // INTERACTWINDOW_H
