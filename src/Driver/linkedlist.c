#include <stdio.h>
#include <stdlib.h>
#include "../Header/linkedlist.h"

List* NextList(List *L){
	List* T = (List*) malloc(sizeof(List));
	First(*T) = Next(First(*L));
	return T;
}

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L)
/* Mengirim true jika list kosong */
{
	return First(L) == Nil;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
	First(*L) = Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
	address P = (address) malloc(sizeof(address)+1);
	Info(P) = X;
	Next(P) = Nil;
	return P;
}

void Dealokasi (address *P) // 4
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
	if(IsEmpty(L)) return Nil;
	if(Info(First(L)) == X) return First(L);
	return Search(*NextList(&L), X);
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
	address P = Alokasi(X);
	Next(P) = First(*L);
	First(*L) = P;
}

void InsVLast (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
	if(IsEmpty(*L)) InsVFirst(L, X);
	else {
		List* tmp = NextList(L);
		InsVLast(tmp, X);
		Next(First(*L)) = First(*tmp);
	}
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
	*X = Info(First(*L));
	First(*L) = Second(*L);
}

void DelVLast (List *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
	if(IsOneElmt(*L)) DelVFirst(L, X);
	else {
		List* tmp = NextList(L);
		DelVLast(tmp, X);
		Next(First(*L)) = First(*tmp);
	}
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
	Next(P) = First(*L);
	First(*L) = P;
}
void InsertAfter (List *L, address P, address Prec) // 19
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
	if(First(*L) == Next(Prec)) InsertFirst(L, P);
	else {
		List* tmp = NextList(L);
		InsertAfter(tmp, P, Prec);
		Next(First(*L)) = First(*tmp);
	}
}
void InsertLast (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
	if(IsEmpty(*L)) InsertFirst(L, P);
	else {
		List* tmp = NextList(L);
		InsertLast(tmp, P);
		Next(First(*L)) = First(*tmp);
	}
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
	*P = First(*L);
	First(*L) = Next(First(*L));
}

void DelP (List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
	if(IsEmpty(*L)) return;
	if(Info(First(*L)) == X) {
		address P;
		DelFirst(L, &P);
	} else {
		List* tmp = NextList(L);
		DelP(tmp, X);
		Next(First(*L)) = First(*tmp);
	}
}

void DelLast (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
{
	if(IsOneElmt(*L)) DelFirst(L, P);
	else {
		List* tmp = NextList(L);
		DelLast(tmp, P);
		Next(First(*L)) = First(*tmp);
	}
}

void DelAfter (List *L, address *Pdel, address Prec) // 24-26
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
	if(First(*L) == Next(Prec)) DelFirst(L, Pdel);
	else {
		List* tmp = NextList(L);
		DelAfter(tmp, Pdel, Prec);
		Next(First(*L)) = First(*tmp);
	}
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L) // 27
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
	printf("[");
	while(!IsEmpty(L)){
		print(Info(First(L)));
		First(L) = Second(L);
		if (!IsEmpty(L)) printf(",");
	}
	printf("]");
}

int NbElmt (List L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
	if(IsEmpty(L)) return 0;
	return NbElmt(*NextList(&L))+1;
}
