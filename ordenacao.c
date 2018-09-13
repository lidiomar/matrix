#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int imprimir_matriz (int **matriz, int linhas, int colunas);
int gerar_matriz(int **matriz, int linhas, int colunas, int valor);
int **alocar_matriz (int linhas, int colunas);
int ordenar (int **mat_a, int linhas_1, int colunas_1,int numThreads);
void* executaThread(void* param);

typedef struct {
	int id;
	int** matriz_1;
	int linhas_1;
	int colunas_1;
	int numThreads;
} threadParams;

int main(int argc, char **argv) {

	int linhas_1;
	int colunas_1;
	int **matriz_1;
	int numThreads;
	

	printf("Informe o número de linhas da matriz:\n");
	scanf("%d",&linhas_1);

	printf("Informe o número de colunas da matriz:\n");
	scanf("%d",&colunas_1);
	
	printf("Informe o número de threads:\n");
	scanf("%d",&numThreads);

	if(numThreads > linhas_1) {
		printf("O numero de threads não pode ser maior que o número de linhas da matriz 1\n");
		return 0;
	}

	matriz_1 = alocar_matriz(linhas_1, colunas_1);
	gerar_matriz(matriz_1,linhas_1,colunas_1,1);
	imprimir_matriz(matriz_1, linhas_1, colunas_1);
	ordenar(matriz_1,linhas_1,colunas_1,numThreads);
	imprimir_matriz(matriz_1, linhas_1, colunas_1);

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

int ordenar (int **mat_a, int linhas_1, int colunas_1,int numThreads) {
	pthread_t *threads;	
	threads = malloc(numThreads * sizeof(pthread_t));

	threadParams *params;
	params = malloc(numThreads * sizeof(threadParams));

	for(int i=0; i<numThreads; i++) {
		
		params[i].id = i;
		params[i].matriz_1 = mat_a;
		params[i].linhas_1 = linhas_1;
		params[i].colunas_1 = colunas_1;
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
	int linhas_1 = param_t->linhas_1;
	int colunas_1 = param_t->colunas_1;
	int numThreads = param_t->numThreads;
	int sum = 0;

	for(int i=id; i<linhas_1; i+= numThreads) {

		for(int j=1; j<colunas_1;j++) {
			int k = j-1;
			int value = matriz_1[i][j];	
			
			while(k >= 0 && matriz_1[i][k] > value) {
				
				matriz_1[i][k+1] = matriz_1[i][k];
				k = k-1;
			}
			matriz_1[i][k+1] = value;
		
		}
			
	}




	return NULL;
}
