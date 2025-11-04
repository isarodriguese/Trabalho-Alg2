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

        free(v);

        return 0;
    }

    if (opcao == 2){
        int *VetQuick, *VetSelect, *VetHeap;
        int tam = 1024; 

        printf("\n");
        printf("Olá! Bem-vindo(a) à análise de algoritmos de ordenação!\n");
        printf("\n");
        printf("Gerando vetor aleatório de %d elementos...\n", tam);
        printf("\n");

        srand(0); // usado para testes
        
        // QuickSort
        if (!(VetQuick = malloc(sizeof(int) * (tam + 1)))) {
            printf("Não foi possível alocar o vetor.");
            return -1;
        }

        GeraVetor(&VetQuick, tam);
        printf("Vetor gerado: ");
        ImprimeVetor(VetQuick, tam);

        QuickSort(VetQuick, 1, tam);
        printf("Vetor ordenado: ");
        ImprimeVetor(VetQuick, tam);
        

        // SelectSort
        if (!(VetSelect = CopiaVetor(&VetQuick, tam))) {
            printf("Não foi possível alocar o vetor.");
            free(VetQuick);
            return -1;
        }
        
        SelectSort(VetSelect, 1, tam);

        // HeapSort
        if (!(VetHeap = CopiaVetor(&VetQuick, tam))) {
            printf("Não foi possível alocar o vetor.");
            free(VetSelect);
            free(VetQuick);
            return -1;
        }
        
        HeapSortV(&VetHeap, tam);

        free(VetSelect);
        free(VetHeap);
        free(VetQuick);

        return 0;
    }

}