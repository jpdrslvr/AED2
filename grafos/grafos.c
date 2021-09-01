/*
** Detalhes:
**
** Grafo ponderado.
** A implementação foi feita como uma lista encadeada simples, sem cabeça (typedef Vertice).
** O typedef Grafo contém o número de vértices, a orientação do gráfico (bool)
** e um ponteiro para um Vertice, representando um vetor onde cada elemento é 
** uma lista de vértices.
** Cada vértice tem o valor v (id do vérticee índice usado no vetor de listas)
** e o peso para o próximo vértice da lista. 
**
** A entrada dos dados do grafo se dá pelas arestas (typedef Aresta),
** contendo o vértice anterior, o próximo e o peso. 
*/

#include <stdio.h>
#include <stdlib.h>

// número máximo de nós
#define MAX_VERTICES 20

// structs
typedef struct Vertice {
	int v, peso;
	struct Vertice *prox; // ponteiro para o próximo vértice
} Vertice;

// grafo representado por um array de vértices (Vertice)
typedef struct Grafo {
	int n;              // número de vértices
	int orientado;		// grafo orientado = 1; ñ orientado = 0
	Vertice *vertices; // lista de adjacência
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
void free_grafo(Grafo *grafo);
void free_vertice(Vertice *vertice);

int main() {
	Aresta aresta;
	int n_arestas, n_vertices, orientado;
	Grafo grafo;

	do{
		printf("Número de vértices: (máx. 20)\n");
		scanf("%d", &n_vertices);
	} while (n_vertices > MAX_VERTICES || n_vertices <= 0);

	printf("Número de arestas:\n");
	scanf("%d", &n_arestas);

	printf("Grafo orientado? (Sim = 1; Não = 0):\n");
	scanf("%d", &orientado);

	grafo = cria_grafo(n_vertices, orientado);

	printf("Arestas: (ant. próx. peso)\n");
	for (int i = 0; i < n_arestas; ++i) {
		scanf("%d %d %d", &aresta.ant, &aresta.prox, &aresta.peso);
		adiciona_aresta(&grafo, aresta);
	}

	print_grafo(grafo);

	// free
	free_grafo(&grafo);
}


Grafo cria_grafo(int n_vertices, int orientado) {

	Grafo grafo;
	grafo.n = n_vertices;
	grafo.orientado = orientado;
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

		// se o gráfico não é orientado
		// swap arestas pra fazer
		// o caminho reverso
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