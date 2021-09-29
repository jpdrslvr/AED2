#include <stdlib.h>
#include <stdio.h>
#include "grafos.h"

static void free_vertice(Vertice *vertice);

Grafo cria_grafo(int n_vertices, int orientado) {

	Grafo grafo = {.n = n_vertices, .orientado = orientado};
	grafo.vertices = (Vertice *) malloc(sizeof(Vertice) * n_vertices); // cria n vértices no grafo

	// inicializa os vértices apontando para NULL
	for (int i = 0; i < n_vertices; ++i) {
		grafo.vertices[i].prox = NULL;
	}

	return grafo;

}


void adiciona_aresta(Grafo *grafo, Aresta aresta) {

	Vertice *ultimo;

	for (int i = 0; i < 2; i++) {
		// encontra o último vértice da lista
		ultimo = &grafo->vertices[aresta.ant];
		while (ultimo->prox != NULL) {
			ultimo = ultimo->prox;
		}

		ultimo->prox = (Vertice *) malloc(sizeof(Vertice));
		ultimo->prox->prox = NULL;
		ultimo->v = aresta.prox;
		ultimo->peso = aresta.peso;

		// se o gráfico não é orientado, swap arestas pra fazer o caminho reverso
		if (!(grafo->orientado)) {
			
			int aux = aresta.ant;
			aresta.ant = aresta.prox;
			aresta.prox = aux;

		} else break;
	}

}

// printa lista de adjacẽncia
void print_grafo(Grafo grafo) {

	Vertice vertice;
	
	for (int i = 0; i < grafo.n; ++i) {
		printf("[%d] -> ", i);
		vertice = grafo.vertices[i];
		while (vertice.prox != NULL) {
			printf("[%d; %d] -> ", vertice.v, vertice.peso);
			vertice = *vertice.prox;
		}
		printf("NULL\n");
	}
}


void free_grafo(Grafo grafo) {
	// free cada vértice
	for (int i = 0; i < grafo.n; ++i)	{
		free_vertice(&grafo.vertices[i]);
	}
	free(grafo.vertices);
}


static void free_vertice(Vertice *vertice) {
	if (vertice->prox != NULL) {
		free_vertice(vertice->prox);
	}
	free(vertice->prox);
}
