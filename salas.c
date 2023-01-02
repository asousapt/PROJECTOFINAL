#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions.h"

#define MAX_CAR 300 
#define STRING char *
#define N_CAMPOS_MAX 100 
#define MAX_LINHA_FICHEIRO 300
#define MAX_UNIDADES_CURRICULARES 100
#define MAX_CURSOS 20
#define MAX_SALAS 100


//passa para o vecto a informacao do ficheiro cursos
void import_txt_salas(SALAS* salas, STRING* V) {
	int i = 0, k, n_campos_lidos;

	//Abre o ficheiro
	FILE* f = fopen("salas.txt", "r");
	if (f == NULL) {
		printf("Erro ao abrir ficheiro salas.txt\n");
		exit(1);
	}

	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao			

			salas[i].codigo = (char*)malloc(sizeof(char) * (strlen(V[0]) + 1));
			strcpy(salas[i].codigo, V[0]);

			salas[i].nome_sala = (char*)malloc(sizeof(char) * (strlen(V[1]) + 5));
			strcpy(salas[i].nome_sala, V[1]);

			salas[i].lotacao = atoi(V[2]);

			salas[i].ocupado = 1;

			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
			free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);

}


// funcao que lista as salas 
void listar_salas(SALAS* salas) {
	int i;
	printf("Numero | Nome | Lotacao\n");
	for (i = 0; i < MAX_SALAS; i++)
	{
		if (salas[i].ocupado == 1) {
			printf("%s %s %d\n", salas[i].codigo, salas[i].nome_sala, salas[i].lotacao);
		}
	}
}

void menu_salas(SALAS* salas) {
	int opcao;

	while (1) {
		printf("\n");
		printf("Bem-vindo ao menu das salas!\n");
		printf("Escolha uma das opcoes:\n");
		printf("1 - Consultar Salas\n");
		printf("2 - Adicionar Salas\n");
		printf("3 - Editar Sala\n");
		printf("4 - Apagar Sala\n");
		printf("0 - Sair\n");
		printf("Introduza a Opcao: ");
		scanf("%d", &opcao);
		system("cls");
		
		switch (opcao) {
		case 1: //lista as salas
			listar_salas(salas);
			break;
		case 2: //cria salas 
			
			break;
		case 3: //Editar salas 
			break;
		case 4: //Apagar salas
		case 0:
			break;
		}
	}


}