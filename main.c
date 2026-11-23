#include <stdio.h>
#include "lista.h"

int main() {
    No *lista = NULL;
    
    int numero = 25;

    inserir(&lista, 1, &numero);

    printf ("=== LISTA ENCADEADA ===\n");

    if (lista != NULL) {
        printf("Valor inserido: %d\n", 
            *(int *)lista->dados);
    }
    return 0;
}