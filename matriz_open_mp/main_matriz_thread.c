#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "matriz_thread.h"


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main(int argc, char **argv) {
    int **mat_a = NULL;
    int **mat_b = NULL;
    int **mat_c = NULL;
    FILE *fmat_a, *fmat_b, *fmat_c;
    int nr_line;
    int *vet_line = NULL;
    int N, M, La, Lb;
    double start_time, end_time;

    if (argc != 3){
            printf ("ERRO: Numero de parametros %s <matriz_a> <matriz_b>\n", argv[0]);
            exit (1);
    }

    fmat_a = fopen(argv[1],"r");
    fmat_b = fopen(argv[2],"r");
    fmat_c = fopen("fileout.map","w");

    if ((fmat_a == NULL) || (fmat_b == NULL) || (fmat_c == NULL)) {
        printf("Error: Na abertura dos arquivos.");
        exit(1);
    }

    // matriz_a NxL1
    extrai_parametros_matriz(fmat_a, &N, &La, &vet_line, &nr_line);
    mat_a = alocar_matriz(N, La);
    filein_matriz (mat_a, N, La, fmat_a, vet_line, nr_line);

    // matriz B = LxM
    extrai_parametros_matriz(fmat_b, &Lb, &M, &vet_line, &nr_line);
    mat_b = alocar_matriz(Lb, M);
    filein_matriz (mat_b, Lb, M, fmat_b, vet_line, nr_line);

    // Restricao da operacao de soma de matrizes
    if (La != Lb){
        printf ("ERROR: matriz a vs matriz b incompativeis.\n");
        exit (1);
    }

    // matriz C = NxM
    mat_c = alocar_matriz(N, M);
    zerar_matriz(mat_c, N, M);

    if ((mat_c == NULL) || (mat_b == NULL) || (mat_a == NULL)) {
            printf("ERROR: Out of memory\n");
    }

    printf("\t\t**** Loaded mat_a NxL(%d,%d) **** \n", N, La);
    imprimir_matriz(mat_a, N, La);

    printf("\t\t**** Loaded mat_b LxM(%d,%d) **** \n", Lb, M);
    imprimir_matriz(mat_b, Lb, N);

    printf("\t\t**** Loaded mat_c NxM(%d,%d) **** \n", N, M);
    imprimir_matriz(mat_c, N, M);

    /*start_time = wtime();
    somar(mat_a,mat_b,mat_c, N, La, M);
    end_time = wtime();
    printf("\t\t**** mat_c (soma) **** \n");
    printf("Runtime: %f\n", end_time - start_time);
    fflush(stdout);*/
    //imprimir_matriz(mat_c, N, M);
    
    
    start_time = wtime();
    multiplicar(mat_a,mat_b,mat_c, N, La, Lb, M,2);
    end_time = wtime();
    printf("\t\t**** mat_c (multiplicar) **** \n");
    printf("Runtime: %f\n", end_time - start_time);
    imprimir_matriz(mat_c, N, M);
        
    
    
    fileout_matriz(mat_c, N, M, fmat_c);

    liberar_matriz(mat_a,N,La);
    liberar_matriz(mat_b,Lb,M);
    liberar_matriz(mat_c,N,M);

    fclose(fmat_a);
    fclose(fmat_b);
    fclose(fmat_c);

    return 0;
}
