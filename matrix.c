#include <stdlib.h>
#include <stdio.h>

int** preencheMatriz(int linhas, int colunas, int** matriz);
void mostraMatriz(int linhas, int colunas, int** matriz);
int** alocaMatriz(int linhas, int colunas);
int** multiplica(int linhas, int colunas, int colunas2, int **matriz_1, int **matriz_2, int **matriz_3);

int main(int argc, char **argv) {
	int linhas;
	int colunas;
	int linhas2;
	int colunas2;
	int **matriz;
	int **matriz_2;
	int **matriz_3;

	printf("Informe o número de linhas da matriz 1:\n");
	scanf("%d",&linhas);

	printf("Informe o número de colunas da matriz 1:\n");
	scanf("%d",&colunas);
	
	printf("Informe o número de linhas da matriz 2:\n");
	scanf("%d",&linhas2);

	if(linhas2 != colunas) {
		printf("O numero de colunas da matriz 1 deve ser igual ao número de linhas da matriz 2\n");
	}

	printf("Informe o número de colunas da matriz 2:\n");
	scanf("%d",&colunas2);


	printf("linhas %d\n", linhas);
	printf("linhas* %d\n", linhas2);
	printf("colunas %d\n", colunas);
	printf("colunas* %d\n", colunas2);

	matriz = alocaMatriz(linhas, colunas);
	mostraMatriz(linhas, colunas, matriz);

	matriz_2 = alocaMatriz(linhas2, colunas2);
	mostraMatriz(linhas2, colunas2, matriz_2);

	matriz_3 = alocaMatriz(linhas, colunas);
	matriz_3 = multiplica(linhas, colunas, colunas2, matriz, matriz_2, matriz_3);
	mostraMatriz(linhas, colunas2, matriz_3);

	return 0;
}


int** multiplica(int linhas, int colunas, int colunas2, int **matriz_1, int **matriz_2, int **matriz_3) {
	int soma = 0;

	for(int i=0; i<linhas; i++) {
		for(int j=0;j<colunas2;j++) {
			for(int k=0;k<colunas;k++) {
				printf("%d %d %d %d\n",i,k,k,j );
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
	
	for(int i=0; i<linhas;i++) {
		matriz[i] = malloc(colunas * sizeof(int));
	}

	return preencheMatriz(linhas, colunas, matriz);
	
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
