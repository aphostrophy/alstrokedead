#include "../point/point.h"
#include "../boolean.h"


#ifndef GRAPH_H
#define GRAPH_H

#define Nil NULL

/*** Definisi Elemen ***/
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
/* I.S. G sembarang
   F.S. G terdefinisi dengan membaca file eksternal dan di asssign ke G */

/* ----- MANAJEMEN MEMORI ----- */
adrPeta AlokPetaGraph(infotypePeta X); 
/* Mengembalikan address hasil alokasi infotypePeta X
   Jika alokasi berhasil, maka address tidak Nil, misalnya
   menghasilkan P, maka idPeta(P)=X, Gerbang(P)=Nil,
   dan Graph_Next(P)=Nil. Jika alokasi gagal, mengembalikan Nil.
*/
adrTerowongan AlokSuccPeta(adrPeta P); 
/* Mengembalikan address hasil alokasi.
   Jika alokasi berhasil, maka address tidak Nil, misalnya
   menghasilkan Pt, maka Graph_Succ(Pt)=P dan Graph_Next(Pt)=Nil. Jika
   alokasi gagal, mengembalikan Nil.
*/

/* ----- OPERASI GRAF ----- */
boolean isPetaEqual(adrPeta P, infotypePeta X); 
/* Mengembalikan true jika idPeta(P) = X.
*/
adrPeta SearchPeta(Graph G, infotypePeta X); 
/* mengembalikan address simpul dengan idPeta=X jika sudah ada pada graph G,
  Nil jika belum
*/
void InsertPeta(Graph* G, infotypePeta X, adrPeta* Pn); 
/* Menambahkan simpul X ke dalam graph, jika alokasi X berhasil.
   I.S. G terdefinisi, X terdefinisi dan belum ada pada G.
   F.S. Jika alokasi berhasil, X menjadi elemen terakhir G, Pn berisi address simpul X. 
        Jika alokasi gagal, G tetap, Pn berisi Nil
*/
void InsertTerowongan(Graph* G, adrPeta prec, adrPeta succ); 
/* Menambahkan busur dari prec menuju succ ke dalam G
   I.S. G, prec, succ terdefinisi.
   F.S. Jika belum ada busur (prec,succ) di G, maka tambahkan busur
        (prec,succ) ke G.
*/

#endif
