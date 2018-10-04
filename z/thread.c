#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

int** preencheMatriz(int linhas, int colunas, int** matriz);
void mostraMatriz(int linhas, int colunas, int** matriz);
int** alocaMatriz(int linhas, int colunas);
void multiplica(int linhas, int colunas, int colunas2, int **matriz_1, int **matriz_2);
void* executaThread(void* param);

typedef struct {
	int* linhaParaMultiplicar;
	int* colunaParaMultiplicar;
	int tam;
} threadParams;

typedef struct {
	pthread_t thread;
	bool disp;
} customThread;

int main(int argc, char **argv) {

	int linhas;
	int colunas;
	int linhas2;
	int colunas2;
	int **matriz;
	int **matriz_2;

	printf("Informe o número de linhas da matriz 1:\n");
	scanf("%d",&linhas);

	printf("Informe o número de colunas da matriz 1:\n");
	scanf("%d",&colunas);
	
	printf("Informe o número de linhas da matriz 2:\n");
	scanf("%d",&linhas2);

	if(linhas2 != colunas) {
		printf("O numero de colunas da matriz 1 deve ser igual ao número de linhas da matriz 2\n");
		return 0;
	}

	printf("Informe o número de colunas da matriz 2:\n");
	scanf("%d",&colunas2);

	matriz = alocaMatriz(linhas, colunas);
	mostraMatriz(linhas, colunas, matriz);

	printf(" x \n");

	matriz_2 = alocaMatriz(linhas2, colunas2);
	mostraMatriz(linhas2, colunas2, matriz_2);

	printf(" = \n\n");

	multiplica(linhas, colunas, colunas2, matriz, matriz_2);

	printf("\n");

	return 1;
}

void multiplica(int linhas, int colunas, int colunas2, int **matriz_1, int **matriz_2) {
	int count = 0;
	int numThreads = 3;
	customThread *customThreads;
	
	customThreads = malloc(numThreads * sizeof(customThread));
	
	for(int i=0; i<linhas; i++) {

		int* linhaParaMultiplicar;
		linhaParaMultiplicar = malloc(colunas * sizeof(int));

		for(int j=0; j<colunas;j++) {
			linhaParaMultiplicar[j] = matriz_1[i][j];
			printf("%d;", linhaParaMultiplicar[j]);
		}

		printf("\n");

		for(int k=0; k<colunas2; k++) {
			int* colunaParaMultiplicar;
			colunaParaMultiplicar = malloc(colunas * sizeof(int));

			for(int l=0; l<colunas; l++) {
				colunaParaMultiplicar[l] = matriz_2[l][k];
			}	

			threadParams params;
			params.linhaParaMultiplicar = linhaParaMultiplicar;
			params.colunaParaMultiplicar = colunaParaMultiplicar;
			params.tam = colunas;

			pthread_create(&customThreads[count].thread,NULL,executaThread,(void*) &params);	
			pthread_join(customThreads[count].thread,NULL);

			count++;
			if(count >= numThreads) {
				count = 0;
			}
		}

		printf("\n");

	}
}

void* executaThread(void* param) {
	threadParams* params = (threadParams*) param;
	int* linhaParaMultiplicar = params->linhaParaMultiplicar;
	int* colunaParaMultiplicar = params->colunaParaMultiplicar;
	int tam = params->tam;
	int sum=0;

	for(int i=0;i<tam;i++) {
		sum+= linhaParaMultiplicar[i] * colunaParaMultiplicar[i];
	}
	printf("%d\n", sum);

	return NULL;
}

int** alocaMatriz(int linhas, int colunas) {
	int **matriz;

	matriz = malloc(linhas * sizeof(int *));

	for(int i=0; i<linhas;i++) {
		matriz[i] = malloc(colunas * sizeof(int));
	}

	matriz = preencheMatriz(linhas, colunas, matriz);
	return matriz;
}

int** preencheMatriz(int linhas, int colunas, int** matriz) {

	for(int i=0;i<linhas;i++) {
		for(int j=0; j<colunas; j++) {
			matriz[i][j] = rand()%100;
		}
	}

	return matriz;
}

void mostraMatriz(int linhas, int colunas, int** matriz) {
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
}
