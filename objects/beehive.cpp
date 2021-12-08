#include "beehive.h"
#include "../utils/settings.h"

Beehive::Beehive(int number_of_bees)
    : current_amount_of_honey_(0),
      current_number_of_bees_(number_of_bees)
      {

      }

void Beehive::resetHoneyAmount() {
    honey_mutex_.lock();
    current_amount_of_honey_ = 0;
    honey_mutex_.unlock();
}

int Beehive::getCurrentNumberOfBees() {
    // Создаем копию переменной current_number_of_bees_ под мьютексом, чтобы избежать data-race.
    bee_mutex_.lock();
    int local_copy = current_number_of_bees_;
    bee_mutex_.unlock();
    return local_copy;
}

int Beehive::getCurrentAmountOfHoney() {
    honey_mutex_.lock();
    int local_copy = current_amount_of_honey_;
    honey_mutex_.unlock();
    return local_copy;
}

void Beehive::appendBee() {
    bee_mutex_.lock();
    current_number_of_bees_++;
    bee_mutex_.unlock();
}

bool Beehive::tryReleaseBee() {
    bool res = false;

    // Т.к. условие и на количество меда и на количество пчел, то берем оба мьютекса.
    bee_mutex_.lock();
    honey_mutex_.lock();
    if (current_number_of_bees_ > LEAST_NUMBER_OF_BEES && current_amount_of_honey_ < TOTAL_AMOUNT_OF_HONEY) {
        current_number_of_bees_--;
        res = true;
    }
    honey_mutex_.unlock();
    bee_mutex_.unlock();
    return res;
}

int Beehive::appendHoney() {
    honey_mutex_.lock();
    int current_honey = current_amount_of_honey_;
    if (current_amount_of_honey_ + 1 <= TOTAL_AMOUNT_OF_HONEY) {
        current_amount_of_honey_++;
    }
    honey_mutex_.unlock();
    return current_honey;
}
