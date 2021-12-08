#include "bee.h"
#include "../utils/settings.h"
#include "../utils/utils.h"

Bee::Bee(const Beehive *beehive, int uuid)
    : beehive_(const_cast<Beehive *>(beehive)),
      uuid_(uuid)
    {
    }

void Bee::run(context* ctx) {
    printf("Initiated bee %d\n", uuid_);
    // Основной цикл.
    while (true) {
        // Если контекст был закрыт, выйти из функции и закрыть поток.
        if (ctx->done()) {
            printf("Bee %d stopping it's cycle\n", uuid_);
            return;
        }

        // Пытаемся вылететь из улья.
        if (beehive_->tryReleaseBee()) {
            printf("Bee %d left the hive to get some honey\n", uuid_);
            // Пчела смогла вылететь из улья.
            // Эмуляция полезной работы ожиданием.
            doImportantWork(MIN_WAIT_BEES, MAX_WAIT_BEES);

            // Пчела вернулась в гнездо.
            beehive_->appendBee();
            printf("Bee %d returned to the hive\n", uuid_);

            // Положить мед в общую кучу.
            // Т.к. между возвращением пчелы и тем, как она положит мед в кучу отпускается мьютекс
            //  и различные мьютексы покрывают количество меда и количество пчел,
            //  то другая пчела или Винни-Пух может взять мьютекс на количество меда.
            int current_honey = beehive_->appendHoney();

            if (current_honey == TOTAL_AMOUNT_OF_HONEY) {
                printf("Bee %d brought honey, but there are no place for it, skipping\n", uuid_);
            } else {
                printf("Bee %d put honey in the save spot, last time there were %d oz of honey\n", uuid_, current_honey);
            }
        }

        // Эмуляция полезной работы ожиданием.
        doImportantWork(MIN_WAIT_BEES, MAX_WAIT_BEES);
    }
}

