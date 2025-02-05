#include <stdio.h>
#include <stdlib.h>

#include "../include/graph.h"

#define SIZE 2

int main(void)
{
    GraphAM* g = emptyGraphAM(SIZE);
    for (int i = 0; i < SIZE; i++) {
        addEdgeAM(g, i, (i+1)%SIZE);
        for (int j = 0; j < rand()%SIZE; j++) {
            addEdgeAM(g, i, (i+rand()%SIZE)%SIZE);
        }
    }
    GraphLinkedList* ll = AMtoLL(g);

    for (int j = 0; j <= 0; j++) {
        displayGraphLL(ll);
        addVertexLL(ll);
        putchar('\n');
    }
    addEdgeLL(ll, 2, 1);
    addEdgeLL(ll, 1, 2);
    for (int j = 0; j <= 0; j++) {
        displayGraphLL(ll);
        removeVertexLL(ll, SIZE-j-1);
        putchar('\n');
    }
    displayGraphLL(ll);
    return 0;
}
