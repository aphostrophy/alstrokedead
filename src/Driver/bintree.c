#include <stdio.h>
#include <stdlib.h>
#include "../Header/bintree.h"
#include "../Header/wahana.h"
#include "../Header/mesinkar.h"
#include "../Header/mesinkata.h"
#include "../Header/list_linkedlist.h"

BinTree listUpgrade[10];
BinTree treeUpgrade[10];

Kata arrNamaWahanaUpgrade[10];
Kata idWahanaUpgrade[8];
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
        if (idx < 8) {
            idWahanaUpgrade[idx] = CKata;
        }
        else if(idx < 16) {
            arrNamaWahanaUpgrade[idx-8] = CKata;
        } else if(idx < 25) {
            arrUpgrade[idx-16] = CKata;
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

int bintree_findIndex(char id){
    int ret = -1;
    for (int i = 0; i < 8 && ret == -1; i++){
        if (id == idWahanaUpgrade[i].TabKata[0]){
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
        if(id == idWahanaUpgrade[i].TabKata[0]) {
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

void PrintAvailableUpgrade(char id, ListNode **head) {
    BinTree P;
    for(int i = 0; i < 8; i++) {
        if(id == idWahanaUpgrade[i].TabKata[0]) {
            P = listUpgrade[i];
            break;
        }
    }

    ListNode *current=*head;
    if(current==NULL){
        printf("Available Upgrade :\n");
        printf("- "); printKata(arrUpgrade[Akar(Left(P))]); printf("\n");
        printf("- "); printKata(arrUpgrade[Akar(Right(P))]); printf("\n");    
    } else {
        // printKata(current->data);
        if(IsKataSama(current->data, arrUpgrade[Akar(Left(P))])) {
            PrintAvailableUpgradeRecursion(Left(P), (&current->next));
        } else if(IsKataSama(current->data, arrUpgrade[Akar(Right(P))])) {
            PrintAvailableUpgradeRecursion(Right(P), (&current->next));
        }
    }
    
}

void PrintAvailableUpgradeRecursion(BinTree P, ListNode **head) {
    if(IsTreeOneElmt(P)) {
        printf("Tidak ada upgrade lagi!!\n");
    } else {
        ListNode *current=*head;
        if(current==NULL){
            printf("Available Upgrade :\n");
            printf("- "); printKata(arrUpgrade[Akar(Left(P))]); printf("\n");
            printf("- "); printKata(arrUpgrade[Akar(Right(P))]); printf("\n");    
        } else {
            // printKata(current->data);
            if(IsKataSama(current->data, arrUpgrade[Akar(Left(P))])) {
                PrintAvailableUpgradeRecursion(Left(P), (&current->next));
            } else if(IsKataSama(current->data, arrUpgrade[Akar(Right(P))])) {
                PrintAvailableUpgradeRecursion(Right(P), (&current->next));
            }
        }
    }
}

void findChild(char id, ListNode **head, arrKata *arrChild) {
    BinTree P;
    for(int i = 0; i < 8; i++) {
        if(id == idWahanaUpgrade[i].TabKata[0]) {
            P = listUpgrade[i];
            break;
        }
    }

    ListNode *current=*head;
    if(current==NULL){
        (*arrChild).TI[0] = copyKata(arrUpgrade[Akar(Left(P))]);
        (*arrChild).TI[1] = copyKata(arrUpgrade[Akar(Right(P))]);
    } else {
        // printKata(current->data);
        if(IsKataSama(current->data, arrUpgrade[Akar(Left(P))])) {
            findChildRecursion(Left(P), (&current->next), arrChild);
        } else if(IsKataSama(current->data, arrUpgrade[Akar(Right(P))])) {
            findChildRecursion(Right(P), (&current->next), arrChild);
        }
    }
    
}

void findChildRecursion(BinTree P, ListNode **head, arrKata *arrChild) {
    if(IsTreeOneElmt(P)) {
        (*arrChild).TI[0].Length = 0;
        (*arrChild).TI[1].Length = 0;
    } else {
        ListNode *current=*head;
        if(current==NULL){
            (*arrChild).TI[0] = copyKata(arrUpgrade[Akar(Left(P))]);
            (*arrChild).TI[1] = copyKata(arrUpgrade[Akar(Right(P))]);
        } else {
            // printKata(current->data);
            if(IsKataSama(current->data, arrUpgrade[Akar(Left(P))])) {
                findChildRecursion(Left(P), (&current->next), arrChild);
            } else if(IsKataSama(current->data, arrUpgrade[Akar(Right(P))])) {
                findChildRecursion(Right(P), (&current->next), arrChild);
            }
        }
    }
}