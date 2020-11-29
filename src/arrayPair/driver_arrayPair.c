#include <stdio.h>
#include "../arrayPair/arrayPair.h"
#include "../boolean.h"

int main(){
    TabInt Action, Barang;
    ArrayPair_MakeEmpty(&Action);
    ArrayPair_MakeEmpty(&Barang);
    ArrayPair_BacaIsi(&Action, "../Saves/ActionPrice.txt");
    ArrayPair_TulisIsiTab(Action);printf("\n");
    ArrayPair_BacaIsi(&Barang, "../Saves/Materials.txt");
    ArrayPair_TulisIsiTab(Barang);printf("\n");
    return 0;
}