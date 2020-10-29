#include "../Header/matriks.h"
#include "../Header/boolean.h"
#include "../Header/mesinkar.h"
#include <stdio.h>


/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS(int NB, int NK, MATRIKS *M) {
	/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
	/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
	/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
	NBrsEff(*M) = NB;
	NKolEff(*M) = NK;
}

/* *** Selektor *** */
// #define NBrsEff(M) (M).NBrsEff
// #define NKolEff(M) (M).NKolEff
// #define Elmt(M,i,j) (M).Mem[(i)][(j)]

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid(int i, int j) {
	/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
	return (i >= BrsMin && i <= BrsMax) && (j >= KolMin && j <= KolMax);
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs(MATRIKS M) {
	/* Mengirimkan indeks baris terkecil M */
	return BrsMin;
}

indeks GetFirstIdxKol(MATRIKS M) {
	/* Mengirimkan indeks kolom terkecil M */
	return KolMin;
}

indeks GetLastIdxBrs(MATRIKS M) {
	/* Mengirimkan indeks baris terbesar M */
	return NBrsEff(M) - 1;
}

indeks GetLastIdxKol(MATRIKS M) {
	/* Mengirimkan indeks kolom terbesar M */
	return NKolEff(M) - 1;
}
boolean IsIdxEff(MATRIKS M, indeks i, indeks j) {
	return (i >= BrsMin && i <= GetLastIdxBrs(M)) && (j >= KolMin && j <= GetLastIdxKol(M));
	/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
}

ElType GetElmtDiagonal(MATRIKS M, indeks i) {
	/* Mengirimkan elemen M(i,i) */
	return Elmt(M, i, i);
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS(MATRIKS MIn, MATRIKS *MHsl) {
	NBrsEff(*MHsl) = NBrsEff(MIn);
  	NKolEff(*MHsl) = NKolEff(MIn);
	for(int i=GetFirstIdxBrs(MIn); i<=GetLastIdxBrs(MIn); i++){
		for (int j=GetFirstIdxKol(MIn); j<=GetLastIdxKol(MIn); j++){
			Elmt(*MHsl, i, j) = Elmt(MIn, i, j);
		}
	}
		
}

/* ********** KELOMPOK BACA/TULIS ********** */
void BacaMATRIKS (MATRIKS * M, char* namafile) {
	/* I.S. Matriks valid dan namafile valid
	/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
	/* Proses: membaca nilai elemen per baris dan kolom dari nama file */

	int NB = 0;
	int NK = 0;

	START(namafile);
	while (!EOP){
		if (EOL){
			NB = NB + 1 ;
			NK = 0;
			ADV();
		} else {
			Elmt(*M, NB, NK) = CC;
			ADV();
			NK = NK + 1;
		}
	}
	// if (EOP){ printf("%c",'X');}
	NKolEff(*M) = NK;
	NBrsEff(*M) = NB+1;
}

void TulisMATRIKS(MATRIKS M, indeks x, indeks y) {
	/* I.S. M terdefinisi */
	/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
		dipisahkan sebuah spasi */
	/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
	/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
	1 2 3
	4 5 6
	8 9 10
	*/
	indeks i,j;
	for (i = 0; i <= GetLastIdxBrs(M); i++) {
		for (j = 0; j <= GetLastIdxKol(M); j++) {
			if (j == GetLastIdxKol(M) && i == GetLastIdxBrs(M)) {
				printf("%c", Elmt(M, i, j));
			} else if (j == GetLastIdxKol(M)) {
				printf("%c\n", Elmt(M, i, j));
			}else if ( (i==x) && (j==y)){
				printf("%c",'P');
			} else {
				printf("%c", Elmt(M, i, j));
			}
		}
	}
}
/* ********** Operasi lain ********** */
/* Mengirimkan banyaknya elemen M */
int NBElmt (MATRIKS M) {
	return ((GetLastIdxBrs(M)+1)*(GetLastIdxKol(M)+1));
}





