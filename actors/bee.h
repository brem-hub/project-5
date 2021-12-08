#pragma once

#include <cstdio>
#include "../objects/beehive.h"

// class bee represents one bee that lives in the Beehive.
// it can get out of the Beehive to gather some honey if needed.
// if it is the last bee in the hive - it won't leave.
class Bee {
 public:
  explicit Bee(const Beehive* beehive, void* context, int uuid);

  void run();

 private:

  static void doImportantWork();

 private:
  Beehive* beehive_;
  void* context_;
  int uuid_;
};
