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


int getRandomInt(int min, int max)
{

    updateRandomSeed();

    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void updateRandomSeed()
{
    auto time = std::chrono::high_resolution_clock::now().time_since_epoch();

    srand(static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::microseconds>(time).count()));
}

void setLabelText(QLabel *label, QString text)
{
    label->setText(text);
}
