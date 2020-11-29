#ifndef _WAHANA_H_
#define _WAHANA_H_

#include <stdio.h>
#include "../mesinkata/mesinkata.h"
#include "../boolean.h"
#include "../linkedlist/list_linkedlist.h"

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
    int panjang;
    int lebar;
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
InfoWahana getWahanabyID(Wahana *W,char id);
int GetIndex(Wahana *W, char id);
int countBrokenWahana(Wahana *W);
void printBrokenWahana(Wahana *W);
InfoWahana getWahanabyID(Wahana *W,char id);
boolean IsWahanaBenar(Kata W, Wahana LW);
boolean IsAdaWahanaGood(Wahana W);
void SetZero(Wahana *W);

#endif