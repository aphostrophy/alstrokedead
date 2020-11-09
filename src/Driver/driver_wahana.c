#include <stdio.h>
#include "wahana.c"

int main() {
    Wahana W;
    char id;
    makeListWahana(&W);

    printf("Masukkan ID wahana yang ingin dicari : ");
    scanf("%s", &id);
    printf("\n");

    printInfo(&W, id);
    return 0;
}