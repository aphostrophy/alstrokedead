#include "point.h"
#include "boolean.h"


#ifndef GRAPH_H
#define GRAPH_H

#define Nil NULL

typedef struct {
	POINT p;
    int map;
} infotypePeta;

typedef struct tPeta* adrPeta;
typedef struct tTerowongan* adrTerowongan;
typedef struct tPeta
{
	infotypePeta idPeta;
    adrTerowongan Gerbang;
    adrPeta Next;
} Peta;
typedef struct tTerowongan
{
    adrPeta Succ;
    adrTerowongan Next;
} Terowongan;

typedef struct
{
    adrPeta First;
} Graph;

/* ----- SELEKTOR ----- */
#define First(G) (G).First
#define idPeta(Pn) (Pn)->idPeta
#define Gerbang(Pn) (Pn)->Gerbang
#define Succ(Pn) (Pn)->Succ
#define Next(Pn) (Pn)->Next

/* ----- KONSTRUKTOR ----- */
void BacaGraph(Graph* G, char* sumber); 

/* ----- MANAJEMEN MEMORI ----- */
adrPeta AlokPetaGraph(infotypePeta X); 
void DeAlokPetaGraph(adrPeta P); 
adrTerowongan AlokSuccPeta(adrPeta P); 
void DealokSuccPeta(adrTerowongan T); 

/* ----- OPERASI GRAF ----- */
boolean isPetaEqual(adrPeta P, infotypePeta X); 
adrPeta SearchPeta(Graph G, infotypePeta X); 
adrTerowongan SearchTerowongan(Graph G, infotypePeta prec, infotypePeta succ); 
void InsertPeta(Graph* G, infotypePeta X, adrPeta* Pn); 
void InsertTerowongan(Graph* G, infotypePeta prec, infotypePeta succ); 

#endif
