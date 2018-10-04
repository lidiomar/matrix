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
    double start_time, end_time, sum;
    int files[4] = {100,500,1000,1500};

    for(int z=0;z<4;z++) {
        
        if(files[z] == 100) {
            fmat_a = fopen("100x100-mat1.map","r");
            fmat_b = fopen("100x100-mat2.map","r");
            fmat_c = fopen("fileout.map","w");
            printf("********************MATRIZ 100X100***************\n\n");    
        }else if(files[z] == 500) {
            fmat_a = fopen("500x500-mat1.map","r");
            fmat_b = fopen("500x500-mat2.map","r");
            fmat_c = fopen("fileout.map","w");
            printf("********************MATRIZ 500X500***************\n\n");
        }else if(files[z] == 1000) {
            fmat_a = fopen("1000x1000-mat1.map","r");
            fmat_b = fopen("1000x1000-mat2.map","r");
            fmat_c = fopen("fileout.map","w");
            printf("********************MATRIZ 1000X1000***************\n\n");
        }else if(files[z] == 1500) {
            fmat_a = fopen("1500x1500-mat1.map","r");
            fmat_b = fopen("1500x1500-mat2.map","r");
            fmat_c = fopen("fileout.map","w");
            printf("********************MATRIZ 1500X1500***************\n\n");    
        }

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

        sum=0;
        printf("*************** Sequencial: \n");
        for(int i=0;i<10;i++) {
            start_time = wtime();
            multiplicar_sequencial(mat_a,mat_b,mat_c, N, La, Lb);
            end_time = wtime();
            sum+=(end_time - start_time);
        }
        printf("%f\n", sum/10);

        
        for(int y=2;y<=4;y++) {
            printf("***************Threads: %d\n", y);
            sum=0;
            for(int i=0;i<10;i++) {
                start_time = wtime();
                multiplicar_thread(mat_a,mat_b,mat_c, N, La, Lb, M,y);
                end_time = wtime();
                sum+=(end_time - start_time);
            }
            printf("%f\n", sum/10);
        }
        

        
        for(int y=2;y<=4;y++) {
            printf("***************Opem MP Static: %d\n", y);
            sum=0;
            for(int i=0;i<10;i++) {
                start_time = wtime();
                multiplicar_static(mat_a,mat_b,mat_c, N, La, Lb, M,y);
                end_time = wtime();
                sum+=(end_time - start_time);
            }
            printf("%f\n", sum/10);
        }
        

            
        for(int y=2;y<=4;y++) {
            printf("***************Opem MP Dynamic: %d\n", y);
            sum=0;
            for(int i=0;i<10;i++) {
                start_time = wtime();
                multiplicar_dynamic(mat_a,mat_b,mat_c, N, La, Lb, M,y);
                end_time = wtime();
                sum+=(end_time - start_time);
            }
            printf("%f\n", sum/10);
        }
        

        //printf("\t\t**** mat_c (multiplicar) **** \n");
        
        //imprimir_matriz(mat_c, N, M);    
        
        fileout_matriz(mat_c, N, M, fmat_c);

        liberar_matriz(mat_a,N,La);
        liberar_matriz(mat_b,Lb,M);
        liberar_matriz(mat_c,N,M);

        fclose(fmat_a);
        fclose(fmat_b);
        fclose(fmat_c);
    }

    return 0;
}
