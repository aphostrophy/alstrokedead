#include <stdio.h>
#include <stdlib.h>
#include "../Header/graph.h"

/* ----- KONSTRUKTOR ----- */
void CreateGraph(infotypePeta X, Graph* G){
    First(*G) = Nil;
    adrPeta P;
    InsertNode(G,X,P);
} // membuat graph baru
void InitGraph(Graph* G, char* source){

} // load graph dari ext

/* ----- MANAJEMEN MEMORI ----- */
adrPeta AlokNodeGraph(infotypePeta X){
    adrPeta P = (adrPeta) malloc(sizeof(Peta));
    if (P != Nil) {
        Id(P) = X;
        Trail(P) = Nil;
        Next(P) = Nil;
    }
    return P;
} // mengembalikan hasil alokasi simpul
void DeAlokNodeGraph(adrPeta P){
    free(P);
} // mengembalikan simpul ke sistem
adrTerowongan AlokSuccNode(adrPeta P){
    adrTerowongan T = (adrTerowongan) malloc(sizeof(Terowongan));
    if (T != Nil) {
        Succ(T) = P;
        Next(T) = Nil;
    }
    return T;
} // mengembalikan hasil alokasi succ simpul
void DealokSuccNode(adrTerowongan T){
    free(T);
} // mengembalikan succ simpul ke sistem

/* ----- OPERASI GRAF ----- */
boolean isNodeEqual(adrPeta P, infotypePeta X){
    if (Id(P).room == X.room && Absis(Id(P).p) == Absis(X.p) && Ordinat(Id(P).p) == Ordinat(X.p)) {
        return true;
    }
    else {
        return false;
    }
} // mengembalikan apakah P memiliki Id X
adrPeta SearchNode(Graph G, infotypePeta X){
    adrPeta P = First(G);
    while (P != Nil) {
        if (isNodeEqual(P,X)) {
            return P;
        }
        else {
            P = Next(P);
        }
    }
    return P;
} // mencari X pada G, return nil jika tiada
adrTerowongan SearchEdge(Graph G, infotypePeta prec, infotypePeta succ){
    adrPeta Prec = SearchNode(G,prec);
    adrTerowongan T = Trail(Prec);
    while (Prec != Nil) {
        if (isNodeEqual(Succ(T),succ)) {
            return T;
        }
        else {
            Prec = Next(Prec);
        }
    }
    return T;
} // mencari succ dari prec pada G, return nil jika tiada
void InsertNode(Graph* G, infotypePeta X, adrPeta* Pn){
    *Pn = AlokNodeGraph(X);
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
} // memasang X ke akhir G
void InsertEdge(Graph* G, infotypePeta prec, infotypePeta succ){
    if (SearchEdge(*G,prec,succ) == Nil) {
        adrPeta P1 = SearchNode(*G,prec);
        adrPeta P2 = SearchNode(*G,succ);
        if (P1 == Nil) {
            InsertNode(G,prec,&P1);
        }
        if (P2 == Nil) {
            InsertNode(G,succ,&P2);
        }
        adrTerowongan T = Trail(P1);
        if (T == Nil) {
            T = AlokSuccNode(P2);
        }
        else {
            while (Next(T) != Nil) {
                T = Next(T);
            }
            T = AlokSuccNode(P2);
        }
    }
} // memasang succ ke akhir prec