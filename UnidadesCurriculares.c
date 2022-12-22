#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#define MAX_CAR 300
#define STRING char *
#define N_CAMPOS_MAX 100
#define MAX_LINHA_FICHEIRO 300


//definicao da estrutura de unidade curricular 
typedef struct 
{
    int codigo;
    char *descricao;
    char *curso; 
    int ano; 
    int semestre; 
    char *docente;
} UNIDADECURRICULAR;

//le uma linha do ficheiro f
//devolve uma string com os campos da linha lida
STRING *Read_Split_Line_File(FILE *f, int *n_campos_lidos){
	//separadores: carateres que fazem a separacao dos campos na linha
	char *separadores = "\t\n", s[MAX_LINHA_FICHEIRO];
	*n_campos_lidos = 0;
	if (!f) return NULL;
	if ( fgets(s , MAX_LINHA_FICHEIRO , f) != NULL){	// fgets le uma linha do ficheiro de texto para a string s
	
		// "partir" a linha lida, usando os separadores definidos
		STRING *Res = (STRING *)malloc(N_CAMPOS_MAX*sizeof(STRING));  // alocacao de um array com n_campos_max ponteiros para STRING
		char *pch = strtok (s, separadores);
		int cont = 0;
		while (pch != NULL){
			
			Res[cont] = (char *)malloc((strlen(pch)+1)*sizeof(char)); // aloca��o do espa�o necess�rio para guardar a string correspondente ao campo
			strcpy(Res[cont++], pch);
			pch = strtok (NULL, separadores);
		}
		*n_campos_lidos = cont;
		return Res;
	}
	return NULL;
}

//passa para o vetor a informacao das unidades curriculares
void import_txt_uc(UNIDADECURRICULAR *uc, STRING *V){

	int i=0,k,n_campos_lidos;
	
	//Abre o ficheiro
	FILE *f = fopen("unidades_curriculares.txt","r");
	if (f == NULL){
		printf("Erro ao abrir ficheiro unidades_curriculares.txt");
		exit(1);
	}
	
	do{
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if(V!=NULL){// caso consigamos ler alguma informacao

		printf("%s\n",V[4]);
			// uc[i].codigo=atoi(V[0]);
			
			// uc[i].descricao = malloc(sizeof(char)*(sizeof(V[1])));
			// strcpy(uc[i].descricao, V[1]);

			// uc[i].curso = malloc(sizeof(char)*(sizeof(V[2])));
			// strcpy(uc[i].curso, V[2]);

			// uc[i].ano=atoi(V[3]);

			// uc[i].semestre=atoi(V[4]);
			
			// uc[i].curso = malloc(sizeof(char)*(sizeof(V[2])));
			// strcpy(uc[i].docente, V[5]);

			for (k = 0; k <n_campos_lidos; k++)
				free (V[k]);
			free (V);
			i++;
		}
	}while(!feof(f));
	
	fclose(f);
}

void menu_uc() { 
    STRING *V;
    printf("Bem-vindo ao menu das unidades curriculares\n");
    UNIDADECURRICULAR *uc = malloc(50*sizeof(UNIDADECURRICULAR));
    import_txt_uc(uc, V);

	
	
}