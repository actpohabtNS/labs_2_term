#include "random.h"
#include <QRegularExpression>
#include <random>

std::random_device device;
std::seed_seq seq{device(),(unsigned)time(nullptr)};
std::mt19937 generator(seq);

int getRandomInt(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}
