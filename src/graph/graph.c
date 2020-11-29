#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/* ----- KONSTRUKTOR ----- */
void BacaGraph(Graph* G, char* sumber){
    /* I.S. G sembarang
       F.S. G terdefinisi dengan membaca file eksternal dan di asssign ke G */
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
    /* Mengembalikan address hasil alokasi infotypePeta X
        Jika alokasi berhasil, maka address tidak Nil, misalnya
        menghasilkan P, maka idPeta(P)=X, Gerbang(P)=Nil,
        dan Graph_Next(P)=Nil. Jika alokasi gagal, mengembalikan Nil.
    */
    adrPeta P = (adrPeta) malloc(sizeof(Peta));
    if (P != Nil) {
        idPeta(P) = X;
        Gerbang(P) = Nil;
        Graph_Next(P) = Nil;
    }
    return P;
} 
adrTerowongan AlokSuccPeta(adrPeta P){
    /* Mengembalikan address hasil alokasi.
    Jika alokasi berhasil, maka address tidak Nil, misalnya
    menghasilkan Pt, maka Graph_Succ(Pt)=P dan Graph_Next(Pt)=Nil. Jika
    alokasi gagal, mengembalikan Nil.
    */
    adrTerowongan T = (adrTerowongan) malloc(sizeof(Terowongan));
    if (T != Nil) {
        Graph_Succ(T) = P;
        Graph_Next(T) = Nil;
    }
    return T;
} 

/* ----- OPERASI GRAF ----- */
boolean isPetaEqual(adrPeta P, infotypePeta X){
    /* Mengembalikan true jika idPeta(P) = X. */
    if (idPeta(P).map == X.map && Absis(idPeta(P).p) == Absis(X.p) && Ordinat(idPeta(P).p) == Ordinat(X.p)) {
        return true;
    }
    else {
        return false;
    }
} 
adrPeta SearchPeta(Graph G, infotypePeta X){
    /* mengembalikan address simpul dengan idPeta=X jika sudah ada pada graph G,
    Nil jika belum */
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
    /* Menambahkan simpul X ke dalam graph, jika alokasi X berhasil.
    I.S. G terdefinisi, X terdefinisi dan belum ada pada G.
    F.S. Jika alokasi berhasil, X menjadi elemen terakhir G, Pn berisi address simpul X. 
            Jika alokasi gagal, G tetap, Pn berisi Nil
    */
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
    /* Menambahkan busur dari prec menuju succ ke dalam G
    I.S. G, prec, succ terdefinisi.
    F.S. Jika belum ada busur (prec,succ) di G, maka tambahkan busur
            (prec,succ) ke G.
    */
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
