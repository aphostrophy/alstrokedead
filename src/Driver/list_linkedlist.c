#include "../Header/list_linkedlist.h"
#include "../Header/wahana.h"
#include <stdio.h>
#include <stdlib.h>

int addUpgrade( Node **head, Kata data )
{
    Node *node = malloc( sizeof( Node ) );
    int success = node != NULL;

    if ( success ){
        node->data = data;
        node->next = *head;
        *head = node;
    }
    return success;
}

void printUpgrades( Node **head )
{
    printf( "%s", "NULL" );
    for( Node *current =*head; current != NULL; current = current->next ) //Mark pakai NULL
    {
        printf("<-");printKata(current->data);
    }
}