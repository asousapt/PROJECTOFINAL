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
			
			alunos[i].regime = (char*)malloc(sizeof(char) * (strlen(V[1]) + 1));
			strcpy(alunos[i].regime, V[1]);

			alunos[i].ano_matricula = atoi(V[2]);

			alunos[i].numero = atoi(V[3]);

			alunos[i].curso = (char*)malloc(sizeof(char) * (strlen(V[4]) + 1));
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
            printf("%d %s", i, regimes[i].regime);
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

//funcao que valida se o regime existe
int valida_regime_escolhido(REGIMES* regimes, int posicaoRegime){
	int i = 0;

	for (i = 0; i < MAX_REGIMES; i++)
	{
		if (regimes[i].ocupado == 1 && i == posicaoRegime) {
			return 1;
		}
	}

	return 0;
}

//funcao que valida o ano de matricula
int valida_ano_matricula(int ano_matricula) {
	if (ano_matricula < 1 || ano_matricula > 3) {
		return 0;
	}
	return 1;
}

//funcao que valida o numero do aluno
int valida_aluno_existe(ALUNOS* alunos, int numero) {
	int i = 0;
	for (i = 0; i < MAX_ALUNOS; i++)
	{
		if (alunos[i].ocupado == 1) {

			if (alunos[i].numero == numero) {
				return 1;
			}
		}
	}
	return 0;
}

//
int get_posicao_vect_alunos(ALUNOS* alunos) {
	int i;
	for (i = 0; i < MAX_ALUNOS; i++)
	{
		if ((alunos[i].ocupado == 0) && (i < MAX_ALUNOS)) {
			return i;
		}
	}
	return -1;
}

//Insere sala
int insere_aluno(ALUNOS* alunos, char* nome, char* regime, int ano_matricula, int numero, char* curso) {
	int posicaoVazia = 0;
	posicaoVazia = get_posicao_vect_alunos(alunos);
	if (posicaoVazia == -1) {
		return -1;
	}

	//insere o novo aluno no vector 
	alunos[posicaoVazia].nome = nome;
	alunos[posicaoVazia].regime = regime;
	alunos[posicaoVazia].ano_matricula = ano_matricula;
	alunos[posicaoVazia].numero = numero;
	alunos[posicaoVazia].curso = curso;
	alunos[posicaoVazia].ocupado = 1;

	return 1;
}

//criar salas
void criar_aluno(ALUNOS* alunos, REGIMES* regimes, CURSO* cursos) {
	//vamos pedir ao utilizador os dados para criar o novo aluno
				//declarecao de variaveis necessarias
	char* nome;
	nome = (char *)malloc(sizeof(char) * 100);
	int posicaoRegime ;
	int ano_matricula ;
	int numero ;
	int posicaoCurso ;

	//vamos pedir o numero 
	do
	{
		printf("Qual o nome do aluno?\n");
		fflush(stdout);
		fgets(nome, sizeof(nome), stdin);
		//scanf("%[^\n]s", nome);
	} while (strlen(nome) == 0);

	//vamos pedir o regime do aluno
	do
	{
		listar_regimes(regimes);
		printf("Qual o regime do aluno (Escolha uma das opcoes acima)?\n");
		scanf("%d", &posicaoRegime);
	} while (valida_regime_escolhido(regimes, posicaoRegime) == 0);

	// vamos pedir o ano de matricula do aluno
	do{
		printf("Indique o ano de matricula do aluno\n");
		scanf("%d", &ano_matricula);
	} while (valida_ano_matricula(ano_matricula) == 0);

	//vamos pedir o numero do aluno
	do
	{
		printf("Qual o numero do aluno?\n");
		scanf("%d", &numero);
	} while (valida_aluno_existe(alunos, numero) == 0);

	//vamos pedir o curso do aluno
	do
	{
		listar_cursos(cursos);
		printf("Qual o curso do aluno (Escolha uma das opcoes acima)?\n");
		scanf("%d", &posicaoCurso);
	} while (valida_curso_escolhido(cursos, posicaoCurso) == 0);

	
	if (insere_aluno(alunos, nome, regimes[posicaoRegime].regime, ano_matricula, numero, cursos[posicaoCurso].codcurso) == 1) {
			printf("%s inserida com sucesso!\n", nome);
			printf("\n");
	}
	else {
		printf("Ocorreu um erro ao guardar o aluno em memoria\n");
		printf("Tente novamente!\n");
		printf("\n");
	}
	free(nome);
}

void export_alunos(ALUNOS* alunos) {
	int i, k = 0;
	FILE *f;
	
	
	f = fopen("alunos.txt","w");
	if (f == NULL){
		printf("Erro ao abrir o ficheiro alunos.txt");
		exit(1);
	}
	
	for ( i = 0; i < MAX_UNIDADES_CURRICULARES; i++)
	{
		if (alunos[i].ocupado == 1) {
			fprintf(f, "%s|%s|%d|%d|%s",
				alunos[i].nome, 
				alunos[i].regime, 
				alunos[i].ano_matricula, 
				alunos[i].numero, 
				alunos[i].curso
			);
		}
	}
	
	fclose(f);
}


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
			criar_aluno(alunos, regimes, cursos);
			break;
		case 3: //Editar aluno 
			break;
		case 4: //Apagar aluno
		case 0:
			break;
		}
	}


}