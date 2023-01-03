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
#define MAX_ALUNOS 3000
#define MAX_REGIMES 5


//passa para o vecto a informacao do ficheiro alunos.txt
void import_txt_alunos(ALUNOS* alunos, STRING* V) {
	int i = 0, k, n_campos_lidos;

	//Abre o ficheiro
	FILE* f = fopen("alunos.txt", "r");
	if (f == NULL) {
		printf("Erro ao abrir ficheiro alunos.txt\n");
		exit(1);
	}

	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao			

			alunos[i].nome = (char*)malloc(sizeof(char) * (strlen(V[0]) + 1));
			strcpy(alunos[i].nome, V[0]);

			alunos[i].regime = (char*)malloc(sizeof(char) * (strlen(V[1]) + 5));
			strcpy(alunos[i].regime, V[1]);

			alunos[i].ano_matricula = atoi(V[2]);

			alunos[i].numero = atoi(V[3]);

            alunos[i].curso = (char*)malloc(sizeof(char) * (strlen(V[4]) + 5));
            strcpy(alunos[i].curso, V[4]);

            alunos[i].ocupado = 1;

			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
			free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);

}

//passa para o vetor a informacao do ficheiro regimes.txt
void import_txt_regimes(REGIMES* regimes, STRING* V) {
    int i = 0, k, n_campos_lidos;

    //Abre o ficheiro
    FILE* f = fopen("regimes.txt", "r");
    if (f == NULL) {
        printf("Erro ao abrir ficheiro regimes.txt\n");
        exit(1);
    }

    do {
        V = Read_Split_Line_File(f, &n_campos_lidos);
        if (V != NULL) {// caso consigamos ler alguma informacao			

            regimes[i].codigo = atoi(V[0]);

            regimes[i].regime = (char*)malloc(sizeof(char) * (strlen(V[1]) + 5));
            strcpy(regimes[i].regime, V[1]);

            regimes[i].ocupado = 1;

            for (k = 0; k < n_campos_lidos; k++)
                free(V[k]);
            free(V);
            i++;
        }
    } while (!feof(f));

    fclose(f);

}

//funca que lista os regimes
void listar_regimes(REGIMES* regimes) {
    int i = 0;

    printf("%s %s\n", "Codigo", "Regime");
    for (i = 0; i < MAX_REGIMES; i++)
    {
        if (regimes[i].ocupado == 1) {
            printf("%d %s\n", i, regimes[i].regime);
        }
    }
}

// funcao que lista os alunos 
void listar_alunos(ALUNOS* alunos) {
	int i;
	printf("Nome | Regime | Ano Matricula | Numero | Curso\n");
	for (i = 0; i < MAX_ALUNOS; i++)
	{
		if (alunos[i].ocupado == 1) {
			printf("%s %s %d %d %s", alunos[i].nome, alunos[i].regime, alunos[i].ano_matricula, alunos[i].numero, alunos[i].curso);
		}
	}
	printf("\n");
}
/*
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
		scanf("%s", &codigo);
	} while (strlen(codigo) == 0);

	//vamos pedir o nome da sala 
	do
	{
		printf("Qual o nome do sala?\n");
		scanf("%s", &nome_sala);
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
*/

//menu relativo as salas
void menu_alunos(ALUNOS* alunos, REGIMES* regimes, CURSO* cursos) {
    int opcao;

	while (1) {
		printf("\n");
		printf("Bem-vindo ao menu das salas!\n");
		printf("Escolha uma das opcoes:\n");
		printf("1 - Consultar Alunos\n");
		printf("2 - Adicionar Aluno\n");
		printf("3 - Editar Aluno\n");
		printf("4 - Apagar Aluno\n");
		printf("0 - Sair\n");
		printf("Introduza a Opcao: ");
		scanf("%d", &opcao);
		system("cls");
		
		switch (opcao) {
		case 1: //lista as salas
			listar_alunos(alunos);
			break;
		case 2: //cria alunos 
			//criar_aluno(alunos);
			break;
		case 3: //Editar aluno 
			break;
		case 4: //Apagar aluno
		case 0:
			break;
		}
	}


}