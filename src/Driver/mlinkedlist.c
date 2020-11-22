#include "../Header/boolean.h"
#include "../Header/list_linkedlist.h"
#include "../Header/mesinkar.h"
#include "../Header/mesinkata.h"
#include "../Header/bintree.h"

int main(){
    bacaUpgrade("../Saves/Upgrade.txt");
    BuildTree();
    ListNode * link[20] = { 0 };
    // for(int i=0;i<20;i++){
    //     link[20] = NULL;
    // }
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
    printf("Oke\n");
    addUpgrade(&link[0], CKata);
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
    printf("Oke\n");
    addUpgrade(&link[0],CKata);
    PrintAvailableUpgrade('S', &link[0]);
    // removeUpgrade(&link[0]);
    printUpgrades(&link[0]);printf("\n");
    printUpgrades(&link[1]);printf("\n");
    return 0;
}