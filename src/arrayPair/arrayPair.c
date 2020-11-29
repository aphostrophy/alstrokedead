#include <stdio.h>
#include "arrayPair.h"
#include "../boolean.h"
#include "pair.h"
#include "../mesinkata/mesinkar.h"
#include "../mesinkata/mesinkata.h"

/*
    Versi IsKataSama yang case sensitive ( di mesin kata dibuat case insensitive)
*/
boolean ArrayPair_IsKataSama (Kata K1, Kata K2) {
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

void ArrayPair_MakeEmpty (TabInt * T){
    int i;
    for(i=IdxMin; i<=IdxMax;i++){
        Pair_ItemLength(*T,i) = ItemLengthUndef;
        Pair_Cost(*T,i) = CostUndef;
    }
}
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
/* Proses: Inisialisasi semua elemen tabel T dengan ValUndef */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */

int ArrayPair_NbElmt (TabInt T){
    int neff;
    neff = 0;
    int i;
    for(i=IdxMin;i<=IdxMax;i++){
        if(Pair_Cost(T,i)==-1 && Pair_ItemLength(T,i)==0){
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
int ArrayPair_MaxNbEl (TabInt T){
    return IdxMax-IdxMin+1;
}
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
/* *** Selektor INDEKS *** */
IdxType ArrayPair_GetFirstIdx (TabInt T){
    return IdxMin;
}
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
IdxType ArrayPair_GetLastIdx (TabInt T){
    return ArrayPair_NbElmt(T)-1;
}
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

/* ********** Test Indeks yang valid ********** */
boolean ArrayPair_IsIdxValid (TabInt T, IdxType i){
    return i>=IdxMin && i<=IdxMax;
}
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean ArrayPair_IsIdxEff (TabInt T, IdxType i){
    return i>=ArrayPair_GetFirstIdx(T) && i<=ArrayPair_GetLastIdx(T);
}
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean ArrayPair_IsEmpty (TabInt T){
    if(ArrayPair_NbElmt(T)==0){
        return true;
    } else{
        return false;
    }
}
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
/* *** Test tabel penuh *** */
boolean ArrayPair_IsFull (TabInt T){
    if(ArrayPair_NbElmt(T)==IdxMax-IdxMin+1){
        return true;
    } else{
        return false;
    }
}
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void ArrayPair_BacaIsi (TabInt * T, char * namafile){
    int even=0; //Baris teks dihitung dari 0
    int i=0;
    int j=0;
    START(namafile);
    while(!EOP){
        IgnoreBlank();
        if(EOL){
            even = (even+1)%2;
            j++;
            ADV();
        } else if(even==0){
            i = 0;
            while ((CC != MARK) && (CC != BLANK) && (i < NMax) && !EOL)
            {
                Pair_Item(*T, j/2).TabKata[i] = CC;
                ADV();
                i++;
            } /* CC = MARK or CC = BLANK */
            IgnoreBlank();
            Pair_ItemLength(*T, j/2) = i;
        } else if(even==1){
            i = 0;
            Pair_Cost(*T, j/2) = 0;
            do {
                Pair_Cost(*T, j/2) *= 10;
                Pair_Cost(*T, j/2) = Pair_Cost(*T, j/2) + (int)CC-48;
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
void ArrayPair_TulisIsiTab (TabInt T){
    int i,j;
    if(ArrayPair_NbElmt(T)==0){
        printf("Empty");
    } else{
        for(i=IdxMin;i<ArrayPair_NbElmt(T);i++){
            for(j=IdxMin;j<Pair_ItemLength(T,i);j++){
                printf("%c", Pair_Item(T,i).TabKata[j]);
            }
            printf(": %d ", Pair_Cost(T,i));
        }
    }
}

void ArrayPair_TulisIsiTabNumbering (TabInt T){
    int i,j;
    if(ArrayPair_NbElmt(T)==0){
        printf("Empty");
    } else{
        for(i=IdxMin;i<ArrayPair_NbElmt(T);i++){
            printf("%d. ", i+1);
            for(j=IdxMin;j<Pair_ItemLength(T,i);j++){
                printf("%c",Pair_Item(T,i).TabKata[j]);
            }
            printf(": %d ", Pair_Cost(T,i));
        }
    }
}
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku; 
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,char* namafile...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType ArrayPair_SearchByItem (TabInt T, Kata X){
    int i;
    if(ArrayPair_IsEmpty(T)){
        return IdxUndef;
    }
    for(i=IdxMin;i<ArrayPair_NbElmt(T);i++){
        if(ArrayPair_IsKataSama(Pair_Item(T,i),X)){
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
boolean ArrayPair_SearchBooleanByItem (TabInt T, Kata X){
    return ArrayPair_SearchByItem(T,X)!= IdxUndef;
}
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */


/* I.S. Tabel T tidak kosong */
/* F.S. Max berisi nilai maksimum T;
        Min berisi nilai minimum T */

/* ********** OPERASI LAIN ********** */

/* ********** SORTING ********** */
void ArrayPair_Sort (TabInt * T, boolean asc){
    int i,j;
    Pair temp;
    if(asc==true){
        for(i=IdxMin;i<ArrayPair_NbElmt(*T);i++){
            for(j=0;j<ArrayPair_NbElmt(*T)-i-1;j++){
                if(Pair_Cost(*T,j)>Pair_Cost(*T,j+1)){
                    temp = Pair_Elmt(*T,j);
                    Pair_Elmt(*T,j) = Pair_Elmt(*T,j+1);
                    Pair_Elmt(*T,j+1) = temp;
                }
            }
        }
    } else{
        for(i=IdxMin;i<ArrayPair_NbElmt(*T);i++){
            for(j=0;j<ArrayPair_NbElmt(*T)-i-1;j++){
                if(Pair_Cost(*T,j)<Pair_Cost(*T,j+1)){
                    temp = Pair_Elmt(*T,j);
                    Pair_Elmt(*T,j) = Pair_Elmt(*T,j+1);
                    Pair_Elmt(*T,j+1) = temp;
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
void ArrayPair_AddAsLastEl (TabInt * T, Pair_ElType X){
    Pair_Elmt(*T, ArrayPair_NbElmt(*T)) = X;
}
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
/* ********** MENGHAPUS ELEMEN ********** */
void ArrayPair_DelLastEl (TabInt * T, Pair_ElType * X){
    *X = Pair_Elmt(*T,ArrayPair_NbElmt(*T)-1);
    Pair_ItemLength(*T,ArrayPair_NbElmt(*T)-1) = ItemLengthUndef;
    Pair_Cost(*T,ArrayPair_NbElmt(*T)-1) = CostUndef;
}
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */