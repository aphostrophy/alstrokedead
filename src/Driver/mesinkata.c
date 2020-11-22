#include "../Header/boolean.h"
#include "../Header/mesinkar.h"
#include "../Header/mesinkata.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NMax 100
#define BLANK ' '

boolean EndKata = false;
Kata CKata;

void IgnoreBlank()
{
    while (CC == BLANK)
    {
        ADV();
    }
}
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTKATA(char *namafile)
{
    START(namafile);
    IgnoreBlank();
    if (CC == MARK)
    {
        EndKata = true;
    }
    else /* CC != MARK */
    {
        EndKata = false;
        SalinKata();
    }
}
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void STARTKATAHANDLEBUY()
{
    STARTBUY();
    IgnoreBlank();
    if (CC == NEWLINE)
    {
        printf("Newline terbaca");
        EndKata = true;
    }
    else /* CC != MARK */
    {
        EndKata = false;
        SalinKata();
    }
}

void ADVKATA()
{
    IgnoreBlank();
    if (CC == MARK)
    {
        EndKata = true;
    }
    else /* CC != MARK */
    {
        SalinKata();
        IgnoreBlank();
    }
}
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.          
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void ADVBUYKATA()
{
    IgnoreBlank();
    if (CC == NEWLINE)
    {
        EndKata = true;
    }
    else /* CC != MARK */
    {
        SalinKata();
        IgnoreBlank();
    }
}

void SalinKata()
{
    int i = 0;
    while ((CC != MARK) && (CC != BLANK) && (i < NMax))
    {
        CKata.TabKata[i] = CC;
        ADV();
        i++;
    } /* CC = MARK or CC = BLANK */
    CKata.Length = i;
}
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

void AKUISISI_BUY(char *action, char* method, int* jumlah, char barang )
{
	char action2[100];
	strcpy(action2,action);
	char * token = strtok(action2, " ");
	strcpy(method,token);
	printf("HH");
	printf("%s",method);
	token = strtok(NULL, " ");
	*jumlah = atoi(token);
	token = strtok(NULL, " ");
	barang = token[0];

}

boolean IsKataSama (Kata K1, Kata K2){
   int i=0;
   if(K1.Length!=K2.Length){
      return false;
   } else{
      while(i<K1.Length){
         if(tolower(K1.TabKata[i])!=tolower(K2.TabKata[i])){
             return false;
         }
         i++;
      }
      return true;
   }
}

Kata KataConcat(Kata K1, Kata K2){
    // for(int i=K1.Length;i<K1.Length+K2.Length;i++){
    //     K1.TabKata[i] = K2.TabKata[i-K1.Length];
    // }
    strncat(K1.TabKata,K2.TabKata,K2.Length);
    K1.Length = K1.Length + K2.Length;
    return K1;
}

Kata copyKata(Kata in) {
    Kata out;
    // printf("%s %d\n", CKata.TabKata, CKata.Length);
    out.Length = in.Length;
    for(int i = 0; i < in.Length; i++) {
        out.TabKata[i] = in.TabKata[i];
    }
    return out;
}

void printKata(Kata in) {
    for(int i = 0; i < in.Length; i++) {
        printf("%c", in.TabKata[i]);
    }
}