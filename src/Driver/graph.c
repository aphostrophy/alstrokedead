#include <stdio.h>
#include <stdlib.h>
#include "../Header/graph.h"

/* ----- KONSTRUKTOR ----- */
void BacaGraph(Graph* G, char* sumber){
    FILE *file_graph = fopen(sumber, "r");
    First(*G) = Nil;
    int tampungan[6];
    int X = fscanf(file_graph,"%d",&tampungan[0]);
    infotypePeta PrecAwal, SuccAwal;
    while (X == 1) {
        for (int i = 1; i < 6; i++) {
            fscanf(file_graph,"%d",&tampungan[i]);
        }
        PrecAwal.map = tampungan[0];
        Absis(PrecAwal.p) = tampungan[1];
        Ordinat(PrecAwal.p) = tampungan[2];
        SuccAwal.map = tampungan[3];
        Absis(SuccAwal.p) = tampungan[4];
        Ordinat(SuccAwal.p) = tampungan[5];
        InsertTerowongan(G,PrecAwal,SuccAwal);
        X = fscanf(file_graph,"%d",&tampungan[0]);
    }
    fclose(file_graph);
} 

/* ----- MANAJEMEN MEMORI ----- */
adrPeta AlokPetaGraph(infotypePeta X){
    adrPeta P = (adrPeta) malloc(sizeof(Peta));
    if (P != Nil) {
        idPeta(P) = X;
        Gerbang(P) = Nil;
        Next(P) = Nil;
    }
    return P;
} 
void DeAlokPetaGraph(adrPeta P){
    free(P);
} 
adrTerowongan AlokSuccPeta(adrPeta P){
    adrTerowongan T = (adrTerowongan) malloc(sizeof(Terowongan));
    if (T != Nil) {
        Succ(T) = P;
        Next(T) = Nil;
    }
    return T;
} 
void DealokSuccPeta(adrTerowongan T){
    free(T);
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
    adrPeta P = First(G);
    while (P != Nil) {
        if (isPetaEqual(P,X)) {
            return P;
        }
        else {
            P = Next(P);
        }
    }
    return P;
} 
adrTerowongan SearchTerowongan(Graph G, infotypePeta prec, infotypePeta succ){
    adrPeta Prec = SearchPeta(G,prec);
    adrTerowongan T = Nil;
    while (Prec != Nil) {
        T = Gerbang(Prec);
        if (isPetaEqual(Succ(T),succ)) {
            return T;
        }
        else {
            Prec = Next(Prec);
        }
    }
    return T;
} 
void InsertPeta(Graph* G, infotypePeta X, adrPeta* Pn){
    *Pn = AlokPetaGraph(X);
    adrPeta P = First(*G);
    if (P != Nil) {
        while (Next(P) != Nil) {
            P = Next(P);
        }
        Next(P) = *Pn;
    }
    else {
        First(*G) = *Pn;
    }
} 
void InsertTerowongan(Graph* G, infotypePeta prec, infotypePeta succ){
    if (SearchTerowongan(*G,prec,succ) == Nil) {
        adrPeta P1 = SearchPeta(*G,prec);
        adrPeta P2 = SearchPeta(*G,succ);
        if (P1 == Nil) {
            InsertPeta(G,prec,&P1);
        }
        if (P2 == Nil) {
            InsertPeta(G,succ,&P2);
        }
        adrTerowongan T = Gerbang(P1);
        if (T == Nil) {
            Gerbang(P1) = AlokSuccPeta(P2);
        }
        else {
            while (Next(T) != Nil) {
                T = Next(T);
            }
            Next(Gerbang(P1)) = AlokSuccPeta(P2);
        }
    }
} 
