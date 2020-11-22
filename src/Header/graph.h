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
    adrPeta Graph_Next;
} Peta;
typedef struct tTerowongan
{
    adrPeta Graph_Succ;
    adrTerowongan Graph_Next;
} Terowongan;

typedef struct
{
    adrPeta Graph_First;
} Graph;

/* ----- SELEKTOR ----- */
#define Graph_First(G) (G).Graph_First
#define idPeta(Pn) (Pn)->idPeta
#define Gerbang(Pn) (Pn)->Gerbang
#define Graph_Succ(Pn) (Pn)->Graph_Succ
#define Graph_Next(Pn) (Pn)->Graph_Next

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
