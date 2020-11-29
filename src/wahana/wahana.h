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

/* *** Selektor - Selektor Penting *** */
/* Selektor properti wahana, representatif sesuai namanya */
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

/* *** Primitif - Primitif Penting *** */
void printListWahana(Wahana *W);
/* Prosedur untuk mencetak list wahana beserta id nya */
void printDetailWahana(Wahana *W, char id, ListNode **head);
/* Prosedur untuk mencetak detail wahana berdasarkan char id nya, 
   menggunakan linked list untuk mencetak history upgradenya */
void printReportWahana(Wahana *W, char id);
/* Prosedur untuk mencetak laporan wahana berupa pengunjung dan penghasilan wahana hari ini,
   serta total pengunjung dan penghasilan wahana selama bermain*/
void printNotBuilded(Wahana *W);
/* Prosedur untuk mencetak list wahana yang belum dibangun */
InfoWahana getWahanabyID(Wahana *W,char id);
/* Fungsi yang mengembalikan info wahana dengan char id yang bersangkutan */
int GetIndex(Wahana *W, char id);
/* Fungsi yang mengembalikan indeks dari wahana dengan char id */
int countBrokenWahana(Wahana *W);
/* Fungsi yang mengembalikan jumlah wahana yang sedang rusak */
void printBrokenWahana(Wahana *W);
/* Prosedur untuk menetak list wahana yang sedang rusak */
boolean IsWahanaBenar(Kata W, Wahana LW);
/* Fungsi yang mengembalikan true jika W terdapat dalam list wahana LW */
boolean IsAdaWahanaGood(Wahana W);
/* Fungsi yang mengembalikan true jika W berada dalam kondisi baik dan tidak rusak */
void SetZero(Wahana *W);
/* Prosedur untuk mengubah jumlah penghasilan dan pengunjung tiap wahana menjadi 0 setiap hari baru
   I.S setiap jumlah pengunjung, penghasilan, dan inside harian wahana bebas, bisa 0 atau sembarang int 
   F.S setiap jumlah pengunjung, penghasilan, dan inside harian wahana menjadi 0 */

#endif