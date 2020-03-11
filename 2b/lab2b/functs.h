#ifndef FUNCTS_H
#define FUNCTS_H

#include <vector>
#include <QString>
#include "task.h"
#include "priorityqueue.h"

std::vector<Task*> getTasks(QString filepath);

PriorityQueue<QString> tasksToPrQ(std::vector<Task*> tasks);

#endif // FUNCTS_H
