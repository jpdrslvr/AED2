#include <stdio.h>
#include <stdlib.h>
/*
** Detalhes:
**
** Grafo ponderado e não orientado.
** A implementação foi feita como uma lista encadeada simples, sem cabeça (typedef Vertice).
** O typedef Grafo contém o número de vértices e um ponteiro para um Vertice,
** representando um vetor onde cada elemento é uma lista de vértices.
** Cada vértice tem o valor v (id do vérticee índice usado no vetor de listas)
** e o peso para o próximo vértice da lista. 
**
** A entrada dos dados do grafo se dá pelas arestas (typedef Aresta),
** contendo o vértice anterior, o próximo e o peso. 
*/

// número máximo de nós
#define MAX 20

// structs
typedef struct Vertice {
	int v, peso;
	struct Vertice *prox; // ponteiro para o próximo vértice
} Vertice;

// grafo representado por um array de vértices (Vertice)
typedef struct Grafo {
	int n;              // número de vértices
	Vertice *vertices; // lista de adjacência
} Grafo;

typedef struct Aresta {
	int ant;
	int prox;
	int peso;
} Aresta;

// funções
Grafo cria_grafo(int n);
void adiciona_aresta(Grafo *grafo, Aresta aresta);
void print_grafo(Grafo grafo);
void free_grafo(Grafo *grafo);
void free_vertice(Vertice *vertice);

int main() {
	Aresta aresta; // vetor de arestas
	int n_arestas, n_vertices;
	Grafo grafo;

	do{
		printf("Número de vértices: (máx. 20)\n");
		scanf("%d", &n_vertices);
	} while (n_vertices > MAX || n_vertices <= 0);

	grafo = cria_grafo(n_vertices);

	printf("Número de arestas:\n");
	scanf("%d", &n_arestas);


	printf("Arestas: (ant. próx. peso)\n");
	for (int i = 0; i < n_arestas; ++i) {
		scanf("%d %d %d", &aresta.ant, &aresta.prox, &aresta.peso);
		adiciona_aresta(&grafo, aresta);
	}

	print_grafo(grafo);

	// free
	free_grafo(&grafo);
	// free(arestas);
}


Grafo cria_grafo(int n) {

	Grafo grafo;
	grafo.n = n;
	grafo.vertices = (Vertice *) malloc(sizeof(Vertice) * n); // cria n vértices no grafo

	// inicializa os vértices apontando para NULL
	for (int i = 0; i < n; ++i) {
		grafo.vertices[i].prox = NULL;
	}

	return grafo;

}


void adiciona_aresta(Grafo *grafo, Aresta aresta) {

	// encontra o último vértice da lista
	Vertice *ultimo = &grafo->vertices[aresta.ant];
	while (ultimo->prox != NULL) {
		ultimo = ultimo->prox;
	}

	ultimo->prox = (Vertice *) malloc(sizeof(Vertice));
	ultimo->prox->prox = NULL;
	ultimo->v = aresta.prox;
	ultimo->peso = aresta.peso;
	
	// // encontra o último vértice da lista
	ultimo = &grafo->vertices[aresta.prox];
	while (ultimo->prox != NULL) {
		ultimo = ultimo->prox;
	}

	ultimo->prox = (Vertice *) malloc(sizeof(Vertice));
	ultimo->prox->prox = NULL;
	ultimo->v = aresta.ant;
	ultimo->peso = aresta.peso;

}

// printa lista de adjacẽncia
void print_grafo(Grafo grafo) {

	Vertice vertice;
	
	for (int i = 0; i < grafo.n; ++i) {
		printf("[%d] -> ", i);
		vertice = grafo.vertices[i];
		do {
			printf("[%d; %d] -> ", vertice.v, vertice.peso);
			vertice = *vertice.prox;
		} while (vertice.prox != NULL);
		printf("NULL\n");
	}
}

void free_grafo(Grafo *grafo) {
	// free cada vértice
	for (int i = 0; i < grafo->n; ++i)	{
		free_vertice(&grafo->vertices[i]);
	}
	free(grafo->vertices);
}

void free_vertice(Vertice *vertice) {
	if (vertice->prox != NULL) {
		free_vertice(vertice->prox);
	}
	free(vertice->prox);
}