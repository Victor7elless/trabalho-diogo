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
    return 0;
}