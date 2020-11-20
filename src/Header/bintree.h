/* ADT Pohon Biner Untuk Tubes */

#ifndef _TREE_
#define _TREE_

#include <string.h>
#include "../Header/boolean.h"

#define bintree_Nil NULL

typedef char string[100];
typedef int bintree_infotype;

typedef struct tNode *addrNode;
typedef struct tNode{
  bintree_infotype info;
  addrNode left;
  addrNode right;
} Node;

typedef addrNode BinTree;

extern BinTree listUpgrade[10];
extern string arrNamaWahana[10];
extern string arrUpgrade[10];

#define Akar(P) (P)->info
#define Left(P) (P)->left
#define Right(P) (P)->right

void BuatTree(BinTree parent, BinTree l, BinTree r);

void BuildTree();
/* I.S P adalah tree kosong */
/* F.S P adalah tree berisi bahan makanan dari restoran engi kitchen */

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
boolean IsUnerLeft(BinTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
boolean IsUnerRight(BinTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
boolean IsBiner(BinTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/

/*fungsi untuk mengecek apakah ada suatu elemen x pada sebuah binary tree P*/
boolean isElement(BinTree P, bintree_infotype X);

/*fungsi untuk mengecek apakah X parent dari Y atau bukan */
boolean isChild(BinTree parent, BinTree child);

void PrintTree(BinTree P, int h);

void PrintUpgradeWahana(char id);

void PrintAvailableUpgrade(char id);

void moveUpgrade(char id, string upgrade);

#endif