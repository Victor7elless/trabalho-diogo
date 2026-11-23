# Lista Encadeada Heterogênea em C

## Descrição

Projeto desenvolvido para a disciplina de Programação de Computadores I, do curso de Sistemas de Informação da UEMS.

O programa implementa uma lista simplesmente encadeada que permite armazenar diferentes tipos de dados utilizando ponteiros genéricos (`void *`) e alocação dinâmica de memória.

## Funcionalidades

- Inserir elementos dos tipos inteiro, decimal e texto.
- Remover elementos da lista.
- Buscar elementos por tipo e valor.
- Imprimir os elementos armazenados.
- Salvar a lista em arquivo binário.
- Carregar os elementos de um arquivo binário.
- Liberar a memória alocada ao encerrar.

## Estrutura do projeto

- `main.c` — menu interativo.
- `lista.c` — implementação das operações.
- `lista.h` — estrutura do nó e declarações das funções.

## Compilação

```bash
gcc -Wall -Wextra main.c lista.c -o programa
```

## Execução

```bash
./programa
```

## Funcionamento

Cada nó contém um ponteiro para o próximo elemento, um identificador do tipo de dado e um ponteiro genérico para o valor armazenado.

A lista utiliza alocação dinâmica com `malloc()` e liberação de memória com `free()`.

Os dados são salvos no arquivo `lista.bin`, permitindo recuperá-los posteriormente.

## Tecnologias

- Linguagem C
- GCC
- Git e GitHub
