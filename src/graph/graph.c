#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/* ----- KONSTRUKTOR ----- */
void BacaGraph(Graph* G, char* sumber){
    FILE *file_graph = fopen(sumber, "r");
    Graph_First(*G) = Nil;
    int tampunganPrec[3];
    int tampunganSucc[3];
    int X = fscanf(file_graph,"%d",&tampunganPrec[0]);
    infotypePeta PrecAwal, SuccAwal;
    while (X == 1) {
        for (int i = 1; i < 3; i++) {
            fscanf(file_graph,"%d",&tampunganPrec[i]);
        }
        for (int i = 3; i < 6; i++) {
            fscanf(file_graph,"%d",&tampunganSucc[i-3]);
        }
        PrecAwal.map = tampunganPrec[0];
        Absis(PrecAwal.p) = tampunganPrec[1];
        Ordinat(PrecAwal.p) = tampunganPrec[2];
        SuccAwal.map = tampunganSucc[0];
        Absis(SuccAwal.p) = tampunganSucc[1];
        Ordinat(SuccAwal.p) = tampunganSucc[2];
        InsertTerowongan(G,PrecAwal,SuccAwal);
        X = fscanf(file_graph,"%d",&tampunganPrec[0]);
    }
    fclose(file_graph);
} 

/* ----- MANAJEMEN MEMORI ----- */
adrPeta AlokPetaGraph(infotypePeta X){
    adrPeta P = (adrPeta) malloc(sizeof(Peta));
    if (P != Nil) {
        idPeta(P) = X;
        Gerbang(P) = Nil;
        Graph_Next(P) = Nil;
    }
    return P;
} 
adrTerowongan AlokSuccPeta(adrPeta P){
    adrTerowongan T = (adrTerowongan) malloc(sizeof(Terowongan));
    if (T != Nil) {
        Graph_Succ(T) = P;
        Graph_Next(T) = Nil;
    }
    return T;
} 

/* ----- OPERASI GRAF ----- */
boolean isPetaEqual(adrPeta P, infotypePeta X){
    if (idPeta(P).map == X.map && Absis(idPeta(P).p) == Absis(X.p) && Ordinat(idPeta(P).p) == Ordinat(X.p)) {
        return true;
    }
    else {
        return false;
    }
} 
adrPeta SearchPeta(Graph G, infotypePeta X){
    adrPeta P = Graph_First(G);
    while (P != Nil) {
        if (isPetaEqual(P,X)) {
            return P;
        }
        else {
            P = Graph_Next(P);
        }
    }
    return P;
} 
void InsertPeta(Graph* G, infotypePeta X, adrPeta* Pn){
    adrPeta NewPeta = AlokPetaGraph(X);
    *Pn = NewPeta;
    adrPeta P = Graph_First(*G);
    if (P != Nil && NewPeta != Nil) {
        while (Graph_Next(P) != Nil) {
            P = Graph_Next(P);
        }
        Graph_Next(P) = *Pn;
    }
    else {
        Graph_First(*G) = *Pn;
    }
} 
void InsertTerowongan(Graph* G, infotypePeta prec, infotypePeta Graph_Succ){
    adrPeta P1 = SearchPeta(*G,prec);
    adrPeta P2 = SearchPeta(*G,Graph_Succ);
    if (P1 == Nil) {
        InsertPeta(G,prec,&P1);
    }
    if (P2 == Nil) {
        InsertPeta(G,Graph_Succ,&P2);
    }
    adrTerowongan T = Gerbang(P1);
    if (T == Nil) {
        Gerbang(P1) = AlokSuccPeta(P2);
    }
    else {
        while (Graph_Next(T) != Nil) {
            T = Graph_Next(T);
        }
        Graph_Next(Gerbang(P1)) = AlokSuccPeta(P2);
    }
} 
