#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "mesinkata.h"

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct ListNode 
{
    Kata data;
    struct ListNode *next;
} ListNode;

int addUpgrade( ListNode **head, Kata data );

void removeUpgrade( ListNode **head);

void printUpgrades( ListNode **head );

Kata saveUpgrade( ListNode **head);

int upgradeLength(ListNode **head)

#endif