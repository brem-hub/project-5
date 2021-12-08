#pragma once
#include <random>


static int random(int min, int max) {
    return min + std::rand() % ((max + 1) - min);
}