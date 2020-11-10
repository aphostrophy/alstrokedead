//  Topik : stackt.c
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#include "../Header/stackt.h"
#include "../Header/boolean.h"
#include <stdio.h>
#include <stdlib.h>
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
boolean IsEmptyStack (Stack S) {
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

	while(!(IsEmptyStack(*S)))
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
	while (!(IsEmptyStack(S))){
		Pop(&S,&X);
		printf("%s\n", X);
	}
}

void AkuisisiBuy(infotype S, int* N, char benda[100]){
  char *token = strtok(S, " ");
  token = strtok(NULL, " ");
  *N = atoi(token);
  token = strtok(NULL, " ");
  strcpy(benda,token);
}

void AkuisisiBuild(infotype S, int* buildX, int* buildY, int* buildMap, char bangunan[100]){
  char *token = strtok(S, " ");
  token = strtok(NULL, " ");
  strcpy(bangunan,token);
  token = strtok(NULL, " ");
  *buildX = atoi(token);
  token = strtok(NULL, " ");
  *buildY = atoi(token);
  token = strtok(NULL, " ");
  *buildMap = atoi(token);
}