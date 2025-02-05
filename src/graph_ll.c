#include <stdio.h>
#include <stdlib.h>

#include "../include/graph.h"

GraphLinkedList* emptyGraphLL(int size) {
    GraphLinkedList* graph = (GraphLinkedList*) malloc(sizeof(GraphLinkedList));
    if (graph == NULL) {
        fprintf(stderr, "Err in emptyGraphLL: failed to allocate memory\n");
        return NULL;
    }
    graph->size = size;

    graph->childrenList = (struct Vertex**) malloc(sizeof(struct Vertex*) * size);
    graph->parentList = (struct Vertex**) malloc(sizeof(struct Vertex*) * size);
    if (graph->childrenList == NULL || graph->parentList == NULL) {
        fprintf(stderr, "Err in emptyGraphLL: failed to allocate memory\n");
        free(graph);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        graph->childrenList[i] = NULL;
        graph->parentList[i] = NULL;
    }

    return graph;
}

void freeGraphLL(GraphLinkedList* graph) {
    if (!graph) return;

    for (int i = 0; i < graph->size; i++) {
        struct Vertex* curr = graph->childrenList[i];
        while (curr) {
            struct Vertex* temp = curr;
            curr = curr->next;
            free(temp);
        }

        curr = graph->parentList[i];
        while (curr) {
            struct Vertex* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    free(graph->childrenList);
    free(graph->parentList);
    free(graph);
}

void addVertexToLL(struct Vertex** start, int id) {
    struct Vertex* newVertex = (struct Vertex*) malloc(sizeof(struct Vertex));
    newVertex->id = id;
    newVertex->next = *start;
    *start = newVertex;
}

struct Vertex* removeVertexFromLL(struct Vertex* start, int id) {
    struct Vertex* current = start;
    struct Vertex* previous = NULL;

    while (current) {
        if (current->id == id) {
            if (previous) {
                previous->next = current->next;
            } else {
                start = current->next;
            }
            free(current);
            return start;
        }
        previous = current;
        current = current->next;
    }
    return start;
}

void addEdgeLL(GraphLinkedList* graph, int parent, int child) {
    if (!graph || !graph->childrenList || !graph->parentList) {
        fprintf(stderr, "Error in addEdgeLL: graph or graph pointer is null\n");
        return;
    }
    addVertexToLL(&graph->childrenList[parent], child);
}

void removeEdgeLL(GraphLinkedList* graph, int parent, int child) {
    if (!graph || !graph->childrenList || !graph->parentList) {
        fprintf(stderr, "Error in removeEdgeLL: graph or graph pointer is null\n");
        return;
    }
    graph->childrenList[parent] = removeVertexFromLL(graph->childrenList[parent], child);
}

void displayGraphLL(const GraphLinkedList* graph) {
    if (!graph || !graph->childrenList) {
        fprintf(stderr, "Err in displayGraphLL: invalid graph LL provided\n");
        return;
    }

    int s = get_str_size(graph->size) + 2;  // Get proper spacing

    for (int i = 0; i < graph->size; i++) {
        print_to_size(s, i);
        printf("-> ");

        struct Vertex* child = graph->childrenList[i];
        while (child) {
            print_to_size(s, child->id);
            child = child->next;
        }
        putchar('\n');
    }
}
