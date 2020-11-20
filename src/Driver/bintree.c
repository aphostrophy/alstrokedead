#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "../Header/bintree.h"
#include "../Header/wahana.h"
#include "../Header/mesinkar.h"
#include "../Header/mesinkata.h"

BinTree listUpgrade[10];
BinTree treeUpgrade[10];

Kata arrNamaWahanaUpgrade[10];
char idWahanaUpgrade[8] = {'S', 'P', 'T', 'C', 'H', 'F','G','Y'};
Kata arrUpgrade[10];
int levelWahana[10] = {1, 1, 1, 1, 1, 1, 1, 1};

void bacaUpgrade(char* namaFile) {
    int idx = 0;
    START(namaFile);
    while(!EOP) {
        IgnoreBlank();
        int i = 0;
        while(!EOL) {
            if(CC == '\n' || CC == '.') break;
            CKata.TabKata[i] = CC;
            ADV();
            i++;
        }
        if(CC == '.') break;
        CKata.Length = i;
        if(idx < 8) {
            arrNamaWahanaUpgrade[idx] = CKata;
        } else if(idx < 17) {
            arrUpgrade[idx-8] = CKata;
        }
        idx++;
        ADV();
    }
}

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
addrNode AlokNode(bintree_infotype X)
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak bintree_Nil, dan misalnya menghasilkan P, 
  maka Akar(P) = X, Left(P) = bintree_Nil, Right(P)=bintree_Nil */
/* Jika alokasi gagal, mengirimkan bintree_Nil */
{
    addrNode P;
    P = (addrNode)malloc(sizeof(Node));
    if (P != bintree_Nil){
        Akar(P) = X;
        Left(P) = bintree_Nil;
        Right(P) = bintree_Nil;
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
    return (P ==  bintree_Nil);
}

boolean IsTreeOneElmt(BinTree P)
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
{
    if (IsTreeEmpty(P)) return false;
    else {
        if (Left(P) == bintree_Nil && Right(P) == bintree_Nil)
            return true;
        else return false;
    }
}

boolean IsUnerLeft(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
{
    if (!IsTreeEmpty(P)) {
        if (Left(P) != bintree_Nil && Right(P) == bintree_Nil) 
            return true;
        return false;
    }
    return false;
}

boolean IsUnerRight(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
{
    if (!IsTreeEmpty(P)){
        if (Right(P) != bintree_Nil && Left(P) == bintree_Nil)
            return true;
        return false;
    }
    return false;
}

boolean IsBiner(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/
{
    if (!IsTreeEmpty(P)) {
        if (Left(P) != bintree_Nil && Right(P) != bintree_Nil) return true;
        return false; 
    }
    return false;
}


/*fungsi untuk mencari bahan makanan */
int findIndex(Kata namaWahana){
    int ret = -1;
    for (int i = 0; i < 8 && ret == -1; i++){
        if (IsKataSama(namaWahana, arrNamaWahanaUpgrade[i])){
            ret = i;
        }
    }
    return ret;
}

boolean isElement(BinTree P,bintree_infotype X){
    if (IsTreeEmpty(P)){
        return false;
    }else{
        if (Akar(P) == X) 
            return true;
        else return isElement(Left(P), X) || isElement(Right(P), X);
    }
}

boolean isChild(BinTree parent, BinTree child){
    if(IsTreeOneElmt(parent)) {
        return false;
    } else {
        if((Akar(Left(parent)) == Akar(child)) || (Akar(Right(parent)) == Akar(child))) {
            return true;
        } else {
            return false;
        }
    }
}

void PrintTreeUtil(BinTree P, int h, int level){
    if(IsTreeEmpty(P)) return;

    if(level == 1) {
        printKata(arrNamaWahanaUpgrade[Akar(P)]); printf("\n");
    } else {
        printKata(arrUpgrade[Akar(P)]); printf("\n");
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
        if(id == idWahanaUpgrade[i]) {
            res = i;
            break;
        }
    }
    if(IsTreeOneElmt(listUpgrade[res])) {
        printf("Tidak ada lagi upgrade yang bisa dilakukan!!\n");
    } else {
        PrintTreeUtil(listUpgrade[res], 2, levelWahana[res]);
    }
}

void moveUpgrade(char id, Kata upgrade) {
    BinTree res_upgrade, res_wahana;
    int idx;
    // Mencari wahana
    for(int i = 0; i < 8; i++) {
        if(id == idWahanaUpgrade[i]) {
            idx = i;
            res_wahana = listUpgrade[i];
            break;
        }
    }

    for(int i = 0; i < 9; i++) {
        if(IsKataSama(upgrade, arrUpgrade[i])) {
            res_upgrade = treeUpgrade[i];
        }
    }
    
    if(isChild(res_wahana, res_upgrade)) {
        listUpgrade[idx] = res_upgrade;
        levelWahana[idx]++;
        PrintAvailableUpgrade(id);
    } else {
        printf("Invalid Upgrade!!\n");
    }
}

void PrintAvailableUpgrade(char id) {
    BinTree res;
    for(int i = 0; i < 8; i++) {
        if(id == idWahanaUpgrade[i]) {
            res = listUpgrade[i];
            break;
        }
    }
    if(IsTreeOneElmt(res)) {
        printf("Tidak ada upgrade lagi!!\n");
    } else {
        printf("Available Upgrade :\n");
        printf("- "); printKata(arrUpgrade[Akar(Left(res))]); printf("\n");
        printf("- "); printKata(arrUpgrade[Akar(Right(res))]); printf("\n");
    }
}