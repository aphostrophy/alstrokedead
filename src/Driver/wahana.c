#include <stdio.h>
#include <string.h>
#include "../Header/boolean.h"
#include "../Header/wahana.h"
#include "../Header/mesinkar.h"
#include "../Header/mesinkata.h"

Kata arrWahanaGood[8];

void bacaWahana(Wahana *W, char* namaFile) {
    /* I.S. List Wahana valid dan namafile valid
	/* F.S. W terdefinisi nilai */
	/* Proses: membaca nilai per baris */
    
    Kata id, nama, deskripsi, bil1, bil2, bil3;
    int harga, durasi, kapasitas;
	int infoKe = 0;
    int kataKe = 1;
    
	START(namaFile);
    
	while (!EOP){
        int i = 0;
        CKata.Length = 0;
        while(CC != BLANK){
            if(CC == '\n') {
                ADV();
                break;
            }
            if(CC == '.') {
                break;
            }
            
            CKata.TabKata[i] = CC;
            i++;
            CKata.Length = i;
            // printf("%s %d\n", CKata.TabKata, CKata.Length);
            ADV();
        }
        switch(kataKe) {
            case 1:
                id = copyKata(CKata);
                break;
            case 2:
                nama = copyKata(CKata);
                break;
            case 3:
                bil1 = copyKata(CKata);
                harga = atoi(bil1.TabKata);
                break;
            case 4:
                bil2 = copyKata(CKata);
                durasi = atoi(bil2.TabKata);
                break;
            case 5:
                bil3 = copyKata(CKata);
                kapasitas = atoi(bil3.TabKata);
                break;
            case 6:
                deskripsi = copyKata(CKata);

                // inisiasi list
                (*W).TI[infoKe].id = copyKata(id);
                (*W).TI[infoKe].nama = copyKata(nama);
                (*W).TI[infoKe].harga = harga;
                (*W).TI[infoKe].durasi = durasi;
                (*W).TI[infoKe].kapasitas = kapasitas;
                (*W).TI[infoKe].status = 'N'; //inisiasi dengan not build
                (*W).TI[infoKe].deskripsi = copyKata(deskripsi);

                //inisiasi jumlah pengunjung dan penghasilan dengan 0
                (*W).TI[infoKe].inside = 0;
                (*W).TI[infoKe].pengunjung = 0;
                (*W).TI[infoKe].total_pengunjung = 0;
                (*W).TI[infoKe].penghasilan = 0;
                (*W).TI[infoKe].total_penghasilan = 0;

                kataKe = 0;
                infoKe++;
                break;
            default:
                break;
        }        
        kataKe++;
        IgnoreBlank();

        if(CC == '.') {
            break;
        }
	}
}

/* SELEKTOR */
Kata getNama(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].nama;
        }
    }
}

int getHarga(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].harga;
        }
    }
}

int getDurasi(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].durasi;
        }
    }
}

int getKapasitas(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].kapasitas;
        }
    }
}

char getStatus(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].status;
        }
    }
}

Kata getDeskripsi(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].deskripsi;
        }
    }
}

int getInside(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].inside;
        }
    }
}

int getPengunjung(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].pengunjung;
        }
    }
}

int getPenghasilan(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].penghasilan;
        }
    }
}

int getTotalPengunjung(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].total_pengunjung;
        }
    }
}

int getTotalPenghasilan(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].total_penghasilan;
        }
    }
}

/* FUNGSIONALITAS */
void printDetailWahana(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            printKata((*W).TI[i].id); printf("\n");
            printKata((*W).TI[i].nama); printf("\n");
            printf("Harga Tiket Wahana : %d\n", (*W).TI[i].harga);
            printf("Durasi Wahana : %d\n", (*W).TI[i].durasi);
            printf("Kapasitas Wahana : %d\n", (*W).TI[i].kapasitas);
            printf("Status Wahana : %c\n", (*W).TI[i].status);
            printKata((*W).TI[i].deskripsi); printf("\n");
            break;
        }
    }
}

void printReportWahana(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
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
        printKata((*W).TI[i].nama); printf(" ");
        printKata((*W).TI[i].id); printf("\n");
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

int countWahanaGood(Wahana *W) {
    int count = 0;
    int i;
    for(i = 0; i < 8; i++) {
        if((*W).TI[i].status == 'G') {
            count++;
        }
    }
    return count;
}

void makeListWahanaGood(Wahana *W) {
    int idx = 0;
    int i;
    for(i = 0; i < 8; i++) {
        if((*W).TI[i].status == 'G') {
            Kata[idx] = copyKata((*W).TI[i].id);
            idx++;
        }
    }
}

void printBrokenWahana(Wahana *W) {
    if(countBrokenWahana(W) == 0) {
        printf("Tidak ada wahana yang sedang rusak.\n");
    } else {
        printf("Wahana yang sedang rusak :\n");
        int count = 1;
        for(int i = 0; i < 8; i++) {
            if((*W).TI[i].status == 'B') {
                printf("%d. ", count); printKata((*W).TI[i].nama); printf("\n");
                count++;
            }
        }
    }
}

void printNotBuilded(Wahana *W){
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].status == 'N'){
            printKata((*W).TI[i].nama); printf("\n");
        }
    }
}

int GetIndex(Wahana *W, char id ){
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return i;
        }
    }
}