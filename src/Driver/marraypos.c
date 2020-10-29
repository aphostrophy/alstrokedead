#include <stdio.h>
#include "../Header/arraypos.h"
#include "../Header/boolean.h"

int main(){
    TabInt Action, Barang;
    ElType max,min;
    BacaIsi(&Action);
    TulisIsiTab(Action);printf("\n");
    BacaIsi(&Barang);
    TulisIsiTab(Barang);printf("\n");
    return 0;
}