#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

struct paciente {
	char nome[100];
	int prio;
};

struct paciente *InicHeap(int N) {
	struct paciente *fila;

	if (!(fila = malloc(N * sizeof(struct paciente))))
		return NULL;
	
	return fila;
}

void InsereHeap(int N, struct paciente V[]) {
	int i, j, aux;

	j = N + 1;
	while(j > 1 && V[i/2] < V[i])
    {
		//troca
		aux = V[i/2];
		V[i/2] = V[i];
		V[i] = aux;
		i = i/2;
	}
}

void RemoveHeap (int *N, struct paciente V[], struct paciente p)//nao esta 100% ainda
{
	int i; 

	while ((i <= N) && ((strcmp(V[i].nome, p.nome) != 0) && (V[i].prioridade != p.prioridade))) i++;
    
	for (i, i <= N, i++) V[i] = V[i + 1];  
    
	(*N)--;

	if (ChecaHeap(N, V) == 0) Heapfy(N, V);
}

void Heapfy (int N, int V[]) 
{
	int i;
	for (i = 1; i < N; j++) InsereHeap(i,V);
}

int ChecaHeap (int N, struct paciente V[]) 
{
	int i;

	for (int i = N; i > 1; i--) 
	{
	    if (V[i].prioridade > V[i/2].prioridade) return 0; // violou o max-heap
	}

	return 1; // ok
}

void ImprimeHeap (int N, struct paciente V[])
{
	for (int i = 1; i <= N; i++) 
	{
		printf("%s (prioridade %d)\n", V[i].nome, V[i].prioridade);
	}
}

void HeapSort (int N, struct paciente V[]) 
{
	int i, aux;

	Heapfy(V);

	for (i = N; i > 1; i--) 
	{
		aux = V[1];
		V[1] = V[i];
		V[i] = aux;
		SacodeHeap(i-1, V);
	}
}

void AlteraHeap (struct paciente V[], int posicao, int prioridade)
{
	V[posicao].prioridade = prioridade;

	if (!ChecaHeap(V)) Heapfy(V);
}

//Falta o SacodeHeap