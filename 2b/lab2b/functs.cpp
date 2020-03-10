#include "functs.h"
#include <QFile>
#include <QDebug>
#include <QRegularExpression>


std::vector<Task *> getTasks(QString filepath)
{
    QFile file(filepath);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "[ ERROR ] failed to open file " << filepath;
        return {};
    }

    std::vector<Task*> tasks;

    QString taskQstr;
    QStringList taskData;

    QTextStream stream(&file);

    while (!stream.atEnd()) {
        taskQstr = file.readLine();
        taskQstr = taskQstr.simplified();

        taskData = taskQstr.split(",");

        tasks.push_back(new Task{taskData[0].toInt(), taskData[1]});
    }


    return tasks;
}

PriorityQueue<QString> tasksToPrQ(std::vector<Task *> tasks)
{
    PriorityQueue<QString> prQ;

    for (Task* task : tasks) {
        prQ.push(task->title, task->priority);
    }

    return prQ;
}
