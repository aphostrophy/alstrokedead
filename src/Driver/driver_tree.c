#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "bintree.c"
#include "mesinkata.c"
#include "mesinkar.c"

int main() {
    bacaUpgrade("../Saves/Upgrade.txt");
    BuildTree();
    // for(int i = 0; i < 8; i++) {
    //     PrintTree(listUpgrade[i], 2);
    // }
    // printf("\n");

    // char id;
    Kata upgrade;
    // scanf("%c", &id);

    int kata_ke = 1;
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
			upgrade = CKata;
		kata_ke++;
		IgnoreBlank();
        }
    }

    PrintUpgradeWahana('T');
    PrintAvailableUpgrade('T');
    moveUpgrade('T', upgrade);
    PrintUpgradeWahana('T'); printf("\n");
    
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
			upgrade = CKata;
            kata_ke++;
            IgnoreBlank();
        }
    }

    moveUpgrade('T', upgrade);
    PrintUpgradeWahana('T');
    return 0;
}