#include <stdio.h>
#include "point.h"

int main() {
    POINT P = MakePOINT(4,6);
    TulisPOINT(P);
    Mirror(&P,true);
    TulisPOINT(P);
    return 0;
}