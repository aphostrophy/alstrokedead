#include "../Header/linkedlist.h"
#include "../Header/mesinkar.h"
#include "../Header/mesinkata.h"
#include <stdio.h>
#include <stdlib.h>

boolean IsEmpty_LinkedList (List L){
    return First_LinkedList(L)==Nil_LinkedList;
}
/* Mengirim true jika list kosong */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty_LinkedList (List *L){
    First_LinkedList(*L)=Nil_LinkedList;
}
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

/****************** Manajemen Memori ******************/
linkedlist_address Alokasi_LinkedList (linkedlist_infotype X){
    linkedlist_address P = (ElmtList *) malloc(sizeof(ElmtList));
    if(P != Nil_LinkedList) {
        Info_LinkedList(P) = X;
        Next_LinkedList(P) = Nil_LinkedList;
        return P;
    } else {
        return Nil_LinkedList;
    }
}
/* Mengirimkan linkedlist_address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka linkedlist_address tidak Nil_LinkedList, dan misalnya */
/* menghasilkan P, maka Info_LinkedList(P)=X, Next_LinkedList(P)=Nil_LinkedList */
/* Jika alokasi gagal, mengirimkan Nil_LinkedList */
void Dealokasi_LinkedList (linkedlist_address *P){
    free(*P);
}
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian linkedlist_address P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
linkedlist_address Search_LinkedList (List L, linkedlist_infotype X)
/* Mencari apakah ada elemen list dengan Info_LinkedList(P)= X */
/* Jika ada, mengirimkan linkedlist_address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil_LinkedList */
{
    linkedlist_address P;
    boolean found=false;
    P = First_LinkedList(L);
    while(!found && P!=Nil_LinkedList) {
        if(IsKataSama(Info_LinkedList(P), X)){
            found = true;
        } else{
            P = Next_LinkedList(P);
        }
    }
    return P;
}

/****************** PRIMITIF BERDASARKAN Nil_LinkedListAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst_LinkedList_LinkedList (List *L, linkedlist_infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan Nil_LinkedListai X jika alokasi berhasil */
{
    linkedlist_address P = Alokasi_LinkedList(X);
    if(P != Nil_LinkedList){
        Next_LinkedList(P) = First_LinkedList(*L);
        First_LinkedList(*L) = P;
    }
}
void InsVLast_LinkedList (List *L, linkedlist_infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* berNil_LinkedListai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    linkedlist_address P = Alokasi_LinkedList(X);
    if(P != Nil_LinkedList){
        InsertLast_LinkedList(L, P);
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst_LinkedList (List *L, linkedlist_infotype *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: Nil_LinkedListai Info_LinkedList disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    linkedlist_address P;
    P = First_LinkedList(*L);
    *X = Info_LinkedList(P);
    DelFirst_LinkedList(L, &P);
    Dealokasi_LinkedList(&P);
}
void DelVLast_LinkedList (List *L, linkedlist_infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: Nil_LinkedListai Info_LinkedList disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    linkedlist_address P;

    DelLast_LinkedList(L, &P);
    *X = Info_LinkedList(P);
    Dealokasi_LinkedList(&P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst_LinkedList (List *L, linkedlist_address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-linkedlist_address P sebagai elemen pertama */
{
    Next_LinkedList(P) = First_LinkedList(*L);
    First_LinkedList(*L) = P;
}
void InsertAfter_LinkedList (List *L, linkedlist_address P, linkedlist_address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
    Next_LinkedList(P) = Next_LinkedList(Prec);
    Next_LinkedList(Prec) = P;
}
void InsertLast_LinkedList (List *L, linkedlist_address P){
    if(IsEmpty_LinkedList(*L)){
        InsertFirst_LinkedList(L, P);
    } else{
        linkedlist_address traverse;
        traverse = First_LinkedList(*L);
        while(Next_LinkedList(traverse) != Nil_LinkedList){
            traverse = Next_LinkedList(traverse);
        }
        InsertAfter_LinkedList(L, P, traverse);
    }
}
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst_LinkedList (List *L, linkedlist_address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First_LinkedList element yg baru adalah suksesor elemen pertama yang lama */
{
    *P = First_LinkedList(*L);
    First_LinkedList(*L) = Next_LinkedList(First_LinkedList(*L));
    Next_LinkedList(*P) = Nil_LinkedList;
}
void DelP_LinkedList (List *L, linkedlist_infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list berlinkedlist_address P, dengan Info_LinkedList(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info_LinkedList berNil_LinkedListai X */
/* maka yang dihapus hanya elemen pertama dengan Info_LinkedList = X */
/* Jika tidak ada elemen list dengan Info_LinkedList(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
    linkedlist_address P, Prec, Pdel;
    boolean found;

    P = First_LinkedList(*L);
    Prec = Nil_LinkedList;
    found = false;
    while ( (P != Nil_LinkedList) && (!found) ) {
        if (IsKataSama(Info_LinkedList(P), X)) {
            found = true;
        } else {
            Prec = P;
            P = Next_LinkedList(P);
        }
    } 
    if (found) {
        if (Prec == Nil_LinkedList) {
            DelFirst_LinkedList(L, &Pdel);
            Dealokasi_LinkedList(&Pdel);
        }
        else {
            DelAfter_LinkedList(L, &Pdel, Prec);
            Dealokasi_LinkedList(&Pdel);
        }
    }
}
void DelLast_LinkedList (List *L, linkedlist_address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
{
    linkedlist_address Prev;
    Prev = Nil_LinkedList;
    *P = First_LinkedList(*L);
    while(Next_LinkedList(*P)!=Nil_LinkedList){
        Prev = *P;
        *P = Next_LinkedList(*P);
    }
    if(Prev==Nil_LinkedList){
        DelFirst_LinkedList(L,P);
    } else{
        DelAfter_LinkedList(L, P, Prev);
    }
}
void DelAfter_LinkedList (List *L, linkedlist_address *Pdel, linkedlist_address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next_LinkedList(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
    linkedlist_address P;
    boolean found;

    P = First_LinkedList(*L);
    found = false;
    while ((P != Nil_LinkedList) && (!found)) {
        if (P == Prec) {
            found = true;
        }
        else {
            P = Next_LinkedList(P);
        }
    }

    *Pdel = Next_LinkedList(P);
    Next_LinkedList(P) = Next_LinkedList(Next_LinkedList(P));
    Next_LinkedList(*Pdel) = Nil_LinkedList;
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo_LinkedList_LinkedList (List L){
    if (IsEmpty_LinkedList(L)) {
        printf("[]");
    }
    else {
        linkedlist_address P;
        P = First_LinkedList(L);
        printf("[%d", Info_LinkedList(P));
        P = Next_LinkedList(P);
        while (P != Nil_LinkedList) {
            printf(",%d", Info_LinkedList(P));
            P = Next_LinkedList(P);
        }  
        printf("]");
    }
}
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen berNil_LinkedListai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
int NbElmt_LinkedList (List L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    if(IsEmpty_LinkedList(L)){
        return 0;
    } else{
        int counter=0;
        linkedlist_address P;
        P= First_LinkedList(L);
        while(P != Nil_LinkedList){
            P = Next_LinkedList(P);
            counter++;
        }
        return counter;
    }
}

// /*** Prekondisi untuk Min: List tidak kosong ***/
// linkedlist_infotype Min_LinkedList (List L)
// /* Mengirimkan Nil_LinkedListai Info_LinkedList(P) yang minimum */
// {
//     linkedlist_infotype min;
//     linkedlist_address P;
//     P = First_LinkedList(L);
//     min = Info_LinkedList(First_LinkedList(L));
//     while(Next_LinkedList(P) != Nil_LinkedList){
//         if(Info_LinkedList(P)<min){
//             min = Info_LinkedList(P);
//         }
//         P = Next_LinkedList(P);
//     }
//     return min;
// }

// /*** Prekondisi untuk Max: List tidak kosong ***/
// linkedlist_infotype Max_LinkedList (List L)
// /* Mengirimkan Nil_LinkedListai Info_LinkedList(P) yang maksimum */
// {
//     linkedlist_infotype max;
//     linkedlist_address P;
//     max = Info_LinkedList(First_LinkedList(L));
//     P = First_LinkedList(L);
//     while(P != Nil_LinkedList){
//         if(Info_LinkedList(P)>max){
//             max = Info_LinkedList(P);
//         }
//         P = Next_LinkedList(P);
//     }
//     return max;
// }

/****************** PROSES TERHADAP LIST ******************/
void Konkat1_LinkedList (List *L1, List *L2, List *L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
    linkedlist_address P;

    CreateEmpty_LinkedList(L3);
	if(IsEmpty_LinkedList(*L1)) {
        First_LinkedList(*L3) = First_LinkedList(*L2);
    } else {
		First_LinkedList(*L3) = First_LinkedList(*L1);
        P = First_LinkedList(*L1);
		while(Next_LinkedList(P) != Nil_LinkedList){
            P = Next_LinkedList(P);
        } 
        Next_LinkedList(P) = First_LinkedList(*L2);
	}
	CreateEmpty_LinkedList(L1);
	CreateEmpty_LinkedList(L2);
}