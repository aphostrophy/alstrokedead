#include <stdio.h>
#include "../point/point.h"

int main() {
    POINT P = MakePOINT(4,6);
    Putar(&P,90);
    TulisPOINT(P);
    Mirror(&P,true);
    TulisPOINT(P);
    return 0;
}