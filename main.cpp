#include <iostream>
#include <thread>
#include "actors/winnie_the_pooh.h"
#include "actors/bee.h"
#include "utils/context.h"
#include "utils/signal_handler.h"
#include <vector>


int main() {

    std::vector<Bee> bees;

    std::vector<std::thread> bee_threads;

    context exit_context;

    int number_of_bees = 10;
    Beehive hive(number_of_bees);

    WinnieThePooh winnie(&hive);

    bees.reserve(number_of_bees);
    bee_threads.reserve(number_of_bees);
    for (int i = 0; i < number_of_bees; ++i) {
        bees.emplace_back(&hive, i);
        bee_threads.emplace_back(&Bee::run, bees[i], &exit_context);
    }

    std::thread winnie_the_pooh(&WinnieThePooh::run, winnie, &exit_context);

    signal_handler::handle(&exit_context);

    winnie_the_pooh.join();
    for (int i = 0; i < number_of_bees; ++i) {
        bee_threads[i].join();
    }

    return 0;
}
