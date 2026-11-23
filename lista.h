#ifndef LISTA_H
#define LISTA_H

typedef struct No {
    struct No *proximo;
    int tipo;
    void *dados;
} No;

int inserir(No **lista, int tipo, void *dados);

void imprimir(No *lista);

#endif


