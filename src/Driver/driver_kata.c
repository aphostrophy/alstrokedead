#include "../Header/mesinkata.h"
#include "../Header/mesinkar.h"
#include <stdio.h>


int main(){
    Kata hasil;
    int in;
    // scanf("%d",&in);
    // hasil = IntToKata(in);
    // printKata(hasil);printf("\n");
    hasil.TabKata[0] = '2';hasil.Length=1;
    in = KataToInt(hasil);
    printf("%d",in);
}