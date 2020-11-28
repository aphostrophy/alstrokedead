#ifndef _WAHANA_H_
#define _WAHANA_H_

#include <stdio.h>
#include <string.h>
#include "mesinkata.h"
#include "boolean.h"
#include "../Header/linkedlist.h"
#include "../Header/list_linkedlist.h"

typedef char string[100];
typedef struct {
    Kata id;
    Kata nama;
    int harga;
    int durasi;
    int kapasitas;
    char status;
    Kata deskripsi;
    int inside;
    int pengunjung;
    int penghasilan;
    int total_pengunjung;
    int total_penghasilan;
    List upgrade;
} InfoWahana;

typedef struct { 
  InfoWahana TI[8]; /* memori tempat penyimpan elemen (container) */
} Wahana;

/* KONSTUKTOR */
void bacaWahana(Wahana *W, char* namaFile);
/* Fungsi untuk mengisi list Wahana W dengan data wahana */

/* SELEKTOR */
Kata getNama(Wahana *W, char id);
int getHarga(Wahana *W, char id);
int getDurasi(Wahana *W, char id);
int getKapasitas(Wahana *W, char id);
char getStatus(Wahana *W, char id);
Kata getDeskripsi(Wahana *W, char id);
int getInside(Wahana *W, char id);
int getPengunjung(Wahana *W, char id);
int getPenghasilan(Wahana *W, char id);
int getTotalPengunjung(Wahana *W, char id);
int getTotalPenghasilan(Wahana *W, char id);
void printListWahana(Wahana *W);
void printDetailWahana(Wahana *W, char id, ListNode **head);
void printReportWahana(Wahana *W, char id);
void printNotBuilded(Wahana *W);
int GetIndex(Wahana *W, char id);
int countBrokenWahana(Wahana *W);
void printBrokenWahana(Wahana *W);

#endif