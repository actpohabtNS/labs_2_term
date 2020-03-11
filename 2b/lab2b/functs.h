#ifndef FUNCTS_H
#define FUNCTS_H

#include <vector>
#include <QString>
#include <QLabel>
#include "task.h"
#include "priorityqueue.h"

std::vector<Task*> getTasks(QString filepath);

PriorityQueue<QString> tasksToPrQ(std::vector<Task*> tasks);

int getRandomInt(int min, int max);

void updateRandomSeed();

void setLabelText(QLabel* label, QString text);

#endif // FUNCTS_H
