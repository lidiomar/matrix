#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

int gerar_matriz(int **matriz, int linhas, int colunas, int valor);
int imprimir_matriz (int **matriz, int linhas, int colunas);
int **alocar_matriz (int linhas, int colunas);
void bla(int **matriz_1, int linhas_1, int colunas_1);
void* executaThread(void* param);
double wtime();

typedef struct {
	int id;
	int** matriz;
	int linhas;
	int colunas;
	int coluna;
	int numThreads;
} threadParams;

int main(int argc, char **argv) {
	int linhas_1;
	int colunas_1;
	int **matriz_1;
	double start_time, end_time;

	printf("Informe o número de linhas da matriz:\n");
	scanf("%d",&linhas_1);

	printf("Informe o número de colunas da matriz:\n");
	scanf("%d",&colunas_1);

	matriz_1 = alocar_matriz(linhas_1, colunas_1);
	gerar_matriz(matriz_1,linhas_1,colunas_1,1);
	
	start_time = wtime();
	bla(matriz_1, linhas_1, colunas_1);
	end_time = wtime();

	imprimir_matriz(matriz_1, linhas_1, colunas_1);
	printf("Runtime: %f\n", end_time - start_time);
}

double wtime() {
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec + (double) t.tv_usec / 1000000;
}

void bla(int **matriz_1, int linhas_1, int colunas_1) {
	int t = 2;

	for(int z=0;z<linhas_1;z++) 
		for(int w=0;w<colunas_1;w++) {

			pthread_t *threads;	
			threads = malloc(t * sizeof(pthread_t));

			threadParams *params;
			params = malloc(t * sizeof(threadParams));

			for(int i=0;i<t;i++) {	
				params[i].id = i;
				params[i].matriz = matriz_1;
				params[i].linhas = linhas_1;
				params[i].colunas = colunas_1;
				params[i].coluna = w;
				params[i].numThreads = t;
				
				pthread_create(&threads[i], NULL, executaThread,(void*)&params[i]);
			}
			
			for (int i = 0; i < t; i++){
				pthread_join(threads[i], NULL);
			}

			free(threads);
			free(params);
		}
}

void* executaThread(void* param) {
	threadParams *param_t;
	param_t = (threadParams*)param;

	int **matriz = param_t->matriz;
	int linhas = param_t->linhas;
	int colunas = param_t->colunas;
	int id = param_t->id;
	int w = param_t->coluna;
	int t = param_t->numThreads;
	 
	for(int i=id;i<linhas;i+=t) {
		
		int l;
		int m;
		int proxL;
		int proxM;
		
		for(int j=colunas-1;j>=0;j--) {
			l = i;
			m = w;
			for(int k=0;k<j;k++) {
				proxM = m+1;
				proxL = l;

				if(proxM >= colunas) {
					proxM = 0;
					proxL++;
					if(proxL >= linhas) {
						proxL = 0;
					}
				}
			
				if(matriz[l][m] > matriz[proxL][proxM] && proxL >= l) {
					int aux = matriz[l][m];
					matriz[l][m] = matriz[proxL][proxM];
					matriz[proxL][proxM] = aux;
				}

				l = proxL;
				m = proxM;
			}	
		}
	}

	return NULL;
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

int **alocar_matriz (int linhas, int colunas) {
	int **matriz;

	matriz = malloc(linhas * sizeof(int *));

	for(int i=0; i<linhas;i++) {
		matriz[i] = malloc(colunas * sizeof(int));
	}
	return matriz;
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