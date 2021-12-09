#include <iostream>
#include <thread>
#include "actors/winnie_the_pooh.h"
#include "actors/bee.h"
#include "utils/settings.h"
#include "utils/context.h"
#include "utils/signal_handler.h"
#include "utils/messages.h"
#include <vector>
#include <algorithm>

/*
 * Система флагов взята из предыдущих проектов, в частности из 2 проекта.
 * Для упрощения, были использованы std::vector и std::string,
 *  реализацию на char** и char* можно посмотреть во 2 проекте.
 */

// Флаги входных параметров.
// Флаг --help
const std::vector<std::string> kHelpFlags = {"-h", "--help"};
// Флаг --number-of-bees
const std::vector<std::string> kNumberOfBeesFLags = {"-n", "--number-of-bees"};

// Глобальный код ошибки.
int error_code;

// Проверить, если флаг верен.
inline bool is_flag_valid(const std::string& input, const std::vector<std::string>& possible_flags){
    return std::any_of(possible_flags.begin(), possible_flags.end(), [&](auto lvl) {return lvl == input; });
}

// Найти флаг в argv.
int find_flag(const std::vector<std::string>& argv, const std::vector<std::string>& possible_flags){
    for (int i = 0; i < argv.size(); ++i){
        if (is_flag_valid(argv[i], possible_flags))
            return i;
    }
    return -1;
}

// Найти флаг --help.
bool find_help_flag(const std::vector<std::string>& argv) {
    return find_flag(argv, kHelpFlags) != -1;
}

// Найти флаг --number-of-bees.
int find_number_of_bees_flag(const std::vector<std::string>& argv) {
    int number_of_bees_flag_index = find_flag(argv, kNumberOfBeesFLags);

    if (number_of_bees_flag_index == -1) {
        error_code = 1;
        return 0;
    }

    if (number_of_bees_flag_index == argv.size() - 1) {
        error_code = 1;
        return 0;
    }
    try {
        return std::stoi(argv[number_of_bees_flag_index + 1]);
    } catch (...) {
        error_code = 1;
        return 0;
    }
}

int main(int argc, char* argv[]) {
    error_code = 0;

    std::vector<std::string> args(argv + 1, argv + argc);

    if (find_help_flag(args)) {
        std::cout << HELP_MESSAGE;
        return 0;
    }

    int number_of_bees = find_number_of_bees_flag(args);

    if (error_code != 0) {
        std::cout << ARGC_EXCEPTION_MESSAGE;
        return error_code;
    }

    if (number_of_bees < DANGEROUS_NUMBER_OF_BEES) {
        std::cout << ARGC_EXCEPTION_MESSAGE;
        error_code = 1;
        return error_code;
    }

    Beehive hive(number_of_bees);
    WinnieThePooh winnie(&hive);

    std::vector<Bee> bees;
    std::vector<std::thread> bee_threads;

    context exit_context;

    // Запускаем потоки пчел и Винни-Пуха.
    bees.reserve(number_of_bees);
    bee_threads.reserve(number_of_bees);
    for (int i = 0; i < number_of_bees; ++i) {
        bees.emplace_back(&hive, i);
        bee_threads.emplace_back(&Bee::run, bees[i], &exit_context);
    }
    std::thread winnie_the_pooh(&WinnieThePooh::run, winnie, &exit_context);


    // Устанавливаем контекст отмены в обработчика прерывания.
    // При получении SIGINT все пчелы и Винни-Пух при первой же возможности закончат выполнение.
    signal_handler::handle(&exit_context);

    // Дожидаемся окончания всех потоков.
    winnie_the_pooh.join();
    for (int i = 0; i < number_of_bees; ++i) {
        bee_threads[i].join();
    }

    return 0;
}
