#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main () {
    struct paciente *v;
    int prio, tam, opcao;
    char nome[64];

    printf("Escolha sua interface:\n");
    printf("1- Pronto Socorro Heap or Quick\n");
    printf("2- Análise dos Algoritmos de Ordenação\n");

    scanf("%d", &opcao);


    if (opcao == 1) {

        printf("Olá! Bem-vindo(a) ao Pronto Socorro Heap or Quick! ");
        ImprimeMenu();
        scanf("%d", &opcao);

        while (opcao != 0) {

            if (opcao == 1){
                v = InicHeap(&tam);
            }

            if (opcao == 2){
                printf("\n");
                printf("Digite o nome e a prioridade do paciente a ser inserido:");
                scanf("%63s", nome);
                scanf("%d", &prio);
                InsereHeap(&v, &tam, nome, prio);
            }

            if (opcao == 3){
                printf("\n");
                printf("Digite o nome e a prioridade do paciente a ser removido:");
                scanf("%63s", nome);
                scanf("%d", &prio);
                RemoveHeap(&v, &tam, nome, prio);
            }

            if (opcao == 4){
                printf("\n");
                ImprimeHeap(v, tam);
                printf("Digite o nome do paciente e a sua nova prioridade:");
                scanf("%63s", nome);
                scanf("%d", &prio);
                AlteraHeap(&v, &tam, nome, prio);
            }
            
            if (opcao == 5){
                break;
            }

            printf("\n");
            ImprimeHeap(v, tam);
            ImprimeMenu();
            scanf("%d", &opcao);
        }

        /*v = InicHeap(&tam);
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
        ImprimeHeap(v, tam);*/

        free(v);

        return 0;
    }

    if (opcao == 2){
        //algoritmos de ordenação
    }
}