
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int inserir(No **lista, int tipo, void *dados) {
    if (lista == NULL || dados == NULL || tipo < 1 || tipo > 3) {
        return 0;
    }

    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 0;
    }

    size_t tamanho;

    if (tipo == 1) {
        tamanho = sizeof(int);
    } else if (tipo == 2) {
        tamanho = sizeof(float);
    } else {
        tamanho = strlen((char *)dados) + 1;
    }

    novo->dados = malloc(tamanho);

    if (novo->dados == NULL) {
        free(novo);
        return 0;
    }

    memcpy(novo->dados, dados, tamanho);

    novo->tipo = tipo;
    novo->proximo = *lista;
    *lista = novo;

    return 1;
}

void imprimir(No *lista) {
    No *atual = lista;

    if (atual == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    printf("\n=== Elementos da lista ===\n");

    while (atual != NULL) {
        if (atual->tipo == 1) {
            printf("Inteiro: %d\n", *(int *)atual->dados);
        } else if (atual->tipo == 2) {
            printf("Decimal: %.2f\n", *(float *)atual->dados);
        } else if (atual->tipo == 3) {
            printf("Texto: %s\n", (char *)atual->dados);
        }

        atual = atual->proximo;
    }
}

No *buscar(No *lista, int tipo, void *dados) {
    if (dados == NULL) {
        return NULL;
    }

    No *atual = lista;

    while (atual != NULL) {
        if (atual->tipo == tipo) {
            if (tipo == 1 &&
                *(int *)atual->dados == *(int *)dados) {
                return atual;
            }

            if (tipo == 2 &&
                *(float *)atual->dados == *(float *)dados) {
                return atual;
            }

            if (tipo == 3 &&
                strcmp((char *)atual->dados, (char *)dados) == 0) {
                return atual;
            }
        }

        atual = atual->proximo;
    }

    return NULL;
}

int remover(No **lista, int tipo, void *dados) {
    if (lista == NULL || dados == NULL) {
        return 0;
    }

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
                encontrado = (strcmp(
                    (char *)atual->dados,
                    (char *)dados
                ) == 0);
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
    if (nomeArquivo == NULL) {
        return 0;
    }

    FILE *arquivo = fopen(nomeArquivo, "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    No *atual = lista;
    int sucesso = 1;

    while (atual != NULL) {
        int tamanho = 0;

        if (atual->tipo == 1) {
            tamanho = (int)sizeof(int);
        } else if (atual->tipo == 2) {
            tamanho = (int)sizeof(float);
        } else if (atual->tipo == 3) {
            size_t comprimento = strlen((char *)atual->dados) + 1;

            if (comprimento > 10000) {
                sucesso = 0;
                break;
            }

            tamanho = (int)comprimento;
        } else {
            sucesso = 0;
            break;
        }

        if (fwrite(&atual->tipo, sizeof(int), 1, arquivo) != 1 ||
            fwrite(&tamanho, sizeof(int), 1, arquivo) != 1 ||
            fwrite(atual->dados, 1, (size_t)tamanho, arquivo)
                != (size_t)tamanho) {
            sucesso = 0;
            break;
        }

        atual = atual->proximo;
    }

    if (fclose(arquivo) != 0) {
        sucesso = 0;
    }

    return sucesso;
}

int carregar(No **lista, const char *nomeArquivo) {
    if (lista == NULL || nomeArquivo == NULL) {
        return 0;
    }

    FILE *arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    No *novaLista = NULL;
    No *ultimo = NULL;

    int tipo;
    int tamanho;
    int erro = 0;

    while (1) {
        size_t lidos = fread(&tipo, 1, sizeof(int), arquivo);

        if (lidos == 0 && feof(arquivo)) {
            break;
        }

        if (lidos != sizeof(int)) {
            erro = 1;
            break;
        }

        if (fread(&tamanho, sizeof(int), 1, arquivo) != 1) {
            erro = 1;
            break;
        }

        if ((tipo == 1 && tamanho != (int)sizeof(int)) ||
            (tipo == 2 && tamanho != (int)sizeof(float)) ||
            (tipo == 3 && (tamanho <= 0 || tamanho > 10000)) ||
            (tipo < 1 || tipo > 3)) {
            erro = 1;
            break;
        }

        No *novo = malloc(sizeof(No));

        if (novo == NULL) {
            erro = 1;
            break;
        }

        novo->dados = malloc((size_t)tamanho);

        if (novo->dados == NULL) {
            free(novo);
            erro = 1;
            break;
        }

        if (fread(novo->dados, 1, (size_t)tamanho, arquivo)
            != (size_t)tamanho) {
            free(novo->dados);
            free(novo);
            erro = 1;
            break;
        }

        if (tipo == 3 &&
            ((char *)novo->dados)[tamanho - 1] != '\0') {
            free(novo->dados);
            free(novo);
            erro = 1;
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

    if (ferror(arquivo)) {
        erro = 1;
    }

    if (fclose(arquivo) != 0) {
        erro = 1;
    }

    if (erro) {
        liberarLista(&novaLista);
        return 0;
    }

    liberarLista(lista);
    *lista = novaLista;

    return 1;
}

void liberarLista(No **lista) {
    if (lista == NULL) {
        return;
    }

    No *atual = *lista;

    while (atual != NULL) {
        No *proximo = atual->proximo;

        free(atual->dados);
        free(atual);

        atual = proximo;
    }

    *lista = NULL;
}
