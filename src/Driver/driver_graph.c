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
        infotypePeta X;
        X.map = 1;
        Absis(X.p) = 1;
        Ordinat(X.p) = 1;
        adrPeta Q = SearchPeta(G,X);
        printf("%d ", idPeta(Q).map);
        printf("%d ", Absis(idPeta(Q).p));
        printf("%d ", Ordinat(idPeta(Q).p));
    }
    else {
        printf("lol no\n");
    }
}