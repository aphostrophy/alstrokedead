#include <stdio.h>
#include <stdlib.h>
#include "../Header/graph.h"

int main() {
    Graph G;
    InitGraph(&G,"./file/graph.txt");
    if (First(G) != Nil) {
        printf("Berhasil!");
    }
    else {
        printf("lol no");
    }
}