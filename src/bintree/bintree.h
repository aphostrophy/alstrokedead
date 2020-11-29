/* ADT Pohon Biner Untuk Tubes */

#ifndef _TREE_
#define _TREE_

#include "../boolean.h"
#include "../mesinkata/mesinkata.h"
#include "../linkedlist/list_linkedlist.h"

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
boolean isChild(BinTree parent, BinTree child);
/*Mengembalikan true jika child adalah leaf / subpohon dari parent*/

/* *** Primitif - Primitif Penting *** */
int bintree_findIndex(char id);
/*Mengembalikan true jika child adalah leaf / subpohon dari parent*/
void PrintTreeUtil(BinTree P, int h, int level);
/*Prosedur untuk mencetak tree P dengan indentasi sebanyak h spasi di setiap levelnya*/
void PrintTree(BinTree P, int h);
/* I.S. P terdefinisi, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
/* Contoh, jika h = 2: 
1) Pohon preorder: (A()()) akan ditulis sbb:
A
2) Pohon preorder: (A(B()())(C()())) akan ditulis sbb:
A
  B
  C
3) Pohon preorder: (A(B(D()())())(C()(E()()))) akan ditulis sbb:
A
  B
    D
  C
    E
*/
void PrintUpgradeWahana(char id);
/*Mencetak pohon upgrade lengkap dari wahana dengan char id*/
void PrintAvailableUpgrade(char id, ListNode **head);
/*Mencetak upgrade yang bisa dilakukan pada wahana dengan char id, memanfaatkan linked list
  untuk mengetahui history upgrade agar bisa memperoleh available upgrade dengan tepat*/
void PrintAvailableUpgradeRecursion(BinTree P, ListNode **head);
/*Implementasi rekursif dari prosedur PrintAvailableUpgrade, dibuat agar bisa 
  meng-traverse dalam tree upgrade wahana dengan char id.*/
void findChild(char id, ListNode **head, arrKata *arrChild);
/*Prosedur untuk mencari kemungkinan upgrade yang mungkin dilakukan pada wahana
  dengan char id, lalu mengembalikannya dalam sebuah list of Kata*/
void findChildRecursion(BinTree P, ListNode **head, arrKata *arrChild);
/*Implementasi rekursif dari prosedur findChild, dibuat agar bisa 
  meng-traverse dalam tree upgrade wahana dengan char id.*/
  
#endif