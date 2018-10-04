#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gerar_matriz(int **matriz, int linha, int coluna, int valor);
int zerar_matriz (int **matriz, int linha, int coluna);
int imprimir_matriz (int **matriz, int linha, int coluna);
int **liberar_matriz (int **matriz, int linha, int coluna);
int **alocar_matriz (int linha, int coluna);
int somar (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M);
int multiplicar_static (int **mat_a, int **mat_b, int **mat_c, int linhas_1, int colunas_1, int linhas_2, int colunas_2, int numThreads);
int multiplicar_dynamic (int **mat_a, int **mat_b, int **mat_c, int linhas_1, int colunas_1, int linhas_2, int colunas_2, int numThreads);
int multiplicar_thread (int **mat_a, int **mat_b, int **mat_c, int linhas_1, int colunas_1, int linhas_2, int colunas_2, int numThreads);
int multiplicar_sequencial (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M);