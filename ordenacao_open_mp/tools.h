#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double wtime();
char **split (const char *str, char sep, int nro_palavras);
int fileout_matriz (int **matriz, int linha, int coluna, FILE *infile);
int contabiliza_file ( FILE *const fin, int* line_length );
char *get_line_file ( FILE *const fin, int get_line, int nro_line, int *vet_line );
int filein_matriz (int **matriz, int linha, int coluna, FILE *file, int *vet_ind, int nr_line);
int conta_line_file ( FILE *const fin, int get_line, int nro_line, int *vet_line );
int nr_line_file ( FILE *const fin, int *vet_line );
int extrai_parametros_matriz ( FILE *const fin, int* linha, int *coluna, int **vet_line, int *nr_line );