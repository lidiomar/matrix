#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "ordenacao.h"


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main(int argc, char **argv) {
    int **mat_a = NULL;
    FILE *fmat_a;
    int nr_line;
    int *vet_line = NULL;
    int N, La;
    int numThreads = 4;
    double start_time, end_time, sum;
    int files[4] = {100,200,300,400};

    for(int z=0;z<4;z++) {
        
        if(files[z] == 100) {
            fmat_a = fopen("100x100-mat.map","r");
            printf("\n\n\n********************MATRIZ 100X100***************\n\n");    
        }else if(files[z] == 200) {
            fmat_a = fopen("200x200-mat.map","r");
            printf("\n\n\n********************MATRIZ 200X200***************\n\n");
        }else if(files[z] == 300) {
            fmat_a = fopen("300x300-mat.map","r");
            printf("\n\n\n********************MATRIZ 300X300***************\n\n");
        }else if(files[z] == 400) {
            fmat_a = fopen("400x400-mat.map","r");
            printf("\n\n\n********************MATRIZ 400X400***************\n\n");
        }

        if (fmat_a == NULL) {
            printf("Error: Na abertura dos arquivos.");
            exit(1);
        }

        extrai_parametros_matriz(fmat_a, &N, &La, &vet_line, &nr_line);
        mat_a = alocar_matriz(N, La);
        filein_matriz (mat_a, N, La, fmat_a, vet_line, nr_line);

        
        printf("*************** Sequencial: \n");    
        sum=0;
        
        extrai_parametros_matriz(fmat_a, &N, &La, &vet_line, &nr_line);
        mat_a = alocar_matriz(N, La);
        filein_matriz (mat_a, N, La, fmat_a, vet_line, nr_line);
        
            
        start_time = wtime();
        ordena_matriz_seq(mat_a, N, La);
        end_time = wtime();
           
        
        printf("%f\n", end_time - start_time);
        
        printf("\n\n\n");
        for(int y=2;y<=numThreads;y++){
            printf("*************** Threads: %d \n", y);    
            sum=0;
            
            extrai_parametros_matriz(fmat_a, &N, &La, &vet_line, &nr_line);
            mat_a = alocar_matriz(N, La);
            filein_matriz (mat_a, N, La, fmat_a, vet_line, nr_line);
            
            
            start_time = wtime();
            ordena_matriz_thread(mat_a, N, La,y);
            end_time = wtime();
            
            printf("%f\n", end_time - start_time);
            
        }
        printf("\n\n\n");    
        for(int y=2;y<=numThreads;y++){
            printf("*************** OMP Static: %d \n", y);
            sum=0;    
            
            extrai_parametros_matriz(fmat_a, &N, &La, &vet_line, &nr_line);
            mat_a = alocar_matriz(N, La);
            filein_matriz (mat_a, N, La, fmat_a, vet_line, nr_line);

            
            start_time = wtime();
            ordena_matriz_omp_static(mat_a, N, La,y);
            end_time = wtime();
            

            printf("%f\n", end_time - start_time);
        }
        printf("\n\n\n");
        for(int y=2;y<=numThreads;y++){
            printf("*************** OMP Dynamic: %d \n", y);
            sum=0;    
            
            extrai_parametros_matriz(fmat_a, &N, &La, &vet_line, &nr_line);
            mat_a = alocar_matriz(N, La);
            filein_matriz (mat_a, N, La, fmat_a, vet_line, nr_line);

            
            start_time = wtime();
            ordena_matriz_omp_dynamic(mat_a, N, La,y);
            end_time = wtime();
            

            printf("%f\n", end_time - start_time);
        }        
            
        
    }

    return 0;
}
