#include "../boolean.h"
#include "list_linkedlist.h"
#include "../mesinkata/mesinkar.h"
#include "../mesinkata/mesinkata.h"
#include "../bintree/bintree.h"

int main(){
    arrKata arrChild;
    bacaUpgrade("../Saves/Upgrade.txt");
    BuildTree();
    ListNode *link[20] = { 0 };
    // for(int i=0;i<20;i++){
    //     link[20] = NULL;
    // }
    PrintAvailableUpgrade('S', &link[0]);
    printUpgrades(&link[0]);printf("\n");
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
    addUpgrade(&link[0], CKata);
    printUpgrades(&link[0]);printf("\n");
    findChild('S', &link[0], &arrChild);
    printKata(arrChild.TI[0]); printf(" "); printKata(arrChild.TI[1]); printf("\n");
    PrintAvailableUpgrade('S', &link[0]);

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

    addUpgrade(&link[0], CKata);
    findChild('S', &link[0], &arrChild);
    printKata(arrChild.TI[0]); printf(" "); printKata(arrChild.TI[1]); printf("\n");
    PrintAvailableUpgrade('S', &link[0]);
    // removeUpgrade(&link[0]);
    printUpgrades(&link[0]);printf("\n");
    printUpgrades(&link[1]);printf("\n");
    removeUpgrade(&link[0]);
    printUpgrades(&link[0]);printf("\n");
    removeUpgrade(&link[0]);
    printUpgrades(&link[0]);printf("\n");
    return 0;
}