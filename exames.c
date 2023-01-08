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

int valida_epoca(EPOCAS* epocas, int opcao) {
	int i = 0; 
	
	for ( i = 0; i < MAX_EPOCAS; i++)
	{
		if ((epocas[i].ocupado == 1) && (epocas[i].codigo == opcao)) {
			return i;
		} 
	}
	
	return -1; 
}
int valida_data_dentro_epoca(DATA* datainsrida, DATA* datainicio, DATA* datafim) {
	if (datainsrida->ano == datainicio->ano || datainsrida->ano == datafim->ano) {
		if (datainsrida->mes == datainicio->mes || datainsrida->mes == datainicio->mes) {
			if (datainsrida->dia >= datainicio->dia && datainsrida->dia <= datafim->dia) {
				return 1;
			}
		}
	}
	return 0;
}

//valida se e fereiado 

int e_feriado(DATA* datainserida, FERIADOS* feriados_datas) {
	int i = 0; 
	for ( i = 0; i <  MAX_FERIADOS ; i++)
	{
		if (feriados_datas[i].dia > 0 ) {
			DATA* dia_feriado = (DATA*)malloc(sizeof(DATA));
			dia_feriado->ano = datainserida->ano; 
			dia_feriado->mes = feriados_datas[i].mes; 
			dia_feriado->dia = feriados_datas[i].dia;

			//vamos comparar as datas 
			if (datainserida->ano == dia_feriado->ano && datainserida->mes == dia_feriado->mes && datainserida->dia == dia_feriado->dia) {
				return 1;
			}

		free(dia_feriado);
		}
	}
	return 0;
}

// funcao valida se existem exames marcados com 3 dias de intervalo
int numero_dias_entre_exames(EXAMES* exames_bv, DATA* datainserida, char* curso, int ano) {
	int i = 0; 
	for ( i = 0; i < MAX_EXAMES_FILE; i++)
	{
		if (exames_bv[i].ocupado == 1 && exames_bv[i].realizado == 0) {
			struct tm tm1 = { 0 };
    		struct tm tm2 = { 0 };
			DATA* data_exame = (DATA*)malloc(sizeof(DATA));
			coloca_data_em_struct(exames_bv[i].data, data_exame);

			 time_t start_standard, end_standard;
			struct tm start_date = {0};
			struct tm end_date = {0};
			double diff;

			start_date.tm_year = datainserida->ano;
			start_date.tm_mon = datainserida->mes;
			start_date.tm_mday = datainserida->dia;
			start_date.tm_hour = 10;
			start_date.tm_min = 00;
			start_date.tm_sec = 00;

			end_date.tm_mday = data_exame->dia;
			end_date.tm_mon = data_exame->mes;
			end_date.tm_year = data_exame->ano;
			end_date.tm_hour = 10;
			end_date.tm_min = 00;
			end_date.tm_sec = 00;

			/* first with standard time */
			start_date.tm_isdst = 0;
			end_date.tm_isdst = 0;
			start_standard = mktime(&start_date);
			end_standard = mktime(&end_date);
			diff = difftime(start_standard, end_standard);

			if (diff > -3 && diff < 3) {
				return 0;
			}
			free(data_exame);
		}
	}
	return 1;
}

DATA* validacao_data(DATA* datainserida, DATA* datainicio, DATA* datafim, FERIADOS* feriado, EXAMES* exames_bv, char* curso_escolhido, int ano_curricular) {
	int ano, mes, dia = 0;	
	int data_valida = 1;
	DATA* hoje = (DATA*)malloc(sizeof(DATA));
	do
	{
		
		hoje = data_actual(hoje);
		printf("Qual a data pretendida? O formato e dd mm aaaa\n");
		ano, mes, dia = 0;
		scanf("%d %d %d", &dia, &mes, &ano);
		if (ano < hoje->ano) {
			data_valida = 0;
		} else {
			if (mes < 1 || mes > 12) {
				data_valida = 0;
			} else {
				if (dia < 1 || dia > 31) {
					data_valida = 0;
				}
				else {
					// vamos verificar se a data esta dentro da epoca escolhida 
					datainserida->ano = ano; 
					datainserida->mes = mes; 
					datainserida->dia = dia;
					
					int dentro_datas =valida_data_dentro_epoca(datainserida,datainicio, datafim);
					if (dentro_datas == 0 ){
						data_valida = 0;
						printf("A data inserida esta fora do intervalo de dados da epoca\n"); 
					} else {
						//valida se e feriado
						int data_de_feriado = e_feriado( datainserida, feriado); 
						if (data_de_feriado == 1) {
							printf("A data introduzida e um feriado\n");
							data_valida = 0;
						}
						else {
							// vamos validar se e fim de semana 
							int weekday  = (datainserida->dia += datainserida->mes < 3 ? datainserida->ano-- : datainserida->ano - 2, 23*datainserida->mes/9 + datainserida->dia + 4 + datainserida->ano/4- datainserida->ano/100 + datainserida->ano/400)%7; 
							if (weekday == 0 || weekday == 6) {
								printf("Nao e permitido marcar exames ao fim de semana\n");
								data_valida = 0;
							} 
							else { 
								//vamos verificar se existe algum exame do mesmo ano curricular ate 3 dias antes ou depois
								datainserida->ano = ano; 
								datainserida->mes = mes; 
								datainserida->dia = dia;
								int valida_dias = 0; 
								valida_dias = numero_dias_entre_exames(exames_bv, datainserida, curso_escolhido, ano_curricular);

								if (valida_dias == 0) {
									printf("Tem um exame marcado com menos de 3 dias de intervalo.\n");
									data_valida = 0;
								}
								else {
									data_valida = 1;
									datainserida->ano = ano; 
									datainserida->mes = mes; 
									datainserida->dia = dia;
								}

							}
						}
					}					
				}
			}
		}
		
	} while (data_valida == 0);
	
	free(hoje);
	return datainserida;
}

int get_next_exameID(EXAMES* exames_bv) {
	int i = 0; 
	int max_codigo = 0;
	for ( i = 0; i < MAX_EXAMES_FILE; i++)
	{
		if (exames_bv[i].ocupado == 1) {
			if (exames_bv[i].codigo > max_codigo) {
				max_codigo = exames_bv[i].codigo;
			}
		}
	}
	return max_codigo + 1;
}

int get_next_exames_posicao(EXAMES* exames_bv) {
	int i = 0; 
	for ( i = 0; i < MAX_EXAMES_FILE; i++)
	{
		if (exames_bv[i].ocupado == 0) {
			return i; 
		}
	}
}

void insere_exame(EXAMES* exames_bv, int exameID, char* curso, char* epoca, char* data_Exame, char* horario, int duracao_exame, char* unidade_curricular, int nova_posicao) {
	exames_bv[nova_posicao].ocupado = 1;
	exames_bv[nova_posicao].realizado = 0;
	exames_bv[nova_posicao].codigo = exameID;
	exames_bv[nova_posicao].curso = curso; 
	exames_bv[nova_posicao].epoca = epoca;
	exames_bv[nova_posicao].data = data_Exame;
	exames_bv[nova_posicao].hora = horario;
	exames_bv[nova_posicao].duracao = duracao_exame; 
	exames_bv[nova_posicao].unidade_curricular = unidade_curricular;
	exames_bv[nova_posicao].sala = "";
	exames_bv[nova_posicao].alunos_inscritos = 0;
} 

// funcao que cria novos exames 
void criar_Exame(EXAMES* exames_bv, ALUNOS* aluno, UNIDADECURRICULAR* uc, SALAS* salas, EPOCAS* epocas, CURSO* cursos, FERIADOS* feriados_datas) {
	int opcaoepoca = -1;
	int duracao_exame = 0; 
	int opcaoUC = -1;
	int posicaoCurso = 0;
	int semestre = 0;
	char* unidade_curricular_escolhida;
	char* curso;
	char* epoca = (char*)malloc(sizeof(char)*10);
	unidade_curricular_escolhida=(char*)malloc(sizeof(char)*50);
	curso = (char*)malloc(sizeof(char)*10);
	DATA* data_inicio_epoca = (DATA*)malloc(sizeof(DATA)); 
	DATA* data_fim_epoca = (DATA*)malloc(sizeof(DATA)); 

	//nesta funcao vamos criar um novo exame
	do
	{
		printf("\n*** SELECAO DE EPOCA ***\n");
		lista_epocas(epocas);
		printf("Indique o codigo da epoca\n"); 
		opcaoepoca = 0;
		scanf("%i", &opcaoepoca);
		if ( valida_epoca(epocas, opcaoepoca) == -1) {
			opcaoepoca = -1;
		} else  {
			opcaoepoca = valida_epoca(epocas, opcaoepoca);
		}
	} while (opcaoepoca == -1);
	
	//coloca as datas de inicio e fim da epoca numa struct
	coloca_data_em_struct(epocas[opcaoepoca].dataInicio, data_inicio_epoca);
	coloca_data_em_struct(epocas[opcaoepoca].dataFim, data_fim_epoca);
	semestre = epocas[opcaoepoca].semestre;
	epoca = epocas[opcaoepoca].epoca;

	printf("\nSeleccionou a epoca %s que vai de %s ate %s\n", epoca,epocas[opcaoepoca].dataInicio, epocas[opcaoepoca].dataFim);
	// if(strcmp(epoca, "Especial") == 0) {
	// 	printf("es");
	// } 
	// else {
		printf("Qual o curso para o qual quer marcar exame?\n" ); 
		
		do {
		listar_cursos(cursos);
		printf("Indique o curso da lista acima\n");
		scanf("%d", &posicaoCurso);
		} while (valida_curso_escolhido( cursos, posicaoCurso) == 0);
		
		curso = cursos[posicaoCurso].codcurso;
		
		// Vamos escolher a UC
		do
		{
			listar_UC_curso_semestre(uc, curso, semestre);
			printf("\nIndiqu o codigo da unidade curricular\n");
			opcaoUC = -1;
			scanf("%d", &opcaoUC);
		} while (valida_UC_curso_semestre( uc,curso,semestre, opcaoUC) == -1);
		
		int posicaoUC = valida_UC_curso_semestre( uc,curso,semestre, opcaoUC);
	
		unidade_curricular_escolhida = uc[posicaoUC].descricao;
		printf("\nEscolheu a unidade curricular de %s\n" , unidade_curricular_escolhida); 
		
		DATA* datainserida = (DATA*)malloc(sizeof(DATA));
		//vamos pedir uma data ao utilizador e validamos se é valida em termos de estrutura 
		int ano_curricular = uc[posicaoUC].ano;
		datainserida = validacao_data(datainserida, data_inicio_epoca, data_fim_epoca, feriados_datas, exames_bv, curso, ano_curricular);

		int horas, minutos = 0;
		do
		{
			printf("Qual a hora de inicio do exame?\n");
			 horas, minutos = 0;
			scanf("%d %d", &horas, &minutos);
			if (horas < 0 || horas > 23) {
				printf("As horas apenas podem ser entre as 0 e as 23\n");
				horas = 0; 
			}
			if (minutos < 0 || minutos > 59) {
				printf("Os minutos vao de 0 a 59\n");
				horas = 0; 
			}
		} while (horas == 0);
		

		//vamos pedir a duracao do exame ao utilizador
		do
		{
			printf("Qual a duracao, em minutos, do exame?\n");
			duracao_exame = 0;
			scanf("%d", &duracao_exame);
		} while (duracao_exame == 0);

	// vamos buscar o proximo espaco livre no array para inserir os dados 
	int exameID = get_next_exameID(exames_bv);
	int nova_posicao = get_next_exames_posicao(exames_bv); 

	char* horario = (char*)malloc(sizeof(char) * 100);
	
	char* data_Exame = (char*)malloc(sizeof(char) * 100);	

	struct tm timeinfo = { 0};
	timeinfo.tm_year = datainserida->ano; 
	timeinfo.tm_mon = datainserida->mes; 
	timeinfo.tm_mday = datainserida->dia;
	timeinfo.tm_hour = horas; 
	timeinfo.tm_min = minutos; 

	//obtemos as datas em formato string 
	time_t rawtime = mktime(&timeinfo); 
	strftime(data_Exame,12, "%d/%m/%Y", localtime(&rawtime));
	strftime(horario,7, "%H:%M", localtime(&rawtime));

	
	insere_exame( exames_bv,  exameID,  curso,  epoca,  data_Exame,  horario, duracao_exame,  unidade_curricular_escolhida,  nova_posicao);
	printf("Exame inserido com sucesso em memoria!\n");



	free(unidade_curricular_escolhida);
	free(data_inicio_epoca);
	free(data_fim_epoca);
	free(datainserida);
	free(data_Exame); 
	free(horario);
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
// funcao responsavel por apagar um exame da estrutura
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

void menu_exames(EXAMES* exames_bv, INSCRICOESEXAMES* inscricoes_exames, ALUNOS* alunos, SALAS* salas, EPOCAS* epocas, UNIDADECURRICULAR* uc, CURSO* cursos, FERIADOS* feriados_datas) {
    int opcaoExame = -1; 
    while(opcaoExame != 0) {
        printf("Bem-vindo ao menu de Exames\n");
        printf("1. Listar Exames\n");
		printf("2. Criar Exames\n");
		printf("3. Editar Exames\n");
		printf("4. Apagar Exames\n");
        printf("Escolha uma opcao\n"); 
        printf("Opcao:"); 
        scanf("%d", &opcaoExame); 
        switch (opcaoExame)
        {
        case 1: //Listar exames
           listar_exames(exames_bv, 0);
            break;
		case 2: // Adicionar novo exame
			criar_Exame(exames_bv, alunos, uc,  salas,  epocas, cursos, feriados_datas);
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
