#ifndef _WAHANA_H_
#define _WAHANA_H_

#include <stdio.h>
#include <string.h>
#include "boolean.h"

typedef char string[100];
typedef struct {
    char id;
    string nama;
    int harga;
    int durasi;
    int kapasitas;
    char status;
    string deskripsi;
    int inside;
    int pengunjung;
    int penghasilan;
    int total_pengunjung;
    int total_penghasilan;
} Infotype;

typedef struct { 
  Infotype TI[8]; /* memori tempat penyimpan elemen (container) */
} Wahana;

/* KONSTUKTOR */
Wahana makeListWahana(Wahana *W);
/* Fungsi untuk mengisi list Wahana W dengan data wahana */

/* SELEKTOR */
char* getNama(Wahana *W, char id);
int getHarga(Wahana *W, char id);
int getDurasi(Wahana *W, char id);
int getKapasitas(Wahana *W, char id);
char getStatus(Wahana *W, char id);
char* getDeskripsi(Wahana *W, char id);
int getInside(Wahana *W, char id);
int getPengunjung(Wahana *W, char id);
int getPenghasilan(Wahana *W, char id);
int getTotalPengunjung(Wahana *W, char id);
int getTotalPenghasilan(Wahana *W, char id);
void printInfo(Wahana *W, char id);
void printNotBuilded(Wahana *W);
#endif