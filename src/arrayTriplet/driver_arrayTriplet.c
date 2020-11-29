#include <stdio.h>
#include "../arrayPair/arrayPair.h"
#include "arrayTriplet.h"
#include "../boolean.h"
#include "../mesinkata/mesinkar.h"
#include "../mesinkata/mesinkata.h"

int main(){
    Triplet_TabInt Upgrade;
    ArrayTriplet_MakeEmpty(&Upgrade);
    ArrayTriplet_BacaIsi(&Upgrade, "../file/HargaUpgrade.txt");
    ArrayTriplet_TulisIsiTab(Upgrade);printf("\n");
    return 0;
}