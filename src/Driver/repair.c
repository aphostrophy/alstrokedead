#include "../Header/repair.h"

void RepairWahana(Wahana *W, char id) {
    char status = getStatus(W,id);
    char* nama = getNama(W,id);
    if (status == 'B') {
        int a;
        for (int i = 0; i < 8; i++) {
            if ((*W).TI[i].nama == nama) {
                a = i;
            }
        }
        (*W).TI[a].status = 'G';
    }
}