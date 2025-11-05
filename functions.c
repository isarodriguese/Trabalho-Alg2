#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

struct paciente {
    int idade; // testando com inteiro, pq nao sei lidar com char
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
int InsereHeap(struct paciente **v, int *tam, int idade, int prio) {
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
    paciente.idade = idade;
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
        InsereHeap(&novo_v, &novo_tam, (*v)[i].idade, (*v)[i].prio);

    free(antigo_v);
    *v = novo_v;
    *tam = novo_tam;
}

// remove um paciente da heap e libera a memoria usada por ele
// retorno: 1 se der certo, 0 se der erro
int RemoveHeap(struct paciente **v, int *tam, int idade, int prio) {
    struct paciente *novo_v;
    int achou = 0, i = 1;

    if (!v)
        return 0;

    while ((i <= *tam) && !achou) {
        if (((*v)[i].idade == idade) && ((*v)[i].prio == prio))
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

// imprime a heap no formato (idade prio) (idade prio) ...
void ImprimeHeap(struct paciente *v, int tam) {
    int i;
    if (!tam)
        printf("Fila de espera vazia\n");
    else {
        printf("Fila de espera: ");
        for (i = 1; i < tam; i++) 
            printf("(%d %d) ", v[i].idade, v[i].prio);
        printf("(%d %d)\n", v[i].idade, v[i].prio);
    }
}

// altera a prioridade de um paciente
void AlteraHeap (struct paciente **v, int *tam, int idade, int prio) {
    int achou = 0, i = 1;

    while ((i <= *tam) && (!achou)) {
        if ((*v)[i].idade == idade)
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
    printf("Insira sua entrada: ");
}

// ------------------------------------------------------------------- Funcoes da analise de algoritmos ----------------------------------------------------------------

int ParticionaVetor(int *v, int inicio, int fim, int *comp, int *trocas) {
    int pivot, pos_pivot = inicio - 1, aux, i;

    (*comp) += 4; // inicio da contagem das comparacoes

    // seleciona a mediana como pivot
    if ((v[inicio] >= v[fim] && v[inicio] <= v[(inicio + fim) / 2]) || (v[inicio] <= v[fim] && v[inicio] >= v[(inicio + fim) / 2]))
        pivot = v[inicio];

    (*comp) += 4;
    if ((v[(inicio + fim) / 2] >= v[inicio] && v[(inicio + fim) / 2] <= v[fim]) || (v[(inicio + fim) / 2] <= v[inicio] && v[(inicio + fim) / 2] >= v[fim])) 
        pivot = v[(inicio + fim) / 2];

    else
        pivot = v[fim];

    // encontra a posicao do pivot no vetor
    i = inicio;
    while (i <= fim && v[i] != pivot) {
        (*comp) += 2;
        i++;
    }

    (*comp) +=2; // comparacoes feitas no fim do loop, no pior caso (seria só uma, se i > fim)

    // coloca o pivot no final do vetor (isso simplifica o algoritmo)
    if (i != fim) {
        aux = v[fim];
        v[fim] = v[i];
        v[i] = aux;
        (*trocas)++;
    }

    // particiona
    for (i = inicio; i <= fim; i++) {
        (*comp) += 2; // uma do for, outra do if
        if (v[i] <= pivot) {
            /* coloca o v[i], menor ou igual ao pivot, antes de onde o pivot vai ficar */
            pos_pivot++;
            aux = v[pos_pivot];
            v[pos_pivot] = v[i];
            v[i] = aux;
            (*trocas)++;
        }
    }

    (*comp)++; // fim do for

    return pos_pivot;

}

void QuickSort(int *v, int inicio, int fim, int *comp, int *trocas) {
    int pos_pivot;
    (*comp)++;
    if (inicio < fim) {
        pos_pivot = ParticionaVetor(v, inicio, fim, comp, trocas);
        QuickSort(v, inicio, pos_pivot - 1, comp, trocas);
        QuickSort(v, pos_pivot + 1, fim, comp, trocas);
    }
}

void SelectSort(int *v, int tam, int *comp, int *trocas) {
    int i, menor, j, aux;
    for (i = 0; i < tam - 1; i++) {
        menor = i;
        (*comp)++; 
        for (j = menor + 1; j <= tam - 1; j++) {
            (*comp) += 2; // do for e do if
            if (v[j] < v[menor])
                menor = j;
        }
        (*comp)++; // fim do segundo for
        aux = v[menor];
        v[menor] = v[i];
        v[i] = aux;
        (*trocas)++;
    }
    (*comp)++; // fim do primeiro for
}

void GeraVetor(int **v, int tam) {
    int i, num;
    for (i = 1; i <= tam; i++) {
        num = rand() % 1025;
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
        (*comp) += 2;
        if ((*v)[i] > (*v)[i/2]) 
            return 0; 
    }
    (*comp)++;
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

    // aloca mais memoria para inserir o elemento
    if (!(novo_v = realloc(*v, sizeof(int) * (*tam + 2))))
        return 0;

    *v = novo_v;

    // inserindo elemento na heap
    (*tam)++;
    (*v)[*tam] = valor;
    i = *tam;

    while ((i > 1) && ((*v)[i/2] < (*v)[i])) {
        (*comp) += 2;
        chave = (*v)[i];
        (*v)[i] = (*v)[i/2];
        (*v)[i/2] = chave;
        i = i/2;
        (*trocas)++;
    }
    (*comp) += 2;

    return 1;
}

// transforma um vetor em um heap de inteiros
void HeapfyV(int **v, int *tam, int *comp, int *trocas) {
    int *novo_v, *antigo_v = *v;
    int i, novo_tam;

    novo_v = InicHeapV(&novo_tam);

    for (i = 1; i <= *tam; i++) {
        (*comp)++;
        InsereHeapV(&novo_v, &novo_tam, antigo_v[i], comp, trocas);
    }
    (*comp)++;
    
    free(antigo_v);
    *v = novo_v;
    *tam = novo_tam;
}

void SacodeHeapV(int **v, int tam, int *comp, int *trocas) {
    int aux;
    int i = 2;

    while (i <= tam) {
        (*comp) += 4; // do while e dos if's
        if (i < tam && (*v)[i] < (*v)[i + 1])
            i++;
        if ((*v)[i/2] >= (*v)[i])
            break;
        aux = (*v)[i/2];
        (*v)[i/2] = (*v)[i];
        (*v)[i] = aux;
        (*trocas)++;
        i *= 2;
    }
}

void HeapSortV(int **v, int tam, int *comp, int *trocas) {
    int aux;
    int i;

    if (!ChecaHeapV(v, &tam, comp))
        HeapfyV(v, &tam, comp, trocas);

    for (i = tam; i > 1; i--) {
        (*comp)++;
        aux = (*v)[1];
        (*v)[1] = (*v)[i];
        (*v)[i] = aux;
        (*trocas)++;
        SacodeHeapV(v, i-1, comp, trocas);
    }
    (*comp)++;
}