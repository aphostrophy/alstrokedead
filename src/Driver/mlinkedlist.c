#include "../Header/boolean.h"
#include "../Header/list_linkedlist.h"
#include "../Header/mesinkar.h"
#include "../Header/mesinkata.h"

int main(){
    ListNode * link[20] = { 0 };
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
    // removeUpgrade(&link[0]);
    printUpgrades(&link[0]);printf("\n");
    printUpgrades(&link[1]);printf("\n");
    return 0;
}