#include "../mesinkata/mesinkar.h"
#ifndef queue_H
#define queue_H

#include "../boolean.h"
#include "../wahana/wahana.h"
#include <stdio.h>
#include <stdlib.h>

#define HEAD 0
#define nil -1

typedef int kesabaran;
typedef int ptime;
typedef int prio;
typedef char wahana_que;
typedef struct { char L[3] ; kesabaran S ;  ptime T; prio X; int ID; char W;} pengunjung;

typedef int address;  
typedef struct { pengunjung *P; 
                 address TAIL;
                 int MaxEl;
               } Queue;
               
#define List(P) (P).L
#define Kesabaran(P) (P).S
#define Tail(Q) (Q).TAIL
#define InfoTail(Q) (Q).P[(Q).TAIL]
#define InfoHead(Q) (Q).P[HEAD]
#define MaxEl(Q) (Q).MaxEl


boolean IsEmpty_Queue (Queue Q);
boolean IsFull_Queue (Queue Q);
int NBElmt_Queue (Queue Q);
void MakeEmpty_Queue (Queue * Q, int Max);
void Dealokasi_Queue(Queue * Q);
void GenerateQueue (Queue * Q, Wahana LW);
//inisialisasi antrean pada program utama
void Enqueue (Queue * Q, pengunjung X);
//Memasukan pengunjung ke Queue
void Dequeue (Queue * Q, pengunjung * X);
//'Melepas' head Queue dari Queue
void DequeueWahana(pengunjung *X,char W);
//dequeue wahana dari list wahana pengunjung
void PrintQueue (Queue Q,int n);
//print queue
void LeaveQueueS(Queue *Q);
//mengecek queue lalu me-remove pengunjung pada queue yang sudah memiliki kesabaran negatif
void EmptyQueue(Queue *Q);
//mengosongkan queue yang terisi
void Enqueue(Queue *Q, pengunjung P);
//Memasukan pengunjung ke Queue
void ReduceKesabaran(Queue *Q);
//Mengurangi kesabaran untuk seluruh pengunjung pada queue
void ReduceTime(Queue *Q,int Time, Wahana LW);
//Mengurangi durasi bermain untuk seluruh pengunjung pada queue bermain
boolean isListWahanaEmpty(char L[3]);
//cek apakah list wahana kosong
void GeneratePengunjung(pengunjung *P, int ID,int prio, Wahana LW);
//Generate pengunjung baru yang bisa masuk ke queue di tengah permainan
void Serve(Queue *Q, Queue *M, char W,Wahana *LW, int *pmoney);
//Prosedur melakukan serve
void LeaveQueueT(Queue *M, Queue *Q, Wahana *LW);
//Prosedur untuk mengeluarkan pengunjung yang sudah habis sisa waktu bermainnya dari queue bermain
//Apabila pengunjung masih memiliki wahana yang ingin dinaiki maka pengunjung akan dikembalikan ke queue utama
void ManageTime(int time, Queue *Q, Queue *M,Wahana LW);
void LeaveWahanaBroke(Queue *M, Queue *Q, Wahana *W);
//Prosedur untuk memaksa keluar pengunjung yang tengah menaiki wahana rusak, pengunjung akan dikembalikan ke queue utama
boolean IsWahanaInList(char W, Queue Q);
//Mengecek apakah suatu ID wahana ada pada list wahana pengunjung
boolean IsDouble(char W, char L[3]);
int getLastIdxListW(char L[3]);
//Mendapatkan indeks terakhir dari list wahana yang ingin dinaiki pengunjung

#endif
