#include "functs.h"
#include <QFile>
#include <QDebug>
#include <QRegularExpression>

std::vector<Task *> getTasks(QString filepath, QString keyObj)
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
        taskData[1] = keyObj + taskData[1];

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

std::vector<Station> getStations(QString filepath)
{
    QFile file(filepath);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "[ ERROR ] failed to open file " << filepath;
        return {};
    }

    std::vector<Station> stations;

    QString stationQstr;
    QStringList stationData;

    QTextStream stream(&file);

    while (!stream.atEnd()) {
        stationQstr = file.readLine();
        stationQstr = stationQstr.simplified();

        stationData = stationQstr.split(",");

        Station station = {stationData[0], stationData[1].simplified() == "d", stationData[2].simplified() == "d"};

        stations.push_back(station);
    }


    return stations;
}

std::vector<Station> getSection(std::vector<Station> line, QString fromSt, QString toSt)
{

    std::vector<Station> section;
    bool inSection = false;

    for (Station st : line) {

        if (!inSection && (st.name == fromSt || st.name == toSt)) {

            inSection = true;
            section.push_back(st);
            continue;

        }

        if (!inSection) continue;

        section.push_back(st);

        if (inSection && (st.name == fromSt || st.name == toSt)) {

            inSection = false;
            break;

        }
    }

    if (inSection) return {};

    return section;

}

MultilevelQueue<QString> lineSectToMlQ(std::vector<Station> line)
{

    MultilevelQueue<QString> mlQ;

    for (uint stNum = 0; stNum < line.size(); stNum++) {

        QString stFilepath = "station_";
        stFilepath += (line[stNum].stLayingDeep ? "deep" : "shallow");
        stFilepath += ".txt";


        mlQ.loadPrQ(tasksToPrQ(getTasks(stFilepath, "St.<" + line[stNum].name + "> ")));


        if (stNum == line.size() - 1) break;

        QString tunFilepath = "tunnel_";
        tunFilepath += (line[stNum].nextTunLayingDeep ? "deep" : "shallow");
        tunFilepath += ".txt";

        mlQ.loadPrQ(tasksToPrQ(getTasks(tunFilepath, "Tun.<" + line[stNum].name + "-" + line[stNum+1].name + "> ")));

    }

    return mlQ;

}
