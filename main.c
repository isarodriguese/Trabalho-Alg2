#include <stdio.h>
#include <stdlib.h>
#define MAX 5;

struct dados {
    int idade; // testando com inteiro, pq nao sei lidar com char
    int prio;
};

// cria um vetor vazio
// retorno: NULL
struct dados *InicHeap(int *tam) {
    struct dados *v;

    v = NULL;
    *tam = 0;
    return v;
}

// aloca memoria para o paciente e o insere conforme a prioridade
// retorno: 1 se der certo, 0 se der erro
int InsereHeap(struct dados **v, int *tam, int idade, int prio) {
    struct dados *novo_v;
    struct dados paciente, chave;
    int i;
    
    if (!v)
        return 0;

    // aloca mais memoria para inserir o paciente
    if (!(novo_v = realloc(*v, sizeof(struct dados) * (*tam + 2))))
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
int ChecaHeap (struct dados **v, int *tam) {
	int i;

	for (i = *tam; i > 1; i--) 
	    if ((*v)[i].prio > (*v)[i/2].prio) 
            return 0; 

	return 1; 
}

// transforma um vetor em um heap
void Heapfy (struct dados **v, int *tam) {
	struct dados *novo_v, *antigo_v = *v;
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
int RemoveHeap(struct dados **v, int *tam, int idade, int prio) {
    struct dados *novo_v;
    int achou = 0, i = 1;

    if (!v)
        return 0;

    while ((i <= *tam) && !achou) {
        if (((*v)[i].idade == idade) && ((*v)[i].prio == prio))
            achou = 1;
        else
            i++;
    }

    if (!achou)
        return 0;

    for (; i < *tam; i++) 
        (*v)[i] = (*v)[i + 1]; 
    
    if (!(novo_v = realloc(*v, sizeof(struct dados) * (*tam))))
        return 0;

    *v = novo_v;
	(*tam)--;

    if (!ChecaHeap(v, tam))
        Heapfy(v, tam);

    return 1;
}

// imprime a heap no formato (idade prio) (idade prio) ...
void ImprimeHeap(struct dados *v, int tam) {
    int i;
    if (!tam)
        printf("Heap vazia!\n");
    else {
        for (i = 1; i < tam; i++) 
            printf("(%d %d) ", v[i].idade, v[i].prio);
        printf("(%d %d)\n", v[i].idade, v[i].prio);
    }
}

// altera a prioridade de um paciente
void AlteraHeap (struct dados **v, int *tam, int pos, int prio) {
    (*v)[pos].prio = prio;

	if (!ChecaHeap(v, tam))
        Heapfy(v, tam);
}

void SacodeHeap(struct dados **v, int tam) {
    struct dados aux;
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

void HeapSort (struct dados **v, int tam) {
	struct dados aux;
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

int main () {
    struct dados *v;
    int idade, prio, num, tam, opcao;

    v = InicHeap(&tam);
    printf("insira a idade e a prioridade dos novos pacientes:\n");
    for (int i = 1; i <= 5; i++) 
        if ((scanf("%d", &idade) == 1) && (scanf("%d", &prio) == 1))
            InsereHeap(&v, &tam, idade, prio);

    ImprimeHeap(v, tam);

    printf("insira a idade e a prioridade dos pacientes a serem removidos:\n");
    for (int i = 1; i <= 5; i++) 
        if ((scanf("%d", &idade) == 1) && (scanf("%d", &prio) == 1))
            RemoveHeap(&v, &tam, idade, prio);

    ImprimeHeap(v, tam);

    printf("alterar prioridade de paciente - digite a posicao dele na fila (valor entre 1 e %d)\n", tam);
    if ((scanf("%d", &num) == 1) && (num >= 1) && (num <= tam)) {
        printf("digite a nova prioridade:\n");
        if ((scanf("%d", &prio) == 1))
            AlteraHeap(&v, &tam, num, prio);
    }

    ImprimeHeap(v, tam);

    printf("Heap ordenada: ");
    HeapSort(&v, tam);
    ImprimeHeap(v, tam);

    free(v);

    return 0;
}