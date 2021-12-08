#include <iostream>
#include <thread>
#include "actors/winnie_the_pooh.h"
#include "actors/bee.h"
#include <vector>


int main() {

    std::vector<Bee> bees;

    std::vector<std::thread> bee_threads;


    void** exit_context = new void *[1];

    Beehive hive(10);

    WinnieThePooh winnie(&hive, exit_context);

    bees.reserve(10);
    for (int i = 0; i < 10; ++i) {
        bees.emplace_back(&hive, exit_context, i);
    }

    std::thread winnie_the_pooh(&WinnieThePooh::run, winnie);

    bee_threads.reserve(10);
    for (int i = 0; i < 10; ++i) {
        bee_threads.emplace_back(&Bee::run, bees[i]);
    }


    // wait for 10 seconds
    std::chrono::seconds timer(10);
    std::this_thread::sleep_for(timer);

    // send exit command.
    // TODO(bremka): use context class.
    exit_context = (void*) 1;

    winnie_the_pooh.join();
    for (int i = 0; i < 10; ++i) {
        bee_threads[i].join();
    }

    return 0;
}
