#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

struct paciente {
    char nome[64];
    int prio;
};

// cria um vetor vazio
// retorno: NULL
struct paciente *InicHeap(int *tam) {
    struct paciente *v;

    v = NULL;
    *tam = 0;
    return v;
}

// aloca memoria para o paciente e o insere conforme a prioridade
// retorno: 1 se der certo, 0 se der erro
int InsereHeap(struct paciente **v, int *tam, const char *nome, int prio) {
    struct paciente *novo_v;
    struct paciente paciente, chave;
    int i;
    
    if (!v)
        return 0;

    // aloca mais memoria para inserir o paciente
    if (!(novo_v = realloc(*v, sizeof(struct paciente) * (*tam + 2))))
        return 0;

    // realloc copiou todo o conteudo de v, mandou pra outro endereco (novo_v) e liberou o endereco antigo
    // pra nao acessarmos memoria liberada, fazemos o ponteiro de v apontar para o endereco novo
    *v = novo_v;

    // inserindo paciente na heap
    strncpy(paciente.nome, nome, sizeof(paciente.nome) - 1);
    paciente.nome[sizeof(paciente.nome) - 1] = '\0';
    paciente.prio = prio;
    (*tam)++;
    (*v)[*tam] = paciente;
    i = *tam;

    while ((i > 1) && ((*v)[i/2].prio < (*v)[i].prio)) {
        chave = (*v)[i];
        (*v)[i] = (*v)[i/2];
        (*v)[i/2] = chave;
        i = i/2;
    }

    return 1;
}

// verifica se esta sendo cumprida a condicao do heap
// retorno: 1 se ok, 0 se violar
int ChecaHeap (struct paciente **v, int *tam) {
	int i;

	for (i = *tam; i > 1; i--) 
	    if ((*v)[i].prio > (*v)[i/2].prio) 
            return 0; 

	return 1; 
}

// transforma um vetor em um heap
void Heapfy (struct paciente **v, int *tam) {
	struct paciente *novo_v, *antigo_v = *v;
    int i, novo_tam;

    novo_v = InicHeap(&novo_tam);

	for (i = 1; i <= *tam; i++) 
        InsereHeap(&novo_v, &novo_tam, (*v)[i].nome, (*v)[i].prio);

    free(antigo_v);
    *v = novo_v;
    *tam = novo_tam;
}

// remove um paciente da heap e libera a memoria usada por ele
// retorno: 1 se der certo, 0 se der erro
int RemoveHeap(struct paciente **v, int *tam, const char *nome, int prio) {
    struct paciente *novo_v;
    int achou = 0, i = 1;

    if (!v)
        return 0;

    while ((i <= *tam) && !achou) {
        if ((strcmp((*v)[i].nome, nome) == 0) && ((*v)[i].prio == prio))
            achou = 1;
        else
            i++;
    }

    if (!achou){
        printf("O paciente não se encontra nessa fila de espera!");
        return 0;
    }

    for (; i < *tam; i++) 
        (*v)[i] = (*v)[i + 1]; 
    
    if (!(novo_v = realloc(*v, sizeof(struct paciente) * (*tam))))
        return 0;

    *v = novo_v;
	(*tam)--;

    if (!ChecaHeap(v, tam))
        Heapfy(v, tam);

    return 1;
}

// imprime a heap no formato (nome prio) (nome prio) ...
void ImprimeHeap(struct paciente *v, int tam) {
    int i;
    if (!tam)
        printf("A fila de espera está vazia\n");
    else {
        printf("Fila de espera: ");
        for (i = 1; i < tam; i++) 
            printf("(%s %d) ", v[i].nome, v[i].prio);
        printf("(%s %d)\n", v[i].nome, v[i].prio);
    }
}

// altera a prioridade de um paciente
void AlteraHeap (struct paciente **v, int *tam, const char *nome, int prio) {
    int achou = 0, i = 1;

    while ((i <= *tam) && (!achou)) {
        if (strcmp((*v)[i].nome, nome) == 0)
        {
            (*v)[i].prio = prio;
            achou = 1;
        }

        else
            i++;
    }

    if (!achou){
        printf("O paciente não se encontra nessa fila de espera!");
    }

	if (!ChecaHeap(v, tam))
        Heapfy(v, tam);
}

void SacodeHeap(struct paciente **v, int tam) {
    struct paciente aux;
    int i = 2;

    while (i <= tam) {
        if (i < tam && (*v)[i].prio < (*v)[i + 1].prio)
            i++;
        if ((*v)[i/2].prio >= (*v)[i].prio)
            break;
        aux = (*v)[i/2];
        (*v)[i/2] = (*v)[i];
        (*v)[i] = aux;
        i *= 2;
    }
}

void HeapSort (struct paciente **v, int tam) {
	struct paciente aux;
    int i;

	if (!ChecaHeap(v, &tam))
        Heapfy(v, &tam);

	for (i = tam; i > 1; i--) {
		aux = (*v)[1];
		(*v)[1] = (*v)[i];
		(*v)[i] = aux;
		SacodeHeap(v, i-1);
	}
}

void ImprimeMenu () {
    printf("\n");
    printf("Aperte:\n");
    printf("1- Para iniciar seu turno\n");
    printf("2- Para inserir um paciente na lista de espera\n");
    printf("3- Para remover um paciente da lista de espera\n");
    printf("4- Para alterar a prioridade de um paciente\n");
    printf("5- Para visualizar todos os pacientes\n");
    printf("0- Para finalizar seu turno\n");
}

// ------------------------------------------------------------------- Funcoes da analise de algoritmos ----------------------------------------------------------------

int ParticionaVetor(int *v, int inicio, int fim, int *comp, int *trocas) {
    int pivot, pos_pivot = inicio - 1, aux, i;

    // seleciona a mediana como pivot
    if (((*comp) += 2, (v[inicio] >= v[fim] && v[inicio] <= v[(inicio + fim) / 2]) || 
         (v[inicio] <= v[fim] && v[inicio] >= v[(inicio + fim) / 2]))) {
        pivot = inicio;
    }
    else if (((*comp) += 2, (v[(inicio + fim) / 2] >= v[inicio] && v[(inicio + fim) / 2] <= v[fim]) || 
              (v[(inicio + fim) / 2] <= v[inicio] && v[(inicio + fim) / 2] >= v[fim]))) {
        pivot = (inicio + fim) / 2;
    }
    else {
        pivot = fim;
    }

    // coloca o pivot no final do vetor
    if (pivot != fim) {
        aux = v[fim];
        v[fim] = v[pivot];
        v[pivot] = aux;
        (*trocas)++;
    }

    // particiona 
    for (i = inicio; i <= fim; i++) {
        (*comp)++; // do if

        if (v[i] <= v[fim]) { 
            pos_pivot++;
            if (pos_pivot != i) { 
                aux = v[pos_pivot];
                v[pos_pivot] = v[i];
                v[i] = aux;
                (*trocas)++;
            }
        }
    }

    return pos_pivot;
}

void QuickSort(int *v, int inicio, int fim, int *comp, int *trocas) {
    int pos_pivot;
    
    if (inicio < fim) {
        pos_pivot = ParticionaVetor(v, inicio, fim, comp, trocas);
        QuickSort(v, inicio, pos_pivot - 1, comp, trocas);
        QuickSort(v, pos_pivot + 1, fim, comp, trocas);
    }
}

void SelectSort(int *v, int tam, int *comp, int *trocas) {
    int i, menor, j, aux;
    
    for (i = 1; i < tam; i++) {
        menor = i;
        
        for (j = i + 1; j <= tam; j++) {
            (*comp)++; 
            if (v[j] < v[menor])
                menor = j;
        }
        
        if (menor != i) {
            aux = v[i];
            v[i] = v[menor];
            v[menor] = aux;
            (*trocas)++;
        }
    }
}

void GeraVetor(int **v, int tam) {
    int i, num;
    for (i = 1; i <= tam; i++) {
        num = rand() % 20000;
        (*v)[i] = num;
    }
}

int *CopiaVetor(int **v, int tam) {
    int i, *copia;

    if (!(copia = malloc(sizeof(int) * (tam + 1))))
        return NULL;

    for (i = 1; i <= tam; i++) 
        copia[i] = (*v)[i];

    return copia;
}

void ImprimeVetor(int *v, int tam) {
    int i;
    for (i = 1; i < tam; i++)
        printf("%d ", v[i]);
    printf("%d\n", v[i]);
    printf("\n");
}

int ChecaHeapV(int **v, int *tam, int *comp) {
    int i;
    for (i = *tam; i > 1; i--) {
        (*comp)++; 
        if ((*v)[i] > (*v)[i/2]) 
            return 0; 
    }
    return 1; 
}

// cria um vetor vazio de inteiros
int *InicHeapV(int *tam) {
    int *v;
    v = NULL;
    *tam = 0;
    return v;
}

// insere elemento no heap de inteiros
int InsereHeapV(int **v, int *tam, int valor, int *comp, int *trocas) {
    int *novo_v;
    int chave, i;
    
    if (!v)
        return 0;

    if (!(novo_v = realloc(*v, sizeof(int) * (*tam + 2))))
        return 0;

    *v = novo_v;
    (*tam)++;
    (*v)[*tam] = valor;
    i = *tam;

    
    while (i > 1) {
        (*comp)++; 
        if ((*v)[i/2] >= (*v)[i])
            break;
            
        chave = (*v)[i];
        (*v)[i] = (*v)[i/2];
        (*v)[i/2] = chave;
        (*trocas)++;
        i = i/2;
    }

    return 1;
}

// transforma um vetor em um heap de inteiros
void HeapfyV(int **v, int *tam, int *comp, int *trocas) {
    int *novo_v, *antigo_v = *v;
    int i, novo_tam;

    novo_v = InicHeapV(&novo_tam);

    for (i = 1; i <= *tam; i++) {
        InsereHeapV(&novo_v, &novo_tam, antigo_v[i], comp, trocas);
    }
    
    free(antigo_v);
    *v = novo_v;
    *tam = novo_tam;
}

void SacodeHeapV(int **v, int tam, int *comp, int *trocas) {
    int aux;
    int i = 1;
    int filho;

    while (i * 2 <= tam) {
        filho = i * 2;
        
        
        (*comp)++; 
        if (filho < tam && (*v)[filho] < (*v)[filho + 1])
            filho++;
            
        (*comp)++; 
        if ((*v)[i] >= (*v)[filho])
            break;
            
        aux = (*v)[i];
        (*v)[i] = (*v)[filho];
        (*v)[filho] = aux;
        (*trocas)++;
        
        i = filho;
    }
}

void HeapSortV(int **v, int tam, int *comp, int *trocas) {
    int i, aux;

    if (!ChecaHeapV(v, &tam, comp))
        HeapfyV(v, &tam, comp, trocas);

    for (i = tam; i > 1; i--) {
        
        aux = (*v)[1];
        (*v)[1] = (*v)[i];
        (*v)[i] = aux;
        (*trocas)++;
        
        SacodeHeapV(v, i-1, comp, trocas);
    }
}
