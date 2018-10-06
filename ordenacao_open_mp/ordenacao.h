#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ordena_matriz_seq(int **matriz, int linhas, int colunas);
void ordena_matriz_thread(int **matriz, int linhas, int colunas, int numThreads);
void ordena_matriz_omp_static(int **matriz, int linhas, int colunas, int numThreads);
void ordena_matriz_omp_dynamic(int **matriz, int linhas, int colunas, int numThreads);


int gerar_matriz(int **matriz, int linha, int coluna, int valor);
int zerar_matriz (int **matriz, int linha, int coluna);
int imprimir_matriz (int **matriz, int linha, int coluna);
int **liberar_matriz (int **matriz, int linha, int coluna);
int **alocar_matriz (int linha, int coluna);