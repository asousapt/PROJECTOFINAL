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
	char* descricao;
	//char* curso;
	char* docente;
	int ano;
	int semestre;
}UNIDADECURRICULAR;

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

//passa para o vetor a informacao das unidades curriculares
void import_txt_uc(UNIDADECURRICULAR* uc, STRING* V) { //, STRING* V

	int i = 0, k, n_campos_lidos; 

	//Abre o ficheiro
	FILE* f = fopen("unidades_curriculares_bv.txt", "r");
	if (f == NULL) {
		printf("Erro ao abrir ficheiro unidades_curriculares_bv.txt\n");
		exit(1);
	}
	//printf("%d", n_campos_lidos);
	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao			

			uc[i].codigo = atoi(V[0]);

			uc[i].descricao = (char*)malloc(sizeof(char) * (strlen(V[1]) + 1));
			strcpy(uc[i].descricao, V[1]);
			//uc[i].descricao = temp_descricao;

			uc[i].docente = (char*)malloc(sizeof(char) * (strlen(V[2]) + 5));
			strcpy(uc[i].docente, V[2]);
			//uc[i].docente = temp_docente;

			//char* temp_curso = (char*)malloc(sizeof(char) * (strlen(V[2]) + 1));
			//strcpy(temp_curso, V[2]);
			//uc[i].curso = temp_curso;

			uc[i].ano = atoi(V[3]);

			uc[i].semestre = atoi(V[4]);


			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
			free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);
}

void criar_uc() {
	UNIDADECURRICULAR uc;
	fflush(stdin);
	printf("Nome da UC:\n");
	scanf("%s", &uc.descricao); //Registrando nome do aluno
	printf("Nome do docente responsavel:\n");
	scanf("%s", &uc.docente); //Registrando numerdo do aluno
	printf("Qual o ano (1, 2, 3)?\n");
	scanf("%d", &uc.ano); //Registrando curso do aluno
	printf("Qual o semestre (1, 2)?\n");
	scanf("%d", &uc.semestre); //Registrando matricula do aluno

	//Retornando sucesso ao usuario
	printf("UC %s criada com sucesso!", uc.descricao);
	//escrevendo aluno no arquivo
	//fprintf(arquivo_aluno, "%s\t", aluno.nome); //escrevendo nome do aluno
	//fprintf(arquivo_aluno, "%s\t", aluno.regime); //escrevendo regime do aluno
	//fprintf(arquivo_aluno, "%d\t", aluno.ano_matricula);//escrevendo ano de matricula do aluno
	//fprintf(arquivo_aluno, "%d\t", aluno.numero); //escrevendo numero do aluno
	//fprintf(arquivo_aluno, "%s\t\n", aluno.curso); //escrevendo curso do aluno
	//fclose(arquivo_aluno);//fechando arquivo
}


void menu_uc() {
	STRING* V{};
	int opcao;
	UNIDADECURRICULAR* uc = (UNIDADECURRICULAR*)malloc(50 * sizeof(UNIDADECURRICULAR));

	printf("Bem-vindo ao menu das unidades curriculares!\n");
	printf("Escolha uma das opcoes:\n");
	printf("1 - Consultar Unidades Curriculares\n");
	printf("2 - Adicionar Unidade Curricular\n");
	printf("0 - Sair\n");
	printf("Opcao: ");
	scanf("%d", &opcao);

	switch (opcao) {
	case 1: 
		import_txt_uc(uc, V);
		int i;

		for (i = 0; i < 50; i++)
		{
			printf("%s | %s | %d | %d\n", uc[i].descricao, uc[i].docente, uc[i].ano, uc[i].semestre);
		}

		break;
	case 2: criar_uc();
		break;
	case 0: exit;
	}
	//import_txt_uc(uc, V);
	

}
int main() {
	menu_uc();
	
	return 0;
}