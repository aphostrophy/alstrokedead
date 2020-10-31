/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include <stdio.h>
#include "../Header/mesinkar.h"
#include "string.h"

char CC;
boolean EOP;
boolean EOL;

static FILE * pita;
static int retval;

void START(char *namafile) {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
  Karakter pertama yang ada pada pita posisinya adalah pada jendela.
  I.S. : sembarang
  F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
	  Jika CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	pita = fopen(namafile,"r");
	ADV();
}

void ADV() {
/* Pita dimajukan satu karakter. 
  I.S. : Karakter pada jendela = CC, CC != MARK
  F.S. : CC adalah karakter berikutnya dari CC yang lama, CC mungkin = MARK.
		Jika  CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	retval = fscanf(pita,"%c",&CC);
	// CC = fgetc(pita);
	// if (CC == '\r') { CC = fgetc(pita); }
	EOP = (CC == MARK);
	EOL = (CC == NEWLINE);
	if (EOP) {
		fclose(pita);
 	}
}
