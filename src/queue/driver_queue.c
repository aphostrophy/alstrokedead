#include <stdio.h>
#include "queue.h"
#include "../wahana/wahana.h"

int main(){
    //Simulasi skenario serve pada program
    //Ada beberapa fungsi pada ADT queue seperti prosedur Serve yang memiliki dependensi ke peta.c (tidak bisa diinclude)
    //Oleh karena itu, driver ini hanya mensimulasikan proses serve dengan menggunakan prosedur-prosedur pada ADT Queue

    Queue Q;
    Queue M;
    pengunjung P;
    Wahana LW;
    
    MakeEmpty_Queue(&M,10);
    bacaWahana(&LW,"../file/wahana.txt");

    //inisialisasi wahana yang berstatus good agar bisa generate queue
    for(int i=0;i<5;i++){
        LW.TI[i].status='G';
    }
    GenerateQueue(&Q,LW);
    printf("ini adalah kondisi antrean pengunjung di awal\n");
    PrintQueue(Q,1);
    printf("\n");

    printf("ini adalah kondisi antrean pengunjung setelah 1x serve\n");
    Dequeue(&Q,&P);
    DequeueWahana(&P,P.L[0]);
    Enqueue(&M,P);
    PrintQueue(Q,1);
    PrintQueue(M,2);
    printf("\n");

    printf("ini adalah kondisi antrean pengunjung setelah 2x serve\n");
    Dequeue(&Q,&P);
    DequeueWahana(&P,P.L[0]);
    Enqueue(&M,P);
    PrintQueue(Q,1);
    PrintQueue(M,2);
    printf("\n");

    printf("ini adalah kondisi antrean pengunjung setelah 3x serve\n");
    Dequeue(&Q,&P);
    DequeueWahana(&P,P.L[0]);
    Enqueue(&M,P);
    PrintQueue(Q,1);
    PrintQueue(M,2);
    printf("\n");

    printf("seluruh pengunjung pada Queue M yang waktu bermainnya bersisa 0 akan keluar dari Queue M\n");
    M.P[0].T=1;
    LeaveQueueT(&M,&Q,&LW);
    PrintQueue(Q,1);
    PrintQueue(M,2);
    printf("\n");

    for(int i=0;i<4;i++){
        Q.P[i].S=0;
    }
    printf("seluruh pengunjung yang memiliki nilai kesabaran <= 0 akan keluar dari Queue Q\n");
    LeaveQueueS(&Q);
    PrintQueue(Q,1);
    PrintQueue(M,2);

    int idx = GetIndex(&LW,M.P[0].W);
    LW.TI[idx].status='B';

    printf("\n");
    printf("jika wahana rusak ketika dinaiki, pengunjung akan dikembalikan ke queue utama\n");
    LeaveWahanaBroke(&M,&Q,&LW);
    PrintQueue(Q,1);
    PrintQueue(M,2);
}