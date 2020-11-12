#include <stdio.h>
#include <string.h>
#include "../Header/boolean.h"
#include "../Header/wahana.h"

string arrNamaWahana[10] = {"SkyCoaster", "PirateShip", "Tornado", "Carousel", "HauntedHouse", "FerrisWheel", "BumperCars", "GyroDrop"};
char idWahana[8] = {'S', 'P', 'T', 'C', 'H', 'F','B','G'};
int arrHargaWahana[8] = {10000, 15000, 50000, 40000, 5000, 10000, 75000, 50000};
int durasiWahana[8] = {20, 15, 10, 10, 25, 20, 15, 10};
int arrKapasitas[8] = {8, 6, 4, 8, 2, 6, 4, 8};
string arrDeskripsi[8] = {"Ini Deskripsi", "Ini Deskripsi", "Ini Deskripsi", "Ini Deskripsi", "Ini Deskripsi", "Ini Deskripsi", "Ini Deskripsi", "Ini Deskripsi"};

/* KONSTUKTOR */
Wahana makeListWahana(Wahana *W) {
    int i;
    for(i = 0; i < 8; i++) {
        (*W).TI[i].id = idWahana[i];
        strcpy((*W).TI[i].nama, arrNamaWahana[i]);
        (*W).TI[i].harga = arrHargaWahana[i];
        (*W).TI[i].durasi = durasiWahana[i];
        (*W).TI[i].kapasitas = arrKapasitas[i];
        (*W).TI[i].status = 'N'; //inisiasi dengan not build
        strcpy((*W).TI[i].deskripsi, arrDeskripsi[i]);

        //inisiasi jumlah pengunjung dan penghasilan dengan 0
        (*W).TI[i].inside = 0;
        (*W).TI[i].pengunjung = 0;
        (*W).TI[i].total_pengunjung = 0;
        (*W).TI[i].penghasilan = 0;
        (*W).TI[i].total_penghasilan = 0;
    }
}

/* SELEKTOR */
char* getNama(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id == id) {
            return (*W).TI[i].nama;
        }
    }
}

int getHarga(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id == id) {
            return (*W).TI[i].harga;
        }
    }
}

int getDurasi(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id == id) {
            return (*W).TI[i].durasi;
        }
    }
}

int getKapasitas(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id == id) {
            return (*W).TI[i].kapasitas;
        }
    }
}

char getStatus(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id == id) {
            return (*W).TI[i].status;
        }
    }
}

char* getDeskripsi(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id == id) {
            return (*W).TI[i].deskripsi;
        }
    }
}

int getInside(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id == id) {
            return (*W).TI[i].inside;
        }
    }
}

int getPengunjung(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id == id) {
            return (*W).TI[i].pengunjung;
        }
    }
}

int getPenghasilan(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id == id) {
            return (*W).TI[i].penghasilan;
        }
    }
}

int getTotalPengunjung(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id == id) {
            return (*W).TI[i].total_pengunjung;
        }
    }
}

int getTotalPenghasilan(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id == id) {
            return (*W).TI[i].total_penghasilan;
        }
    }
}

void printDetailWahana(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id == id) {
            printf("Wahana ID : %c\n", (*W).TI[i].id);
            printf("Nama Wahana : %s\n", (*W).TI[i].nama);
            printf("Harga Tiket Wahana : %d\n", (*W).TI[i].harga);
            printf("Durasi Wahana : %d\n", (*W).TI[i].durasi);
            printf("Kapasitas Wahana : %d\n", (*W).TI[i].kapasitas);
            printf("Status Wahana : %c\n", (*W).TI[i].status);
            printf("Deskripsi Wahana : %s\n", (*W).TI[i].deskripsi);
            break;
        }
    }
}

void printReportWahana(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id == id) {
            printf("Jumlah Pengunjung Wahana hari ini : %d\n", (*W).TI[i].pengunjung);
            printf("Jumlah Penghasilan Wahana hari ini : %d\n", (*W).TI[i].penghasilan);
            printf("Jumlah Total Pengunjung Wahana : %d\n", (*W).TI[i].total_pengunjung);
            printf("Jumlah Total Pengunjung Wahana : %d\n", (*W).TI[i].total_penghasilan);
            break;
        }
    }
}

void printListWahana(Wahana *W) {
    for(int i = 0; i < 8; i++) {
        printf("%s (%c)\n", (*W).TI[i].nama, (*W).TI[i].id);
    }
}

int countBrokenWahana(Wahana *W) {
    int res = 0;
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].status == 'B') {
            res++;
        }
    }
    return res;
}

void printBrokenWahana(Wahana *W) {
    if(countBrokenWahana(W) == 0) {
        printf("Tidak ada wahana yang sedang rusak.\n");
    } else {
        printf("Wahana yang sedang rusak :\n");
        int count = 1;
        for(int i = 0; i < 8; i++) {
            if((*W).TI[i].status == 'B') {
                printf("%d. %s\n", count, (*W).TI[i].nama);
                count++;
            }
        }
    }
}

void printNotBuilded(Wahana *W){
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].status == 'N'){
            printf("%s\n", (*W).TI[i].nama);
        }
    }
}

int GetIndex(Wahana *W, char id ){
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id == id) {
            return i;
        }
    }
}