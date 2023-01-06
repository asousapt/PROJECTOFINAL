#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
#include<ctype.h>
#include "functions.h"

#define MAX_CAR 300
#define STRING char *
#define N_CAMPOS_MAX 100
#define MAX_LINHA_FICHEIRO 300
#define MAX_EXAMES_FILE 100
#define MAX_UNIDADES_CURRICULARES 100

char *trim(char *str)
{
    char *end;

    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    end[1] = '\0';

    return str;
}

DATA* data_actual(DATA* DataActual) {
	time_t rawtime;
   	 struct tm *data;

 	time(&rawtime);
   	data = gmtime(&rawtime );

	DataActual->ano = data->tm_year+1900; 
	DataActual->mes = data->tm_mon+1;
	DataActual->dia = data->tm_mday; 
	
	return DataActual;
}

DATA* coloca_data_em_struct(char* datastr, DATA* data_exame) {
	int posicao = 1; 
	char* token = strtok(datastr, "/");
   	while( token != NULL ) {
		switch (posicao)
		{
		case 1:
			data_exame->dia = atoi(token);
			break;
		case 2:
			data_exame->mes = atoi(token);
			break;
		case 3:
			data_exame->ano = atoi(token);
			break;
		}
      token = strtok(NULL, "/");
	  posicao++; 
   }
   return data_exame;
}

int exame_ja_realizado(DATA* data_actual, DATA* data_exame) { 
	// Se o ano do exame for maior que o ano do dia de hoje nao foi realizado
	if (data_exame->ano > data_actual->ano) {
		return 0;
	}
	// Se o ano do exame for menor que o ano do dia de hoje ja foi realizado
	if (data_exame->ano < data_actual->ano) {
		return 1;
	}
	// Vamos comparar 2 datas do mesmo ano  
	if (data_exame->ano == data_actual->ano) {
		if (data_exame->mes > data_actual->mes) {
			return 0;
		}
		if (data_exame->mes < data_actual->mes) {
			return 1;
		}
		if (data_exame->mes == data_actual->mes) {
			if (data_exame->dia >= data_actual->dia) {
				return 0;
			} 
			else {
				return 1;
			}
		}
	}	
}

int get_ano_uc(UNIDADECURRICULAR* uc, char* unidade_curricular, char* curso) { 
	int i = 0; 
	for ( i = 0; i < MAX_UNIDADES_CURRICULARES; i++)
	{
		if ((uc[i].ocupado == 1)) {

			if ((strcmp(trim(uc[i].descricao), trim(unidade_curricular)) == 0) && (strcmp(trim(uc[i].curso), trim(curso)) == 0)) {
				return uc[i].ano;
			}
		}
	}
	return 0;
}

//passa para o vetor a informacao dos exames
void import_txt_exames(EXAMES* exames_bv, STRING* V, UNIDADECURRICULAR* uc) {

	DATA* hoje = (DATA*)malloc(sizeof(DATA));
	hoje = data_actual(hoje);

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
			strcpy(exames_bv[i].unidade_curricular,V[1]);

			//vamos buscar o ano 
			exames_bv[i].ano =  get_ano_uc(uc,trim(V[1]), trim(V[2]));
			
			exames_bv[i].curso = (char*)malloc(sizeof(char) * (strlen(V[2]) + 1));
			strcpy(exames_bv[i].curso, V[2]);

			exames_bv[i].epoca = (char*)malloc(sizeof(char) * (strlen(V[3]) + 1));
			strcpy(exames_bv[i].epoca, V[3]);

			exames_bv[i].data = (char*)malloc(sizeof(char) * (strlen(V[4]) + 1));
			strcpy(exames_bv[i].data, V[4]);

			//aloca espaco em memoria para a data do exame
			DATA* DataExame = (DATA*)malloc(sizeof(DATA));
			DataExame = coloca_data_em_struct(V[4], DataExame);
			
			exames_bv[i].hora = (char*)malloc(sizeof(char) * (strlen(V[5]) + 1));
			strcpy(exames_bv[i].hora, V[5]);	

			exames_bv[i].duracao = atoi(V[6]);

			exames_bv[i].sala = (char*)malloc(sizeof(char) * (strlen(V[7]) + 1));
			strcpy(exames_bv[i].sala, V[7]);

			exames_bv[i].alunos_inscritos = atoi(V[8]);
			
			//vamos colocar na estrutura se o exame já foi realizado ou nao para que na funcao de  apagar seja mais facil de gerir
            exames_bv[i].realizado = exame_ja_realizado(hoje, DataExame);

			exames_bv[i].ocupado = 1;
			
			free(DataExame);

			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
			free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);
	free(hoje);
}

void import_txt_inscricoes_exames(INSCRICOESEXAMES* inscricoes_exames, STRING* V){
int i = 0, k, n_campos_lidos; 

	//Abre o ficheiro
	FILE* f = fopen("inscricoes_exames.txt", "r");
	if (f == NULL) {
		printf("Erro ao abrir ficheiro inscricoes_exames.txt\n");
		exit(1);
	}
	
	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao			

			inscricoes_exames[i].codigo = atoi(V[0]);

			inscricoes_exames[i].unidade_curricular = (char*)malloc(sizeof(char) * (strlen(V[1]) + 1));
			strcpy(inscricoes_exames[i].unidade_curricular, V[1]);
			
			inscricoes_exames[i].numero_aluno = atoi(V[2]);

			inscricoes_exames[i].ano_matricula = atoi(V[3]);

			inscricoes_exames[i].epoca = (char*)malloc(sizeof(char) * (strlen(V[4]) + 4));
			strcpy(inscricoes_exames[i].epoca, V[4]);
			
			inscricoes_exames[i].ocupado = 1;

			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
			free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);
}

// funcao que cria novos exames 
void criar_Exame(EXAMES* exames_bv, ALUNOS* aluno, UNIDADECURRICULAR* uc, SALAS* salas) {
	//nesta funcao vamos criar um novo exame

}

//funcao que valida se o exame que introduziu pode ser apagado 
int valida_codigo_exame_apagar(EXAMES* exames_bv, int codigo_exame) { 
	int i = 0; 
	for ( i = 0; i < MAX_EXAMES_FILE; i++)
	{
		if ((exames_bv[i].ocupado == 1) && (exames_bv[i].realizado == 1)) {
			if (exames_bv[i].codigo == codigo_exame) {
				return i;
			}
		}
	}
	return -1;
}



void apagar_exame(EXAMES * exames_bv) {
	int codigoexame = 0;
	int posicao_apagar = -1;
	do
	{	
		listar_exames(exames_bv, 1); 
		printf("Qual o codigo do exame a apagar\n");
		scanf("%d", &codigoexame);
		posicao_apagar = valida_codigo_exame_apagar(exames_bv, codigoexame);
		if (posicao_apagar == -1) {
			printf("O exame que introduziu nao se encontra na lista\n");
			codigoexame	= 0;
		}
	} while (codigoexame == 0);

	//apaga o exame da lista
	
	exames_bv[posicao_apagar].ocupado = 0;
	exames_bv[posicao_apagar].realizado = 0;
	exames_bv[posicao_apagar].codigo = 0;
	exames_bv[posicao_apagar].curso = ""; 
	exames_bv[posicao_apagar].epoca = "";
	exames_bv[posicao_apagar].data = "";
	exames_bv[posicao_apagar].hora = "";
	exames_bv[posicao_apagar].duracao = 0; 
	exames_bv[posicao_apagar].unidade_curricular = "";
	exames_bv[posicao_apagar].sala = "";
	exames_bv[posicao_apagar].alunos_inscritos = 0;
	printf("Exame eliminado com sucesso!\n");
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
				trim(exames_bv[i].data),
				trim(exames_bv[i].hora),
				exames_bv[i].duracao,
				exames_bv[i].sala,
				exames_bv[i].alunos_inscritos
			);
		}
	}
	fclose(f);
}

void listar_exames(EXAMES* exames_bv, int jarealizados){ 
	
	int i = 0; 
	printf("\n%s %s %s %s %s %s %s %s\n", "Cod", "UC", "Curso", "Epoca", "Data", "Hora", "Sala", "Inscritos" );
	for ( i = 0; i < MAX_EXAMES_FILE; i++)
	{
		if (jarealizados == 0) {
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
		else {
			if ((exames_bv[i].ocupado == 1) && (exames_bv[i].realizado == 1)) {
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
	}
	printf("\n");
}

void menu_exames(EXAMES* exames_bv, INSCRICOESEXAMES* inscricoes_exames, ALUNOS* alunos, SALAS* salas) {
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
           listar_exames(exames_bv, 0);
            break;
		case 2: // Adicionar novo exame 
			break;
		case 3: // editar Exame 
			break;
		case 4: //Apagar exame 
			apagar_exame(exames_bv);
			break;
        case 0:
            opcaoExame = 0;
            break;
        }
    }
	
	

}
