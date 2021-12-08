#include "bee.h"
#include "../utils/settings.h"
#include "../utils/utils.h"

Bee::Bee(const Beehive *beehive, void *context, int uuid)
    : beehive_(const_cast<Beehive *>(beehive)),
      context_(context),
      uuid_(uuid)
{
}

void Bee::run() {
    printf("Initiated bee %d\n", uuid_);
    // main cycle of action.
    while (true) {
        // if context is not null - break from the cycle.
        if (context_) {
            printf("Bee %d stopping it's cycle\n", uuid_);
            return;
        }

        if (beehive_->tryReleaseBee()) {
            printf("Bee %d left the hive to get some honey\n", uuid_);
            // could release from the hive.
            // go and get some honey.
            doImportantWork();

            printf("Bee %d returned to the hive\n", uuid_);
            // return to the hive.
            beehive_->appendBee();

            printf("Bee %d put honey in the save spot\n", uuid_);
            // bring honey.
            beehive_->appendHoney();

            continue;
        }

        // stay in hive and do something.
        doImportantWork();
    }
}
void Bee::doImportantWork() {
    std::chrono::milliseconds timer(random(MIN_WAIT_BEES, MAX_WAIT_BEES));
    std::this_thread::sleep_for(timer);
}
