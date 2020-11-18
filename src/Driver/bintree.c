#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "../Header/bintree.h"
#include "../Header/wahana.h"

BinTree listUpgrade[10];
BinTree treeUpgrade[10];
string arrNamaWahana[10] = {"Sky Coaster", "Pirate Ship", "Tornado", "Carousel", "Haunted House", "Ferris Wheel", "Giant Swings", "Gyro Drop"};
char idWahana[8] = {'S', 'P', 'T', 'C', 'H', 'F','G','Y'};
string arrUpgrade[10] = {"Money Up S", "Money Up M", "Money Up XL", "capacity up S", "capacity up M", "capacity up XL", "speed up S", "speed up M", "speed up XL"};

void buatTree(BinTree parent,BinTree l, BinTree r){
    Left(parent) = l;
    Right(parent) = r;
}

void BuildTree()
/* I.S P adalah tree kosong */
/* F.S P adalah tree berisi wahana willy wangky*/
{
    for (int i = 0; i < 8; i++) {
        listUpgrade[i] = AlokNode(i);
    }
    for (int i = 0; i < 9; i++) {
        treeUpgrade[i] = AlokNode(i);
    }

    buatTree(listUpgrade[0], treeUpgrade[0], treeUpgrade[3]);
    buatTree(listUpgrade[1], treeUpgrade[0], treeUpgrade[6]);
    buatTree(listUpgrade[2], treeUpgrade[0], treeUpgrade[3]);
    buatTree(listUpgrade[3], treeUpgrade[0], treeUpgrade[6]);
    buatTree(listUpgrade[4], treeUpgrade[0], treeUpgrade[3]);
    buatTree(listUpgrade[5], treeUpgrade[0], treeUpgrade[6]);
    buatTree(listUpgrade[6], treeUpgrade[0], treeUpgrade[3]);
    buatTree(listUpgrade[7], treeUpgrade[0], treeUpgrade[6]);
    buatTree(treeUpgrade[0], treeUpgrade[1], treeUpgrade[2]);
    buatTree(treeUpgrade[0], treeUpgrade[1], treeUpgrade[2]);
    buatTree(treeUpgrade[3], treeUpgrade[4], treeUpgrade[5]);
    buatTree(treeUpgrade[6], treeUpgrade[7], treeUpgrade[8]);
}

/* Manajemen Memory */
addrNode AlokNode(idx X)
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
int findIndex(string namaWahana){
    int ret = -1;
    for (int i = 0; i < 8 && ret == -1; i++){
        if (strcmp(namaWahana, arrNamaWahana[i]) == 0){
            ret = i;
        }
    }
    return ret;
}

boolean isElement(BinTree P,idx X){
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

    if(level == 1) {
        printf("%s\n", arrNamaWahana[Akar(P)]);
    } else {
        printf("%s\n", arrUpgrade[Akar(P)]);
    }
  
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

void PrintUpgradeWahana(char id) {
    int res;
    for(int i = 0; i < 8; i++) {
        if(id == idWahana[i]) {
            res = i;
            break;
        }
    }
    PrintTree(listUpgrade[res], 2);
}