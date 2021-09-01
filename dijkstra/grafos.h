#include <stdlib.h>
#include <stdio.h>

// structs
typedef struct Vertice {
	int v, peso;
	struct Vertice *prox; // ponteiro para o próximo vértice
} Vertice;

// grafo representado por um array de vértices (Vertice)
typedef struct Grafo {
	int n;              // número de vértices
	int orientado;		// grafo orientado = 1; ñ orientado = 0
	Vertice *vertices;  // lista de adjacência
} Grafo;

typedef struct Aresta {
	int ant;
	int prox;
	int peso;
} Aresta;

// funções
Grafo cria_grafo(int n_vertices, int orientado);
void adiciona_aresta(Grafo *grafo, Aresta aresta);
void print_grafo(Grafo grafo);
void free_grafo(Grafo grafo);
