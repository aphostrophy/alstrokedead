#include <stdio.h>
#include "arrayTriplet.h"
#include "../boolean.h"
#include "triplet.h"
#include "../mesinkata/mesinkar.h"
#include "../mesinkata/mesinkata.h"

boolean ArrayTriplet_IsKataSama (Kata K1, Kata K2) {
    if(K1.Length != K2.Length) {
        return false;
    } else {
        int i;
        for(i = 0; i < K1.Length; i++) {
            if(K1.TabKata[i] != K2.TabKata[i]) {
                return false;
            }
        }
        return true;
    }
}

void ArrayTriplet_MakeEmpty (Triplet_TabInt * T){
    int i;
    for(i=IdxMin; i<=IdxMax;i++){
        Triplet_NamaLength(*T,i) = NamaLengthUndef;
        Triplet_BahanLength(*T,i) = NamaLengthUndef;
        Triplet_Cost(*T,i) = CostUndef;
    }
}
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
/* Proses: Inisialisasi semua elemen tabel T dengan ValUndef */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */

int ArrayTriplet_NbElmt (Triplet_TabInt T){
    int neff;
    neff = 0;
    int i;
    for(i=IdxMin;i<=IdxMax;i++){
        if(Triplet_Cost(T,i)==-1 && Triplet_NamaLength(T,i)==0){
            return neff;
        } else{
            neff++;
        }
    }
    return neff;
}
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */
int ArrayTriplet_MaxNbEl (Triplet_TabInt T){
    return IdxMax-IdxMin+1;
}
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
/* *** Selektor INDEKS *** */
IdxType ArrayTriplet_GetFirstIdx (Triplet_TabInt T){
    return IdxMin;
}
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
IdxType ArrayTriplet_GetLastIdx (Triplet_TabInt T){
    return ArrayTriplet_NbElmt(T)-1;
}
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

/* ********** Test Indeks yang valid ********** */
boolean ArrayTriplet_IsIdxValid (Triplet_TabInt T, IdxType i){
    return i>=IdxMin && i<=IdxMax;
}
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean ArrayTriplet_IsIdxEff (Triplet_TabInt T, IdxType i){
    return i>=ArrayTriplet_GetFirstIdx(T) && i<=ArrayTriplet_GetLastIdx(T);
}
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean ArrayTriplet_IsEmpty (Triplet_TabInt T){
    if(ArrayTriplet_NbElmt(T)==0){
        return true;
    } else{
        return false;
    }
}
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
/* *** Test tabel penuh *** */
boolean ArrayTriplet_IsFull (Triplet_TabInt T){
    if(ArrayTriplet_NbElmt(T)==IdxMax-IdxMin+1){
        return true;
    } else{
        return false;
    }
}
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void ArrayTriplet_BacaIsi (Triplet_TabInt * T, char * namafile){
    int triple=0; //Baris teks dihitung dari 0
    int i=0;
    int j=0;
    START(namafile);
    while(!EOP){
        IgnoreBlank();
        if(EOL){
            triple = (triple+1)%3;
            j++;
            ADV();
        } else if(triple==0){
            i = 0;
            while ((CC != MARK) && (CC != BLANK) && (i < NMax) && !EOL)
            {
                Triplet_Nama(*T, j/3).TabKata[i] = CC;
                ADV();
                i++;
            } /* CC = MARK or CC = BLANK */
            IgnoreBlank();
            Triplet_NamaLength(*T, j/3) = i;
        } else if(triple==1){
            i = 0;
            while((CC != MARK) && (CC != BLANK) && (i < NMax) && !EOL){
                Triplet_Bahan(*T, j/3).TabKata[i] = CC;
                ADV();
                i++;
            }
            IgnoreBlank();
            Triplet_BahanLength(*T, j/3) = i;
        } else if(triple==2){
            i = 0;
            Triplet_Cost(*T, j/3) = 0;
            do {
                Triplet_Cost(*T, j/3) *= 10;
                Triplet_Cost(*T, j/3) = Triplet_Cost(*T, j/3) + (int)CC-48;
                ADV();
            }while(CC!=MARK && CC!=BLANK && !EOL);
            IgnoreBlank();
        }
    }
}
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxNbEl(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxNbEl(T); Lakuchar* namafilekan N kali: Baca elemen mulai dari indeks 
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
void ArrayTriplet_TulisIsiTab (Triplet_TabInt T){
    int i,j;
    if(ArrayTriplet_NbElmt(T)==0){
        printf("Empty");
    } else{
        for(i=IdxMin;i<ArrayTriplet_NbElmt(T);i++){
            for(j=IdxMin;j<Triplet_NamaLength(T,i);j++){
                printf("%c", Triplet_Nama(T,i).TabKata[j]);
            }
            printf("\n");
            for(j=IdxMin;j<Triplet_BahanLength(T,i);j++){
                printf("%c", Triplet_Bahan(T,i).TabKata[j]);
            }
            printf(": %d ", Triplet_Cost(T,i));
            printf("\n");
        }
    }
}

void ArrayTriplet_TulisIsiTabNumbering (Triplet_TabInt T){
    int i,j;
    if(ArrayTriplet_NbElmt(T)==0){
        printf("Empty");
    } else{
        for(i=IdxMin;i<ArrayTriplet_NbElmt(T);i++){
            printf("%d. ", i+1);
            for(j=IdxMin;j<Triplet_NamaLength(T,i);j++){
                printf("%c",Triplet_Nama(T,i).TabKata[j]);
            }
            printf("\n");
            for(j=IdxMin;j<Triplet_BahanLength(T,i);j++){
                printf("%c", Triplet_Bahan(T,i).TabKata[j]);
            }
            printf(": %d ", Triplet_Cost(T,i));
        }
    }
}
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku; 
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,char* namafile...,en] */

/* Jika tabel kosong : menulis empty */

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType ArrayTriplet_SearchByNama (Triplet_TabInt T, Kata X){
    int i;
    if(ArrayTriplet_IsEmpty(T)){
        return IdxUndef;
    }
    for(i=IdxMin;i<ArrayTriplet_NbElmt(T);i++){
        if(ArrayTriplet_IsKataSama(Triplet_Nama(T,i),X)){
            return i;
        }
    }
    return IdxUndef;
}
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
boolean ArrayTriplet_SearchBooleanByNama (Triplet_TabInt T, Kata X){
    return ArrayTriplet_SearchByNama(T,X)!= IdxUndef;
}
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */


/* I.S. Tabel T tidak kosong */
/* F.S. Max berisi nilai maksimum T;
        Min berisi nilai minimum T */

/* ********** OPERASI LAIN ********** */

/* ********** SORTING ********** */
void ArrayTriplet_Sort (Triplet_TabInt * T, boolean asc){
    int i,j;
    Triplet temp;
    if(asc==true){
        for(i=IdxMin;i<ArrayTriplet_NbElmt(*T);i++){
            for(j=0;j<ArrayTriplet_NbElmt(*T)-i-1;j++){
                if(Triplet_Cost(*T,j)>Triplet_Cost(*T,j+1)){
                    temp = Triplet_Elmt(*T,j);
                    Triplet_Elmt(*T,j) = Triplet_Elmt(*T,j+1);
                    Triplet_Elmt(*T,j+1) = temp;
                }
            }
        }
    } else{
        for(i=IdxMin;i<ArrayTriplet_NbElmt(*T);i++){
            for(j=0;j<ArrayTriplet_NbElmt(*T)-i-1;j++){
                if(Triplet_Cost(*T,j)<Triplet_Cost(*T,j+1)){
                    temp = Triplet_Elmt(*T,j);
                    Triplet_Elmt(*T,j) = Triplet_Elmt(*T,j+1);
                    Triplet_Elmt(*T,j+1) = temp;
                }
            }
        }      
    }
}
/* I.S. T boleh kosong */
/* F.S. Jika asc = true, T terurut membesar */
/*      Jika asc = false, T terurut mengecil */
/* Proses : Mengurutkan T dengan salah satu algoritma sorting,
   algoritma bebas */

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void ArrayTriplet_AddAsLastEl (Triplet_TabInt * T, Triplet_ElType X){
    Triplet_Elmt(*T, ArrayTriplet_NbElmt(*T)) = X;
}
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
/* ********** MENGHAPUS ELEMEN ********** */
void ArrayTriplet_DelLastEl (Triplet_TabInt * T, Triplet_ElType * X){
    *X = Triplet_Elmt(*T,ArrayTriplet_NbElmt(*T)-1);
    Triplet_NamaLength(*T,ArrayTriplet_NbElmt(*T)-1) = NamaLengthUndef;
    Triplet_Cost(*T,ArrayTriplet_NbElmt(*T)-1) = CostUndef;
}
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */