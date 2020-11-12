#include "../Header/repair.h"

void RepairWahana(Wahana *W, char id) {
    char status = getStatus(W,id);
    if (status == 'B') {
        (*W).TI[GetIndex(W,id)].status = 'G';
    }
}