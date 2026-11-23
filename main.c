#include <stdio.h>
#include "lista.h"

int main() {
    No *lista = NULL;
    
    int numero = 25;
    float decimal = 8.5;
    char texto[] = "Olá, mundo!";

    inserir(&lista, 1, &numero);
    inserir(&lista, 2, &decimal);
    inserir(&lista, 3, texto);

    imprimir(lista);
    printf("\n=== Busca de elementos ===\n");
    int procurado = 25;
    No *resultado = buscar(lista, 1, &procurado);

    if (resultado != NULL) {
        printf("Elemento encontrado: %d\n", *(int *)resultado->dados);
    } else {
        printf("Elemento não encontrado.\n");
    }

    printf("\n=== Remoção de elementos ===\n");
    float valorRemover = 8.5;
    if (remover(&lista, 2, &valorRemover)) {
        printf("Elemento removido com sucesso.\n");
    } else {
        printf("Elemento não encontrado para remoção.\n");
    }

    imprimir(lista);

    
    printf("\n=== Salvando lista em arquivo ===\n");
    if (salvar(lista, "lista.bin")) {
        printf("Lista salva com sucesso.\n");
    } else {
        printf("Erro ao salvar a lista.\n");
    }

    // Testando o carregamento do arquivo binario
    printf("\n=== TESTE DE CARREGAMENTO ===\n");

    if (carregar(&lista, "lista.bin")) {
        printf("Lista carregada com sucesso!\n");
        imprimir(lista);
    } else {
        printf("Erro ao carregar a lista!\n");
    }


    return 0;
}