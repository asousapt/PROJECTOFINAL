#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"functions.h"

#define MAX_CAR 300 
#define STRING char *
#define N_CAMPOS_MAX 100 
#define MAX_EPOCAS 10



//passa para o vecto a informacao do ficheiro salas.txt
void import_txt_epocas(EPOCAS* epocas, STRING* V) {
	int i = 0, k, n_campos_lidos;

	//Abre o ficheiro
	FILE* f = fopen("epocas.txt", "r");
	if (f == NULL) {
		printf("Erro ao abrir ficheiro salas.txt\n");
		exit(1);
	}

	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao			

			epocas[i].epoca = (char*)malloc(sizeof(char) * (strlen(V[0]) + 1));
			strcpy(epocas[i].epoca, V[0]);

			epocas[i].dataInicio = (char*)malloc(sizeof(char) * (strlen(V[1]) + 5));
			strcpy(epocas[i].dataInicio, V[1]);

            epocas[i].dataFim = (char*)malloc(sizeof(char) * (strlen(V[2]) + 1));
			strcpy(epocas[i].dataFim, V[2]);

			epocas[i].semestre = atoi(V[3]);


			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
			free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);

}