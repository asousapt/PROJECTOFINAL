#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
#include<ctype.h>
#include"functions.h"
#include <math.h>
#include <limits.h>

#define MAX_CAR 300
#define STRING char *
#define N_CAMPOS_MAX 100
#define MAX_LINHA_FICHEIRO 300
#define MAX_EXAMES_FILE 100
#define MAX_UNIDADES_CURRICULARES 100
#define MAX_EPOCAS 10
#define MAX_FERIADOS 20 
#define MAX_EXAMES_SALAS 100
#define MAX_SALAS 100

int valida_Sala_tem_exame(EXAMESSALAS* exames_salas, int exameID, char* codigo){
	int i = 0; 
	for ( i = 0; i < MAX_EXAMES_SALAS; i++)
	{
		if (exames_salas[i].exameid == exameID && strcmp(exames_salas[i].sala, codigo) == 0 ) {
			return 0;
		}
	}
	return 1;
}

int nova_posicao_vazia(EXAMESSALAS* exames_salas) {
	int i = 0; 
	for ( i = 0; i < MAX_EXAMES_SALAS; i++)
	{
		if (exames_salas[i].exameid == 0 ) {
			return i;
		}
	}
}

void atribuir_salas(EXAMES* exames_bv, SALAS* salas, EXAMESSALAS* exames_salas) {
   int exameID, i = 0; 
   char* data_exame = (char * )malloc(sizeof(char) *12 );
   char* hora_exame = (char * )malloc(sizeof(char) *8 );
   char* sala_escolhida = (char * )malloc(sizeof(char) *5 );
	listar_exames( exames_bv, 0);
	do
	{
		printf("Qual o ID do exame que quer atribuir uma sala?\n");
		scanf("%i", &exameID);
	} while (exameID == 0);

	printf("Seleccione uma sala\n");

	do
	{
		listar_salas(salas);
		printf("Qual a sala pretendida?\n");
		scanf("%s", sala_escolhida);
	} while (valida_Sala_tem_exame( exames_salas,  exameID,  sala_escolhida) == 0);
	
 
	for ( i = 0; i < MAX_EXAMES_FILE; i++)
	{
		if (exames_bv[i].codigo == exameID) {
			data_exame = exames_bv[i].data; 
			hora_exame =  exames_bv[i].hora;
		}
	}
	
	int newID  = nova_posicao_vazia( exames_salas);

	exames_salas[newID].exameid = exameID;
	exames_salas[newID].sala = sala_escolhida;
	exames_salas[newID].data = data_exame;
	exames_salas[newID].hora = hora_exame;

	printf("Sala atribuida com sucesso\n");

	free(sala_escolhida);
	free(data_exame);
	free(hora_exame);
}

//IMporta as salas atribuidas aos exames
void import_txt_exames_salas(EXAMESSALAS* exames_salas, STRING* V) {
	DATA* hoje = (DATA*)malloc(sizeof(DATA));
	hoje = data_actual(hoje);

	int i = 0, k, n_campos_lidos;

	//Abre o ficheiro
	FILE* f = fopen("exames_salas.txt", "r");
	if (f == NULL) {
		printf("Erro ao abrir ficheiro exames_salas.txt\n");
		exit(1);
	}

	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao

			exames_salas[i].exameid = atoi(V[0]);
			
            exames_salas[i].sala = (char*)malloc(sizeof(char) * (strlen(V[1]) + 1));
			strcpy(exames_salas[i].sala,trim(V[1]));

			exames_salas[i].data = (char*)malloc(sizeof(char) * (strlen(V[2]) + 1));
			strcpy(exames_salas[i].data, V[2]);
            DATA* DataExame = (DATA*)malloc(sizeof(DATA));
			DataExame = coloca_data_em_struct(V[2], DataExame);
			
			exames_salas[i].hora = (char*)malloc(sizeof(char) * (strlen(V[3]) + 1));
			strcpy(exames_salas[i].hora, V[3]);	
			
			//vamos colocar na estrutura se o exame já foi realizado ou nao para que na funcao de  apagar seja mais facil de gerir
            exames_salas[i].realizado = exame_ja_realizado(hoje, DataExame);
			
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

void consulta_Salas_exame(EXAMES* exames_bv, EXAMESSALAS* exames_salas, SALAS* salas) {
	int exameID, i,k = 0; 
	listar_exames( exames_bv, 0);
	do
	{
		printf("Qual o ID do exame que quer consultar?\n");
		scanf("%i", &exameID);
	} while (exameID == 0);

	printf("Numero | Nome | Lotacao\n");
	for ( i = 0; i < MAX_EXAMES_SALAS; i++)
	{
		if (exames_salas[i].exameid == exameID) {
			for ( k = 0; k < MAX_SALAS; k++)
			{	
				if ((strcmp(salas[k].codigo, exames_salas[i].sala) == 0) && salas[k].ocupado == 1) {
					printf("%s %s %d\n", salas[k].codigo, salas[k].nome_sala, salas[k].lotacao);
				}
			}	
		}
	}
} 

void export_exames_salas(EXAMESSALAS* exames_salas){
	int i, k = 0;
	FILE *f;
	
	
	f = fopen("exames_salas.txt","w");
	if (f == NULL){
		printf("Erro ao abrir o ficheiro -> exames_salas.txt");
		exit(1);
	}
	
	for ( i = 0; i < MAX_EXAMES_SALAS; i++)
	{
		if (exames_salas[i].exameid != 0) {
			fprintf(f, "%d|%s|%s|%s\n", 
				exames_salas[i].exameid,
				exames_salas[i].sala,
				exames_salas[i].data, 
				exames_salas[i].hora
			);
		}
	}
	fclose(f);
}

