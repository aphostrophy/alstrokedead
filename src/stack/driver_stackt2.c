#include <stdio.h>
#include <stdlib.h>
#include "stackt2.h"
#include "../boolean.h"
#include "stackt2.c"
#include "../mesinkata/mesinkata.c"
#include "../mesinkata/mesinkar.c"
#include "../wahana/wahana.c"

int main(){
    Kata BUY; BUY.TabKata[0] = 'b'; BUY.TabKata[1] = 'u'; BUY.TabKata[2] = 'y'; BUY.TabKata[3] = ' '; BUY.TabKata[4] = '5'; BUY.TabKata[5] = ' '; BUY.TabKata[6] = 'D'; BUY.TabKata[7] = 'i'; BUY.Length = 8;
	Kata BUILD; BUILD.TabKata[0] = 'b'; BUILD.TabKata[1] = 'u'; BUILD.TabKata[2] = 'i';BUILD.TabKata[3] = 'l'; BUILD.TabKata[4] ='d' ; BUILD.TabKata[5] = ' '; BUILD.TabKata[6] = 'W'; BUILD.TabKata[7] = 'a'; BUILD.TabKata[8] = '-'; BUILD.TabKata[9] ='C' ;BUILD.TabKata[10] = ' '; BUILD.TabKata[11] ='1' ;BUILD.TabKata[12] = ' '; BUILD.TabKata[13] ='2' ; BUILD.TabKata[14] =' ' ;  BUILD.TabKata[15] ='3' ;BUILD.Length = 16;
	Kata UPGRADE; UPGRADE.TabKata[0] = 'u';UPGRADE.TabKata[1] = 'p';UPGRADE.TabKata[2] = 'g';UPGRADE.TabKata[3] = 'r';UPGRADE.TabKata[4] = 'a';UPGRADE.TabKata[5] = 'd';UPGRADE.TabKata[6]= 'e'; UPGRADE.Length = 7;
    Kata X;
    Stack S;
    CreateEmpty(&S);
    Push(&S, BUY);
    Push(&S, BUILD);
    Push(&S, UPGRADE);
    printf("%s", "Isi topnya adalah ");
    printKata(InfoTop(S));
    printf("%s\n", "Isi stacknya adalah");
    PrintStack(S);
    Reverse(&S);
    printf("%s\n", "Isi reverse stacknya adalah");
    PrintStack(S);
    int N; Kata Benda;
    AkuisisiBuyV2(InfoTop(S),&N,&Benda);
    printf("%d %d %s\n", N ,Benda.Length, Benda.TabKata);
    Pop(&S, &X);
    int buildX; int buildY; int buildMap; Kata bangunan;
    AkuisisiBuildV2(InfoTop(S), &buildX, &buildY, &buildMap, &bangunan);
    printf("%d %d %d %d %s\n", buildX , buildY, buildMap, bangunan.Length, bangunan.TabKata);
    printKata(bangunan);
    printf("\n");
    Kata NNN;
    NNN = IntToKata(1000);
    printf("%d %s\n", NNN.Length, NNN.TabKata);
    return 0;
}