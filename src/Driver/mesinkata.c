#include "../Header/boolean.h"
#include "../Header/mesinkar.h"
#include "../Header/mesinkata.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NMax 50
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

void STARTKATAHANDLEBUY(char *namafile)
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

void SalinKata()
{
    int i = 0;
    while ((CC != MARK) && (CC != BLANK) && (i < NMax))
    {
        CKata.TabKata[i] = CC;
		printf("%c",CC);
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