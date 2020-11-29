#include <stdio.h>
#include "../arrayPair/arrayPair.h"
#include "../mesinkata/mesinkar.h"
#include "../mesinkata/mesinkata.h"
#include "../boolean.h"

int main(){
    TabInt Action, Barang;
    ArrayPair_MakeEmpty(&Action);
    ArrayPair_MakeEmpty(&Barang);
    ArrayPair_BacaIsi(&Action, "../file/ActionPrice.txt");
    ArrayPair_TulisIsiTab(Action);printf("\n");
    ArrayPair_BacaIsi(&Barang, "../file/Materials.txt");
    ArrayPair_TulisIsiTab(Barang);printf("\n");
    return 0;
}