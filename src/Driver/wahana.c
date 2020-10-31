#include <stdio.h>
#include "boolean.h"

Wahana makeWahana(int id, char* nama, char* tipe, int harga, int durasi, int kapasitas, char* deskripsi) {
    Wahana W;

    W.id = id;
    W.nama = nama;
    W.tipe = tipe;
    W.harga = harga;
    W.durasi = durasi;
    W.kapasitas = kapasitas;
    W.deskripsi = deskripsi;

    return W;
}
