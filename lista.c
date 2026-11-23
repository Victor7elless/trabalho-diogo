#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int inserir(No **lista, int tipo, void *dados) {
    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memória!!\n");
        return 0;
    }

    novo->dados = malloc(
        tipo == 1 ? sizeof(int) :
        tipo == 2 ? sizeof(float) :
        strlen((char *)dados) + 1
    );

    if (novo->dados == NULL) {
        free(novo);
        return 0;

    }

    if (tipo == 1) {
        *(int *)novo->dados = *(int *)dados;
    } else if (tipo == 2) {
        *(float*)novo->dados = *(float*)dados;
    } else {
        strcpy((char *)novo->dados, (char *)dados);
    }

    

    novo->tipo = tipo;
    novo->proximo = *lista;
    *lista = novo;

    return 1;
}

void imprimir (No *lista) {
        No *atual = lista;

        if (atual == NULL) {
            printf("A lista está vazia.\n");
            return;
        }

        printf("\n=== Elementos da lista ===\n");

        while (atual != NULL) {
            if (atual-> tipo == 1) {
                printf("Inteiro: %d\n", *(int *)atual->dados);
            }
            else if (atual->tipo == 2) {
                printf("Decimal: %.2f\n", *(float *)atual->dados);
            }
            else if (atual->tipo == 3) {
                printf("Texto: %s\n", (char *)atual->dados);
            }

            atual = atual->proximo;
        }
    }