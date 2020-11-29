#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"
#include "../mesinkata/mesinkata.h"
#include "../mesinkata/mesinkar.h"

int main() {
    bacaUpgrade("../file/Upgrade.txt");
    BuildTree();
    for(int i = 0; i < 8; i++) {
        PrintTree(listUpgrade[i], 2);
    }
    printf("\n");

    // char id;
    Kata upgrade;
    // scanf("%c", &id);
    
    return 0;
}