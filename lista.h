#ifndef LISTA_H
#define LISTA_H

typedef struct No {
    struct No *proximo;
    int tipo;
    void *dados;
} No;

int inserir(No **lista, int tipo, void *dados);

void imprimir(No *lista);

No *buscar(No *lista, int tipo, void *dados);

int remover(No **lista, int tipo, void *dados);

int salvar(No *lista, const char *nomeArquivo);

int carregar(No **lista, const char *nomeArquivo);

void liberarLista(No **lista);

#endif


