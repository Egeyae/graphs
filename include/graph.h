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
} GraphLinkedList;

// AM Related funcs
GraphAM* emptyGraphAM(int size);
void freeGraphAM(GraphAM* graph);
void addEdgeAM(const GraphAM* graph, int parent, int child);
void removeEdgeAM(const GraphAM* graph, int parent, int child);
void displayGraphAM(const GraphAM* graph);
void addVertexAM(GraphAM* graph); // add a new column+row at the end
void removeVertexAM(GraphAM* graph, const int id);
int* getChildrenAM(const GraphAM* graph, const int id);
int isConnectedAM(const GraphAM* graph, const int parent, const int child);
int inDegreeAM(const GraphAM* graph, const int id);
int outDegreeAM(const GraphAM* graph, const int id);

// Conversion funcs
GraphLinkedList* AMtoLL(const GraphAM* graph);
GraphAM* LLtoAM(const GraphLinkedList* graph);

// LL Related funcs
GraphLinkedList* emptyGraphLL(int size);
void freeGraphLL(GraphLinkedList* graph);
void addEdgeLL(GraphLinkedList* graph, int parent, int child);
void removeEdgeLL(GraphLinkedList* graph, int parent, int child);
void displayGraphLL(const GraphLinkedList* graph);
void addVertexLL(GraphLinkedList* graph); // adds a new vertex at the end
void removeVertexLL(GraphLinkedList* graph, const int id);
int* getChildrenLL(const GraphLinkedList* graph, const int id);
int isConnectedLL(const GraphLinkedList* graph, const int parent, const int child);
int inDegreeLL(const GraphLinkedList* graph, const int id);
int outDegreeLL(const GraphLinkedList* graph, const int id);

// General funcs
int get_str_size(int size);
int print_to_size(int size, int n);

#endif //GRAPH_H
