#include "visualize.h"
#include <QTimer>
#include <QDebug>
#include <QMetaObject>

const int COMP_DUR = 900;
const int SWAP_DUR = 1500;
const int REP_DUR = 1200;

void visualizeComparison(table *table, int elem1, int elem2)
{
    table->highlightItems(0, elem1, 0, elem2, Qt::lightGray);

    QTimer::singleShot(COMP_DUR, [table, elem1, elem2]{table->highlightItems(0, elem1, 0, elem2, Qt::white);});
}

void visualizeSwap(table *table, int elem1, int elem2)
{
    table->highlightItems(0, elem1, 0, elem2, Qt::yellow);

    QTimer::singleShot(SWAP_DUR/2, [table, elem1, elem2]{table->swapItemsText(0, elem1, 0, elem2);});

    QTimer::singleShot(SWAP_DUR, [table, elem1, elem2]{table->highlightItems(0, elem1, 0, elem2, Qt::white);});
}

void visualizeReplace(table *table, int idx, QString text)
{
    table->getTable()->item(0, idx)->setBackground(Qt::green);

    QTimer::singleShot(REP_DUR/2, [table, idx, text]{table->getTable()->item(0, idx)->setText(text);});

    QTimer::singleShot(REP_DUR, [table, idx]{table->getTable()->item(0, idx)->setBackground(Qt::white);});
}

void visualizeMove(QTimer* timer, std::queue<visualization> *visuals, table *table, Date* afterSortingArr)
{
    visualization vis = visuals->front();

    switch (vis.type) {
    case 0:
        timer->setInterval(COMP_DUR+100);
        visualizeComparison(table, vis.idx1, vis.idx2);
        break;
    case 1:
        timer->setInterval(SWAP_DUR+100);
        visualizeSwap(table, vis.idx1, vis.idx2);
        break;
    case 2:
        timer->setInterval(REP_DUR+100);
        visualizeReplace(table, vis.idx1, vis.text);
        break;
    default:
        qDebug() << "Uknown visualization type:" << vis.type;
        break;
    }

    visuals->pop();

    if (visuals->empty())
    {
        if (afterSortingArr)
        {
            table->setColor(Qt::green);

            QTimer::singleShot(1000, [table, afterSortingArr]{table->setDateArray(afterSortingArr, table->getTable()->columnCount());});

            QTimer::singleShot(1000, [table]{table->setColor(Qt::white);});
        }

        timer->stop();
    }

}

void visualizeItems(std::queue<visualization> *visuals, table *table, Date* afterSortingArr)
{
    QTimer* timer = new QTimer();
    timer->setInterval(200);
    QObject::connect(timer, &QTimer::timeout, [timer, visuals, table, afterSortingArr]{visualizeMove(timer, visuals, table, afterSortingArr);});
    timer->start();
}

