#ifndef GRAPH_H
#define GRAPH_H

typedef struct GraphAM {
    int size; // number of vertices
    int* adjacencyMatrix;
} GraphAM;

struct Vertex {
    int id;
    struct Vertex* next;
};

typedef struct GraphLinkedList {
    int size;
    struct Vertex** childrenList;
    struct Vertex** parentList;
} GraphLinkedList;

GraphAM* emptyGraphAM(int size);
void freeGraphAM(GraphAM* graph);
void addEdgeAM(const GraphAM* graph, int parent, int child);
void removeEdgeAM(const GraphAM* graph, int parent, int child);
void displayGraphAM(const GraphAM* graph);

GraphLinkedList* AMtoLL(const GraphAM* graph);
GraphAM* LLtoAM(const GraphLinkedList* graph);

GraphLinkedList* emptyGraphLL(int size);
void freeGraphLL(GraphLinkedList* graph);
void addEdgeLL(GraphLinkedList* graph, int parent, int child);
void removeEdgeLL(GraphLinkedList* graph, int parent, int child);
void displayGraphLL(const GraphLinkedList* graph);


int get_str_size(int size);
int print_to_size(int size, int n);

#endif //GRAPH_H
