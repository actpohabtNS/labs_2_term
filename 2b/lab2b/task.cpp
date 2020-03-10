#include "task.h"
#include <QDebug>

Task::Task(int priority, QString title)
{
    this->priority = priority;
    this->title = title;
}

void Task::print()
{
    qDebug() << title;
}
