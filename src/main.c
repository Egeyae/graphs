#include <stdio.h>
#include <stdlib.h>

#include "../include/graph.h"

#define SIZE 12

int main(void)
{
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
    GraphAM* am = LLtoAM(ll);
    displayGraphAM(am);
    putchar('\n');
    displayGraphLL(ll);
    return 0;
}
