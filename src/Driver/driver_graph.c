#include <stdio.h>
#include <stdlib.h>
#include "../Header/graph.h"

int main() {
    Graph G;
    infotypePeta PA;
    PA.room = 2;
    Absis(PA.p) = 3;
    Ordinat(PA.p) = 4;
    CreateGraph(PA,&G);
}