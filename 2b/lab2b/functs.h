#ifndef FUNCTS_H
#define FUNCTS_H
#include <vector>
#include <QString>
#include <QLabel>
#include "task.h"
#include "priorityqueue.h"
#include "multilevelqueue.h"

struct Station {
    QString name;
    bool stLayingDeep;
    bool nextTunLayingDeep;
};

std::vector<Station> getStations(QString filepath);

std::vector<Station> getSection(std::vector<Station> line, QString fromSt, QString toSt);

MultilevelQueue<QString> lineSectToMlQ(std::vector<Station> line);

std::vector<Task*> getTasks(QString filepath,  QString keyObj = "");

PriorityQueue<QString> tasksToPrQ(std::vector<Task*> tasks);

int getRandomInt(int min, int max);

void updateRandomSeed();

void setLabelText(QLabel* label, QString text);

#endif // FUNCTS_H
