#include <stdio.h>
#include "triplet.h"
#include "../boolean.h"

/*** KONSTRUKTOR ***/
Triplet MakeTriplet(Kata nama, Kata bahan,int cost){
    Triplet T;
    T.nama = nama;
    T.bahan = bahan;
    T.cost = cost;
    return T;
}