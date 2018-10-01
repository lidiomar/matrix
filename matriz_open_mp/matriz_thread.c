#include "matriz_thread.h"
#include <pthread.h>

int zerar_matriz (int **matriz, int linha, int coluna){
	return gerar_matriz(matriz,linha,coluna,0);
}


int gerar_matriz(int **matriz, int linha, int coluna, int valor){
	for (int i=0; i < linha; i++)
	  for (int j=0; j < coluna; j++)
	        if (valor == -9999)
				matriz[i][j] = rand() % 100;
	        else
				matriz[i][j] = valor;
	return 0;
}

int imprimir_matriz (int **matriz, int linhas, int colunas){
	for(int i=0;i<linhas;i++) {
		printf("\n");
		for(int j=0; j<colunas; j++) {
			if(j == 0) {
				printf("|");
			}

			if(matriz[i][j] < 10)
				printf("  %d |", matriz[i][j]);
			else {
				printf(" %d |", matriz[i][j]);
			}

		}
	}
	printf("\n\n");
	return 1; 
}

int **liberar_matriz (int **matriz, int linha, int coluna) {
    for (int i =0; i < linha; i++)
		free(matriz[i]);
    free(matriz);
    return NULL;
}

int **alocar_matriz (int linhas, int colunas) {
	int **matriz;

	matriz = malloc(linhas * sizeof(int *));

	for(int i=0; i<linhas;i++) {
		matriz[i] = malloc(colunas * sizeof(int));
	}
	return matriz;
}

int multiplicar (int **matriz_1, int **matriz_2, int **matriz_3, int linhas_1, int colunas_1, int linhas_2, int colunas_2, int numThreads) {
	int sum = 0;

	#pragma omp parallell reduction(+:sum)
	{
		for(int i=0; i<linhas_1; i++) {
			for(int j=0; j<colunas_2;j++) {
				for(int k=0; k<colunas_1;k++) {
					sum+= matriz_1[i][k] * matriz_2[k][j];
				}
				matriz_3[i][j] = sum;
				sum = 0;
			}
		}
	}
	return 0;  
}

int somar (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
	// if ((N != M) || (N != L) || (L != M)) {
	//      printf("ERRO: != NxMxL\n");
	//      exit (1);
	// }
	for (int i=0; i < N; i++)
	  for (int j=0; j < M; j++)
		mat_c[i][j] = mat_a[i][j]+mat_b[i][j];
  return 0;
}


