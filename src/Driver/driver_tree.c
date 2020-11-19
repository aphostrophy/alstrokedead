#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "bintree.c"

int main() {
    BuildTree();
    // for(int i = 0; i < 8; i++) {
    //     PrintTree(listUpgrade[i], 2);
    // }
    // printf("\n");

    char id;
    string upgrade;
    scanf("%c", &id);
    scanf("%s", upgrade);
    PrintUpgradeWahana(id);
    PrintAvailableUpgrade(id);
    moveUpgrade(id, upgrade);
    PrintUpgradeWahana(id); printf("\n");
    scanf("%s", upgrade);
    moveUpgrade(id, upgrade);
    PrintUpgradeWahana(id);
    return 0;
}