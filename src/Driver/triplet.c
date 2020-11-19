#include <stdio.h>
#include "../Header/triplet.h"
#include "../Header/boolean.h"

Triplet MakeTriplet(Kata nama, Kata bahan,int cost){
    Triplet T;
    T.nama = nama;
    T.bahan = bahan;
    T.cost = cost;
    return T;
}