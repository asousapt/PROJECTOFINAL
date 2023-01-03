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


//passa para o vecto a informacao do ficheiro salas.txt
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

//verifica se a sala ja existe
int valida_sala_existe_vector(SALAS* salas, char* nome_sala) {
	int i = 0; 
	for ( i = 0; i < MAX_UNIDADES_CURRICULARES; i++)
	{
		if (salas[i].ocupado == 1) {
			
			if (strcmp(salas[i].nome_sala, nome_sala) == 0) { 
				return 1;
			}	
		}
	}
	return 0;
}

//
int get_posicao_vect_salas(SALAS* salas) {
	int i;
	for (i = 0; i < MAX_SALAS; i++)
	{
		if ((salas[i].ocupado == 0) && (i < MAX_SALAS)) {
			return i;
		}
	}
	return -1;
}

//Insere sala
int insere_sala(SALAS* salas, char* codigo, char* nome_sala, int lotacao) {
	int posicaoVazia = 0;
	posicaoVazia = get_posicao_vect_salas(salas);
	if (posicaoVazia == -1) {
		return -1;
	}

	//insere a nova sala no vector 
	salas[posicaoVazia].codigo = codigo;
	salas[posicaoVazia].nome_sala = nome_sala;
	salas[posicaoVazia].lotacao = lotacao;
	salas[posicaoVazia].ocupado = 1;

	return 1;
}

//criar salas
void criar_sala(SALAS* salas) {
	//vamos pedir ao utilizador os dados para criar a nova sala
				//declarecao de variaveis necessarias
	char* codigo;
	char* nome_sala;
	int lotacao;
	//vamos pedir o numero 
	do
	{
		printf("Qual o numero da sala?\n");
		scanf("%s", codigo);
	} while (strlen(codigo) == 0);

	//vamos pedir o nome da sala 
	do
	{
		printf("Qual o nome do sala?\n");
		scanf("%s", nome_sala);
	} while (strlen(nome_sala) == 0);

	// introducao da lotacao
	
		printf("Indique a lotacao da sala\n");
		scanf("%d", &lotacao);

	//valida se a sala já existe no nosso vector
	//No caso de retornar 1 a UC ja existe, caso contrario podemos inserir 
	if (valida_sala_existe_vector(salas, nome_sala) == 1) {
		printf("A unidade curricular já existe!\n");
	}
	else {
		if (insere_sala(salas, codigo, nome_sala, lotacao) == 1) {
			printf("%s inserida com sucesso!\n", nome_sala);
			printf("\n");
		}
		else {
			printf("Ocorreu um erro ao guardar a sala em memoria\n");
			printf("Tente novamente!\n");
			printf("\n");
		}
	}
}

//menu relativo as salas
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
			criar_sala(salas);
			break;
		case 3: //Editar salas 
			break;
		case 4: //Apagar salas
		case 0:
			break;
		}
	}


}