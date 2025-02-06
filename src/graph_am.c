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

void addVertexAM(GraphAM* graph) {
    if (graph == NULL || graph->adjacencyMatrix == NULL) {
        fprintf(stderr, "Err in addVertexAM: invalid graph AM provided\n");
        return;
    }

    const int newSize = graph->size + 1;
    int* newAdjMatrix = (int*) malloc(newSize * newSize * sizeof(int));
    if (newAdjMatrix == NULL) {
        fprintf(stderr, "Err in addVertexAM: memory allocation error\n");
        return;
    }

    for (int i = 0; i < graph->size; i++) {
        for (int j = 0; j < graph->size; j++) {
            newAdjMatrix[i * newSize + j] = graph->adjacencyMatrix[i * graph->size + j];
        }
        newAdjMatrix[i * newSize + graph->size] = 0;  // New column
    }

    for (int j = 0; j < newSize; j++) {
        newAdjMatrix[graph->size * newSize + j] = 0;
    }

    free(graph->adjacencyMatrix);
    graph->adjacencyMatrix = newAdjMatrix;
    graph->size = newSize;
}

void removeVertexAM(GraphAM* graph, const int id) {
    if (graph == NULL || graph->adjacencyMatrix == NULL) {
        fprintf(stderr, "Err in removeVertexAM: invalid graph AM provided\n");
        return;
    }
    if (id < 0 || id >= graph->size) {
        fprintf(stderr, "Err in removeVertexAM: invalid vertex ID\n");
        return;
    }

    const int newSize = graph->size - 1;
    if (newSize == 0) {
        free(graph->adjacencyMatrix);
        graph->adjacencyMatrix = NULL;
        graph->size = 0;
        return;
    }

    int* newAdjMatrix = (int*) malloc(newSize * newSize * sizeof(int));
    if (newAdjMatrix == NULL) {
        fprintf(stderr, "Err in removeVertexAM: memory allocation error\n");
        return;
    }

    for (int i = 0, new_i = 0; i < graph->size; i++) {
        if (i == id) continue;
        for (int j = 0, new_j = 0; j < graph->size; j++) {
            if (j == id) continue;
            newAdjMatrix[new_i * newSize + new_j] = graph->adjacencyMatrix[i * graph->size + j];
            new_j++;
        }
        new_i++;
    }

    free(graph->adjacencyMatrix);
    graph->adjacencyMatrix = newAdjMatrix;
    graph->size = newSize;
}

int* getChildrenAM(const GraphAM* graph, const int id) {
    if (graph == NULL || graph->adjacencyMatrix == NULL) {
        fprintf(stderr, "Err in getChildrenAM: invalid graph AM provided\n");
        return NULL;
    }
    if (id < 0 || id >= graph->size) {
        fprintf(stderr, "Err in getChildrenAM: invalid vertex ID\n");
        return NULL;
    }
    int* children = (int*) malloc(graph->size * sizeof(int));
    if (children == NULL) {
        fprintf(stderr, "Err in getChildrenAM: memory allocation error\n");
        return NULL;
    }
    for (int i = 0; i < graph->size; i++) {
        children[i] = graph->adjacencyMatrix[id * graph->size + i];
    }
    return children;
}

int isConnectedAM(const GraphAM* graph, const int parent, const int child) {
    if (graph == NULL || graph->adjacencyMatrix == NULL) {
        fprintf(stderr, "Err in isConnectedAM: invalid graph AM provided\n");
        return 0;
    }
    if (child < 0 || child >= graph->size || parent < 0 || parent >= graph->size) {
        fprintf(stderr, "Err in isConnectedAM: invalid vertex ID\n");
        return 0;
    }
    return graph->adjacencyMatrix[parent*graph->size + child];
}

int inDegreeAM(const GraphAM* graph, const int id) {
    // no need for graph check nor id check, if any problem, isConnectedAM returns 0
    int count = 0;
    for (int i = 0; i < graph->size; i++) {
        if (isConnectedAM(graph, i, id) == 1) {
            count++;
        }
    }
    return count;
}
int outDegreeAM(const GraphAM* graph, const int id) {
    // no need for graph check nor id check, if any problem, isConnectedAM returns 0
    int count = 0;
    for (int i = 0; i < graph->size; i++) {
        if (isConnectedAM(graph, id, i) == 1) {
            count++;
        }
    }
    return count;
}