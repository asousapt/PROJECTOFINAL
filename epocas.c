#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"functions.h"

#define MAX_CAR 300 
#define STRING char *
#define N_CAMPOS_MAX 100 
#define MAX_EPOCAS 10



//passa para o vecto a informacao do ficheiro epocas.txt
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

			epocas[i].codigo = atoi(V[0]);	

			epocas[i].epoca = (char*)malloc(sizeof(char) * (strlen(V[1]) + 1));
			strcpy(epocas[i].epoca, V[1]);

			epocas[i].dataInicio = (char*)malloc(sizeof(char) * (strlen(V[2]) + 5));
			strcpy(epocas[i].dataInicio, V[2]);

            epocas[i].dataFim = (char*)malloc(sizeof(char) * (strlen(V[3]) + 1));
			strcpy(epocas[i].dataFim, V[3]);

			epocas[i].semestre = atoi(V[4]);
			
			epocas[i].ocupado = 1;

			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
			free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);

}

void lista_epocas(EPOCAS* epocas) {
	int i = 0;
	printf("\n%s %s %s %s\n", "Cod", "Epoca", "Data Inicio", "Data Fim");
	for ( i = 0; i < MAX_EPOCAS; i++)
	{
		if (epocas[i].ocupado == 1){
			printf("%d %s %s %s\n",epocas[i].codigo, epocas[i].epoca, epocas[i].dataInicio, epocas[i].dataFim);
		}
	}
}