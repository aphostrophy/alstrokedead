#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "mesinkata.h"

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct Node 
{
    Kata data;
    struct Node *next;
} Node;

int addUpgrade( Node **head, Kata data );

void printUpgrades( Node **head );

#endif