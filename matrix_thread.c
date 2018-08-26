#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int** preencheMatriz(int linhas, int colunas, int** matriz);
void mostraMatriz(int linhas, int colunas, int** matriz);
int** alocaMatriz(int linhas, int colunas);
int** multiplica(int linhas, int colunas, int **matriz_1, int **matriz_2, int **matriz_3);
void* chamaThread(void* param);

typedef struct {
	int* linhaParaMultiplicar;
	int** matriz_2;
	int linhas;
	int colunas;
	int id;
} threadParams;

int main(int argc, char **argv) {

	int linhas = 2;
	int colunas = 2;
	int **matriz;
	int **matriz_2;
	int **matriz_3;

	matriz = alocaMatriz(linhas, colunas);
	mostraMatriz(linhas, colunas, matriz);

	printf(" x \n");

	matriz_2 = alocaMatriz(linhas, colunas);
	mostraMatriz(linhas, colunas, matriz_2);

	matriz_3 = alocaMatriz(linhas, colunas);
	matriz_3 = multiplica(linhas, colunas, matriz, matriz_2, matriz_3);

	return 0;
}


int** multiplica(int linhas, int colunas, int **matriz_1, int **matriz_2, int **matriz_3) {
	int soma = 0;
	pthread_t *threads;
	threadParams *params;

	threads = malloc(linhas * sizeof(pthread_t));
	params = malloc(linhas * sizeof(threadParams));

	for(int i=0; i<linhas; i++) {
		int* linhaParaMultiplicar;
		linhaParaMultiplicar = malloc(colunas * sizeof(int));

		for(int j=0; j<colunas;j++) {
			linhaParaMultiplicar[j] = matriz_1[i][j];
		}
		
			
		params[i].linhaParaMultiplicar = linhaParaMultiplicar;
		params[i].matriz_2 = matriz_2;
		params[i].linhas = linhas;
		params[i].colunas = colunas;
		params[i].id = i;

		pthread_create(&threads[i], NULL, chamaThread,(void*)&params[i]);
		//chamaThread((void*)&params);
	}

	for (int i = 0; i < linhas; i++){
		pthread_join(threads[i], NULL);
   	}

	return NULL;
}

void* chamaThread(void* param) {
	threadParams *param_t;
	param_t = (threadParams*)param;

	printf("Thread: %d\n", param_t->id);

	int* linhaParaMultiplicar = param_t->linhaParaMultiplicar;
	int** matriz_2 = param_t->matriz_2;
	int linhas = param_t->linhas;
	int colunas = param_t->colunas;
	int sum=0;

	
	for(int i=0; i<colunas;i++) {
		for(int j=0; j<linhas;j++) {
			sum+= linhaParaMultiplicar[j] * matriz_2[j][i];
		}
		printf("%d\n",sum);
		sum=0;
	}
	return NULL;
}

int** alocaMatriz(int linhas, int colunas) {
	int **matriz;

	matriz = malloc(linhas * sizeof(int *));

	for(int i=0; i<colunas;i++) {
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
