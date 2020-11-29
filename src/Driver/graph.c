#include <stdio.h>
#include <stdlib.h>
#include "../Header/graph.h"

/* ----- KONSTRUKTOR ----- */
void BacaGraph(Graph* G, char* sumber){
    FILE *file_graph = fopen(sumber, "r");
    Graph_First(*G) = Nil;
    int tampunganPrec[3];
    int tampunganSucc[3];
    int X = fscanf(file_graph,"%d",&tampunganPrec[0]);
    infotypePeta Prec1, Succ1;
    adrPeta Prec; adrPeta Succ;
    while (X == 1) {
        for (int i = 1; i < 3; i++) {
            fscanf(file_graph,"%d",&tampunganPrec[i]);
        }
        for (int i = 3; i < 6; i++) {
            fscanf(file_graph,"%d",&tampunganSucc[i-3]);
        }
        Prec1.map = tampunganPrec[0];
        Absis(Prec1.p) = tampunganPrec[1];
        Ordinat(Prec1.p) = tampunganPrec[2];
        if (Graph_First(*G) == Nil) {
            Prec = AlokPetaGraph(Prec1);
            Graph_First(*G) = Prec;
        }
        else {
            InsertPeta(G,Prec1,&Prec);
        }
        Succ1.map = tampunganSucc[0];
        Absis(Succ1.p) = tampunganSucc[1];
        Ordinat(Succ1.p) = tampunganSucc[2];
        InsertPeta(G,Succ1,&Succ);
        InsertTerowongan(G,Prec,Succ);
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
    boolean found = false;
    while (P != Nil && !found) {
        if (isPetaEqual(P,X)) {
            found = true;
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
    if (NewPeta != Nil) {
        adrPeta P = Graph_First(*G);
        while (Graph_Next(P) != Nil) {
            P = Graph_Next(P);
        }
        Graph_Next(P) = *Pn;
    }
} 
void InsertTerowongan(Graph* G, adrPeta prec, adrPeta succ){
    adrTerowongan T = Gerbang(prec);
    if (T == Nil) {
        Gerbang(prec) = AlokSuccPeta(succ);
    }
    else {
        while (Graph_Next(T) != Nil) {
            T = Graph_Next(T);
        }
        Graph_Next(Gerbang(prec)) = AlokSuccPeta(succ);
    }
} 
