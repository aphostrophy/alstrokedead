#include <stdio.h>
#include "pair.h"
#include "../boolean.h"

/*** KONSTRUKTOR ***/
Pair MakePair(Kata item, int cost){
    Pair P;
    P.item = item;
    P.cost = cost;
    return P;
}