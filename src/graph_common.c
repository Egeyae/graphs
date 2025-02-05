#include <stdio.h>
#include <stdlib.h>

#include "../include/graph.h"

GraphLinkedList* AMtoLL(const GraphAM* graph) {
    GraphLinkedList* ll = emptyGraphLL(graph->size);
    if (ll == NULL) {
        return NULL;
    }
    for (int i = 0; i < graph->size; i++) {
        for (int j = 0; j < graph->size; j++) {
            if (graph->adjacencyMatrix[i*graph->size + j] == 1) {
                addEdgeLL(ll, i, j);
            }
        }
    }
    return ll;
}

GraphAM* LLtoAM(const GraphLinkedList* graph) {
    GraphAM* am = emptyGraphAM(graph->size);
    if (am == NULL) {
        return NULL;
    }
    for (int i = 0; i < graph->size; i++) {
        struct Vertex* curr = graph->childrenList[i];
        while (curr != NULL) {
            addEdgeAM(am, i, curr->id);
            curr = curr->next;
        }
    }
    return am;
}

int get_str_size(int size) {
    int i = 1;
    while (size >= 10) {
        size = size / 10;
        i++;
    }
    return i;
}

// GPT
int print_to_size(int size, int n) {
    int s = snprintf(NULL, 0, "%d", n);  // Get the string size of n
    int spaces = size - s;               // Calculate spaces needed

    if (spaces < 0) spaces = 0;          // Avoid negative spaces

    char *str = malloc(s + spaces + 1);  // Allocate space for number + spaces + null terminator
    if (!str) return -1;                 // Check for allocation failure

    snprintf(str, s + spaces + 1, "%d%*s", n, spaces, "");  // Format string with padding

    printf("%s", str);  // Print the formatted string
    free(str);            // Free allocated memory

    return s + spaces;    // Return total length of the output string
}