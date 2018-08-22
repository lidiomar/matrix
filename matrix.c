#include <stdlib.h>
#include <stdio.h>

int** preencheMatriz(int linhas, int colunas, int** matriz);
void mostraMatriz(int linhas, int colunas, int** matriz);
int** alocaMatriz(int linhas, int colunas);
int** multiplica(int linhas, int colunas, int **matriz_1, int **matriz_2, int **matriz_3);

int main(int argc, char **argv) {

	int linhas = 2;
	int colunas = 2;
	int **matriz;
	int **matriz_2;
	int **matriz_3;

	matriz = alocaMatriz(linhas, colunas);
	mostraMatriz(linhas, colunas, matriz);

	matriz_2 = alocaMatriz(linhas, colunas);
	mostraMatriz(linhas, colunas, matriz_2);

	matriz_3 = alocaMatriz(linhas, colunas);
	matriz_3 = multiplica(linhas, colunas, matriz, matriz_2, matriz_3);
	mostraMatriz(linhas, colunas, matriz_3);

	return 0;
}


int** multiplica(int linhas, int colunas, int **matriz_1, int **matriz_2, int **matriz_3) {
	int soma = 0;

	for(int i=0; i<linhas; i++) {
		for(int j=0;j<colunas;j++) {
			for(int k=0;k<colunas;k++) {
				soma += matriz_1[i][k] * matriz_2[k][j];
			}
			matriz_3[i][j] = soma;
			soma = 0;
		}
		
	}

	return matriz_3;
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
