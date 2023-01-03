#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions.h"

#define _CRT_SECURE_NO_WARNINGS
#define MAX_FERIADOS 20 
#define STRING char *
#define MAX_LINHA_FICHEIRO 300
#define N_CAMPOS_MAX 100

void import_feriados(FERIADOS* feriado, STRING* V) {
    int i = 0, k, n_campos_lidos; 

	//Abre o ficheiro
	FILE* f = fopen("feriados.txt", "r");
	if (f == NULL) {
		printf("Erro ao abrir ficheiro feriados.txt\n");
		exit(1);
	}

	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao			

			feriado[i].dia = atoi(V[0]);
            feriado[i].mes = atoi(V[1]);

			for (k = 0; k < n_campos_lidos; k++) 
				free(V[k]);
				free(V);
			
			i++;
		}
	} while (!feof(f));

	fclose(f);

}

void lista_feriados(FERIADOS* feriado) {
    int i;
    printf("%s  %s", "Dia", "Mes\n");
    for ( i = 0; i < MAX_FERIADOS; i++)
    {
        if (feriado[i].dia > 0 ) {
             printf("%-3d %3d\n", feriado[i].dia, feriado[i].mes); 
        }
    }
}