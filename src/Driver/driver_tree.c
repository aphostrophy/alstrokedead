#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "bintree.c"

int main() {
    BuildTree(&treeWahana);
    PrintTree(treeWahana, 2);
    return 0;
}