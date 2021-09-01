#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafos.h"

#define MAX_VERTICES 20

void dijkstra(Grafo grafo, int inicio, int *dist, int *anterior);
void print_caminho(int inicio, int fim, int *dist, int *anterior);
void print_dijkstra(int *dist, int *anterior, int n);
int menor_caminho_rec(int inicio, int fim, int *dist, int *anterior, int custo);

int main() {
	
	int n_arestas, n_vertices, orientado;
	Aresta aresta;
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
	
	printf("\nLista de adjacência:\n");
	print_grafo(grafo);

	// ----------- DIJKSTRA -----------

	printf("\nAlgoritmo de Dijkstra:\n");

	// // aloca vetores para as distâncias e vértices anteriores
	int *dist = (int *) malloc(sizeof(int) * n_vertices);
	int *anterior = (int *) malloc(sizeof(int) * n_vertices);
	
	int inicio, fim, continuar = 1;

	while (continuar == 1) {
		printf("Vértices para o caminho mínimo:\n");
		scanf("%d %d", &inicio, &fim);
		
		dijkstra(grafo, inicio, dist, anterior);
		print_dijkstra(dist, anterior, grafo.n);
		
		printf("Menor caminho:\n");
		print_caminho(inicio, fim, dist, anterior);

		printf("\nContinuar?(S = 1, N = 0)\n");
		scanf("%d", &continuar);
	}
	

	free(dist);
	free(anterior);

    free_grafo(grafo);

	return EXIT_SUCCESS;
}

/*Algoritmo de dijkstra para grafos orientados ou não orientados a partir da
lista de adjacência de um grafo. Retorna por referência 2 vetores: 
"dist" - distâncias mínimas do início até cada vértice;
"anterior" - vértices anteriores no caminho. */
void dijkstra(Grafo grafo, int inicio, int *dist, int *anterior) {

	int *visitados = (int *) malloc(sizeof(int) * grafo.n);
	int d;
	Vertice v;

	// Inicialização de estruturas auxiliares
	// distância inicial -> ifinita
	// vértices anteriores -> -1
	// visitados -> visitado = 1, ñ visitado = 0
	for (int i = 0; i < grafo.n; i++) {
		dist[i] = INT_MAX; 
		anterior[i] = -1;
		visitados[i] = 0;
	}
	dist[inicio] = 0;          // a distância de inicio -> inicio é 0
	anterior[inicio] = inicio; // vértice anterir é o mesmo

	for (int i = 0; i < grafo.n; i++) {
		v = grafo.vertices[inicio];

		while (v.prox) {
			// verifica se o vértice já foi visitado
			if (visitados[v.v]) v = *v.prox;
			else {
				d = dist[inicio] == INT_MAX ? v.peso : v.peso + dist[inicio];
				
				// atualiza distância e vértice anterior
				if (d < dist[v.v]) {
					dist[v.v] = d;
					anterior[v.v] = inicio;
				}
				v = *v.prox;
			}
		}

		// relaxa o vértice atual como visitado
		visitados[inicio] = 1;

		// encontra o próximo vértice não visitado com a menor distância
		d = INT_MAX;
		for (int j = 0; j < grafo.n; j++) {
			if (visitados[j] == 0 && d > dist[j]) {
				inicio = j;
				d = dist[j];
			} 
		}
	}

	free(visitados);
}

// função para imprimir os vetores com as distâncias e vértices anteriores 
void print_dijkstra(int *dist, int *anterior, int n) {
	printf("Vértice\t\tDistância\tV. Anterior\n");
	printf("-------------------------------------------\n");
	for (int i = 0; i < n; i++) {
		printf("%d\t\t", i);

		if (dist[i] == INT_MAX) printf("Inf\t\t");
		else printf("%d\t\t", dist[i]);

		if (anterior[i] == -1) printf("-\t\t\n");
		else printf("%d\t\t\n", anterior[i]);
	}
}

// função para imprimir o menor caminho
void print_caminho(int inicio, int fim, int *dist, int *anterior) {
	int custo = menor_caminho_rec(inicio, fim, dist, anterior, 0);
	if (custo == -1) printf("Caminho %d -> %d impossível.\n", inicio, fim);
	else printf("; custo = %d\n", custo);
}

// função auxiliar pra imprimir o menor caminho recursivamente
int menor_caminho_rec(int inicio, int fim, int *dist, int *anterior, int custo) {
	if(inicio != fim) {
		if (dist[fim] == INT_MAX) {
			return -1;
		}

		custo += dist[fim];

		menor_caminho_rec(inicio, anterior[fim], dist, anterior, custo);
		printf(" -> ");
	}

	printf("%d", fim);
	return custo;
}