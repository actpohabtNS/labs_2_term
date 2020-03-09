#ifndef BENCHMARK_H
#define BENCHMARK_H
#include "arrcilcularlinkedlist.h"
#include "vectcircularlinkedlist.h"
#include "circularlinkedlist.h"
#include <chrono>
#include <vector>
#include <QtDebug>


std::vector<unsigned long long> benchmarkArray(int startN, int n);

std::vector<unsigned long long> benchmarkVector(int startN, int n);

std::vector<unsigned long long> benchmarkSpecStruct(int startN, int n);

template<typename T> std::vector<unsigned long long> benchmarkCLL(int startN, int n) {
    std::vector<unsigned long long> res;

    T CLL;

    for (int i = 0; i < startN; i++) {
        Station* st = new Station;
        updateRandomSeed();
        st->randomize();

        CLL.push(st);
    }

    auto start = std::chrono::high_resolution_clock::now();
// ==========================================================
//                           Create empty


    for (int i = 0; i < n; i ++) {

        T create_CLL;
    }



// ==========================================================
    auto stop = std::chrono::high_resolution_clock::now();
    auto durCreateEmpty = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    res.push_back(durCreateEmpty.count());

    start = std::chrono::high_resolution_clock::now();
// ==========================================================
//                           Insert

    for (int i = 0; i < n; i ++) {
        Station* st = new Station;
        st->randomize();

        CLL.insert(getRandomInt(1, n), st);
    }


// ==========================================================
    stop = std::chrono::high_resolution_clock::now();
    auto durInsert = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    res.push_back(durInsert.count());

    start = std::chrono::high_resolution_clock::now();
// ==========================================================
//                           Get

    for (int i = 0; i < n; i ++) {
        Station* st = CLL.get(getRandomInt(1, n));
        st->name = st->name.toInt() + 1;
    }

// ==========================================================
    stop = std::chrono::high_resolution_clock::now();
    auto durGet = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    res.push_back(durGet.count());

    start = std::chrono::high_resolution_clock::now();
// ==========================================================
//                           Set

    for (int i = 0; i < n; i ++) {
        Station* st = new Station;
        st->randomize();

        CLL.set(getRandomInt(1, n), st);
    }

// ==========================================================
    stop = std::chrono::high_resolution_clock::now();
    auto durSet = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    res.push_back(durSet.count());

    start = std::chrono::high_resolution_clock::now();
// ==========================================================
//                           Remove

    for (int i = 0; i < n; i ++) {
        CLL.remove(getRandomInt(1, n));
    }

// ==========================================================
    stop = std::chrono::high_resolution_clock::now();
    auto durRemove = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    res.push_back(durRemove.count());

    auto durSum = std::chrono::duration_cast<std::chrono::milliseconds>(durCreateEmpty + durInsert + durGet + durSet + durRemove);
    res.push_back(durSum.count());

    return res;
}

#endif // BENCHMARK_H
