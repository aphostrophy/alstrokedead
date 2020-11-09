//  Topik : stackt.c
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#include "../Header/stackt.h"
#include "../Header/boolean.h"
#include <stdio.h>
#include <string.h>


/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty (Stack *S){
  /* I.S. sembarang; */
  /* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
  /* jadi indeksnya antara 0.. MaxEl */
  /* Ciri stack kosong : TOP bernilai Nil */
  Top(*S) = Nil ;
}


/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmpty (Stack S) {
  /* Mengirim true jika Stack kosong: lihat definisi di atas */
  return (Top(S)==Nil);
}

boolean IsFull (Stack S){
  /* Mengirim true jika tabel penampung nilai elemen stack penuh */
  return (Top(S)==MaxEl-1);
}


/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, infotype X){
  /* Menambahkan X sebagai elemen Stack S. */
  /* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
  /* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
  Top(*S) = Top(*S) +1 ;
  strcpy(InfoTop(*S),X);
}


/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, infotype* X){
  /* Menghapus X dari Stack S. */
  /* I.S. S  tidak mungkin kosong */
  /* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
  strcpy((*X), InfoTop(*S));
  Top(*S) = Top(*S) -1;
}

void Reverse(Stack *S){
  /* Memutar balikkan isi stack */
  /*	I.S.  S tidak kosong dan terdefinisi */
  /*	F.S.	Isi dari S terbalik urutannya */
  Stack Stemp;
	infotype X;
	CreateEmpty(&Stemp);

	while(!(IsEmpty(*S)))
	{
		Pop(S,&X);
		Push(&Stemp,X);
	}
	(*S) = Stemp;
}
void PrintStack(Stack S){
  /*	I.S. S tidak kosong dan terdefinisi */
  /*	F.S. Seluruh isi S dicetak */
  char X[100];
	while (!(IsEmpty(S))){
		Pop(&S,&X);
		printf("%s\n", X);
	}
}
