#ifndef FUNCTS_H
#define FUNCTS_H
#include <vector>

int getRandomInt(int min, int max);

void updateRandomSeed();

int* createRandomIntArray(int size, int from = 0, int to = -1);

int* createSortedIntArray(int size, bool ascending);

int* almostSortedIntArray(int size, bool ascending = true);

#endif // FUNCTS_H
