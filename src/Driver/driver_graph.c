#include <stdio.h>
#include <stdlib.h>
#include "../Header/graph.h"

int main() {
    Graph G;
    BacaGraph(&G,"../file/graph.txt");
    if (Graph_First(G) != Nil) {
        printf("Berhasil!\n");
        adrPeta P = Graph_First(G);
        while (P != Nil) {
            printf("%d ", idPeta(P).map);
            printf("%d ", Absis(idPeta(P).p));
            printf("%d ", Ordinat(idPeta(P).p));
            printf("\n");
            P = Graph_Next(P);
        }
    }
    else {
        printf("lol no\n");
    }
}