#include <stdio.h>
#include <stdlib.h>

#include "../include/graph.h"

GraphLinkedList* emptyGraphLL(const int size) {
    GraphLinkedList* graph = (GraphLinkedList*) malloc(sizeof(GraphLinkedList));
    if (graph == NULL) {
        fprintf(stderr, "Err in emptyGraphLL: failed to allocate memory\n");
        return NULL;
    }
    graph->size = size;

    graph->childrenList = (struct Vertex**) malloc(sizeof(struct Vertex*) * size);
    if (graph->childrenList == NULL) {
        fprintf(stderr, "Err in emptyGraphLL: failed to allocate memory\n");
        free(graph);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        graph->childrenList[i] = NULL;
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
    }

    free(graph->childrenList);
    free(graph);
}

void appendVertexToLL(struct Vertex** start, const int id) {
    struct Vertex* newVertex = (struct Vertex*) malloc(sizeof(struct Vertex));
    newVertex->id = id;
    newVertex->next = *start;
    *start = newVertex;
}

struct Vertex* delVertexFromLL(struct Vertex* start, const int id) {
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

void addEdgeLL(GraphLinkedList* graph, const int parent, const int child) {
    if (!graph || !graph->childrenList) {
        fprintf(stderr, "Error in addEdgeLL: graph or graph pointer is null\n");
        return;
    }
    appendVertexToLL(&graph->childrenList[parent], child);
}

void removeEdgeLL(GraphLinkedList* graph, int parent, int child) {
    if (!graph || !graph->childrenList) {
        fprintf(stderr, "Error in removeEdgeLL: graph or graph pointer is null\n");
        return;
    }
    graph->childrenList[parent] = delVertexFromLL(graph->childrenList[parent], child);
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

void addVertexLL(GraphLinkedList* graph) {
    if (!graph || !graph->childrenList) {
        fprintf(stderr, "Error in addVertexLL: invalid graph LL provided\n");
        return;
    }

    int newSize = graph->size + 1;

    // Resize the adjacency lists
    struct Vertex** newChildrenList = (struct Vertex**) realloc(graph->childrenList, sizeof(struct Vertex*) * newSize);

    if (!newChildrenList) {
        fprintf(stderr, "Error in addVertexLL: memory allocation failed\n");
        return;
    }

    graph->childrenList = newChildrenList;

    // Initialize new lists for the new vertex
    graph->childrenList[graph->size] = NULL;

    // Update size
    graph->size = newSize;
}

void removeVertexLL(GraphLinkedList* graph, const int id) {
    if (!graph || !graph->childrenList) {
        fprintf(stderr, "Error in removeVertexLL: invalid graph LL provided\n");
        return;
    }
    if (id < 0 || id >= graph->size) {
        fprintf(stderr, "Error in removeVertexLL: invalid vertex ID\n");
        return;
    }

    struct Vertex* curr;

    curr = graph->childrenList[id];
    while (curr) {
        struct Vertex* temp = curr;
        curr = curr->next;
        free(temp);
    }

    for (int i = id; i < graph->size - 1; i++) {
        graph->childrenList[i] = graph->childrenList[i + 1];
    }

    struct Vertex** newChildrenList = (struct Vertex**) realloc(graph->childrenList, sizeof(struct Vertex*) * (graph->size - 1));

    if (!newChildrenList) {
        fprintf(stderr, "Error in removeVertexLL: memory allocation failed\n");
        return;
    }

    graph->childrenList = newChildrenList;

    graph->size--;
}

int* getChildrenLL(const GraphLinkedList* graph, const int id) {
    if (!graph || !graph->childrenList) {
        fprintf(stderr, "Error in getChildrenLL: invalid graph LL provided\n");
        return NULL;
    }
    if (id < 0 || id >= graph->size) {
        fprintf(stderr, "Error in getChildrenLL: invalid vertex ID\n");
        return NULL;
    }
    int* children = (int*) malloc(sizeof(int) * graph->size);
    if (!children) {
        fprintf(stderr, "Error in getChildrenLL: memory allocation failed\n");
        return NULL;
    }
    struct Vertex* curr = graph->childrenList[id];
    int counter = 0;
    while (curr != NULL) {
        children[counter] = curr->id;
        curr = curr->next;
        counter++;
    }
    return children;
}

int isConnectedLL(const GraphLinkedList* graph, const int parent, const int child) {
    if (!graph || !graph->childrenList) {
        fprintf(stderr, "Error in isConnectedLL: invalid graph LL provided\n");
        return 0;
    }
    if (parent < 0 || parent >= graph->size || child < 0 || child >= graph->size) {
        fprintf(stderr, "Error in isConnectedLL: invalid parent or child index\n");
        return 0;
    }
    struct Vertex* curr = graph->childrenList[parent];
    while (curr != NULL) {
        if (curr->id == child) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

int inDegreeLL(const GraphLinkedList* graph, const int id) {
    // no need for graph check nor id check, if any problem, isConnectedAM returns 0
    int count = 0;
    for (int i = 0; i < graph->size; i++) {
        if (isConnectedLL(graph, i, id) == 1) {
            count++;
        }
    }
    return count;
}
int outDegreeLL(const GraphLinkedList* graph, const int id) {
    // no need for graph check nor id check, if any problem, isConnectedAM returns 0
    int count = 0;
    for (int i = 0; i < graph->size; i++) {
        if (isConnectedLL(graph, id, i) == 1) {
            count++;
        }
    }
    return count;
}