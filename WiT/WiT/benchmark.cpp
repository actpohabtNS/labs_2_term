#include "benchmark.h"
#include "binfile.h"
#include "functs.h"
#include "textfile.h"
#include "train.h"
#include "searchoptionswindow.h"
#include <QFile>

std::vector<unsigned long long> benchmarkVector(int elements)
{
    std::vector<unsigned long long> res;
    auto start = std::chrono::high_resolution_clock::now();
// ==========================================================
//                           Generate + add


    std::vector<train> trains;

    for (int i = 0; i < elements; i ++) {
        srand(static_cast<unsigned int>(time(0) + i*100000));

        train randomTrain;
        randomTrain.randomize();
        trains.push_back(randomTrain);
    }



// ==========================================================
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    res.push_back(duration1.count());

    start = std::chrono::high_resolution_clock::now();
// ==========================================================
//                          Search


    std::vector<train> foundTrains = searchTrains(trains, "54", {false, true, true, false, false, false, true, true, true});


// ==========================================================
    stop = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    res.push_back(duration2.count());

    res.push_back(duration1.count() + duration2.count());

// ==========================================================
//                          File size

    res.push_back(sizeof (train) * trains.size());

// ==========================================================

    return res;
}




std::vector<unsigned long long> benchmarkTextFile(int elements)
{
    std::vector<unsigned long long> res;
    auto start = std::chrono::high_resolution_clock::now();
// ==========================================================
//                           Generate + add


    std::vector<train> trains;

    for (int i = 0; i < elements; i ++) {
        srand(static_cast<unsigned int>(time(0) + i*100000));

        train randomTrain;
        randomTrain.randomize();
        trains.push_back(randomTrain);
    }

    textFile textfile("benchText.txt");
    textfile.writeTrains(trains);

// ==========================================================
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    res.push_back(duration1.count());

    trains = {};

    start = std::chrono::high_resolution_clock::now();
// ==========================================================
//                          Read


    trains = textfile.getData();


// ==========================================================
    stop = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    res.push_back(duration2.count());

    start = std::chrono::high_resolution_clock::now();
// ==========================================================
//                          Search


    std::vector<train> foundTrains = searchTrains(trains, "54", {false, true, true, false, false, false, true, true, true});


// ==========================================================
    stop = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    res.push_back(duration3.count());

    res.push_back(duration1.count() + duration2.count() + duration3.count());

// ==========================================================
//                          File size


    QFile* qfile = new QFile("benchText.txt");
    res.push_back(qfile->size());


// ==========================================================

    return res;
}




std::vector<unsigned long long> benchmarkBinFile(int elements)
{
    std::vector<unsigned long long> res;
    auto start = std::chrono::high_resolution_clock::now();
// ==========================================================
//                           Generate + add


    std::vector<train> trains;

    binFile binfile("benchBin.bin");

    for (int i = 0; i < elements; i ++) {
        srand(static_cast<unsigned int>(time(0) + i*100000));

        train randomTrain;
        randomTrain.randomize();

        binfile.addTrain(randomTrain);
        //trains.push_back(randomTrain);
    }

    //binfile.writeTrains(trains);

// ==========================================================
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    res.push_back(duration1.count());

    trains = {};

    start = std::chrono::high_resolution_clock::now();
// ==========================================================
//                          Read


    trains = binfile.getData();


// ==========================================================
    stop = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    res.push_back(duration2.count());

    start = std::chrono::high_resolution_clock::now();
// ==========================================================
//                          Search


    std::vector<train> foundTrains = searchTrains(trains, "54", {false, true, true, false, false, false, true, true, true});


// ==========================================================
    stop = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    res.push_back(duration3.count());

    res.push_back(duration1.count() + duration2.count() + duration3.count());

// ==========================================================
//                          File size


    QFile* qfile = new QFile("benchBin.bin");
    res.push_back(qfile->size());


// ==========================================================

    return res;
}
