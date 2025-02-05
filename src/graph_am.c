#include <stdio.h>
#include <stdlib.h>

#include "../include/graph.h"

GraphAM* emptyGraphAM(const int size) {
    GraphAM* graph = (GraphAM*) malloc(sizeof(GraphAM));
    if (graph == NULL) {
        fprintf(stderr, "Err in emptyGraphAM: memory allocation error\n");
        return NULL;
    }
    graph->size = size;
    graph->adjacencyMatrix = (int*) malloc(size * size * sizeof(int));
    if (graph->adjacencyMatrix == NULL) {
        fprintf(stderr, "Err in emptyGraphAM: memory allocation error\n");
        return NULL;
    }
    for (int i = 0; i < size*size; i++) {
        graph->adjacencyMatrix[i] = 0;
    }
    return graph;
}

void freeGraphAM(GraphAM* graph) {
    if (graph == NULL) {
        return;
    }
    if (graph->adjacencyMatrix != NULL) {
        free(graph->adjacencyMatrix);
    }
    free(graph);
}

void addEdgeAM(const GraphAM* graph, int parent, int child) {
    if (graph == NULL || graph->adjacencyMatrix == NULL) {
        fprintf(stderr, "Err in addEdgeAM: invalid graph AM provided\n");
        return;
    }
    if (parent < 0 || child < 0 || child >= graph->size || parent >= graph->size) {
        fprintf(stderr, "Err in addEdgeAM: invalid parent or child\n");
        return;
    }
    graph->adjacencyMatrix[parent*graph->size + child] = 1;
}

void removeEdgeAM(const GraphAM* graph, int parent, int child) {
    if (graph == NULL || graph->adjacencyMatrix == NULL) {
        fprintf(stderr, "Err in removeEdgeAM: invalid graph AM provided\n");
        return;
    }
    if (parent < 0 || child < 0 || child >= graph->size || parent >= graph->size) {
        fprintf(stderr, "Err in removeEdgeAM: invalid parent or child\n");
        return;
    }
    graph->adjacencyMatrix[parent*graph->size + child] = 0;
}

void displayGraphAM(const GraphAM* graph) {
    if (graph == NULL || graph->adjacencyMatrix == NULL) {
        fprintf(stderr, "Err in displayGraphAM: invalid graph AM provided\n");
        return;
    }
    int s = get_str_size(graph->size) + 2;

    print_to_size(s, 0);

    for (int i = 0; i < graph->size; i++) {
        print_to_size(s, i);
    }
    putchar('\n');
    for (int i = 0; i < graph->size; i++) {
        print_to_size(s, i);
        for (int j = 0; j < graph->size; j++) {
            print_to_size(s, graph->adjacencyMatrix[i*graph->size + j]);
        }
        printf("\n");
    }
}
