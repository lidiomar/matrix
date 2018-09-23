#include <stdlib.h>
#include <stdio.h>

int gerar_matriz(int **matriz, int linhas, int colunas, int valor);
int imprimir_matriz (int **matriz, int linhas, int colunas);
int **alocar_matriz (int linhas, int colunas);
void ordena_bloco(int **matriz, int l, int m, int linhas, int colunas);

void ordena_linhas_matriz3(int **matriz, int linhas, int colunas, int x, int y);
void ordena_linhas_matriz(int **matriz, int linhas, int colunas);

int main(int argc, char **argv) {
	int linhas_1;
	int colunas_1;
	int **matriz_1;

	printf("Informe o número de linhas da matriz:\n");
	scanf("%d",&linhas_1);

	printf("Informe o número de colunas da matriz:\n");
	scanf("%d",&colunas_1);

	matriz_1 = alocar_matriz(linhas_1, colunas_1);
	gerar_matriz(matriz_1,linhas_1,colunas_1,1);
	printf("Matriz original\n");
	imprimir_matriz(matriz_1, linhas_1, colunas_1);
	ordena_linhas_matriz(matriz_1, linhas_1, colunas_1);
	printf("Matriz ordenada\n");
	imprimir_matriz(matriz_1, linhas_1, colunas_1);

}


void ordena_linhas_matriz2(int **matriz, int linhas, int colunas) {
	for(int i=0; i<colunas;i++) {
		ordena_bloco(matriz, 0, i, linhas, colunas);
	}
}

void ordena_bloco(int **matriz, int l, int m, int linhas, int colunas) {
	for(int j=0;j<colunas;j++) {
		printf("[%d][%d] -> [%d]\n",l, m, matriz[l][m] );
		m++;
		if(m >=colunas) {
			m = 0;
			l = l+1;

			if(l >= linhas) {
				l = 0;
			}
		}
	}
}
void ordena_linhas_matriz3(int **matriz, int linhas, int colunas, int x, int y) {
	int l;
	int m;
	int proxL;
	int proxM;
	
	for(int j=colunas-1;j>=0;j--) {
		l = 2;
		m = 1;
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
		
			if(matriz[l][m] > matriz[proxL][proxM]) {
				int aux = matriz[l][m];
				matriz[l][m] = matriz[proxL][proxM];
				matriz[proxL][proxM] = aux;
			}

			l = proxL;
			m = proxM;
		}	
	}
			
	
}

void ordena_linhas_matriz(int **matriz, int linhas, int colunas) {
	int l = 0;
	int m = 0;

	for(int w=0;w<colunas;w++) {
		m = w;
		
		for(int i=0;i<linhas;i++) {
				
			printf("[%d][%d]\n",i, w);
			ordena_linhas_matriz3(matriz, linhas, colunas, i, w);

			m = m + colunas;
			if(m >=colunas) {
				m = 0;
				l = l+1;

				if(l >= linhas) {
					l = 0;
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