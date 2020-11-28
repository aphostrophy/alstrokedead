//  Topik : stackt.c
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#include "../Header/stackt2.h"
#include "../Header/boolean.h"
#include "../Header/mesinkar.h"
#include "../Header/mesinkata.h"
#include <stdio.h>
#include <stdlib.h>


/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty (Stack *S){
  /* I.S. sembarang; */
  /* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl_Stack */
  /* jadi indeksnya antara 0.. MaxEl_Stack */
  /* Ciri stack kosong : TOP berStack_Nilai Stack_Nil */
  Top(*S) = Stack_Nil ;
}


/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack (Stack S) {
  /* Mengirim true jika Stack kosong: lihat definisi di atas */
  return (Top(S)==Stack_Nil);
}

boolean IsFull (Stack S){
  /* Mengirim true jika tabel penampung Stack_Nilai elemen stack penuh */
  return (Top(S)==MaxEl_Stack-1);
}


/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, infotype X){
  /* Menambahkan X sebagai elemen Stack S. */
  /* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
  /* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
  
  Top(*S) = Top(*S) +1 ;
  InfoTop(*S) = copyKata(X);
}


/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, infotype* X){
  /* Menghapus X dari Stack S. */
  /* I.S. S  tidak mungkin kosong */
  /* F.S. X adalah Stack_Nilai elemen TOP yang lama, TOP berkurang 1 */
  (*X) = copyKata(InfoTop(*S));
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
  Kata X;
	while (!(IsEmptyStack(S))){
		Pop(&S,&X);
    // printKata(X);
    if (X.TabKata[0] == 'b' && X.TabKata[2] == 'y'){
			int n; Kata Benda;
			AkuisisiBuyV2(X,&n,&Benda);
      printf("Beli ");printKata(Benda);printf(" sejumlah %d",n);
		} else if (X.TabKata[0] == 'b' && X.TabKata[2] == 'i') {
			int PbuildX; int PbuildY; int PbuildMap; Kata Bangunan; int sizeBaris; int sizeKolom;
			AkuisisiBuildV2(X,&PbuildX,&PbuildY,&PbuildMap,&Bangunan,&sizeBaris,&sizeKolom);
			printf("Membangun "); printKata(Bangunan);
      printf(" di titik(%d,%d) pada peta %d dengan ukuran (%dx%d)",PbuildX,PbuildY,PbuildMap,sizeBaris,sizeKolom);
		} else if (X.TabKata[0] == 'u'){
			char idWahana;Kata Nama_Upgrade;
			AkuisisiUpgrade(X, &idWahana, &Nama_Upgrade);
      printf("Mengupgrade "); printKata(Nama_Upgrade);
      printf(" di wahana dengan id %c",Nama_Upgrade,idWahana);
	  }
    printf("\n");
  }
}


void AkuisisiBuyV2(infotype S, int* Nbenda, Kata* benda){
  Kata N;
  int i = 4 ; int j = 0 ; int cnt = 0;
  while (S.TabKata[i] != ' ') {
    cnt = cnt + 1;
    (N).TabKata[j] = S.TabKata[i];
    i++; j++;
  }
  (N).Length = cnt ;
  *Nbenda = KataToInt(N);
  cnt = 0 ; j = 0 ;
  while (S.TabKata[i] == ' ') {
    i++;
  }
  while (S.TabKata[i] != ' ' && i < S.Length) {
    cnt = cnt + 1;
    (*benda).TabKata[j] = S.TabKata[i];
    i++; j++;
  }
  (*benda).Length = cnt ;
}

void AkuisisiBuildV2(infotype S, int* buildX, int* buildY, int* buildMap, Kata* bangunan, int* sizeX, int* sizeY){
  int i = 6 ; int j = 0 ; int cnt = 0;
  Kata Xbuild; Kata Ybuild; Kata Mapbuild; Kata SsizeX; Kata SsizeY;
  while (S.TabKata[i] != ' ' &&i < S.Length) {
    cnt = cnt + 1;
    (*bangunan).TabKata[j] = S.TabKata[i];
    i++; j++;
  }
  (*bangunan).Length = cnt ;
  cnt = 0 ; j = 0 ;
  while (S.TabKata[i] == ' ') {
    i++;
  }
  while (S.TabKata[i] != ' ' && i < S.Length) {
    cnt = cnt + 1;
    Xbuild.TabKata[j] = S.TabKata[i];
    i++; j++;
  }
  Xbuild.Length = cnt ;
  *buildX = KataToInt(Xbuild);
  cnt = 0 ; j = 0 ;
  while (S.TabKata[i] == ' ') {
    i++;
  }
  while (S.TabKata[i] != ' ' && i < S.Length) {
    cnt = cnt + 1;
    (Ybuild).TabKata[j] = S.TabKata[i];
    i++; j++;
  }
  (Ybuild).Length = cnt ;
  *buildY = KataToInt(Ybuild);
  cnt = 0 ; j = 0 ;
  while (S.TabKata[i] == ' ') {
    i++;
  }
  while (S.TabKata[i] != ' ' && i < S.Length) {
    cnt = cnt + 1;
    (Mapbuild).TabKata[j] = S.TabKata[i];
    i++; j++;
  }
  (Mapbuild).Length = cnt ;
  *buildMap = KataToInt(Mapbuild);
  cnt = 0 ; j = 0 ;
  while (S.TabKata[i] == ' ') {
    i++;
  }
  while (S.TabKata[i] != ' ' && i < S.Length) {
    cnt = cnt + 1;
    (SsizeX).TabKata[j] = S.TabKata[i];
    i++; j++;
  } 

  (SsizeX).Length = cnt ;
  *sizeX = KataToInt(SsizeX);
  cnt = 0 ; j = 0 ;
  while (S.TabKata[i] == ' ') {
    i++;
  }
  while (S.TabKata[i] != ' ' && i < S.Length) {
    cnt = cnt + 1;
    (SsizeY).TabKata[j] = S.TabKata[i];
    i++; j++;
  }
  (SsizeY).Length = cnt ;
  *sizeY = KataToInt(SsizeY);
  cnt = 0 ; j = 0 ;
}

void AkuisisiUpgrade(Kata K, char *idWahana, Kata *Nama_Upgrade){
  int i=0;int j=0;
  while(K.TabKata[i]!=' '){
    i++;
  }
  i++;
  *idWahana = K.TabKata[i];
  i++;
  while(K.TabKata[i]==' '){ //Pengaman
    i++;
  }
  while(i < K.Length){
    Nama_Upgrade->TabKata[j] = K.TabKata[i];
    i++;j++;
  }
  Nama_Upgrade->Length=j;
}

