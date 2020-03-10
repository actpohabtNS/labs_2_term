#ifndef TASK_H
#define TASK_H

#include <QString>

class Task
{
public:
    Task(int priority = 0, QString title = "");

    void print();

    int priority;
    QString title;
};

#endif // TASK_H
