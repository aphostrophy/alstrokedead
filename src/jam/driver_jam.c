#include <stdio.h>
#include "../boolean.h"
#include "../jam/jam.h"

int main() {
    JAM buka, tutup;
    Hour(buka) = 9; Minute(buka) = 0;
    Hour(tutup) = 21; Minute(tutup) = 0;

    printf("Durasi Main Day: %ld menit\n", Durasi(buka, tutup));
    printf("Durasi Prep Day: %ld menit\n", Durasi(tutup, buka));

    int n;
    printf("Masukkan n : "); scanf("%d", &n); printf("\n");
    printf("Durasi Main Day setelah n menit : %ld\n", Durasi(NextNMenit(buka, n),tutup));
    printf("Durasi Prep Day setelah n menit : %ld\n", Durasi(NextNMenit(tutup, n),buka));
}