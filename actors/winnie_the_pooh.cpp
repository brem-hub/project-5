#include <cstdio>
#include "winnie_the_pooh.h"
#include "../utils/utils.h"
#include "../utils/settings.h"

WinnieThePooh::WinnieThePooh(const Beehive *beehive)
    : beehive_(const_cast<Beehive *>(beehive))
    {
    }

void WinnieThePooh::run(context* ctx) {
    printf("Initiated Winnie-the-Pooh\n");
    // Основной цикл.
    while (true) {
        // Если контекст был закрыт, выйти из функции и закрыть поток.
        if (ctx->done()) {
            printf("Winnie-the-Pooh exiting from it's cycle\n");
            return;
        }

        // Если количество меда достаточно, Винни-Пух попытается атаковать улей.
        // Если у Винни-Пуха не получится получить весь мед, то он вылечится
        //  и опять попытается атаковать.
        if (beehive_->getCurrentAmountOfHoney() > BOUNDARY_AMOUNT_OF_HONEY) {
            attack();
            continue;
        }

        // Эмуляция полезной работы ожиданием.
        doImportantWork(MIN_WAIT_WINNIE, MAX_WAIT_WINNIE);
    }
}

void WinnieThePooh::attack() {
    printf("Winnie-the-Pooh tries to attack the hive\n");

    // Мы считаем, что атака происходит моментально, поэтому не берем мьютексы на атаку,
    //  только на текущее количество пчел в улье.
    // При большом количестве пчел, Винни-Пух не сможет нападать на улей, при дефолтных условиях, т.к.
    //  ограничение на 30 единиц меда позволит пчелам очень быстро заполнить улей,
    //  а ограничение в 3 пчелы не позволит Винни-Пуху украсть мед, в итоге ситуация эскалируется до того,
    //  что Винни-Пух будет пытаться безуспешно украсть мед, а пчелы будут сидеть в улье, т.к. он заполнен
    //  и нет смысла вылетать за новым медом. Для того чтобы исправить данную ситуацию, необходимо находить баланс
    //  между количеством пчел и количеством меда. Настройки находятся в /utils/settings.h
    int current_bees = beehive_->getCurrentNumberOfBees();
    if (current_bees > DANGEROUS_NUMBER_OF_BEES) {
        // Винни-Пух был напуган пчелами.
        printf("Winnie-the-Pooh got scared and flew away, because there were %d bees\n", current_bees);
        // Эмуляция "лечения" укуса.
        doImportantWork(MIN_WAIT_WINNIE, MAX_WAIT_WINNIE);
        return;
    }

    int current_honey = beehive_->getCurrentAmountOfHoney();
    printf("Winnie-the-Pooh succeeded in stealing the honey. He stole %d oz of honey\n", current_honey);

    // Винни-Пух крадет весь мед.
    beehive_->resetHoneyAmount();
}
