#include "../Header/queue.h"
#include "../Header/wahana.h"
#include "../Header/mesinkata.h"
#include <stdio.h>
#include <stdlib.h>


Wahana LW;
Queue Q;
Queue M;
int pmoney=50000;

void HandleServe(){
	Kata Action, Nama_Wahana;
    char bangunan = getBangunanSekitar();
    if(bangunan=='A'){
        printf("Mau serve untuk wahana apa? :");
        Kata SERVE;
        int kata_ke = 1;
        SERVE.TabKata[0] = 's';SERVE.TabKata[1] = 'e';SERVE.TabKata[2] = 'r';SERVE.TabKata[3] = 'v';SERVE.TabKata[4] = 'e';
        SERVE.Length = 5;
        STARTBUY();
        while(!EOP){
            int i = 0;
            CKata.Length=0;
            while(CC!=BLANK){
                CKata.TabKata[i] = CC;
                if(CC=='\n'){
                    break;
                }
                i++;
                CKata.Length=i;
                ADV();
            }
            if(kata_ke==1){
                Action = CKata;
            } else if(kata_ke==2){
                Nama_Wahana = CKata;
            }
            if(CC=='\n'){
                break;
            }
            kata_ke++;
            IgnoreBlank();
        }
        if(IsKataSama(Action, SERVE)){
            Serve(&Q,&M,Nama_Wahana.TabKata[0],&LW,&pmoney);
        }
        else{
            printf("Command salah! Tekan apapun untuk melanjutkan\n");
            getchar();
        }
    }
    else{
		printf("Tidak ada wahana di sekitar Anda");
		getchar();       
    }
    // Validasi apakah yang diketik benar benar "upgrade"
    // Validasi apakah uang masih cukup dan validasi apakah waktu cukup , validasi apakah bahan bangunan cukup untuk upgrade
    // Kalo memang sabi maka push ke stack, tambah waktu yang dibtuhkan , tambah uang yang dibutuhkan, tambah bahan bangunan yang dibutuhkan, kalo tidak keluarkan pesan error

}

//============================== BATAS SUCI =====================================
int main(){
    MakeEmpty_Queue(&M,10);
    bacaWahana(&LW, "../file/wahana.txt");
    printListWahana(&LW);
    LW.TI[0].status='G';
    LW.TI[1].status='G';
    LW.TI[2].status='G';
    LW.TI[3].status='G';
    GenerateQueue(&Q,LW);
    PrintQueue(Q);
    // Serve(&Q,&M,'C',&LW,&pmoney);
    HandleServe();
    ManageTime(5,&Q,&M,LW);
    PrintQueue(Q);
    PrintQueue(M);
    printf("%d\n",pmoney);
    // InfoWahana N= getWahanabyID(&LW,'C');
    // N.inside=N.inside+1;
    // printf("%d\n",N.inside);
    // Serve(&Q,&M,'C',&LW,&pmoney);
    // ManageTime(5,&Q,&M,LW);
    // PrintQueue(Q);
    // PrintQueue(M);
    // Serve(&Q,&M,'P',&LW,&pmoney);
    // ManageTime(5,&Q,&M,LW);
    // PrintQueue(Q);
    // PrintQueue(M);
    // Serve(&Q,&M,'T',&LW,&pmoney);
    // ManageTime(5,&Q,&M,LW);
    // PrintQueue(Q);
    // PrintQueue(M);
    // Serve(&Q,&M,'P',&LW,&pmoney);
    // ManageTime(5,&Q,&M,LW);
    // PrintQueue(Q);
    // PrintQueue(M);
    // Serve(&Q,&M,'T',&LW,&pmoney);
    // ManageTime(5,&Q,&M,LW);
    // PrintQueue(Q);
    // PrintQueue(M);
    // Serve(&Q,&M,'T',&LW,&pmoney);
    // ManageTime(5,&Q,&M,LW);
    // PrintQueue(Q);
    // PrintQueue(M);
    // printf("%d",pmoney);
    // ManageTime(5,&Q,&M,LW);
    // PrintQueue(Q);
    // PrintQueue(M);
}
