#pragma once

#include "../objects/beehive.h"
class WinnieThePooh {
 public:
  WinnieThePooh(const Beehive* beehive, void* context);

  void run();

  static void doImportantWork();

 private:
  void attack();

 private:
  Beehive* beehive_;
  void* context_;

};
