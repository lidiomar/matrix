#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int** preencheMatriz(int linhas, int colunas, int** matriz);
void mostraMatriz(int linhas, int colunas, int** matriz);
int** alocaMatriz(int linhas, int colunas);
void multiplica(int linhas, int colunas, int colunas2, int **matriz_1, int **matriz_2);
void* executa(void* param, pid_t pid);

typedef struct {
	int id;
	int* linhaParaMultiplicar;
	int** matriz_2;
	int colunas;
	int colunas2;
	int* result;
} threadParams;
void bla(int i, threadParams *params, int **matriz_1, int **matriz_2, int colunas, int colunas2,pid_t pid);

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
	int aux;
	pid_t pid;

	threads = malloc(linhas * sizeof(pthread_t));
	params = malloc(linhas * sizeof(threadParams));

	pid = fork();

	for(int i=0; i<linhas; i++) {
		if(i%2 == 0 && pid != 0) {		
			bla(i, params,matriz_1, matriz_2, colunas, colunas2, pid);
		}else if(i%2 != 0 && pid == 0) {
			bla(i, params,matriz_1, matriz_2, colunas, colunas2, pid);
		}
		
	}

}

void bla(int i, threadParams *params, int **matriz_1, int **matriz_2, int colunas, int colunas2,pid_t pid) {
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
	executa((void*)&params[i], pid);
}

void* executa(void* param, pid_t pid) {
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
		printf("PID: %d VALOR: %d\n", pid, sum);
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
