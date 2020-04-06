#ifndef VISUALIZE_H
#define VISUALIZE_H
#include "table.h"
#include <queue>

struct visualization{
    short type; //0 - comparison, 1 - swap, 2 - replace from an auxilary array
    int idx1, idx2;
    QString text;
};

void visualizeComparison(table* table, int elem1, int elem2);
void visualizeSwap(table* table, int elem1, int elem2);
void visualizeReplace(table* table, int idx, QString text);
void visualizeMove(QTimer* timer, std::queue<visualization>* visuals, table* table);
void visualizeItems(std::queue<visualization> *visuals, table *table, Date* afterSortingArr = nullptr);

#endif // VISUALIZE_H
