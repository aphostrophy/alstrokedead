#include <stdio.h>
#include <stdlib.h>
#include "../Header/graph.h"

int main() {
    Graph G;
    BacaGraph(&G,"../file/graph.txt");
    if (Graph_First(G) != Nil) {
        printf("Berhasil!");
    }
    else {
        printf("lol no");
    }
}