#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define MAX_CAR 300
#define STRING char *
#define N_CAMPOS_MAX 100
#define MAX_LINHA_FICHEIRO 300


//definicao da estrutura de unidade curricular 
typedef struct
{
	int codigo;
	char* unidade_curricular;
	char* epoca;
	char* data;
	char* hora;
	int duracao;
	char* sala;
	int alunos_inscritos;
} EXAMES;

typedef struct
{
	int codigo;
	char* exame;
	int num_aluno;
	int ano;
	char* estatuto;
}INSCRICAOEXAMES;

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

//passa para o vetor a informacao dos exames
void import_txt_exames(EXAMES* exames, STRING* V) {

	int i = 0, k, n_campos_lidos;

	//Abre o ficheiro
	FILE* f = fopen("exames.txt", "r");
	if (f == NULL) {
		printf("Erro ao abrir ficheiro exames");
		exit(1);
	}

	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao

			exames[i].codigo = atoi(V[0]);

			exames[i].unidade_curricular = (char*)malloc(sizeof(char) * (strlen(V[1])));
			strcpy(exames[i].unidade_curricular, V[1]);

			exames[i].epoca = (char*)malloc(sizeof(char) * (strlen(V[2])));
			strcpy(exames[i].epoca, V[2]);

			exames[i].data = (char*)malloc(sizeof(char) * (strlen(V[3])));
			strcpy(exames[i].data, V[3]);

			exames[i].hora = (char*)malloc(sizeof(char) * (strlen(V[4])));
			strcpy(exames[i].hora, V[4]);

			exames[i].duracao = atoi(V[5]);

			exames[i].sala = (char*)malloc(sizeof(char) * (strlen(V[6])));
			strcpy(exames[i].sala, V[6]);

			exames[i].alunos_inscritos = atoi(V[7]);

			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
			free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);

}

void import_txt_exames_marcados(INSCRICAOEXAMES* exames_marcados, STRING* V) {

	int i = 0, k, n_campos_lidos;

	//Abre o ficheiro
	FILE* f = fopen("inscricoes_exame.txt", "r");
	if (f == NULL) {
		printf("Erro ao abrir ficheiro inscricoes_exame");
		exit(1);
	}

	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao

			exames_marcados[i].codigo = atoi(V[0]);

			exames_marcados[i].exame = (char*)malloc(sizeof(char) * (strlen(V[1])));
			strcpy(exames_marcados[i].exame, V[1]);

			exames_marcados[i].num_aluno = atoi(V[2]);

			exames_marcados[i].ano = atoi(V[3]);

			exames_marcados[i].estatuto = (char*)malloc(sizeof(char) * (strlen(V[4])));
			strcpy(exames_marcados[i].estatuto, V[4]);

			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
			free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);
}

void menu_exames() {//menu marcacao de exames
	STRING* V{};
	int i, opcao;
	
	EXAMES* exames = (EXAMES*)malloc(50 * sizeof(EXAMES));
	INSCRICAOEXAMES* exames_marcados = (INSCRICAOEXAMES*)malloc(50 * sizeof(INSCRICAOEXAMES));

	printf("||\t   Marcacao de Exames   \t||\n");
	printf("||\t   Escolha uma opcao:   \t||\n");
	printf("==========================================\n");
	printf("||1 - Consulta de calendario de exames\t||\n");
	printf("||2 - Consultar marcacoes efetuadas\t||\n");
	printf("||3 - Marcar exame\t\t\t||\n");
	printf("||4 - Alterar marcacao\t\t\t||\n");
	printf("||0 - Sair\t\t\t\t||\n"); // Podera ser voltar atrás em vez de sair da aplicacao pois torna-se mais eficiente
	printf("==========================================\n");
	printf("Opcao: ");
	scanf("%d", &opcao);
	system("cls");

	switch (opcao) {
	case 1:
		import_txt_exames(exames, V);
		printf("------------------CALENDARIO DE EXAMES------------------\n");
		printf("UNIDADE CURRICULAR|EPOCA|DATA|HORA|DURACAO|SALA|ALUNOS INSCRITOS\n");
		for (i = 0; i < 50; i++)
		{
			printf("%s|%s|%s|%s|%d|%s|%d\n", exames[i].unidade_curricular, exames[i].epoca, exames[i].data, exames[i].hora,
				exames[i].duracao, exames[i].sala, exames[i].alunos_inscritos);
		}
		break;

	case 2: 
		import_txt_exames_marcados(exames_marcados, V);
		printf("------------------CONSULTA DE EXAMES MARCADOS------------------\n");
		printf("UNIDADE CURRICULAR|NUMERO ALUNO|ANO|ESTATUTO\n");
		for (i = 0; i < 50; i++)
		{
			printf("%s|%d|%d|%s\n", exames_marcados[i].exame, exames_marcados[i].num_aluno, exames_marcados[i].ano, exames_marcados[i].estatuto);
		}
		break;

	case 0: exit;
		break;
	}
}

int main() {
	menu_exames();

	return 0;
}