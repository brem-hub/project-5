#include <cstdio>
#include "winnie_the_pooh.h"
#include "../utils/utils.h"
#include "../utils/settings.h"

WinnieThePooh::WinnieThePooh(const Beehive *beehive, void *context)
    : beehive_(const_cast<Beehive *>(beehive)),
      context_(context) {
}

void WinnieThePooh::run() {
    printf("Initiated Winnie-the-Pooh\n");
    while (true) {
        // if context is not null - break from the cycle.
        if (context_) {
            printf("Winnie-the-Pooh exiting from it's cycle\n");
            return;
        }

        if (beehive_->getCurrentAmountOfHoney() > BOUNDARY_AMOUNT_OF_HONEY) {
            // Winnie-the-Pooh can attack the hive.
            attack();
            continue;
        }

        // Winnie-the-Pooh sleeps.
        doImportantWork();
    }
}

void WinnieThePooh::doImportantWork() {
    std::chrono::milliseconds timer(random(MIN_WAIT_WINNIE, MAX_WAIT_WINNIE));
    std::this_thread::sleep_for(timer);
}

void WinnieThePooh::attack() {
    printf("Winnie-the-Pooh tries to attack the hive\n");
//    beehive_->underAttack();

    if (beehive_->getCurrentNumberOfBees() > DANGEROUS_NUMBER_OF_BEES) {
        // Winnie-the-Pooh got spooked.
        printf("Winnie-the-Pooh got scared and he flew away!\n");
//        beehive_->releaseAttack();
        doImportantWork();
        return;
    }

    printf("Winnie-the-Pooh succeeded in stealing the honey\n");
    // Steal all the honey.
    beehive_->setAmountOfHoneyLocked(0);
//    beehive_->releaseAttack();
}
