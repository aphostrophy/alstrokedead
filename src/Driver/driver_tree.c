#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "bintree.c"

int main() {
    BuildTree();
    for(int i = 0; i < 8; i++) {
        PrintTree(listUpgrade[i], 2);
    }
    printf("\n");

    char id;
    scanf("%c", &id);
    PrintUpgradeWahana(id);
    
    return 0;
}