#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "bintree.c"
#include "mesinkata.c"
#include "mesinkar.c"

int main() {
    bacaUpgrade("../Saves/Upgrade.txt");
    BuildTree();
    // for(int i = 0; i < 8; i++) {
    //     PrintTree(listUpgrade[i], 2);
    // }
    // printf("\n");

    printf("%d\n", findIndex('T'));
    return 0;
}