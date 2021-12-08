#pragma once

#include <thread>
#include <mutex>

class Beehive {
 public:
  explicit Beehive(int number_of_bees);

  int getCurrentNumberOfBees();

  int getCurrentAmountOfHoney();

  void setAmountOfHoneyLocked(int new_amount);

  void appendBee();

  bool tryReleaseBee();

  void appendHoney();

  void underAttack();

  void releaseAttack();

 private:

  std::mutex bee_mutex_;
  int current_number_of_bees_{};

  std::mutex honey_mutex_;
  int current_amount_of_honey_{};
};
