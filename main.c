
#include <stdio.h>
#include "lista.h"

int main() {
    No *lista = NULL;
    int opcao;

    do {
        printf("\n===== LISTA ENCADEADA =====\n");
        printf("1 - Inserir elemento\n");
        printf("2 - Remover elemento\n");
        printf("3 - Buscar elemento\n");
        printf("4 - Imprimir lista\n");
        printf("5 - Salvar lista\n");
        printf("6 - Carregar lista\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            break;
        }

        switch (opcao) {
            
case 1: {
    int tipo;

    printf("\n=== INSERIR ELEMENTO ===\n");
    printf("1 - Inteiro\n");
    printf("2 - Decimal\n");
    printf("3 - Texto\n");
    printf("Escolha o tipo: ");

    if (scanf("%d", &tipo) != 1) {
        printf("Tipo invalido!\n");
        return 1;
    }

    if (tipo == 1) {
        int numero;

        printf("Digite um numero inteiro: ");
        if (scanf("%d", &numero) != 1) {
            printf("Numero invalido!\n");
            return 1;
        }

        if (inserir(&lista, 1, &numero)) {
            printf("Inteiro inserido com sucesso!\n");
        }
    }
    else if (tipo == 2) {
        float decimal;

        printf("Digite um numero decimal: ");
        if (scanf("%f", &decimal) != 1) {
            printf("Numero invalido!\n");
            return 1;
        }

        if (inserir(&lista, 2, &decimal)) {
            printf("Decimal inserido com sucesso!\n");
        }
    }
    else if (tipo == 3) {
        char texto[256];

        printf("Digite um texto: ");
        scanf(" %255[^\n]", texto);

        if (inserir(&lista, 3, texto)) {
            printf("Texto inserido com sucesso!\n");
        }
    }
    else {
        printf("Tipo invalido!\n");
    }

    break;
}


            
case 2: {
    int tipo;

    printf("\n=== REMOVER ELEMENTO ===\n");
    printf("1 - Inteiro\n");
    printf("2 - Decimal\n");
    printf("3 - Texto\n");
    printf("Escolha o tipo: ");

    if (scanf("%d", &tipo) != 1) {
        printf("Tipo invalido!\n");
        return 1;
    }

    if (tipo == 1) {
        int numero;

        printf("Digite o inteiro que deseja remover: ");
        if (scanf("%d", &numero) != 1) {
            printf("Numero invalido!\n");
            return 1;
        }

        if (remover(&lista, 1, &numero)) {
            printf("Elemento removido com sucesso!\n");
        } else {
            printf("Elemento nao encontrado!\n");
        }
    }
    else if (tipo == 2) {
        float decimal;

        printf("Digite o decimal que deseja remover: ");
        if (scanf("%f", &decimal) != 1) {
            printf("Numero invalido!\n");
            return 1;
        }

        if (remover(&lista, 2, &decimal)) {
            printf("Elemento removido com sucesso!\n");
        } else {
            printf("Elemento nao encontrado!\n");
        }
    }
    else if (tipo == 3) {
        char texto[256];

        printf("Digite o texto que deseja remover: ");
        if (scanf(" %255[^\n]", texto) != 1) {
            printf("Texto invalido!\n");
            return 1;
        }

        if (remover(&lista, 3, texto)) {
            printf("Elemento removido com sucesso!\n");
        } else {
            printf("Elemento nao encontrado!\n");
        }
    }
    else {
        printf("Tipo invalido!\n");
    }

    break;
}


            
case 3: {
    int tipo;
    No *resultado = NULL;

    printf("\n=== BUSCAR ELEMENTO ===\n");
    printf("1 - Inteiro\n");
    printf("2 - Decimal\n");
    printf("3 - Texto\n");
    printf("Escolha o tipo: ");

    if (scanf("%d", &tipo) != 1) {
        printf("Tipo invalido!\n");
        return 1;
    }

    if (tipo == 1) {
        int numero;

        printf("Digite o inteiro que deseja buscar: ");
        if (scanf("%d", &numero) != 1) {
            printf("Numero invalido!\n");
            return 1;
        }

        resultado = buscar(lista, 1, &numero);
    }
    else if (tipo == 2) {
        float decimal;

        printf("Digite o decimal que deseja buscar: ");
        if (scanf("%f", &decimal) != 1) {
            printf("Numero invalido!\n");
            return 1;
        }

        resultado = buscar(lista, 2, &decimal);
    }
    else if (tipo == 3) {
        char texto[256];

        printf("Digite o texto que deseja buscar: ");
        if (scanf(" %255[^\n]", texto) != 1) {
            printf("Texto invalido!\n");
            return 1;
        }

        resultado = buscar(lista, 3, texto);
    }
    else {
        printf("Tipo invalido!\n");
        break;
    }

    if (resultado != NULL) {
        printf("Elemento encontrado!\n");

        if (resultado->tipo == 1) {
            printf("Valor: %d\n", *(int *)resultado->dados);
        }
        else if (resultado->tipo == 2) {
            printf("Valor: %.2f\n", *(float *)resultado->dados);
        }
        else if (resultado->tipo == 3) {
            printf("Valor: %s\n", (char *)resultado->dados);
        }
    }
    else {
        printf("Elemento nao encontrado!\n");
    }

    break;
}

            case 4:
                imprimir(lista);
                break;

            
case 5: {
    printf("\n=== SALVAR LISTA ===\n");

    if (salvar(lista, "lista.bin")) {
        printf("Lista salva com sucesso!\n");
    } else {
        printf("Erro ao salvar a lista!\n");
    }

    break;
}


            
case 6: {
    printf("\n=== CARREGAR LISTA ===\n");

    if (carregar(&lista, "lista.bin")) {
        printf("Lista carregada com sucesso!\n");
        imprimir(lista);
    } else {
        printf("Erro ao carregar a lista!\n");
    }

    break;
}


            case 0:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

liberarLista(&lista);

printf("Memoria liberada com sucesso!\n");

return 0;
}
