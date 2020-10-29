#include <stdio.h>
#include "../Header/arrayPair.h"
#include "../Header/boolean.h"

int main(){
    TabInt Action, Barang;
    MakeEmpty(&Action);
    MakeEmpty(&Barang);
    BacaIsi(&Action, "../Saves/Actions.txt");
    TulisIsiTab(Action);printf("\n");
    BacaIsi(&Barang, "../Saves/Materials.txt");
    TulisIsiTab(Barang);printf("\n");
    return 0;
}