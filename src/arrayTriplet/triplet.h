#ifndef _TRIPLET_H_
#define _TRIPLET_H_

#include <stdio.h>
#include "../boolean.h"
#include "../mesinkata/mesinkata.h"

/*** Definisi Elemen ***/
typedef struct{
    Kata nama;
    Kata bahan;
    int cost;
} Triplet;

/*** KONSTRUKTOR ***/
Triplet MakeTriplet(Kata nama, Kata bahan,int cost);


#endif