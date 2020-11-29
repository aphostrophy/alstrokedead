#include <stdio.h>
#include <stdlib.h>
#include "../mesinkata/mesinkata.h"

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct ListNode 
{
    Kata data;
    struct ListNode *next;
} ListNode;

int addUpgrade( ListNode **head, Kata data );
/*
Menambahkan elemen terakhir berupa Kata ke salah satu linked list yang tersimpan dalam list of linked list
    I.S : list of linked list terdefinisi dan diakhiri null
    F.S : menambah elemen terakhir pada salah satu linked list yang ada di dalam list 
*/

void removeUpgrade( ListNode **head);
/* 
Membuang elemen terakhir yang terdefinisi dari salah satu linked list yang tersimpan dalam list of linked list
    I.S : list of linked list terdefinisi dan diakhiri null
    F.S : salah satu elemen terakhir dari linked list yang ada di dalam list akan terbuang jika tidak empty, jika empty tidak terjadi apa-apa
*/

void printUpgrades( ListNode **head );
/*
Mencetak isi dari salah satu linkedlist
    I.S : list of linked list terdefinisi dan diakhiri null
    F.S : mencetak semua Kata yang tersimpan dalam node-node linkedlist hingga node = NULL
*/

Kata saveUpgrade( ListNode **head);
/*
Mereturn semua Kata pada node-node linked list 
    I.S : list of linked list terdefinisi dan diakhiri null
    F.S : Semua Kata pada nodes dikonkat menjadi 1 kata yang panjang, intinya sama seperti printUpgrade tapi direturn
*/

int upgradeLength(ListNode **head);
/*
    I.S : list of linked list terdefinisi dan diakhiri null
    F.S : mereturn panjang dari linked list
*/

#endif