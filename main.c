#include <stdio.h>
#include <stdlib.h>
#define MAX 5;

int main () {
    struct dados *v;
    int idade, prio, num, tam, opcao;

    printf("Escolha sua interface:\n");
    printf("1- Pronto Socorro Heap or Quick\n");
    printf("2- Análise dos Algoritmos de Ordenação\n");

    scanf("%d", &opcao);


    if (opcao == 1) {

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

    if (opcao == 2){
        //algoritmos de ordenação
    }
}