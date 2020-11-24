#include "../Header/queue.h"
#include "../Header/wahana.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

boolean IsEmpty_Queue (Queue Q){
    return (Tail(Q)==nil);
}

boolean IsFull_Queue (Queue Q){
    return (Tail(Q)==MaxEl(Q)-1);
}

int NBElmt_Queue (Queue Q){
    return (Tail(Q)+1);
}

void MakeEmpty_Queue (Queue * Q, int Max){
    (*Q).P = (pengunjung*) malloc ((Max) * sizeof(pengunjung));
    if ((*Q).P != NULL){
        MaxEl(*Q)=Max;
    }
    else{
        MaxEl(*Q)=0;
    }
    Tail(*Q)=nil;
}

void Dealokasi_Queue (Queue *Q){
    MaxEl(*Q) = 0;
    free((*Q).P); 
}

void GenerateQueue (Queue * Q){
    int i,j;
    char wahana[9]={'S','P','T','C','H','F','B','G','-'};
    MakeEmpty_Queue(Q,10);
    // srand(time(0));
    for (i=0;i<5;i++){
        for (j=0;j<3;j++){
            if (j==0){
                (*Q).P[i].L[j]=wahana[rand() % 8];
            }
            else{
                (*Q).P[i].L[j]=wahana[rand() % 9];
            }
        }
        while((*Q).P[i].L[1]==(*Q).P[i].L[0] || (*Q).P[i].L[1]==(*Q).P[i].L[2]){
            (*Q).P[i].L[1]=wahana[rand() % 9];
        }
        while((*Q).P[i].L[2]==(*Q).P[i].L[0]){
            (*Q).P[i].L[2]=wahana[rand() % 9];
        }

        if ((*Q).P[i].L[1]=='-'){
            (*Q).P[i].L[2]=='-';
        }
        (*Q).P[i].S = 10;
        (*Q).P[i].X = (i+1);
        (*Q).P[i].T = 0;
        (*Q).P[i].ID = (i+1); 
        (*Q).P[i].W = '-';
        Tail(*Q)=Tail(*Q)+1;
    }
}

void GeneratePengunjung(pengunjung *P,int ID){
    Queue Q;
    GenerateQueue(&Q);
    *P = Q.P[0];
    (*P).ID=ID;
}

void Dequeue (Queue * Q, pengunjung * X){
    if (!IsEmpty_Queue(*Q)){
        int i;
        *X = (*Q).P[0];
        for (i=1;i<=Tail(*Q);i++){
            (*Q).P[i-1]=(*Q).P[i];
        }
        (*Q).TAIL=(*Q).TAIL-1;
    }
}

//print queue
void PrintQueue (Queue Q){
    int j=0;
    printf("[%d/5]\n",(Q.TAIL+1));
    while (j<=Q.TAIL){
        int i=0;
        int count=0;
        printf("(");
        while (Q.P[j].L[i] != '-' && i<3){
            count=count+1;
            i=i+1;
        }
        i=0;
        while (Q.P[j].L[i] != '-' && i<3){
            switch (Q.P[j].L[i]){
                case 'S':
                    printf("Sky Coaster");
                    break;
                case 'P':
                    printf("Pirate Ship");
                    break;
                case 'T':
                    printf("Tornado");
                    break;
                case 'C':
                    printf("Carousel");
                    break;
                case 'H':
                    printf("Haunted House");
                    break;
                case 'F':
                    printf("Ferris Wheel");
                    break;
                case 'B':
                    printf("Bumper Car");
                    break;
                case 'G':
                    printf("Gyro Drop");
                    break;
                default:
                    printf("ya gamungkin sih");  
            }

            if (i!=(count-1)){
                printf(",");
            }
            i=i+1;
        }
        printf(")");
        printf(", ");
        printf("kesabaran : %d  prio : %d //customer %d\n", Q.P[j].S,Q.P[j].X,Q.P[j].ID);
        j=j+1;
    }
}

//cek apakah list wahana kosong
boolean isListWahanaEmpty(char L[3]){
    return L[0]=='-';
}

//dequeue wahana dari list wahana pengunjung
void DequeueWahana(pengunjung *X,char W){
    int i,idx;
    boolean found=false;

    if(!isListWahanaEmpty((*X).L)){
        for(i=0;i<3;i++){
            if ((*X).L[i]==W){
                (*X).W=W;
                found=true;
                (*X).L[i]='-';
                idx=i;
            }
        }
        if(found){
            if(idx!=3){
                for(i=idx+1;i<3;i++){
                    (*X).L[i-1]=(*X).L[i];
                }
            }
            (*X).L[2]='-';
        }
    }
}

//mengosongkan queue yang terisi
void EmptyQueue(Queue *Q){
    pengunjung P;
    while(!IsEmpty_Queue(*Q)){
        Dequeue(Q,&P);
    }
    Dealokasi_Queue(Q);
}

void Enqueue(Queue *Q, pengunjung P){
    boolean found=false;
    int i=0;

    if (IsEmpty_Queue(*Q)){
        (*Q).P[0]=P;
    }
    else{
        for (i=(*Q).TAIL;i>=0;i--){
            if ((*Q).P[i].X <= P.X){ //ver 1 pake < bukan <=
                found=true;
                for (int j=(*Q).TAIL;j>=(i+1);j--){
                    (*Q).P[j+1]=(*Q).P[j];
                }
            }
            if (found){
                break;
            }
        }
        if (found){
            (*Q).P[i+1]=P;
        }
        else if(found==false){
            for (int j=(*Q).TAIL;j>=0;j--){
                (*Q).P[j+1]=(*Q).P[j];
            }
            (*Q).P[0]=P;            
        }
    }
    (*Q).TAIL=(*Q).TAIL+1;
}

void ReduceKesabaran(Queue *Q){
    if(!IsEmpty_Queue(*Q)){
        for(int i=0;i<=(*Q).TAIL;i++){
            (*Q).P[i].S--;
            (*Q).P[i].X--;
        }
    }
}

void ReduceTime(Queue *Q,int Time){
    if(!IsEmpty_Queue(*Q)){
        for(int i=0;i<=(*Q).TAIL;i++){
            (*Q).P[i].T = (*Q).P[i].T - Time;
        }
    }  
}

void LeaveQueueT(Queue *M, Queue *Q, Wahana W){
    int idx[5];
    int lastidx=0;
    for (int i=0;i<=(*M).TAIL;i++){
        if ((*M).P[i].T <= 0){
            idx[lastidx]=i;
            lastidx++;
        }
    }
    lastidx=lastidx-1;
    for(int i=0;i<=lastidx;i++){
        pengunjung X;
        X = (*M).P[idx[i]];
        if(isListWahanaEmpty(X.L)==false){
            X.X=X.X-1; //masukin ke queue main
            Enqueue(Q,X);
        }
        for(int j=idx[i];j<=(*M).TAIL;j++){
            (*M).P[j]=(*M).P[j+1];
        }
        for(int k=i;k<=lastidx;k++){
            idx[k]=idx[k]-1;
        }
        (*M).TAIL=(*M).TAIL-1;
    }
}

//mengecek queue lalu me-remove pengunjung pada queue yang sudah memiliki kesabaran negatif
void LeaveQueueS(Queue *Q){
    int idx[5];
    int lastidx=0;
    for (int i=0;i<=(*Q).TAIL;i++){
        if ((*Q).P[i].S <= 0){
            idx[lastidx]=i;
            lastidx++;
        }
    }
    lastidx=lastidx-1;
    for(int i=0;i<=lastidx;i++){
        for(int j=idx[i];j<=(*Q).TAIL;j++){
            (*Q).P[j]=(*Q).P[j+1];
        }
        for(int k=i;k<=lastidx;k++){
            idx[k]=idx[k]-1;
        }
        (*Q).TAIL=(*Q).TAIL-1;
    }
}

void Serve(Queue *Q, Queue *M, char W,Wahana LW, int pmoney){
    if (getStatus(&LW,W)!='B' && (getInside(&LW,W)!=getKapasitas(&LW,W))){
        pengunjung X;
        //Dequeue
        Dequeue(Q,&X);
        DequeueWahana(&X,W);

        //set durasi bermain pengunjung
        X.T=getDurasi(&LW,W);

        //masukin pengunjung ke array bermain global
        Enqueue(M,X);
    
        //increment inside wahana
        InfoWahana N= getWahanabyID(&LW,W);
        N.inside=N.inside+1;

        //kurangi kesabaran & naikin prioritas orang di antrian
        ReduceKesabaran(Q);

        //tambah duit
        pmoney=pmoney+getHarga(&LW,W);
    }
    else{
        printf("Maaf wahana rusak atau kapasitasnya sudah penuh");
        //kurangi kesabaran orang di antrian
        ReduceKesabaran(Q);    
    }
}

