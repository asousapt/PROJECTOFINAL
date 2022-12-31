#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_CAR 300 
#define STRING char *
#define N_CAMPOS_MAX 100 
#define MAX_LINHA_FICHEIRO 300
#define MAX_UNIDADES_CURRICULARES 100
#define MAX_CURSOS 20


//definicao da estrutura de unidade curricular 
typedef struct
{
	int codigo;
	char* descricao;
	char* docente;
	int ano;
	int semestre;
	char* curso;
	int ocupado;
}UNIDADECURRICULAR;

//Definicao da estrutura CURSO onde estao as informacoes relativas aos cursos
typedef struct {
	char* codcurso; 
	char* descricao;
	int ocupado;
} CURSO; 

//le uma linha do ficheiro f
//devolve uma string com os campos da linha lida
STRING* Read_Split_Line_File(FILE* f, int* n_campos_lidos) {
	//separadores: carateres que fazem a separacao dos campos na linha
	char* separadores = (char*)"|", s[MAX_LINHA_FICHEIRO];
	*n_campos_lidos = 0;
	if (!f) return NULL;
	if (fgets(s, MAX_LINHA_FICHEIRO, f) != NULL) {	// fgets le uma linha do ficheiro de texto para a string s

		// "partir" a linha lida, usando os separadores definidos
		STRING* Res = (STRING*)malloc(N_CAMPOS_MAX * sizeof(STRING));  // alocacao de um array com n_campos_max ponteiros para STRING
		char* pch = strtok(s, separadores);
		int cont = 0;
		while (pch != NULL) {

			Res[cont] = (char*)malloc((strlen(pch) + 1) * sizeof(char)); // aloca��o do espa�o necess�rio para guardar a string correspondente ao campo
			strcpy(Res[cont++], pch);
			pch = strtok(NULL, separadores);
		}
		*n_campos_lidos = cont;
		return Res;
	}
	return NULL;
}
//passa para o vecto a informacao do ficheiro cursos
void import_txt_cursos(CURSO* curso, STRING* V) {
	int i = 0, k, n_campos_lidos; 

	//Abre o ficheiro
	FILE* f = fopen("cursos.txt", "r");
	if (f == NULL) {
		printf("Erro ao abrir ficheiro cursos.txt\n");
		exit(1);
	}

	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao			

			curso[i].codcurso = (char*)malloc(sizeof(char) * (strlen(V[0]) + 1));
			strcpy(curso[i].codcurso, V[0]);
			
			curso[i].descricao = (char*)malloc(sizeof(char) * (strlen(V[1]) + 5));
			strcpy(curso[i].descricao, V[1]);

			curso[i].ocupado = 1;

			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
				free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);

}

//passa para o vetor a informacao das unidades curriculares
void import_txt_uc(UNIDADECURRICULAR* uc, STRING* V) { //, STRING* V

	int i = 0, k, n_campos_lidos; 

	//Abre o ficheiro
	FILE* f = fopen("Ficheiros_bv/unidades_curriculares_bv.txt", "r");
	if (f == NULL) {
		printf("Erro ao abrir ficheiro unidades_curriculares_bv.txt\n");
		exit(1);
	}
	
	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao			

			uc[i].codigo = atoi(V[0]);

			uc[i].descricao = (char*)malloc(sizeof(char) * (strlen(V[1]) + 1));
			strcpy(uc[i].descricao, V[1]);
			
			uc[i].docente = (char*)malloc(sizeof(char) * (strlen(V[2]) + 5));
			strcpy(uc[i].docente, V[2]);
			
			uc[i].ano = atoi(V[3]);

			uc[i].semestre = atoi(V[4]);

			uc[i].curso = (char*)malloc(sizeof(char) * (strlen(V[5]) + 5));
			strcpy(uc[i].curso, V[5]);

			uc[i].ocupado = 1;

			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
			free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);
}

// funcao que lista as unidades curriculares 
void listar_UC(UNIDADECURRICULAR* uc) {
	int i;
	printf("%-2s %s %40s %17s %7s %10s\n", "Cod", "Nome","Docente", "Curso", "Ano", "Semestre");
	for (i = 0; i < MAX_UNIDADES_CURRICULARES; i++)
	{
		if (uc[i].ocupado == 1) {
			printf("%-3d %-37s %-19s %s %d %d\n",uc[i].codigo, uc[i].descricao, uc[i].docente, uc[i].curso, uc[i].ano, uc[i].semestre);
		}
	}
}

//funcao que lista os cursos do vector cursos
void listar_cursos(CURSO* cursos) {
	int i = 0;

	printf("%s %s\n","Cod", "Curso");
	for (i = 0; i < MAX_CURSOS; i++)
	{
		if (cursos[i].ocupado == 1) {
			printf("%-3d %s\n", i, cursos[i].descricao);
		}
	}
}

// valida se o utilizador introduziu um dos cursos da lista 
int valida_curso_escolhido(CURSO* cursos, int escolhido) {
	int i = 0; 
	
	for ( i = 0; i < MAX_CURSOS; i++)
	{
		if (cursos[i].ocupado == 1 && i == escolhido) {
			return 1;
		}
	}
	
	return 0;
}

//funcao que valida se o utilizador introduziu bem os dados do ano e do semestre
int valida_ano_semestre(int ano, int semestre) { 
	if(ano < 1 || ano > 3 ) {
		return 0; 
	}
	if(semestre < 1 || semestre > 2 ) {
		return 0; 
	}
	return 1; 
} 

int valida_UC_existe_vector(UNIDADECURRICULAR* uc, char* descricao, char* curso) {
	int i = 0; 
	for ( i = 0; i < MAX_UNIDADES_CURRICULARES; i++)
	{
		if (uc[i].ocupado == 1) {
			
			if ((strcmp(uc[i].descricao,descricao) == 0) && strcmp(uc[i].curso,curso) == 0) { 
				return 1;
			}	
		}
	}
	return 0;
}

int get_newID_UC(UNIDADECURRICULAR* uc) {
	int i, ID= 0; 
	for ( i = 0; i < MAX_UNIDADES_CURRICULARES; i++)
	{
		if ((uc[i].ocupado == 1) && (i < MAX_UNIDADES_CURRICULARES)) {
			ID = uc[i].codigo + 1;
		}
	}
	return ID;
}

int get_posicao_vect_UC(UNIDADECURRICULAR* uc) {
	int i; 
	for ( i = 0; i < MAX_UNIDADES_CURRICULARES; i++)
	{
		if ((uc[i].ocupado == 0) && (i < MAX_UNIDADES_CURRICULARES)) {
			return i;
		}
	}
	return -1;
}

int insere_uc(UNIDADECURRICULAR* uc, char* descricao, char* docente, char* curso, int ano, int semestre) {
	int ID = 0;
	int posicaoVazia = 0;
	posicaoVazia = get_posicao_vect_UC(uc); 
	if (posicaoVazia == -1) {
		return -1;
	}
	ID = get_newID_UC(uc);
	
	//insere a nova unidade curricular no vector 
	uc[posicaoVazia].codigo = ID;
	uc[posicaoVazia].descricao = descricao;
	uc[posicaoVazia].docente = docente;
	uc[posicaoVazia].curso = curso;
	uc[posicaoVazia].ano = ano; 
	uc[posicaoVazia].semestre = semestre;
	uc[posicaoVazia].ocupado = 1;

	return 1;
}

void criar_UC(UNIDADECURRICULAR* uc, CURSO* cursos) {
	//vamos pedir ao utilizador os dados para criar a nova unidade curricular
				//declarecao de variaveis necessarias
				int codigo = 0; 
				char* descricao;
				char* docente;
				int posicaoCurso; 
				int ano; 
				int semestre;
				//vamos pedir o nome da unidade curricular 
				do
				{
					printf("Qual o nome da unidade curricular?\n"); 
					scanf("%s", descricao); 
				} while (strlen(descricao) == 0); 
				
				//vamos pedir o nome do docnete 
				do
				{
					printf("Qual o nome do docente?\n"); 
					scanf("%s", docente); 
				} while (strlen(docente) == 0); 

				//seleccao do curso 

				do {
				listar_cursos(cursos);
				printf("Indique o curso da lista acima\n");
				scanf("%d", &posicaoCurso);
				} while (valida_curso_escolhido( cursos, posicaoCurso) == 0);
				
				// introducao do ano e do semestre
				do{
					printf("Indique o ano (1,2,3) e o semestre (1,2) da unidade curricular\n");
					scanf("%d %d", &ano, &semestre);
				}while (valida_ano_semestre( ano, semestre) == 0);

				//valida se a unidade curricular já existe no nosso vector
				//No caso de retornar 1 a UC ja existe, caso contrario podemos inserir 
				if (valida_UC_existe_vector(uc,  descricao, cursos[posicaoCurso].codcurso) == 1) {
					printf("A unidade curricular já existe!\n"); 
				} else {
					if (insere_uc(uc, descricao, docente, cursos[posicaoCurso].codcurso, ano, semestre) == 1 ) {
						printf("Unidade curricular inserida com sucesso!\n");
						printf("\n");			
					} else {
						printf("Ocorreu um erro ao guardar a unidade curricular em memoria\n");
						printf("Tente novamente!\n");		
						printf("\n");
					}
				}
}

void menu_uc() {
	STRING* V;
	int opcao;
	UNIDADECURRICULAR* uc = (UNIDADECURRICULAR*)malloc(MAX_UNIDADES_CURRICULARES * sizeof(UNIDADECURRICULAR));
	import_txt_uc(uc, V);
	CURSO* cursos = (CURSO*)malloc(MAX_CURSOS * sizeof(CURSO));
	import_txt_cursos(cursos, V);

	while(1){
		printf("\n");
		printf("Bem-vindo ao menu das unidades curriculares!\n");
		printf("Escolha uma das opcoes:\n");
		printf("1 - Consultar Unidades Curriculares\n");
		printf("2 - Adicionar Unidade Curricular\n");
		printf("3 - Editar Unidade Curricular\n");
		printf("4 - Apagar Unidade Curricular\n");
		printf("0 - Sair\n");
		printf("Introduza a Opcao: ");
		scanf("%d", &opcao);
		
		switch (opcao) {
			case 1: //lista as unidades curriculares
				listar_UC(uc);
				break;
			case 2: //cria unidades curriculares 
				criar_UC(uc, cursos);
				break;
			case 3: //Editar unidades curriculares 
				break; 
			case 4: //Apagar unidades curriculares
			case 0: return 0;
		}
	}
	

}
