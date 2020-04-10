#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <QString>
#include <vector>
#include "train.h"

std::vector<unsigned long long> benchmarkVector(int n);

std::vector<unsigned long long> benchmarkTextFile(int n);

std::vector<unsigned long long> benchmarkBinFile(int n);

unsigned long long benchSortingBySeq(QString sorting, std::vector<QString> sortingSequence, std::vector<train>& trains, std::vector<train>& temp);

#endif // BENCHMARK_H
