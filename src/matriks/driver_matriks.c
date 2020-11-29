#include "../mesinkata/mesinkar.c"
#include <stdlib.h>
#include <stdio.h>
#include "matriks.c"

int main(){
	
	MATRIKS m;
	BacaMATRIKS(&m, "../file/1.txt");
	
	MATRIKS n;
	CopyMATRIKS(m, &n);
	TulisMATRIKS(n,0,3);
	printf("\n");
	
	Elmt(n, 1, 1) = 'S';
	Elmt(n, 1, 2) = 'O';
	Elmt(n, 1, 3) = 'S';
	printf("%d\n", m.NBrsEff );
	printf("%d\n", m.NKolEff );
	
	TulisMATRIKS(m,0,0);
	printf("\n");
	
	TulisMATRIKS(n,2,3);
	printf("\n%d\n", NBElmt(m));
	MATRIKS m0, m1, m2, m3;
	printf("\n Isi Peta 0\n");
	BacaMATRIKS(&m0, "../file/0.txt");
	TulisMATRIKS(m0,1,1);
	printf("\n Isi Peta 1\n");
	BacaMATRIKS(&m1, "../file/1.txt");
	TulisMATRIKS(m1,1,1);
	printf("\n Isi Peta 2\n");
	BacaMATRIKS(&m2, "../file/2.txt");
	TulisMATRIKS(m2,1,1);
	printf("\n Isi Peta 3\n");
	BacaMATRIKS(&m3, "../file/3.txt");
	TulisMATRIKS(m3,1,1);
	if (IsBujurSangkar(m3)){
		printf("Map 3 adalah matriks bujur sangkar\n");
	} else {
		printf("Map 3 bukan matriks bujur sangkar\n");
	}
	if (IsSimetri(m3)){
		printf("Map 3 adalah matriks simetri\n");
	} else {
		printf("Map 3 bukan matriks simetri\n");
	}
	return 0;
}