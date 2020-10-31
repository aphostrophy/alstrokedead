#include <stdio.h>
#include "../Header/pair.h"
#include "../Header/boolean.h"

Pair MakePair(Kata item, int cost){
    Pair P;
    P.item = item;
    P.cost = cost;
    return P;
}