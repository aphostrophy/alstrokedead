#include <stdio.h>
#include "../arrayPair/arrayPair.h"
#include "arrayTriplet.h"
#include "../boolean.h"

int main(){
    Triplet_TabInt Upgrade;
    ArrayTriplet_MakeEmpty(&Upgrade);
    ArrayTriplet_BacaIsi(&Upgrade, "../Saves/HargaUpgrade.txt");
    ArrayTriplet_TulisIsiTab(Upgrade);printf("\n");
    return 0;
}