#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int gerar_matriz(int **matriz, int linhas, int colunas, int valor);
int imprimir_matriz (int **matriz, int linhas, int colunas);
int **alocar_matriz (int linhas, int colunas);
void ordena_matriz(int **matriz, int linhas, int colunas);
double wtime();

int main(int argc, char **argv) {
	int linhas = 3;
	int colunas = 3;
	int **matriz_1;
	double start_time, end_time;
	

	matriz_1 = alocar_matriz(linhas, colunas);

	gerar_matriz(matriz_1,linhas,colunas,1);
	imprimir_matriz(matriz_1,linhas,colunas);

	start_time = wtime();
	ordena_matriz(matriz_1, linhas, colunas);
	end_time = wtime();
	printf("Runtime: %f\n", end_time - start_time);
	imprimir_matriz(matriz_1,linhas,colunas);
}

double wtime() {
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec + (double) t.tv_usec / 1000000;
}

void ordena_matriz(int **matriz, int linhas, int colunas) {
	#pragma  omp parallel
	{
		for(int g=0; g<linhas;g++){
			for(int h=0;h<colunas;h++) {
				for(int i=0;i<linhas;i++) {

					int l;
					int m;
					int proxL;
					int proxM;
					
					for(int j=colunas-1;j>=0;j--) {
						l = h;
						m = i;
						for(int k=0;k<j;k++) {
							proxL = l;
							proxM = m+1;

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
			}
		}
	}
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