#include <stdio.h>
#include <stdlib.h>
#include "-I../Header/bintree.h"

#define max(a, b) a>b?a:b
#define min(a, b) a<b?a:b
#define abs(a) a<0?-a:a 
#define selisih(a, b) abs(a-b)
#define swap(a,b) {infotype tmp; tmp = b; b = a; a = tmp;}

#define intput(a)     scanf("%d", &a)
#define intput2(a,b)  scanf("%d %d", &a, &b)
#define charput(a)    scanf(" %c", &a)
#define print(a)      printf("%d", a)
#define prints(a)     printf("%d ", a)
#define println(a)    printf("%d\n", a)
#define printc(a)     printf("%c", a)
#define printcs(a)    printf("%c ", a)
#define printcln(a)   printf("%c\n", a)
#define ENDL          printf("\n")

#define fori(i,n)     for(int i = 0; i < n; i++)
#define forii(i,s,e)  for(int i = s; i < e; i++)

/* *** Konstruktor *** */
BinTree Tree(infotype Akar, BinTree L, BinTree R)
/* Menghasilkan sebuah pohon biner dari A, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */
{
  BinTree T = (BinTree) malloc(sizeof(BinTree));
  if(T != Nil){
    Akar(T) = Akar;
    Left(T) = L;
    Right(T) = R;
  }
  return T;
}

void MakeTree(infotype Akar, BinTree L, BinTree R, BinTree *P)
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R
   jika alokasi berhasil. P = Nil jika alokasi gagal. */
{
  *P = Tree(Akar, L, R);
}

BinTree BuildBalanceTree(int n)
/* Menghasilkan sebuah balanced tree dengan n node, nilai setiap node dibaca */
/* Jika n == 0, kembalikan Nil.
   Mula-mula, baca nilai dari root dari stdin, lalu bangun pohon biner di kiri
   (dengan membaca dari stdin) lalu di tree kanan (dengan membaca dari stdin). 
   misal dari stdin: 1, 2, 3, 4, 5, 6, 7, hasilnya:
       1
     2   5
    3 4 6 7
  */
{
  if(n == 0) return Nil;
  int Akar; intput(Akar);
  BinTree Left = BuildBalanceTree(n/2);
  BinTree Right = BuildBalanceTree(n - n/2 - 1);
  return Tree(Akar, Left, Right);
}

/* Manajemen Memory */
addrNode AlokNode(infotype X)
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P,
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
  return Tree(X, Nil, Nil);
}

void DealokNode(addrNode P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */
{
  free(P);
}

/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty(BinTree P)
/* Mengirimkan true jika P adalah pohon biner kosong */
{
  return P == Nil;
}

boolean IsTreeOneElmt(BinTree P)
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
{
  if (IsTreeEmpty(P)) return false;
  return IsTreeEmpty(Left(P)) && IsTreeEmpty(Right(P));
}

boolean IsUnerLeft(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
{
  if (IsTreeEmpty(P)) return false;
  if (!IsTreeEmpty(Right(P))) return false;
  return !IsTreeEmpty(Left(P));
}

boolean IsUnerRight(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
{
  if (IsTreeEmpty(P)) return false;
  if (!IsTreeEmpty(Left(P))) return false;
  return !IsTreeEmpty(Right(P));
}

boolean IsBiner(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/
{
  if (IsTreeEmpty(P)) return false;
  return ((!IsTreeEmpty(Left(P))) && (!IsTreeEmpty(Right(P))));
}

/* *** Traversal *** */
void PrintPreorder(BinTree P)
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara preorder: akar, pohon kiri, dan pohon kanan.
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup ().
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh:
   (A()()) adalah pohon dengan 1 elemen dengan akar A
   (A(B()())(C()())) adalah pohon dengan akar A dan subpohon kiri (B()()) dan subpohon kanan (C()()) */
{
  printc('(');
  if(!IsTreeEmpty(P)){
    print(Akar(P));
    PrintPreorder(Left(P));
    PrintPreorder(Right(P));
  }
  printc(')');
}
void PrintInorder(BinTree P)
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara inorder: pohon kiri, akar, dan pohon kanan.
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup ().
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh:
   (()A()) adalah pohon dengan 1 elemen dengan akar A
   ((()B())A(()C())) adalah pohon dengan akar A dan subpohon kiri (()B()) dan subpohon kanan (()C()) */
{
  printc('(');
  if(!IsTreeEmpty(P)){
    PrintInorder(Left(P));
    print(Akar(P));
    PrintInorder(Right(P));
  }
  printc(')');
}

void PrintPostorder(BinTree P)
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara postorder: pohon kiri, pohon kanan, dan akar.
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup ().
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh:
   (()()A) adalah pohon dengan 1 elemen dengan akar A
   ((()()B)(()()C)A) adalah pohon dengan akar A dan subpohon kiri (()()B) dan subpohon kanan (()()C) */
{
  printc('(');
  if(!IsTreeEmpty(P)){
    PrintPostorder(Left(P));
    PrintPostorder(Right(P));
    print(Akar(P));
  }
  printc(')');
}

void PrintTreeUtil(BinTree P, int h, int level){
  if(IsTreeEmpty(P)) return;
  print(Akar(P)); ENDL;
  if(!IsTreeEmpty(Left(P))){
    fori(i, h*level) printc(' ');
    PrintTreeUtil(Left(P), h, level+1);
  }
  if(!IsTreeEmpty(Right(P))){
    fori(i, h*level) printc(' ');
    PrintTreeUtil(Right(P), h, level+1);
  }
}

void PrintTree(BinTree P, int h)
/* I.S. P terdefinisi, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
/* Contoh, jika h = 2: 
1) Pohon preorder: (A()()) akan ditulis sbb:
A
2) Pohon preorder: (A(B()())(C()())) akan ditulis sbb:
A
  B
  C
3) Pohon preorder: (A(B(D()())())(C()(E()()))) akan ditulis sbb:
A
  B
    D
  C
    E
*/
{
  PrintTreeUtil(P, h, 1);
}

/* *** Searching *** */
boolean SearchTree(BinTree P, infotype X)
/* Mengirimkan true jika ada node dari P yang bernilai X */
{
  if(IsTreeEmpty(P)) return false;
  if(Akar(P) == X) return true;
  return SearchTree(Left(P), X) || SearchTree(Right(P), X);
}

/* *** Fungsi-Fungsi Lain *** */
int NbElmt(BinTree P)
/* Mengirimkan banyaknya elemen (node) pohon biner P */
{
  if(IsTreeEmpty(P)) return 0;
  return 1 + NbElmt(Left(P)) + NbElmt(Right(P));
}

int NbDaun(BinTree P)
/* Mengirimkan banyaknya daun (node) pohon biner P */
/* Prekondisi: P tidak kosong */
{
  if(IsTreeEmpty(P)) return 0;
  if(IsTreeOneElmt(P)) return 1;
  if(IsUnerRight(P)) return NbDaun(Right(P));
  if(IsUnerLeft(P)) return NbDaun(Left(P));
  return NbDaun(Left(P)) + NbDaun(Right(P));
}

boolean IsSkewLeft(BinTree P)
/* Mengirimkan true jika P adalah pohon condong kiri */
/* Pohon kosong adalah pohon condong kiri */
{
  if(IsTreeEmpty(P)) return true;
  if(IsTreeOneElmt(P)) return true;
  if(!IsUnerLeft(P)) return false;
  return IsSkewLeft(Left(P));
}

boolean IsSkewRight(BinTree P)
/* Mengirimkan true jika P adalah pohon condong kanan */
/* Pohon kosong adalah pohon condong kanan */
{
  if(IsTreeEmpty(P)) return true;
  if(IsTreeOneElmt(P)) return true;
  if(!IsUnerRight(P)) return false;
  return IsSkewRight(Right(P));
}

int Level(BinTree P, infotype X)
/* Mengirimkan level dari node X yang merupakan salah satu simpul dari pohon biner P.
   Akar(P) level-nya adalah 1. Pohon P tidak kosong. */
{
  if(IsTreeEmpty(P)) return -1;
  if(Akar(P) == X) return 1;
  int Kiri = Level(Left(P), X);
  int Kanan = Level(Right(P), X);
  if(Kiri == -1 && Kanan == -1) return -1;
  if(Kiri == -1) return 1 + Kanan;
  if(Kanan == -1) return 1 + Kiri;
  return 1+min(Kiri, Kanan);
}

int Tinggi(BinTree P)
/* Pohon Biner mungkin kosong. Tinggi pohon kosong = 0.
   Mengirim "height" yaitu tinggi dari pohon */
{
  if(IsTreeEmpty(P)) return 0;
  return max(1+Tinggi(Left(P)), 1+Tinggi(Right(P)));
}

/* *** Operasi lain *** */
void AddDaunTerkiri(BinTree *P, infotype X)
/* I.S. P boleh kosong */
/* F.S. P bertambah simpulnya, dengan X sebagai simpul daun terkiri */
{
  if(IsTreeEmpty(*P)) *P = AlokNode(X);
  else AddDaunTerkiri(&Left(*P), X);
}

boolean AddDaunUtil(BinTree *P, infotype X, infotype Y, boolean Kiri){
  if(IsTreeEmpty(*P)) return false;
  if(IsTreeOneElmt(*P)){
    if(Akar(*P) == X){
      if(Kiri) Left(*P) = AlokNode(Y);
      else Right(*P) = AlokNode(Y);
      return true;  
    }
    return false;
  }
  if (AddDaunUtil(&Left(*P), X, Y, Kiri)) return true;
  return AddDaunUtil(&Right(*P), X, Y, Kiri);
}

void AddDaun(BinTree *P, infotype X, infotype Y, boolean Kiri)
/* I.S. P tidak kosong, X adalah salah satu daun Pohon Biner P */
/* F.S. P bertambah simpulnya, dengan Y sebagai anak kiri X (jika Kiri = true), atau
        sebagai anak Kanan X (jika Kiri = false) */
/*		Jika ada > 1 daun bernilai X, diambil daun yang paling kiri */
{
  if(!AddDaunUtil(P, X, Y, Kiri)) *P = AlokNode(Y);
}

void DelDaunTerkiri(BinTree *P, infotype *X)
/* I.S. P tidak kosong */
/* F.S. P dihapus daun terkirinya, dan didealokasi, dengan X adalah info yang semula
        disimpan pada daun terkiri yang dihapus */
{
  if(IsTreeEmpty(*P)) return;
  if(IsTreeOneElmt(*P)){
    *X = Akar(*P);
    *P = Nil;
    return;
  }
  if(IsUnerRight(*P)) DelDaunTerkiri(&Right(*P), X);
  else DelDaunTerkiri(&Left(*P), X);
}

void DelDaun(BinTree *P, infotype X)
/* I.S. P tidak kosong, minimum ada 1 daun bernilai X. */
/* F.S. Semua daun bernilai X dihapus dari P. */
{
  if(IsTreeEmpty(*P)) return;
  if(IsTreeOneElmt(*P)) {
    if(Akar(*P) == X) *P = Nil;
    return;
  }
  DelDaun(&Left(*P), X);
  DelDaun(&Right(*P), X);
}

List MakeListDaun(BinTree P)
/* Jika P adalah pohon kosong, maka menghasilkan list kosong. */
/* Jika P bukan pohon kosong: menghasilkan list yang elemennya adalah semua daun pohon P,
   jika semua alokasi list berhasil.
   Daun terkiri menjadi elemen pertama dari list, diikuti elemen kanannya, dst.
   Menghasilkan list kosong jika ada alokasi yang gagal. */
{
  if(IsTreeEmpty(P)) return Nil;
  if(IsTreeOneElmt(P)) return Alokasi(Akar(P));
  return Concat(MakeListDaun(Left(P)), MakeListDaun(Right(P)));
}

List MakeListPreorder(BinTree P)
/* Jika P adalah pohon kosong, maka menghasilkan list kosong. */
/* Jika P bukan pohon kosong: menghasilkan list yang elemennya adalah semua elemen pohon P
   dengan urutan preorder, jika semua alokasi berhasil.
   Menghasilkan list kosong jika ada alokasi yang gagal. */
{
  if(IsTreeEmpty(P)) return Nil;
  List E = Alokasi(Akar(P));
  if(E != Nil){
    Next(E) = MakeListPreorder(Left(P));
    E = Concat(E, MakeListPreorder(Right(P)));
  }
  return E;
}

List MakeListLevel(BinTree P, int N)
/* Jika P adalah pohon kosong, maka menghasilkan list kosong. */
/* Jika P bukan pohon kosong: menghasilkan list yang elemennya adalah semua elemen pohon P
   yang levelnya=N, jika semua alokasi berhasil.
   Elemen terkiri menjadi elemen pertama dari list, diikuti elemen kanannya, dst.
   Menghasilkan list kosong jika ada alokasi yang gagal. */
{
  if(IsTreeEmpty(P)) return Nil;
  if(N == 1) return Alokasi(Akar(P));
  List Left = MakeListLevel(Left(P), N-1);
  List Right = MakeListLevel(Right(P), N-1);
  if(Left == Nil) return Right;
  if(Right == Nil) return Left;
  return Concat(Left, Right);
}

/* *** Binary  Search  Tree  *** */
boolean BSearch(BinTree P, infotype X)
/* Mengirimkan true jika ada node dari P yang bernilai X */
{
  if(IsTreeEmpty(P)) return false;
  if(Akar(P) == X) return true;
  if(Akar(P) < X) return BSearch(Right(P), X);
  return BSearch(Left(P), X);
}

void InsSearch(BinTree *P, infotype X)
/* Menghasilkan sebuah pohon Binary Search Tree P dengan tambahan simpul X. Belum ada simpul P yang bernilai X. */
{
  if(IsTreeEmpty(*P))  *P = AlokNode(X);
  else {
    if(X >= Akar(*P)) InsSearch(&Right(*P), X);
    else InsSearch(&Left(*P), X);
  }
}

void DelNode(BinTree *P){
  if(Right(*P) != Nil) DelNode(&Right(*P));
  else *P = Left(*P);
}

void DelBtree(BinTree *P, infotype X)
/* I.S. Pohon P tidak  kosong */
/* F.S. Nilai X yang dihapus pasti ada */
/* Sebuah node dengan nilai X dihapus */
{
  if(X < Akar(*P)){
    DelBtree(&Left(*P), X);
  } else if (X > Akar(*P)){
    DelBtree(&Right(*P), X);
  } else {
    if(IsTreeOneElmt(*P)) *P = Nil;
    if(IsUnerLeft(*P)) *P = Left(*P);
    if(IsUnerRight(*P)) *P = Right(*P);
    if(IsBiner(*P)) DelNode(&Left(*P));
  }
}