#include "../Header/matriks.h"
#include "../Header/mesinkar.h"
#include <stdlib.h>
#include <stdio.h>

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
	return 0;
}