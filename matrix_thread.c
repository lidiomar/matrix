#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int** preencheMatriz(int linhas, int colunas, int** matriz);
void mostraMatriz(int linhas, int colunas, int** matriz);
int** alocaMatriz(int linhas, int colunas);
void multiplica(int linhas, int colunas, int colunas2, int **matriz_1, int **matriz_2);
void* executaThread(void* param);

typedef struct {
	int id;
	int* linhaParaMultiplicar;
	int** matriz_2;
	int colunas;
	int colunas2;
	int* result;
} threadParams;

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
		params[i].colunas = colunas;
		params[i].colunas2 = colunas2;
		params[i].id = i;

		pthread_create(&threads[i], NULL, executaThread,(void*)&params[i]);
	}
	
	for (int i = 0; i < linhas; i++){
		pthread_join(threads[i], NULL);
		
		for(int j=0;j<colunas2;j++) {
			if(j == 0) {
				printf("|");
			}
			if(params[i].result[j] < 10)
				printf("  %d |", params[i].result[j]);
			else {
				printf(" %d |", params[i].result[j]);
			}
		}
		printf("\n");
   	}

}

void* executaThread(void* param) {
	threadParams *param_t;
	param_t = (threadParams*)param;
	int* linhaParaMultiplicar = param_t->linhaParaMultiplicar;
	int** matriz_2 = param_t->matriz_2;
	int colunas = param_t->colunas;
	int colunas2 = param_t->colunas2;
	int sum=0;

	param_t->result = malloc(colunas2 * sizeof(int));
	
	for(int i=0; i<colunas2;i++){
		for(int j=0; j<colunas; j++){
			sum+= linhaParaMultiplicar[j] * matriz_2[j][i];
		}
		param_t->result[i] = sum;
		sum=0;
	}

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

	return 0;
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
