#ifndef _WAHANA_H_
#define _WAHANA_H_

#include <stdio.h>
#include "boolean.h"

typedef struct {
    int id;
    char* nama;
    char* tipe;
    int harga;
    int durasi;
    int kapasitas;
    char* deskripsi;
} Wahana;

Wahana makeWahana(int id, char* nama, char* tipe, int harga, int kapasitas, char* deskripsi);

#endif