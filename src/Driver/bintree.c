#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "../Header/bintree.h"
#include "../Header/wahana.h"

BinTree tempTreeWahana[10];
BinTree tempTreeKlasifikasi[10];
BinTree treeWahana;
nama arrKlasifikasi[10] = {"Wahana", "Anak-anak", "Dewasa", "Murah", "Mahal", "Murah", "Mahal"};
nama arrNamaWahana[10] = {"Sky Coaster", "Pirate Ship", "Tornado", "Carousel", "Haunted House", "Ferris Wheel", "Giant Swings", "Gyro Drop"};
nama arrTipeWahana[10] = {"tipe1", "tipe2", "tipe1", "tipe2", "tipe1", "tipe2", "tipe1", "tipe2"};
int arrHargaWahana[10] = {10000, 15000, 50000, 40000, 5000, 10000, 75000, 50000};
int arrKapasitas[10] = {8, 6, 4, 8, 2, 6, 4, 8};
nama arrDeskripsi[10] = {"Ini Deskripsi", "Ini Deskripsi", "Ini Deskripsi", "Ini Deskripsi", "Ini Deskripsi", "Ini Deskripsi", "Ini Deskripsi", "Ini Deskripsi"};

void buatTree(BinTree parent,BinTree l, BinTree r){
    Left(parent) = l;
    Right(parent) = r;
}

void BuildTree(BinTree *P)
/* I.S P adalah tree kosong */
/* F.S P adalah tree berisi wahana willy wangky*/
{
    for (int i = 0; i < 8; i++)
        tempTreeWahana[i] = AlokNode(i);
    for (int i = 0; i < 7; i++)
        tempTreeKlasifikasi[i] = AlokNode(i);

    buatTree(tempTreeKlasifikasi[0], tempTreeKlasifikasi[1], tempTreeKlasifikasi[2]);
    buatTree(tempTreeKlasifikasi[1], tempTreeKlasifikasi[3], tempTreeKlasifikasi[4]);
    buatTree(tempTreeKlasifikasi[2], tempTreeKlasifikasi[5], tempTreeKlasifikasi[6]);
    buatTree(tempTreeKlasifikasi[3], tempTreeWahana[0], tempTreeWahana[1]);
    buatTree(tempTreeKlasifikasi[4], tempTreeWahana[2], tempTreeWahana[3]);
    buatTree(tempTreeKlasifikasi[5], tempTreeWahana[4], tempTreeWahana[5]);
    buatTree(tempTreeKlasifikasi[6], tempTreeWahana[6], tempTreeWahana[7]);

    *P = tempTreeKlasifikasi[0];
}

/* Manajemen Memory */
addrNode AlokNode(infotype X)
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P, 
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    addrNode P;
    P = (addrNode)malloc(sizeof(Node));
    if (P != Nil){
        Akar(P) = X;
        Left(P) = Nil;
        Right(P) = Nil;
    }
    return P;
}

void DealokNode(addrNode P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */
{
    free(P);
}


/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty(BinTree P)
/* Mengirimkan true jika P adalah pohon biner kosong */
{
    return (P ==  Nil);
}

boolean IsTreeOneElmt(BinTree P)
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
{
    if (IsTreeEmpty(P)) return false;
    else {
        if (Left(P) == Nil && Right(P) == Nil)
            return true;
        else return false;
    }
}

boolean IsUnerLeft(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
{
    if (!IsTreeEmpty(P)) {
        if (Left(P) != Nil && Right(P) == Nil) 
            return true;
        return false;
    }
    return false;
}

boolean IsUnerRight(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
{
    if (!IsTreeEmpty(P)){
        if (Right(P) != Nil && Left(P) == Nil)
            return true;
        return false;
    }
    return false;
}

boolean IsBiner(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/
{
    if (!IsTreeEmpty(P)) {
        if (Left(P) != Nil && Right(P) != Nil) return true;
        return false; 
    }
    return false;
}

/*fungsi untuk mencari bahan makanan */
int findIndex(nama namaWahana){
    int ret = -1;
    for (int i = 0; i < 8 && ret == -1; i++){
        if (strcmp(namaWahana, arrNamaWahana[i]) == 0){
            ret = i;
        }
    }
    return ret;
}

boolean isElement(BinTree P,infotype X){
    if (IsTreeEmpty(P)){
        return false;
    }else{
        if (Akar(P) == X) 
            return true;
        else return isElement(Left(P), X) || isElement(Right(P), X);
    }
}

boolean isParent(BinTree Now, BinTree X, BinTree Y){
    if (Akar(Now) == Akar(X)) {
        if (Left(Now) != Nil) 
            if (Akar(Left(Now)) == Akar(Y))
                return true;
        if (Right(Now) != Nil)
            if (Akar(Right(Now)) == Akar(Y))
                return true;
        return false;        
    }else {
        if (isElement(Left(Now), Akar(X)))
            return isParent(Left(Now), X, Y);
        else if (isElement(Right(Now), Akar(X)))
            return isParent(Right(Now), X, Y);
        else return false;
    }
}

void PrintTreeUtil(BinTree P, int h, int level){
  if(IsTreeEmpty(P)) return;

  printf("%d\n", Akar(P));

  if(!IsTreeEmpty(Left(P))){
    for (int i = 0; i < h*level; i++) {
        printf(" ");
    }
    PrintTreeUtil(Left(P), h, level+1);
  }
  if(!IsTreeEmpty(Right(P))){
    for(int i = 0; i < h*level; i++){
        printf(" ");
    }
    PrintTreeUtil(Right(P), h, level+1);
  }
}

void PrintTree(BinTree P, int h)
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
{
  PrintTreeUtil(P, h, 1);
}