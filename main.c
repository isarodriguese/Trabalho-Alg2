#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define MAX 5;

int main () {
    struct paciente *v;
    int idade, prio, tam, opcao;

    printf("\n");
    printf("Escolha sua interface:\n");
    printf("1- Pronto Socorro Heap or Quick\n");
    printf("2- Análise dos Algoritmos de Ordenação\n");

    printf("Insira sua entrada: ");
    scanf("%d", &opcao);


    if (opcao == 1) {

        printf("\n");
        printf("Olá! Bem-vindo(a) ao Pronto Socorro Heap or Quick! ");
        ImprimeMenu();
        scanf("%d", &opcao);

        while (opcao != 0) {

            if (opcao == 1){
                printf("\n");
                printf("Seu turno foi iniciado!\n");
                v = InicHeap(&tam);
            }

            if (opcao == 2){
                printf("\n");
                printf("Digite o nome e a prioridade do paciente a ser inserido: ");
                scanf("%d", &idade);
                scanf("%d", &prio);
                InsereHeap(&v, &tam, idade, prio);
            }

            if (opcao == 3){
                printf("\n");
                printf("Digite o nome e a prioridade do paciente a ser removido: ");
                scanf("%d", &idade);
                scanf("%d", &prio);
                RemoveHeap(&v, &tam, idade, prio);
            }

            if (opcao == 4){
                printf("\n");
                ImprimeHeap(v, tam);
                printf("Digite o nome do paciente e a sua nova prioridade: ");
                scanf("%d", &idade);
                scanf("%d", &prio);
                AlteraHeap(&v, &tam, idade, prio);
            }
            
            printf("\n");
            ImprimeHeap(v, tam);
            ImprimeMenu();
            scanf("%d", &opcao);
        }

        return 0;
    }

    if (opcao == 2){
        int *v;
        int tam = 1024; 

        printf("\n");
        printf("Olá! Bem-vindo(a) à análise de algoritmos de ordenação!\n");
        printf("\n");
        printf("Gerando vetor aleatório de %d elementos...\n", tam);
        printf("\n");

        srand(0); // usado para testes
        
        // QuickSort
        if (!(v = malloc(sizeof(int) * (tam + 1)))) {
            printf("Não foi possível alocar o vetor.");
            return -1;
        }

        GeraVetor(&v, tam);
        QuickSort(v, 1, tam);
        printf("QuickSort: ");
        ImprimeVetor(v, tam);
        free(v);

        // SelectSort
        if (!(v = malloc(sizeof(int) * (tam + 1)))) {
            printf("Não foi possível alocar o vetor.");
            return -1;
        }

        GeraVetor(&v, tam);
        SelectSort(v, 1, tam);
        printf("SelectSort: ");
        ImprimeVetor(v, tam);
        free(v);

        // HeapSort
        if (!(v = malloc(sizeof(int) * (tam + 1)))) {
            printf("Não foi possível alocar o vetor.");
            return -1;
        }
        
        GeraVetor(&v, tam);
        HeapSortV(&v, tam);
        printf("HeapSort: ");
        ImprimeVetor(v, tam);
        free(v);

        return 0;
    }

    free(v);

}