#include "point.h"
#include "boolean.h"


#ifndef GRAPH_H
#define GRAPH_H

#define Nil NULL

typedef struct {
	int room;
	POINT p;
} infotypePeta;

typedef struct tPeta* adrPeta;
typedef struct tTerowongan* adrTerowongan;
typedef struct tPeta
{
	infotypePeta Id;
    adrTerowongan Trail;
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
#define Id(Pn) (Pn)->Id
#define Trail(Pn) (Pn)->Trail
#define Succ(Pn) (Pn)->Succ
#define NPred(Pn) (Pn)->NPred
#define Next(Pn) (Pn)->Next

/* ----- KONSTRUKTOR ----- */
void CreateGraph(infotypePeta X, Graph* G); // membuat graph baru
void InitGraph(Graph* G, char* source); // load graph dari ext

/* ----- MANAJEMEN MEMORI ----- */
adrPeta AlokNodeGraph(infotypePeta X); // mengembalikan hasil alokasi simpul
void DeAlokNodeGraph(adrPeta P); // mengembalikan simpul ke sistem
adrTerowongan AlokSuccNode(adrPeta P); // mengembalikan hasil alokasi succ simpul
void DealokSuccNode(adrTerowongan T); // mengembalikan succ simpul ke sistem

/* ----- OPERASI GRAF ----- */
boolean isNodeEqual(adrPeta P, infotypePeta X); // mengembalikan apakah P memiliki Id X
adrPeta SearchNode(Graph G, infotypePeta X); // mencari X pada G, return nil jika tiada
adrTerowongan SearchEdge(Graph G, infotypePeta prec, infotypePeta succ); // mencari succ dari prec pada G, return nil jika tiada
void InsertNode(Graph* G, infotypePeta X, adrPeta* Pn); // memasang X ke akhir G
void InsertEdge(Graph* G, infotypePeta prec, infotypePeta succ); // memasang succ ke akhir prec

#endif