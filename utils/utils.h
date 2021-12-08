#pragma once
#include <random>

/*
 * Генерация случайного числа.
 * @param: min - минимальная граница.
 * @param: max - максимальная граница.
 * @returns: число из интервала [min, max].
 */
static int random(int min, int max) {
    return min + std::rand() % ((max + 1) - min);
}

/*
 * Остановить текущий поток на время в промежутке [min, max].
 * @param: min - минимальное время ожидания в мс.
 * @param: max - максимальное время ожидания в мс.
 */
static void doImportantWork(int min, int max) {
    std::chrono::milliseconds timer(random(min, max));
    std::this_thread::sleep_for(timer);
}