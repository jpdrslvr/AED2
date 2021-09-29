#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "grafos.h"

#define MAX_VERTICES 20

// struct representando um conjunto
struct conjunto {
	int parent, rank;
};

// -- OPERAÇÕES COM CONJUNTOS --
// https://en.wikipedia.org/wiki/Disjoint-set_data_structure
void union_(struct conjunto *conjuntos, int x, int y);
int find(struct conjunto *conjuntos, int i);
void print_conjuntos(struct conjunto *conjuntos, int size);

// -- KRUSKAL -- 
Grafo kruskal(Aresta *arestas, int n_arestas, int n_vertices);

int main() {
	
	int n_arestas, n_vertices;
	Aresta *arestas;
	Grafo grafo;

	do{
		printf("Número de vértices: (máx. 20)\n");
		scanf("%d", &n_vertices);
	} while (n_vertices > MAX_VERTICES || n_vertices <= 0);

	printf("Número de arestas:\n");
	scanf("%d", &n_arestas);

	arestas = (Aresta *) malloc(sizeof(Aresta) * n_arestas);
	grafo = cria_grafo(n_vertices, 0);

	printf("Arestas: (ant. próx. peso)\n");
	for (int i = 0; i < n_arestas; ++i) {
		scanf("%d %d %d", &arestas[i].ant, &arestas[i].prox, &arestas[i].peso);
		adiciona_aresta(&grafo, arestas[i]);
	}

	printf("\nLista de adjacência:\n");
	print_grafo(grafo);

	// ALGORITMO DE KRUSKAL

	Grafo mst = kruskal(arestas, n_arestas, n_vertices);
	printf("\nÁrvore Geradora Mínima (MST):\n");
	print_grafo(mst);

	free(arestas);
    free_grafo(grafo);
    free_grafo(mst);

	return EXIT_SUCCESS;
}

// Faz a união entre dois subconjuntos que contém x e y.
void union_(struct conjunto *conjuntos, int x, int y) {
	// raízes dos nós x e y
	int raiz_x = find(conjuntos, x);
	int raiz_y = find(conjuntos, y);

	if (conjuntos[raiz_x].rank == conjuntos[raiz_y].rank) {
		// subconjuntos já fazem parte do mesmo conjunto
		conjuntos[raiz_y].parent = raiz_x;
		conjuntos[raiz_x].rank++;
	} else if (conjuntos[raiz_x].rank < conjuntos[raiz_y].rank) {
		// nó pai de raiz_x passa a ser raiz_y
		conjuntos[raiz_x].parent = raiz_y;
	}
	else {
		// nó pai de raiz_y passa a ser raiz_x
		conjuntos[raiz_y].parent = raiz_x;
	}
}

// Encontra raiz de um subconjunto.
int find(struct conjunto *conjuntos, int i) {
	if (conjuntos[i].parent != i) {
		conjuntos[i].parent = find(conjuntos, conjuntos[i].parent);
	}

	return conjuntos[i].parent;
}

// Função auxiliar para printar os subconjuntos. Só usada para debugar o código
void print_conjuntos(struct conjunto *conjuntos, int size) {
    char strs[20][100] = {"\0"};
    char buffer[5];

    for (int i = 0; i < size; i++) {
        sprintf(buffer, "%d, ", i);
        strcat(strs[find(conjuntos, i)], buffer);
    }

    printf("{");

    for (int i = 0; i < size; i++) {
        if (strlen(strs[i]) > 0) {
            printf("{%s\b\b}", strs[i]);
        }
    }
    
    printf("}\n");
   
}

// Função para comparar duas arestas pelo peso, usada na função qsort()
int comp(const void *a, const void *b) {
	return ((Aresta *)a)->peso > ((Aresta *)b)->peso;
}

// Implementação do algoritmo de Kruskal a partir de um vetor de arestas.
// Retorna a árvore geradora mínima do grafo (das arestas) em lista de
// adjacência.
Grafo kruskal(Aresta *arestas, int n_arestas, int n_vertices) {
	// cria grafo não orientado para a árvore geradora mínima
	Grafo mst = cria_grafo(n_vertices, 0);
	int i = 0, ant, prox, n_arestas_mst = 0;

	// ordena vetor de arestas pelo peso
	qsort(arestas, n_arestas, sizeof(Aresta), comp);

	// cria subconjuntos para cada vértice
	struct conjunto *conjuntos = malloc(sizeof(struct conjunto) * n_vertices);
	for (int i = 0; i < n_vertices; i++) {
		conjuntos[i].parent = i;
		conjuntos[i].rank = 0;
	}

	// Loop para quando número de arestas é igual ao número de vértices - 1.
	for(int i = 0; n_arestas_mst < n_vertices - 1; i++) {
		// arestas[i] é a aresta de menor custo pois o vetor
		// de arestas foi ordenado

		ant  = find(conjuntos, (arestas + i)->ant);
		prox = find(conjuntos, (arestas + i)->prox);
		
		// Encontra a raiz de cada subconjunto. Se forem diferentes, faz a união
		// dos subconjuntos e adiciona a aresta ao grafo (mst). Se forem iguais,
		// ignora, pois adicionar a aresta vai gerar um ciclo.
		
		if (ant != prox) { // não há ciclo

			// faz a união dos subconjuntos que contém ant e prox
			union_(conjuntos, ant, prox);
			
			// print_conjuntos(conjuntos, n_vertices);
			
			// adiciona a aresta à árvore
			adiciona_aresta(&mst, *(arestas + i));
			n_arestas_mst++;
		}

	}

	free(conjuntos);

	return mst;

}