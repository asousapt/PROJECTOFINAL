#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include <string.h>


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
	int data;
	int hora;
	int duracao;
	char* sala;
	int alunos_inscritos;
} EXAMES;

//le uma linha do ficheiro f
//devolve uma string com os campos da linha lida
STRING* Read_Split_Line_File(FILE* f, int* n_campos_lidos) {
	//separadores: carateres que fazem a separacao dos campos na linha
	char* separadores = "|\n", s[MAX_LINHA_FICHEIRO];
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
void import_txt_exames(EXAMES* exames_bv, STRING* V) {

	int i = 0, k, n_campos_lidos;

	//Abre o ficheiro
	FILE* f = fopen("exames_bv.txt", "r");
	if (f == NULL) {
		printf("Erro ao abrir ficheiro exames_bv.txt");
		exit(1);
	}

	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao


			exames_bv[i].codigo = atoi(V[0]);

			exames_bv[i].unidade_curricular = malloc(sizeof(char) * (sizeof(V[1])));
			strcpy(exames_bv[i].unidade_curricular, V[1]);

			exames_bv[i].epoca = malloc(sizeof(char) * (sizeof(V[2])));
			strcpy(exames_bv[i].epoca, V[2]);

			exames_bv[i].data = atoi(V[3]);

			exames_bv[i].hora = atoi(V[4]);

			exames_bv[i].duracao = atoi(V[5]);

			exames_bv[i].sala = malloc(sizeof(char) * (sizeof(V[6])));
			strcpy(exames_bv[i].sala, V[6]);

			exames_bv[i].alunos_inscritos = atoi(V[7]);

			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
			free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);
}

void menu_exames() {
	STRING* V;
	printf("Bem-vindo ao menu consulta dos exames\n");
	EXAMES *exames_bv = malloc(50 * sizeof(EXAMES));
	import_txt_exames(exames_bv, V);

}