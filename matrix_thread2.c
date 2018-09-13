#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int imprimir_matriz (int **matriz, int linhas, int colunas);
int gerar_matriz(int **matriz, int linhas, int colunas, int valor);
int **alocar_matriz (int linhas, int colunas);
int multiplicar (int **mat_a, int **mat_b, int **mat_c, int linhas_1, int colunas_1, int linhas_2, int colunas_2, int numThreads);
void* executaThread(void* param);

typedef struct {
	int id;
	int** matriz_1;
	int** matriz_2;
	int** matriz_3;
	int linhas_1;
	int colunas_1;
	int linhas_2;
	int colunas_2;
	int* result;
	int numThreads;
} threadParams;

int main(int argc, char **argv) {

	int linhas_1;
	int colunas_1;
	int linhas_2;
	int colunas_2;
	int **matriz_1;
	int **matriz_2;
	int **matriz_3;
	int numThreads;
	

	printf("Informe o número de linhas da matriz 1:\n");
	scanf("%d",&linhas_1);

	printf("Informe o número de colunas da matriz 1:\n");
	scanf("%d",&colunas_1);
	
	printf("Informe o número de linhas da matriz 2:\n");
	scanf("%d",&linhas_2);

	if(linhas_2 != colunas_1) {
		printf("O numero de colunas da matriz 1 deve ser igual ao número de linhas da matriz 2\n");
		return 0;
	}

	printf("Informe o número de colunas da matriz 2:\n");
	scanf("%d",&colunas_2);

	printf("Informe o número de threads:\n");
	scanf("%d",&numThreads);

	if(numThreads > linhas_1) {
		printf("O numero de threads não pode ser maior que o número de linhas da matriz 1\n");
		return 0;
	}

	matriz_1 = alocar_matriz(linhas_1, colunas_1);
	gerar_matriz(matriz_1,linhas_1,colunas_1,1);
	imprimir_matriz(matriz_1, linhas_1, colunas_1);

	printf(" x \n");

	matriz_2 = alocar_matriz(linhas_2, colunas_2);
	gerar_matriz(matriz_2,linhas_2,colunas_2,1);
	imprimir_matriz(matriz_2, linhas_2, colunas_2);

	printf(" = \n\n");

	matriz_3 = alocar_matriz(linhas_1, colunas_2);
	multiplicar(matriz_1,matriz_2,matriz_3, linhas_1, colunas_1, linhas_2, colunas_2,numThreads);
	imprimir_matriz(matriz_3, linhas_1, colunas_2);
	return 1;
}

int gerar_matriz(int **matriz, int linhas, int colunas, int valor){
	for(int i=0;i<linhas;i++) {
		for(int j=0; j<colunas; j++) {
			if(valor != 0) {
				matriz[i][j] = rand()%100;
			}else {
				matriz[i][j] = 0;
			}
		}
	}

	return 0;
}

int zerar_matriz (int **mat, int l, int c){
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

int **liberar_matriz (int **mat, int l, int c) {
	return 0; 	 
}

int **alocar_matriz (int linhas, int colunas) {
	int **matriz;

	matriz = malloc(linhas * sizeof(int *));

	for(int i=0; i<linhas;i++) {
		matriz[i] = malloc(colunas * sizeof(int));
	}
	return matriz;
}

int multiplicar (int **mat_a, int **mat_b, int **mat_c, int linhas_1, int colunas_1, int linhas_2, int colunas_2, int numThreads) {
	pthread_t *threads;	
	threads = malloc(numThreads * sizeof(pthread_t));

	threadParams *params;
	params = malloc(numThreads * sizeof(threadParams));

	for(int i=0; i<numThreads; i++) {
		
		params[i].id = i;
		params[i].matriz_1 = mat_a;
		params[i].matriz_2 = mat_b;
		params[i].matriz_3 = mat_c;
		params[i].linhas_1 = linhas_1;
		params[i].linhas_2 = linhas_2;
		params[i].colunas_1 = colunas_1;
		params[i].colunas_2 = colunas_2;
		params[i].numThreads = numThreads;
		
		pthread_create(&threads[i], NULL, executaThread,(void*)&params[i]);
	}

	for (int i = 0; i < numThreads; i++){
		pthread_join(threads[i], NULL);
	}

	return 0;  
}

void* executaThread(void* param) {
	threadParams *param_t;
	param_t = (threadParams*)param;

	int id = param_t->id;
	int **matriz_1 = param_t->matriz_1;
	int **matriz_2 = param_t->matriz_2;
	int **matriz_3 = param_t->matriz_3;

	int linhas_1 = param_t->linhas_1;
	int colunas_1 = param_t->linhas_2;
	int linhas_2 = param_t->linhas_2;
	int colunas_2 = param_t->colunas_2;
	int numThreads = param_t->numThreads;
	int sum = 0;

	for(int i=id; i<linhas_1; i+= numThreads) {
		for(int j=0; j<colunas_2;j++) {
			for(int k=0; k<colunas_1;k++) {
				sum+= matriz_1[i][k] * matriz_2[k][j];
			}
			matriz_3[i][j] = sum;
			sum = 0;
		}
	}

	return NULL;
}
