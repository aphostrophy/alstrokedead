/* ADT Pohon Biner Untuk Tubes */

#ifndef _TREE_
#define _TREE_

#include "./boolean.h"
#include "./mesinkata.h"
#include "./list_linkedlist.h"

#define bintree_Nil NULL

typedef int bintree_infotype;

typedef struct tNode *addrNode;
typedef struct tNode{
  bintree_infotype info;
  addrNode left;
  addrNode right;
} Node;

typedef addrNode BinTree;

extern BinTree listUpgrade[10];
extern Kata arrNamaWahana[10];
extern Kata arrUpgrade[10];

#define Akar(P) (P)->info
#define Left(P) (P)->left
#define Right(P) (P)->right

void bacaUpgrade(char* namaFile);

void BuatTree(BinTree parent, BinTree l, BinTree r);

void BuildTree();
/* I.S P adalah tree kosong */
/* F.S P adalah tree berisi daftar upgrade dari wahana-wahana wangky */

/* Manajemen Memory */
addrNode AlokNode(bintree_infotype X);
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Niil, dan misalnya menghasilkan P, 
  maka Akar(P) = X, Left(P) = Niil, Right(P)=Niil */
/* Jika alokasi gagal, mengirimkan Niil */

void DealokNode(addrNode P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */

/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty(BinTree P);
/* Mengirimkan true jika P adalah pohon biner kosong */
boolean IsTreeOneElmt(BinTree P);
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
boolean isElement(BinTree P, bintree_infotype X);
/*fungsi untuk mengecek apakah ada suatu elemen x pada sebuah binary tree P*/

/*fungsi untuk mengecek apakah X parent dari Y atau bukan */
boolean isChild(BinTree parent, BinTree child);

int bintree_findIndex(char id);

void PrintTree(BinTree P, int h);

void PrintUpgradeWahana(char id);

void PrintAvailableUpgrade(char id, ListNode **head);

void PrintAvailableUpgradeRecursion(BinTree P, ListNode **head);

#endif