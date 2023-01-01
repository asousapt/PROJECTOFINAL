#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "functions.h"

#define MAX_CAR 300
#define STRING char *
#define N_CAMPOS_MAX 100
#define MAX_LINHA_FICHEIRO 300
#define MAX_EXAMES_FILE 100

//passa para o vetor a informacao dos exames
void import_txt_exames(EXAMES* exames_bv, STRING* V) {

	int i = 0, k, n_campos_lidos;

	//Abre o ficheiro
	FILE* f = fopen("exames.txt", "r");
	if (f == NULL) {
		printf("Erro ao abrir ficheiro exames.txt");
		exit(1);
	}

	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao

			exames_bv[i].codigo = atoi(V[0]);

            exames_bv[i].curso = (char *)malloc(sizeof(char) * (sizeof(V[1])));
			strcpy(exames_bv[i].curso, V[1]);

			exames_bv[i].unidade_curricular = (char *)malloc(sizeof(char) * (sizeof(V[2])));
			strcpy(exames_bv[i].unidade_curricular, V[2]);

			exames_bv[i].epoca = (char *)malloc(sizeof(char) * (sizeof(V[3])));
			strcpy(exames_bv[i].epoca, V[3]);

			exames_bv[i].data = atoi(V[4]);

			exames_bv[i].hora = atoi(V[5]);

			exames_bv[i].duracao = atoi(V[6]);

			exames_bv[i].sala = (char *)malloc(sizeof(char) * (sizeof(V[7])));
			strcpy(exames_bv[i].sala, V[7]);

			exames_bv[i].alunos_inscritos = atoi(V[8]);
			
            exames_bv[i].realizado = 1;

			exames_bv[i].ocupado = 1;

			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
			free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);
}

void listar_exames(EXAMES* exames_bv){ 

}

void menu_exames(EXAMES* exames_bv) {
    int opcaoExame = -1; 
    while(opcaoExame != 0) {
        printf("Bem-vindo ao menu de Exames\n");
        printf("1. Listar Exames\n");
        printf("Escolha uma opcao\n"); 
        printf("Opcao:"); 
        scanf("%d", &opcaoExame); 
        switch (opcaoExame)
        {
        case 1:
           listar_exames(exames_bv);
            break;
        
        case 0:
            opcaoExame = 0;
            break;
        }
    }
	
	

}