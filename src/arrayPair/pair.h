#ifndef _PAIR_H_
#define _PAIR_H_

#include <stdio.h>
#include "../boolean.h"
#include "../mesinkata/mesinkata.h"

/* Definisi elemen Pair */
typedef struct{
    Kata item;
    int cost;
} Pair;

/*** KONSTRUKTOR ***/
Pair MakePair(Kata item, int cost);


#endif