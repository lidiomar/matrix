#include "ordenacao.h"
#include <pthread.h>
#include <omp.h>
#include <stdbool.h>

void* executaThread(void* param);

typedef struct {
	int id;
	int** matriz;
	int linhas;
	int colunas;
	int coluna;
	int numThreads;
} threadParams;

void ordena_matriz_seq(int **matriz, int linhas, int colunas) {
	for(int y=0; y<linhas;y++){ 
		for(int w=0;w<colunas;w++) {
			for(int i=0;i<linhas;i++) {
				int l;
				int m;
				int proxL;
				int proxM;
				
				for(int j=colunas-1;j>=0;j--) {
					l = i;
					m = w;
					bool ordered = true;
					for(int k=0;k<j;k++) {
						proxL = l;
						proxM = m+1;

						if(proxM >= colunas) {
							proxL++;
							proxM = 0;
							if(proxL >= linhas) {
								proxL = 0;
							}
						}
					
						if(matriz[l][m] > matriz[proxL][proxM] && proxL >= l) {
							int aux = matriz[l][m];
							matriz[l][m] = matriz[proxL][proxM];
							matriz[proxL][proxM] = aux;
							ordered = false;
						}

						l = proxL;
						m = proxM;
					}
					if(!ordered) {
						break;
					}
				}
			}
		}
	}
}

void ordena_matriz_thread(int **matriz_1, int linhas_1, int colunas_1, int numThreads) {
	int t = numThreads;

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
			bool ordered = true;
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
					ordered = false;
				}

				l = proxL;
				m = proxM;
			}
			if(!ordered) {
				break;
			}	
		}
	}

	return NULL;
}


void ordena_matriz_omp_static(int **matriz, int linhas, int colunas, int numThreads)  {
	
	for(int y=0; y<linhas;y++){ 
		#pragma omp parallel for num_threads(numThreads)
		{
			for(int w=0;w<colunas;w++) {
				for(int i=0;i<linhas;i++) {
					int l;
					int m;
					int proxL;
					int proxM;
					
					for(int j=colunas-1;j>=0;j--) {
						l = i;
						m = w;
						bool ordered = true;
						for(int k=0;k<j;k++) {
							proxL = l;
							proxM = m+1;

							if(proxM >= colunas) {
								proxL++;
								proxM = 0;
								if(proxL >= linhas) {
									proxL = 0;
								}
							}
						
							if(matriz[l][m] > matriz[proxL][proxM] && proxL >= l) {
								int aux = matriz[l][m];
								matriz[l][m] = matriz[proxL][proxM];
								matriz[proxL][proxM] = aux;
								ordered = false;
							}

							l = proxL;
							m = proxM;
						}
						if(!ordered) {
							break;
						}
					}
				}
			}
		}
	}

}


void ordena_matriz_omp_dynamic(int **matriz, int linhas, int colunas, int numThreads)  {
	
	for(int y=0; y<linhas;y++){
		#pragma omp parallel for schedule(dynamic) num_threads(numThreads)
		{ 
			for(int w=0;w<colunas;w++) {
				for(int i=0;i<linhas;i++) {
					int l;
					int m;
					int proxL;
					int proxM;
					
					for(int j=colunas-1;j>=0;j--) {
						l = i;
						m = w;
						bool ordered = true;
						for(int k=0;k<j;k++) {
							proxL = l;
							proxM = m+1;

							if(proxM >= colunas) {
								proxL++;
								proxM = 0;
								if(proxL >= linhas) {
									proxL = 0;
								}
							}
						
							if(matriz[l][m] > matriz[proxL][proxM] && proxL >= l) {
								int aux = matriz[l][m];
								matriz[l][m] = matriz[proxL][proxM];
								matriz[proxL][proxM] = aux;
								ordered = false;
							}

							l = proxL;
							m = proxM;
						}
						if(!ordered) {
							break;
						}
					}
				}
			}
		}
	}
	
}


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