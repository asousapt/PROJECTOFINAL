#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define MAX_ALUNOS 3000
#define MAX_INSCRICOES 3000
#define MAX_REGIMES 5


void import_txt_inscricoes_exames(INSCRICOESEXAMES* inscricoes_exames, STRING* V) { //, STRING* V

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

			inscricoes_exames[i].epoca = (char*)malloc(sizeof(char) * (strlen(V[4]) + 1));
			strcpy(inscricoes_exames[i].epoca, V[4]);

      		inscricoes_exames[i].regime = (char*)malloc(sizeof(char) * (strlen(V[4]) + 1));
			strcpy(inscricoes_exames[i].regime, V[4]);

			inscricoes_exames[i].ocupado = 1;

			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
			free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);
}

//lista as inscricoes efetuadas
void listar_inscricoes(INSCRICOESEXAMES* inscricoes_exames, EXAMES* exames_bv){
	int exameID = 0;
	do
	{
		listar_exames( exames_bv, 0);
		scanf("%i", &exameID);
	} while (exameID == 0);

  int i;
	printf("%s %s %s %s %s %s\n", "ID", "Unidade Curricular","Numero Aluno", "Ano Matricula", "Epoca", "Regime\n");
	for (i = 0; i < MAX_INSCRICOES; i++)
	{
		if (inscricoes_exames[i].ocupado == 1 && inscricoes_exames[i].codigo == exameID) {
			printf("%d %s %d %d %s %s\n",inscricoes_exames[i].codigo, inscricoes_exames[i].unidade_curricular, inscricoes_exames[i].numero_aluno, 
      inscricoes_exames[i].ano_matricula, inscricoes_exames[i].epoca, inscricoes_exames[i].regime);
		}
	}
}

int valida_aluno_inscrito(INSCRICOESEXAMES* inscricoes_exames, int opcaoAluno) {
	int i = 0;
	for (i = 0; i < MAX_INSCRICOES; i++)
	{
		if (inscricoes_exames[i].ocupado == 1) {

			if (inscricoes_exames[i].numero_aluno == opcaoAluno) {

				return 1;
			}
		}
	}
	return 0;
}

//lista as inscricoes por aluno
void lista_inscricoes_aluno(INSCRICOESEXAMES* inscricoes_exames){
  
 int i;
 int opcaoAluno = 0;

 printf("Insira o numero do aluno: ");
 scanf("%d", &opcaoAluno);

 if(valida_aluno_inscrito(inscricoes_exames, opcaoAluno)==1){
	printf("%s %s %s %s %s %s\n", "ID", "Unidade Curricular","Numero Aluno", "Ano Matricula", "Epoca", "Regime\n");
	for (i = 0; i < MAX_INSCRICOES; i++)
	{
		if (inscricoes_exames[i].numero_aluno == opcaoAluno) {
			printf("%d %s %d %d %s %s\n",inscricoes_exames[i].codigo, inscricoes_exames[i].unidade_curricular, inscricoes_exames[i].numero_aluno, 
      inscricoes_exames[i].ano_matricula, inscricoes_exames[i].epoca, inscricoes_exames[i].regime);
		}
	}
  }
}

int valida_uc_escolhida(EXAMES* exames, int opcao_uc) {
	int i = 0; 
	
	for ( i = 0; i < MAX_EXAMES_FILE; i++)
	{
		if (exames[i].ocupado == 1 && i == opcao_uc) {
			return 1;
		}
	}
	
	return 0;
}

//valida 3 ano e regimes
int valida_epoca_especial(int ano_matricula, int opcaoREgime, REGIMES* regimes){
    int i;
	for ( i = 0; i < MAX_REGIMES; i++)
	{
		if (regimes[i].ocupado == 1) {
			if (strcmp(regimes[i].regime, "Normal") > 0 || strcmp(regimes[i].regime, "Erasmus") > 0 || ano_matricula == 3) {
				return 1;
			}
		}
	}
	
    return 0;
}

int get_espaco_vazio(INSCRICOESEXAMES* inscricoes_exames) { 
	int i= 0; 
	for ( i = 0; i < MAX_INSCRICOES; i++)
	{
		if (inscricoes_exames[i].ocupado == 0) {
			return i;
		}
	}
	
}

char* regime_aluno (ALUNOS* alunos, int numero ) {
	int i =0; 
	for ( i = 0; i < MAX_ALUNOS; i++)
	{
		if (alunos[i].numero == numero) {
			return alunos[i].regime;
		} 
	}
	
}

void inscrever_aluno(INSCRICOESEXAMES* inscricoes_exames, EXAMES* exames, ALUNOS* alunos, REGIMES* regimes){
  int opcao_uc;
  int opcaoAluno = 0;
  int ano_matricula = 0;
  char* epoca;
  int opcaoRegime;
  int ocupado;
  int exameID;
  char* regime;

  do{
    printf("Qual o numero do aluno");
    scanf("%d", &opcaoAluno);
  } while (valida_aluno_existe(alunos, opcaoAluno) == 0);

	regime = regime_aluno(alunos, opcaoAluno);
  do {
    printf("Qual o ano de matricula do aluno");
    scanf("%d", &ano_matricula);
  } while(valida_ano_matricula(ano_matricula)==1);

  do{
    printf("Qual o estatuto do aluno");
    scanf("%d", &opcaoRegime);
  }while (valida_regime_escolhido(regimes, opcaoRegime)==1);
   

  if (valida_epoca_especial(ano_matricula, opcaoRegime, regimes)){
    listar_exames(exames, 0);
    printf("Qual a Unidade Curricular para a qual pretende inscrever o aluno");
    scanf("%d", &opcao_uc);
  }

  do{
    listar_exames(exames, 0);
    printf("Qual a Unidade Curricular para a qual pretende inscrever o aluno");
    scanf("%d", &opcao_uc);
  }while (valida_uc_escolhida(exames, opcao_uc) == 1);

	int posicao = get_espaco_vazio(inscricoes_exames);

	inscricoes_exames[posicao].codigo = opcao_uc;
	inscricoes_exames[posicao].epoca = epoca;
	inscricoes_exames[posicao].ano_matricula = ano_matricula;
	inscricoes_exames[posicao].regime = regime;
	inscricoes_exames[posicao].numero_aluno = opcaoAluno;
	inscricoes_exames[posicao].ocupado = 1;
	printf("Aluno inscrito com sucesso!\n");
}

void export_inscricoes(INSCRICOESEXAMES* inscricoes_exames) {
	int i, k = 0;
	FILE *f;
	
	
	f = fopen("inscricoes_exames.txt","w");
	if (f == NULL){
		printf("Erro ao abrir o ficheiro -> inscricoes_exames.txt");
		exit(1);
	}
	
	for ( i = 0; i < MAX_INSCRICOES; i++)
	{
		if (inscricoes_exames[i].ocupado == 1) {
			fprintf(f, "%d|%s|%d|%d|%s\n", inscricoes_exames[i].codigo,
			inscricoes_exames[i].unidade_curricular, 
			inscricoes_exames[i].numero_aluno, 
			inscricoes_exames[i].ano_matricula,
			inscricoes_exames[i].epoca);
	}}
	
	fclose(f);
}

void menu_inscricao_exames(INSCRICOESEXAMES* inscricoes_exames, EXAMES* exames, ALUNOS* alunos, REGIMES* regimes){
  STRING* V;
	int opcao = -1;

	while(opcao != 0){
		printf("\n");
		printf("Bem-vindo ao menu de inscrição de exames!\n");
		printf("Escolha uma das opções:\n");
		printf("1 - Inscrever aluno\n");
		printf("2 - Consultar Inscrições\n");
		printf("3 - Lista por aluno \n");
		printf("4 - Apagar \n");
		printf("0 - Sair\n");
		printf("Introduza a Opcao: ");
		scanf("%d", &opcao);
		
		switch (opcao) {
			case 1: //inscreve um novo aluno
				inscrever_aluno(inscricoes_exames, exames, alunos, regimes);
				break;
			case 2: //lista as inscricoes
				listar_inscricoes(inscricoes_exames, exames);
				break;
			case 3: // 
			 	lista_inscricoes_aluno(inscricoes_exames);
				break; 
			case 4: //
				
				break;
		}
	}
}
