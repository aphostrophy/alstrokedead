#include "mesinkata.h"
#include "mesinkar.h"
#include <stdio.h>


int main(){
	Kata Action, StackEl, Barang, Jumlah;
	Kata SPASI; SPASI.TabKata[0] = ' ' ; SPASI.Length = 1;
   	int kata_ke = 1;
    STARTBUY();
    while(!EOP && !EOL){
		int i = 0;
		CKata.Length=0;
        while(CC!=BLANK){
			if(CC=='\r'){
				CC ='\n';
			}
			if(CC=='\n'){
				break;
			}
			CKata.TabKata[i] = CC;
			i++;
			CKata.Length=i;
			// printf("%c",CC);
			ADV();
		}
		if(kata_ke==1){
			Action = CKata;
		} else if(kata_ke==2){
			Jumlah = CKata;
		} else if(kata_ke==3){
			Barang = CKata;
		}
		if(CC=='\n'){
			break;
		}
		kata_ke++;
		IgnoreBlank();
    }
    StackEl = KataConcat(StackEl,Action);StackEl = KataConcat(StackEl,SPASI);StackEl = KataConcat(StackEl,Jumlah);StackEl = KataConcat(StackEl,SPASI);StackEl = KataConcat(StackEl,Barang);
    printKata(StackEl);printf("\n");

    Kata hasil;
    int in;
    scanf("%d",&in);
    hasil = IntToKata(in);
    printKata(hasil);printf("\n");
    hasil.TabKata[0] = '2';hasil.Length=1;
    in = KataToInt(hasil);
    printf("%d",in);printf("\n");
}