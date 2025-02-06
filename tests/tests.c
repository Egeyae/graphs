#include <stdio.h>
#include <stdlib.h>

#include "../include/graph.h"

#define SIZE 6

int main(void)
{
    printf("1\n\n");
    GraphAM* g = emptyGraphAM(SIZE);
    for (int i = 0; i < SIZE; i++) {
        addEdgeAM(g, i, (i+1)%SIZE);
        for (int j = 0; j < rand()%SIZE; j++) {
            addEdgeAM(g, i, (i+rand()%SIZE)%SIZE);
        }
    }
    displayGraphAM(g);
    printf("\n");
    GraphLinkedList* ll = AMtoLL(g);
    displayGraphLL(ll);
    printf("\n");

    return 0;
}

