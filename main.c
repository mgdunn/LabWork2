#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



// Function to create a new graph
Graph new_graph(int V) {
    Graph graph;
    graph.V = V;
    graph.edges = (EdgeList*)malloc(V * sizeof(EdgeList));

    for (int i = 0; i < V; i++) {
        graph.edges[i].head = NULL;
    }
    return graph;
}


// Function to create a new edge node
EdgeNodePtr createEdgeNode(int to_vertex, int weight) {
    EdgeNodePtr newNode = (EdgeNodePtr)malloc(sizeof(struct edgeNode));
   
    newNode->edge.to_vertex = to_vertex;
    newNode->edge.weight = weight;
    newNode->next = NULL;
    return newNode;
}


// Function to insert a node at the front of the list
void insertAtFront(EdgeList* list, EdgeNodePtr newNode) {
    newNode->next = list->head;
    list->head = newNode;
}


int main() {
    Graph G;

    // Open the input file
    FILE* input_file = fopen("input.txt", "r");

    scanf_s("%d", &G.V);


    // Initialize an array of edge counts and set them all to 0
    int* edgeCounts = (int*)malloc(G.V * sizeof(int));
    for (int i = 0; i < G.V; i++) {
        edgeCounts[i] = 0;
    }


    // Loops through each vertex
    for (int i = 0; i < G.V; i++) {
        int numEdges;
        scanf_s("%d", &numEdges); 


        // Loop through each edge for the current vertex
        for (int j = 0; j < numEdges; j++) {
            int to_vertex;
            int weight;

            scanf_s("%d,%d", &to_vertex, &weight);

            // Create a new edge node
            EdgeNodePtr newNode = createEdgeNode(to_vertex, weight);
            insertAtFront(&(G.edges[i]), newNode);

            // Increment the edge count for the to-vertex
            edgeCounts[to_vertex] = edgeCounts[to_vertex] + weight;
        }
    }


    // Print the in-degrees
    printf("In-degrees:\n");
    for (int i = 0; i < G.V; i++) {
        printf("Vertex %d: %d\n", i, edgeCounts[i]);
    }


    // Free allocated memory
    for (int i = 0; i < G.V; i++) {
        EdgeNodePtr current = G.edges[i].head;
        while (current != NULL) {
            EdgeNodePtr temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(G.edges);

    return 0;
}

