#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

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

    if (opcao == 2) {
        int *VetOriginal, *VetQuick, *VetSelect, *VetHeap;
        int tam = 1024,
        NTrocasQuick = 0, NComparacoesQuick = 0,
        NTrocasSelect = 0, NComparacoesSelect = 0,
        NTrocasHeap = 0, NComparacoesHeap = 0;

        printf("\n");
        printf("Olá! Bem-vindo(a) à análise de algoritmos de ordenação!\n");
        printf("\n");
        printf("Gerando vetor aleatório de %d elementos...\n", tam);
        printf("\n");

        srand(0); 
        
        // QuickSort
        if (!(VetOriginal = malloc(sizeof(int) * (tam + 1)))) {
            printf("Não foi possível alocar o vetor.");
            return -1;
        }

        GeraVetor(&VetOriginal, tam);
        printf("Vetor gerado: ");
        ImprimeVetor(VetOriginal, tam);

        // QuickSort - usa cópia do original
        if (!(VetQuick = CopiaVetor(&VetOriginal, tam))) {
            printf("Não foi possível alocar o vetor.");
            free(VetOriginal);
            return -1;
        }
        QuickSort(VetQuick, 1, tam, &NComparacoesQuick, &NTrocasQuick);

        // SelectSort - usa cópia do ORIGINAL, não do QuickSort
        if (!(VetSelect = CopiaVetor(&VetOriginal, tam))) {
            printf("Não foi possível alocar o vetor.");
            free(VetQuick);
            free(VetOriginal);
            return -1;
        }
        SelectSort(VetSelect, tam, &NComparacoesSelect, &NTrocasSelect);

        // HeapSort - usa cópia do ORIGINAL
        if (!(VetHeap = CopiaVetor(&VetOriginal, tam))) {
            printf("Não foi possível alocar o vetor.");
            free(VetSelect);
            free(VetQuick);
            free(VetOriginal);
            return -1;
        }
        HeapSortV(&VetHeap, tam, &NComparacoesHeap, &NTrocasHeap);

        printf("Resultados finais:\n");
        printf("QuickSort: %d comparações, %d trocas\n", NComparacoesQuick, NTrocasQuick);
        printf("HeapSort: %d comparações, %d trocas\n", NComparacoesHeap, NTrocasHeap);
        printf("SelectSort: %d comparações, %d trocas\n", NComparacoesSelect, NTrocasSelect);

        printf("\n");
        printf("Análise:\n");
        if (NComparacoesQuick <= NComparacoesHeap && NComparacoesQuick <= NComparacoesSelect) 
            printf("Melhor algoritmo: QuickSort\n");
        else if (NComparacoesHeap <= NComparacoesQuick && NComparacoesHeap <= NComparacoesSelect) 
            printf("Melhor algoritmo: HeapSort\n");
        else 
            printf("Melhor algoritmo: SelectSort\n");
        printf("\n");
        
        free(VetOriginal);
        free(VetSelect);
        free(VetHeap);
        free(VetQuick);

        return 0;
    }

}
