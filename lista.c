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

No *buscar(No *lista, int tipo, void *dados) {
    No *atual = lista;

    while (atual !=NULL) {
        if (atual->tipo == tipo) {
            if (tipo == 1 && *(int *)atual->dados == *(int *)dados) {
                return atual;
            }
            if (tipo == 2 && *(float *)atual->dados == *(float *)dados) {
                return atual;
            }
            if (tipo == 3 && strcmp((char *)atual->dados, (char *)dados) == 0) {
                return atual;
            }
        }
        atual = atual->proximo;

    }
    return NULL;
}

int remover(No **lista, int tipo, void *dados) {
    No *atual = *lista;
    No *anterior = NULL;

    while (atual != NULL) {
        int encontrado = 0;

        if (atual->tipo == tipo) {
            if (tipo == 1) {
                encontrado = (*(int *)atual->dados == *(int *)dados);
            } else if (tipo == 2) {
                encontrado = (*(float *)atual->dados == *(float *)dados);
            } else if (tipo == 3) {
                encontrado = (strcmp((char *)atual->dados, (char *)dados) == 0);
            }
        }
        if (encontrado) {
            if (anterior == NULL) {
                *lista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual->dados);
            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return 0;
}

int salvar(No *lista, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    No *atual = lista;

    while (atual != NULL) {
        int tamanho = 0;

        if (atual->tipo == 1) {
            tamanho = sizeof(int);
        }
        else if (atual->tipo == 2) {
            tamanho = sizeof(float);
        } else if (atual->tipo == 3) {
            tamanho = strlen((char *)atual->dados) + 1;
        }
        else {
            fclose(arquivo);
            return 0;
        }
        if (fwrite(&atual->tipo, sizeof(int), 1, arquivo) != 1 ||
            fwrite(&tamanho, sizeof(int), 1, arquivo) != 1 ||
            fwrite(atual->dados, 1, tamanho, arquivo) != (size_t)tamanho) {
            fclose(arquivo);
            return 0;
        }

        atual = atual->proximo;

    }

    if (fclose(arquivo) != 0) {
        return 0;
    }  
    return 1;
}

int carregar(No **lista, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    No *novaLista = NULL;
    No *ultimo = NULL;

    int tipo;
    int tamanho;

    while (fread(&tipo, sizeof(int), 1, arquivo) == 1) {
        if (fread(&tamanho, sizeof(int), 1, arquivo) != 1) {
            break;
        }

        if ((tipo == 1 && tamanho != sizeof(int)) ||
            (tipo == 2 && tamanho != sizeof(float)) ||
            (tipo == 3 && (tamanho <= 0 || tamanho > 10000)) ||
            (tipo < 1 || tipo > 3)) {
            break;
        }

        No *novo = malloc(sizeof(No));

        if (novo == NULL) {
            break;
        }

        novo->dados = malloc(tamanho);

        if (novo->dados == NULL) {
            free(novo);
            break;
        }

        if (fread(novo->dados, 1, tamanho, arquivo) != (size_t)tamanho) {
            free(novo->dados);
            free(novo);
            break;
        }

        if (tipo == 3 && ((char *)novo->dados)[tamanho - 1] != '\0') {
            free(novo->dados);
            free(novo);
            break;
        }

        novo->tipo = tipo;
        novo->proximo = NULL;

        if (novaLista == NULL) {
            novaLista = novo;
        } else {
            ultimo->proximo = novo;
        }
        ultimo = novo;
    }

    int sucesso = feof(arquivo) && !ferror(arquivo);
    fclose(arquivo);

    if (!sucesso) {
        while (novaLista != NULL) {
            No *temp = novaLista;
            novaLista = novaLista->proximo;
            free(temp->dados);
            free(temp);
        }
        return 0;
    }
    while (*lista != NULL) {
        No *temp = *lista;
        *lista = (*lista)->proximo;
        free(temp->dados);
        free(temp);
    }
    *lista = novaLista;
    return 1;
}