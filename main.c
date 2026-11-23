
#include <stdio.h>
#include "lista.h"

void limparEntrada(void) {
    int caractere;

    while ((caractere = getchar()) != '\n' &&
           caractere != EOF) {
    }
}

int lerInteiro(const char *mensagem, int *valor) {
    printf("%s", mensagem);

    if (scanf("%d", valor) != 1) {
        limparEntrada();
        return 0;
    }

    limparEntrada();
    return 1;
}

int lerDecimal(const char *mensagem, float *valor) {
    printf("%s", mensagem);

    if (scanf("%f", valor) != 1) {
        limparEntrada();
        return 0;
    }

    limparEntrada();
    return 1;
}

int lerTexto(const char *mensagem, char *texto, int tamanho) {
    printf("%s", mensagem);

    if (fgets(texto, tamanho, stdin) == NULL) {
        return 0;
    }

    int i = 0;

    while (texto[i] != '\0' && texto[i] != '\n') {
        i++;
    }

    if (texto[i] == '\n') {
        texto[i] = '\0';
    } else if (texto[i] != '\0') {
        limparEntrada();
    }

    return i > 0;
}

int main(void) {
    No *lista = NULL;
    int opcao = -1;

    do {
        printf("\n===== LISTA ENCADEADA =====\n");
        printf("1 - Inserir elemento\n");
        printf("2 - Remover elemento\n");
        printf("3 - Buscar elemento\n");
        printf("4 - Imprimir lista\n");
        printf("5 - Salvar lista\n");
        printf("6 - Carregar lista\n");
        printf("0 - Sair\n");

        if (!lerInteiro("Escolha uma opcao: ", &opcao)) {
            printf("Entrada invalida!\n");
            continue;
        }

        switch (opcao) {
            case 1: {
                int tipo;

                printf("\n=== INSERIR ELEMENTO ===\n");
                printf("1 - Inteiro\n");
                printf("2 - Decimal\n");
                printf("3 - Texto\n");

                if (!lerInteiro("Escolha o tipo: ", &tipo)) {
                    printf("Tipo invalido!\n");
                    break;
                }

                if (tipo == 1) {
                    int numero;

                    if (!lerInteiro("Digite um numero inteiro: ", &numero)) {
                        printf("Numero invalido!\n");
                        break;
                    }

                    if (inserir(&lista, 1, &numero)) {
                        printf("Inteiro inserido com sucesso!\n");
                    } else {
                        printf("Erro ao inserir inteiro!\n");
                    }
                } else if (tipo == 2) {
                    float decimal;

                    if (!lerDecimal("Digite um numero decimal: ", &decimal)) {
                        printf("Numero invalido!\n");
                        break;
                    }

                    if (inserir(&lista, 2, &decimal)) {
                        printf("Decimal inserido com sucesso!\n");
                    } else {
                        printf("Erro ao inserir decimal!\n");
                    }
                } else if (tipo == 3) {
                    char texto[256];

                    if (!lerTexto("Digite um texto: ", texto, sizeof(texto))) {
                        printf("Texto invalido!\n");
                        break;
                    }

                    if (inserir(&lista, 3, texto)) {
                        printf("Texto inserido com sucesso!\n");
                    } else {
                        printf("Erro ao inserir texto!\n");
                    }
                } else {
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

                if (!lerInteiro("Escolha o tipo: ", &tipo)) {
                    printf("Tipo invalido!\n");
                    break;
                }

                if (tipo == 1) {
                    int numero;

                    if (!lerInteiro("Digite o inteiro que deseja remover: ", &numero)) {
                        printf("Numero invalido!\n");
                        break;
                    }

                    if (remover(&lista, 1, &numero)) {
                        printf("Elemento removido com sucesso!\n");
                    } else {
                        printf("Elemento nao encontrado!\n");
                    }
                } else if (tipo == 2) {
                    float decimal;

                    if (!lerDecimal("Digite o decimal que deseja remover: ", &decimal)) {
                        printf("Numero invalido!\n");
                        break;
                    }

                    if (remover(&lista, 2, &decimal)) {
                        printf("Elemento removido com sucesso!\n");
                    } else {
                        printf("Elemento nao encontrado!\n");
                    }
                } else if (tipo == 3) {
                    char texto[256];

                    if (!lerTexto("Digite o texto que deseja remover: ", texto, sizeof(texto))) {
                        printf("Texto invalido!\n");
                        break;
                    }

                    if (remover(&lista, 3, texto)) {
                        printf("Elemento removido com sucesso!\n");
                    } else {
                        printf("Elemento nao encontrado!\n");
                    }
                } else {
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

                if (!lerInteiro("Escolha o tipo: ", &tipo)) {
                    printf("Tipo invalido!\n");
                    break;
                }

                if (tipo == 1) {
                    int numero;

                    if (!lerInteiro("Digite o inteiro que deseja buscar: ", &numero)) {
                        printf("Numero invalido!\n");
                        break;
                    }

                    resultado = buscar(lista, 1, &numero);
                } else if (tipo == 2) {
                    float decimal;

                    if (!lerDecimal("Digite o decimal que deseja buscar: ", &decimal)) {
                        printf("Numero invalido!\n");
                        break;
                    }

                    resultado = buscar(lista, 2, &decimal);
                } else if (tipo == 3) {
                    char texto[256];

                    if (!lerTexto("Digite o texto que deseja buscar: ", texto, sizeof(texto))) {
                        printf("Texto invalido!\n");
                        break;
                    }

                    resultado = buscar(lista, 3, texto);
                } else {
                    printf("Tipo invalido!\n");
                    break;
                }

                if (resultado != NULL) {
                    printf("Elemento encontrado!\n");

                    if (resultado->tipo == 1) {
                        printf("Valor: %d\n", *(int *)resultado->dados);
                    } else if (resultado->tipo == 2) {
                        printf("Valor: %.2f\n", *(float *)resultado->dados);
                    } else if (resultado->tipo == 3) {
                        printf("Valor: %s\n", (char *)resultado->dados);
                    }
                } else {
                    printf("Elemento nao encontrado!\n");
                }

                break;
            }

            case 4:
                imprimir(lista);
                break;

            case 5:
                printf("\n=== SALVAR LISTA ===\n");

                if (salvar(lista, "lista.bin")) {
                    printf("Lista salva com sucesso!\n");
                } else {
                    printf("Erro ao salvar a lista!\n");
                }
                break;

            case 6:
                printf("\n=== CARREGAR LISTA ===\n");

                if (carregar(&lista, "lista.bin")) {
                    printf("Lista carregada com sucesso!\n");
                    imprimir(lista);
                } else {
                    printf("Erro ao carregar a lista!\n");
                }
                break;

            case 0:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opção invalida!\n");
                break;
        }

    } while (opcao != 0);

    liberarLista(&lista);

    printf("Memoria liberada com sucesso!\n");

    return 0;
}
