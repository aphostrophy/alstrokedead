#include <stdio.h>
#include "wahana.c"

int main() {
    Wahana W;
    char id;
    
    bacaWahana(&W, "../file/wahana.txt");

    printf("Masukkan ID wahana yang ingin dicari : ");
    scanf("%c", &id);
    printf("\n");

    printDetailWahana(&W, id);
    return 0;
}