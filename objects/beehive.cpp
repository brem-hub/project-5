#include "beehive.h"
#include "../utils/settings.h"

Beehive::Beehive(int number_of_bees)
    : current_amount_of_honey_(0),
      current_number_of_bees_(number_of_bees) {

}

void Beehive::setAmountOfHoneyLocked(int new_amount) {
    bool locker = honey_mutex_.try_lock();

    current_amount_of_honey_ = new_amount;

    if (locker) {
        honey_mutex_.unlock();
    }
}

int Beehive::getCurrentNumberOfBees() {
    // we create local copy so real value of current_number_of_bees_ is not a data race.
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

void Beehive::appendHoney() {
    honey_mutex_.lock();
    if (current_amount_of_honey_ + 1 <= TOTAL_AMOUNT_OF_HONEY) {
        current_amount_of_honey_++;
    }
    honey_mutex_.unlock();
}
void Beehive::underAttack() {
    // wait for first possibility to lock and lock.
    honey_mutex_.lock();
    bee_mutex_.lock();
}

void Beehive::releaseAttack() {
    honey_mutex_.unlock();
    bee_mutex_.unlock();
}
