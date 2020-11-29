#include "../boolean.h"
#include "list_linkedlist.h"
#include "../mesinkata/mesinkar.h"
#include "../mesinkata/mesinkata.h"
#include "../bintree/bintree.h"

int main(){
    arrKata arrChild;
    bacaUpgrade("../file/Upgrade.txt");
    BuildTree();
    ListNode *link[20] = { 0 };
    // for(int i=0;i<20;i++){
    //     link[20] = NULL;
    // }
    PrintAvailableUpgrade('T', &link[2]);
    printUpgrades(&link[2]);printf("\n");
    STARTBUY();
    while(!EOL){
        int i=0;
        while(!EOL){
            if(CC=='\n') break;
            CKata.TabKata[i] = CC;
            i++;
            ADV();
        }
        CKata.Length = i;
        if(CC=='\n') break;
        ADV();
    }
    addUpgrade(&link[2], CKata);
    printUpgrades(&link[2]);printf("\n");
    findChild('T', &link[2], &arrChild);
    printKata(arrChild.TI[0]); printf(" "); printKata(arrChild.TI[1]); printf("\n");
    PrintAvailableUpgrade('T', &link[2]);

    STARTBUY();
    while(!EOL){
        int i=0;
        while(!EOL){
            if(CC=='\n') break;
            CKata.TabKata[i] = CC;
            i++;
            ADV();
        }
        CKata.Length = i;
        if(CC=='\n') break;
        ADV();
    }

    addUpgrade(&link[2], CKata);
    findChild('T', &link[2], &arrChild);
    printKata(arrChild.TI[0]); printf(" "); printKata(arrChild.TI[1]); printf("\n");
    PrintAvailableUpgrade('T', &link[2]);
    // removeUpgrade(&link[0]);
    printUpgrades(&link[2]);printf("\n");
    printUpgrades(&link[2]);printf("\n");
    removeUpgrade(&link[2]);
    printUpgrades(&link[2]);printf("\n");
    removeUpgrade(&link[2]);
    printUpgrades(&link[2]);printf("\n");
    return 0;
}