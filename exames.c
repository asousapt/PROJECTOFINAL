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
		printf("Erro ao abrir ficheiro exames.txt\n");
		exit(1);
	}

	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao

			exames_bv[i].codigo = atoi(V[0]);
			
            exames_bv[i].unidade_curricular = (char*)malloc(sizeof(char) * (strlen(V[1]) + 1));
			strcpy(exames_bv[i].unidade_curricular, V[1]);

			exames_bv[i].curso = (char*)malloc(sizeof(char) * (strlen(V[2]) + 1));
			strcpy(exames_bv[i].curso, V[2]);

			exames_bv[i].epoca = (char*)malloc(sizeof(char) * (strlen(V[3]) + 1));
			strcpy(exames_bv[i].epoca, V[3]);

			exames_bv[i].data = (char*)malloc(sizeof(char) * (strlen(V[4]) + 1));
			strcpy(exames_bv[i].data, V[4]);
		
			exames_bv[i].hora = (char*)malloc(sizeof(char) * (strlen(V[5]) + 1));
			strcpy(exames_bv[i].hora, V[5]);	

			exames_bv[i].duracao = atoi(V[6]);

			exames_bv[i].sala = (char*)malloc(sizeof(char) * (strlen(V[7]) + 1));
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

//Funcao que exporta os exames activos na aplicacao
void export_exames(EXAMES* exames_bv){
	int i, k = 0;
	FILE *f;
	
	
	f = fopen("exames.txt","w");
	if (f == NULL){
		printf("Erro ao abrir o ficheiro -> exames.txt");
		exit(1);
	}
	
	for ( i = 0; i < MAX_EXAMES_FILE; i++)
	{
		if (exames_bv[i].ocupado == 1) {
			fprintf(f, "%d|%s|%s|%s|%s|%s|%d|%s|%d\n", 
				exames_bv[i].codigo,
				exames_bv[i].unidade_curricular,
				exames_bv[i].curso, 
				exames_bv[i].epoca,
				exames_bv[i].data,
				exames_bv[i].hora,
				exames_bv[i].duracao,
				exames_bv[i].sala,
				exames_bv[i].alunos_inscritos
			);
		}
	}
	fclose(f);
}

void listar_exames(EXAMES* exames_bv){ 
	int i = 0; 
	printf("%s %s %s %s %s %s %s %s", "Cod", "UC", "Curso", "Epoca", "Data", "Hora", "Sala", "Inscritos" );
	for ( i = 0; i < MAX_EXAMES_FILE; i++)
	{
		if (exames_bv[i].ocupado == 1) {
			printf("%d %-36s %-3s %-5s %-3s %-3s %-4s %-6d \n", 
			exames_bv[i].codigo, 
			exames_bv[i].unidade_curricular, 
			exames_bv[i].curso, 
			exames_bv[i].epoca, 
			exames_bv[i].data, 
			exames_bv[i].hora, 
			exames_bv[i].sala, 
			exames_bv[i].alunos_inscritos);
		}
	}
	printf("\n");
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
        case 1: //Listar exames
           listar_exames(exames_bv);
            break;
		case 2: // Adicionar novo exame 
			break;
		case 3: // editar Exame 
			break;
        case 0:
            opcaoExame = 0;
            break;
        }
    }
	
	

}