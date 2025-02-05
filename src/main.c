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
    for (int j = 0; j <= 3; j++) {
        displayGraphAM(g);
        addVertexAM(g);
        putchar('\n');
    }
    for (int j = 0; j <= 3; j++) {
        displayGraphAM(g);
        removeVertexAM(g, SIZE-j-1);
        putchar('\n');
    }
    return 0;
}
