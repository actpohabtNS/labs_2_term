#ifndef GRAPHSWINDOW_H
#define GRAPHSWINDOW_H

#include <QWidget>
#include <QTimer>

#include "lgraph.h"
#include "mgraph.h"
#include "console.h"
#include "benchmark.h"

namespace Ui {
class GraphsWindow;
}

class GraphsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GraphsWindow(QWidget *parent = nullptr);
    ~GraphsWindow();

    void setGraphValues(const Graph& graph);

private slots:
    void on_createNewGraphButton_clicked();

    void on_adjMatrixRadioButton_clicked();

    void on_adjListRadioButton_clicked();

    void on_newEdgeFromInput_valueChanged(int arg1);

    void on_newEdgeToInput_valueChanged(int arg1);

    void on_newEdgeButton_clicked();

    void on_addNodeButton_clicked();

    void on_printGraphButton_clicked();

    void on_isConnectedButton_clicked();

    void on_isCyclicButton_clicked();

    void on_getComponentsButton_clicked();

    void on_minDist2Button_clicked();

    void on_minDist1AllButton_clicked();

    void on_minDistAllButton_clicked();

    void on_topSortButton_clicked();

    void on_spanningTreeButton_clicked();

    void on_minSpanningTreeButton_clicked();

    void on_toTheOtherGraphTypeButton_clicked();

    void on_demoButton_clicked();

    void on_isBenchmarkInput_stateChanged(int arg1);

private:
    Ui::GraphsWindow *ui;

    MGraph* _mgr;
    LGraph* _lgr;
    Graph* _currGraph;

    Console* _console;

    template <typename T, class ...Types>
    void _writeBench(QString text, T alg(Types ...Args), Types ...Args)
    {
        auto time = benchAlg(alg, Args...);

        this->_console->printTech(text + " " + QString::number(time) + " microseconds");
    }

    void _manageNewEdgeInputs();
    void _setNewEdgeMaxValues();
    void _setMinDist2MaxValues();
    void _setMinDist1ALLMaxValues();
    void _setMaxValues();
    void _setGraphs();
    void _setToOtherTypeButton();
    void _clearAllInputs();
};

#endif // GRAPHSWINDOW_H
