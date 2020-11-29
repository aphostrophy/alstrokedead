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
void GenerateQueue (Queue * Q);
void Enqueue (Queue * Q, pengunjung X);
void Dequeue (Queue * Q, pengunjung * X);
void DequeueWahana(pengunjung *X,char W);
void PrintQueue (Queue Q);
void LeaveQueueS(Queue *Q);
void EmptyQueue(Queue *Q);
void Enqueue(Queue *Q, pengunjung P);
void ReduceKesabaran(Queue *Q);
void ReduceTime(Queue *Q,int Time);
boolean isListWahanaEmpty(char L[3]);
void GeneratePengunjung(pengunjung *P, int ID);
void Serve(Queue *Q, Queue *M, char W,Wahana LW, int pmoney);
void LeaveQueueT(Queue *M, Queue *Q, Wahana W);

#endif
