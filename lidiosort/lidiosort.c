#include <stdlib.h>
#include <stdio.h>

int gerar_matriz(int **matriz, int linhas, int colunas, int valor);
int **alocar_matriz (int linhas, int colunas);
int imprimir_matriz (int **matriz, int linhas, int colunas);
void ordena_linhas_matriz(int **matriz, int linhas, int colunas);
int **gera_transposta(int **matriz, int linhas, int colunas);
int **ordena_matriz(int **matriz, int linhas, int colunas);
void ordena_linha(int **matriz, int i, int colunas);

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

	printf("Matriz com linhas ordenadas (decrescente)\n");
	imprimir_matriz(matriz_1, linhas_1, colunas_1);
	matriz_1 = gera_transposta(matriz_1, linhas_1, colunas_1);

	printf("Matriz transposta\n");
	imprimir_matriz(matriz_1, linhas_1, colunas_1);
	ordena_linhas_matriz(matriz_1, linhas_1, colunas_1);

	printf("Matriz com linhas ordenadas (decrescente)\n");
	imprimir_matriz(matriz_1, linhas_1, colunas_1);

	matriz_1 = ordena_matriz(matriz_1, linhas_1, colunas_1);
	printf("Matriz ordenada\n");
	imprimir_matriz(matriz_1, linhas_1, colunas_1);

}


void ordena_linhas_matriz(int **matriz, int linhas, int colunas) {
	for(int i=0; i < linhas; i++) {
		for(int k=colunas-1; k>=0; k--) {
			for(int j=0; j<k;j++) {
				if(matriz[i][j] < matriz[i][j+1]) {
					int aux = matriz[i][j];
					matriz[i][j] = matriz[i][j+1];
					matriz[i][j+1] = aux;
				}
			}
		}
	}
}

int **ordena_matriz(int **matriz, int linhas, int colunas) {
	int **matriz_ordenada;
	matriz_ordenada = alocar_matriz(linhas, colunas);

	int k = colunas-1;
	int indice_menor;

	for(int h=0;h<linhas;h++) {
		for(int i=0;i<linhas;i++) {

			indice_menor = 0;
			for(int j=1; j<linhas;j++) {
				if(matriz[indice_menor][k] > matriz[j][k]) {
					indice_menor = j; 	
				}
			}
	
			matriz_ordenada[h][i] = matriz[indice_menor][k];
			matriz[indice_menor][k] = 9999999; 	
			ordena_linha(matriz,indice_menor,colunas);
		}		
	}
	return matriz_ordenada;
}

void ordena_linha(int **matriz, int i, int colunas) {

	for(int j=colunas-1;j>=0;j--) {
		for(int k=0;k<j;k++) {
			if(matriz[i][k] < matriz[i][k+1]) {
				int aux = matriz[i][k];
				matriz[i][k] = matriz[i][k+1];
				matriz[i][k+1] = aux;
			}
		}
	}
}

int **gera_transposta(int **matriz, int linhas, int colunas) {
	int **matriz_transposta;
	matriz_transposta = alocar_matriz(linhas, colunas);

	for(int i=0;i<linhas;i++) {
		for(int j=0; j<colunas; j++) {
			matriz_transposta[j][i] = matriz[i][j];
		}
	}

	return matriz_transposta;

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
