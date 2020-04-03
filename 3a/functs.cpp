#include "functs.h"
#include <QDebug>
#include <QRegularExpression>
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>


static std::random_device rd; // random device engine, usually based on /dev/random on UNIX-like systems
// initialize Mersennes' twister using rd to generate the seed
static std::mt19937 rng(rd());

int getRandomInt(int min, int max)
{
    static std::uniform_int_distribution<int> uid(min,max); // random dice
    return uid(rng); // use rng as a generator
}

void updateRandomSeed()
{
    auto time = std::chrono::high_resolution_clock::now().time_since_epoch();

    srand(static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::microseconds>(time).count()));
}

void randomizeIntArray(int arr[], int size, int from, int to)
{

    for (int i = 0; i < size; i++) {
        arr[i] = getRandomInt(from, to);
    }

}

std::vector<int> create_random_vector(int n) {
  std::random_device r;
  std::seed_seq      seed{r(), r(), r(), r(), r(), r(), r(), r()};
  std::mt19937       eng(seed); // a source of random data

  std::uniform_int_distribution<int> dist;
  std::vector<int> v(n);

  generate(begin(v), end(v), bind(dist, eng));
  return v;
}
