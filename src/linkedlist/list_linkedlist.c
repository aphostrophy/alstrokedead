#include <stdio.h>
#include <stdlib.h>
#include "list_linkedlist.h"
#include "../mesinkata/mesinkar.h"


int addUpgrade( ListNode **head, Kata data )
/*
Menambahkan elemen terakhir berupa Kata ke salah satu linked list yang tersimpan dalam list of linked list
    I.S : list of linked list terdefinisi dan diakhiri null
    F.S : menambah elemen terakhir pada salah satu linked list yang ada di dalam list 
*/
{
    ListNode *node = malloc( sizeof( ListNode ) );
    int success = node != NULL;
    if(success){
        node->data = data;
        node->next = NULL;
        ListNode *current=*head;
        if(current==NULL){
            *head = node;
        } else{
            // Traversing hingga mencapai ujung dan elemen ujung diisi node baru
            while(current->next!=NULL){
                current=current->next;
            }
            current->next = node;
        }
    }
    return success;
}

void removeUpgrade( ListNode **head )
/* 
Membuang elemen terakhir yang terdefinisi dari salah satu linked list yang tersimpan dalam list of linked list
    I.S : list of linked list terdefinisi dan diakhiri null
    F.S : salah satu elemen terakhir dari linked list yang ada di dalam list akan terbuang jika tidak empty, jika empty tidak terjadi apa-apa
*/
{
    ListNode *current=*head , *prev;
        if(current==NULL){ //Kasus list kosong
            printf("There is nothing to remove from upgrades");
        } else{
            // Traversing sampai ujung lalu buang elemen terakhir
            prev = current;
            while(current->next!=NULL){
                prev = current;
                current=current->next;
            }
            if(prev==current){
                prev->next = NULL; // Kasus list one elmt, elmt pertama dijadikan NULL
                *head = NULL;
            }else{
                prev->next = NULL;
                free(current);
            }

        }
}

void printUpgrades( ListNode **head )
/*
Mencetak isi dari salah satu linkedlist
    I.S : list of linked list terdefinisi dan diakhiri null
    F.S : mencetak semua Kata yang tersimpan dalam node-node linkedlist hingga node = NULL
*/
{
    for( ListNode *current =*head; current != NULL; current = current->next ) //Mark pakai NULL
    {
        printKata(current->data);printf(" ");
    }
}

int upgradeLength(ListNode **head)
/*
Mereturn semua Kata pada node-node linked list 
    I.S : list of linked list terdefinisi dan diakhiri null
    F.S : Semua Kata pada nodes dikonkat menjadi 1 kata yang panjang, intinya sama seperti printUpgrade tapi direturn
*/
{
    int len=0;
    for( ListNode *current =*head; current != NULL; current = current->next ) //Mark pakai NULL
    {
        len++;
    }
    return len;
}

Kata saveUpgrade( ListNode **head)
/*
    I.S : list of linked list terdefinisi dan diakhiri null
    F.S : mereturn panjang dari linked list
*/
{
    Kata allUpgrades;allUpgrades.TabKata[0]='a';allUpgrades.Length=0;
    Kata SENTINEL; SENTINEL.TabKata[0]='X';SENTINEL.Length = 1;
    Kata SPASI; SPASI.TabKata[0] = ' ' ; SPASI.Length = 1;
    // Semua Kata Nodes diconcat ke allUpgrades dan diakhiri SENTINEL berupa Kata panjang 1 X
    for( ListNode *current=*head; current !=NULL; current= current->next){
        allUpgrades = KataConcat(allUpgrades,current->data);allUpgrades = KataConcat(allUpgrades,SPASI);
    }
    allUpgrades = KataConcat(allUpgrades, SENTINEL);
    return allUpgrades;
}