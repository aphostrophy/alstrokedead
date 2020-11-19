#include <stdio.h>
#include "../Header/arrayPair.h"
#include "../Header/arrayTriplet.h"
#include "../Header/boolean.h"

int main(){
    Triplet_TabInt Upgrade;
    ArrayTriplet_MakeEmpty(&Upgrade);
    ArrayTriplet_BacaIsi(&Upgrade, "../Saves/HargaUpgrade.txt");
    ArrayTriplet_TulisIsiTab(Upgrade);printf("\n");
    return 0;
}